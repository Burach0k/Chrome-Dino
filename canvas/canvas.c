#include <SDL2/SDL.h>
#include <stdbool.h>
#include <sys/time.h>
#include <ncurses.h>

#include "../dino/dino.h"
#include "../row/row.h"
#include "../barrierStrip/barrierStrip.h"

typedef struct Canvas{
    void (*render)(struct Canvas *);
    bool running;
    int width, height;
    double msecs;
    SDL_Window *window;
    SDL_Event event;
} Canvas;

void drowPicture(SDL_Renderer *renderer, const int *picture, int x0, int y0, int h, int sizex, int sizey) {
    for (int i = 0; i < sizey; i++)
        for (int j = 0; j < sizex; j++) {
            SDL_Rect rect = { x0  + j*h, y0  + i*h, h, h };

            if(*(picture + i*sizex + j) == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(renderer, &rect);
            } else if (*(picture + i*sizex + j) == 2) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_RenderFillRect(renderer, &rect);
            }
        }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

static void eventListener(struct Canvas * this, struct Dino* dino) {
    while(SDL_PollEvent(&this->event)) {
        if(this->event.type == SDL_QUIT) this->running = false;

        if(this->event.type == SDL_KEYDOWN) {
            switch(this->event.key.keysym.sym) {
                case SDLK_UP:
                    dino->event = JUMP;
                    break;
            }
        }
    }
}

static bool checkIntersection(struct BarrierStrip* bs, struct Barrier * barriers, int x0, int count, struct Dino* dino) {
    for(int i = 0; i < count; i++) {
        int barrierPosition = x0 + (barriers + i)->x0;

        if (barrierPosition <= dino->x0 + dino->width && barrierPosition >= dino->x0) {
            int barrierWidth = (barriers + i)->width;
            int barrierHeight = (barriers + i)->height;

            for(int w = 0; w < barrierWidth; w++) {
                for(int h = 0; h < barrierHeight; h++) {
                    int cell = *((barriers + i)->picture + w + h * (barriers + i)->width);

                    if (cell != 0) {
                        bool pointTopOfDino = (barriers + i)->y0 + h >= dino->y0;
                        bool pointBottomOfDino = (barriers + i)->y0 + h <= dino->y0 + dino->height;

                        if (pointTopOfDino && pointBottomOfDino) {
                            int x = (barrierPosition + w * bs->size - dino->x0) / dino->pictureSize;
                            int y = ((barriers + i)->y0 + h* bs->size - dino->y0) / dino->pictureSize;

                            if (x <= (dino->width / dino->pictureSize) && y <= (dino->height / dino->pictureSize)) {
                                if (*(dino->picture + x + y * (dino->height / dino->pictureSize)) == 1 ) {
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

static void destroy(struct Dino *dino, struct Row *row, struct BarrierStrip * bs, SDL_Renderer *renderer) {
    free(dino);
    free(row);
    free(bs);
    SDL_DestroyRenderer(renderer);
}

static void render(struct Canvas * this) {
    struct timeval start, stop;
    bool isCrossing = false;
    SDL_Renderer *renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    BarrierStrip * barrierStrip = new_BarrierStrip(800, 200, 175);
    Dino *dino = new_Dino(3, 100, 110);
    Row *row = new_Row(800, 1);

    gettimeofday(&start, NULL);

    while(this->running) {
        eventListener(this, dino);

        if (!isCrossing) {
            gettimeofday(&stop, NULL);
            this->msecs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

            if (this->msecs > 1.0 / 60.0) {
                gettimeofday(&start, NULL);
                SDL_RenderClear(renderer);

                row->start(row, renderer);
                barrierStrip->start(barrierStrip, renderer, 200);
                dino->start(dino, renderer);

                if (barrierStrip->firstLine->x0 < barrierStrip->width) {
                    isCrossing = checkIntersection(
                        barrierStrip,
                        barrierStrip->firstLine->barriers,
                        barrierStrip->firstLine->x0,
                        barrierStrip->firstLine->coun,
                        dino);
                } else if (barrierStrip->secondLine->x0 < barrierStrip->width) {
                    isCrossing = checkIntersection(
                        barrierStrip,
                        barrierStrip->secondLine->barriers,
                        barrierStrip->secondLine->x0,
                        barrierStrip->secondLine->coun,
                        dino);
                }

                SDL_RenderPresent(renderer);
            }
        }
    }

    destroy(dino, row, barrierStrip, renderer);
}

Canvas* new_Canvas(SDL_Window *window, int width, int height) {
    Canvas *canvas = NULL;
    canvas = malloc(sizeof(Canvas));

    canvas->running = true;
    canvas->msecs = 0;
    canvas->window = window;
    canvas->render = render;
    canvas->width = width;
    canvas->height = height;

    return canvas;
}
