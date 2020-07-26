#include <SDL2/SDL.h>
#include <stdbool.h>
#include <sys/time.h>
#include <ncurses.h>

#include "../dino/dino.h"
#include "../row/row.h"
#include "../barrierStrip/barrierStrip.h"

typedef struct Canvas{
    void (*render)(struct Canvas *);
    SDL_Window *window;
    bool running;
    double msecs;
} Canvas;

void drowPicture(SDL_Renderer *renderer, const int *picture, int x0, int y0, int h, int sizex, int sizey) {
    for (int i = 0; i < sizey; i++)
        for (int j = 0; j < sizex; j++)
            if(*(picture + i*sizex + j) == 1) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_Rect rect = { x0  + j*h, y0  + i*h, h, h };
                SDL_RenderFillRect(renderer, &rect);
            } else if (*(picture + i*sizex + j) == 2) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
                SDL_Rect rect = { x0  + j*h, y0  + i*h, h, h };
                SDL_RenderFillRect(renderer, &rect);
            }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

static bool checkIntersection(struct BarrierStrip* bs, struct Barrier * barriers, int x0, int count, struct Dino* dino) {
    for(int i = 0; i < count; i++) {
        int barrierPosition = x0 + (barriers + i)->x0;
        int dispersion = dino->width + dino->speed;

        if ((barrierPosition - dino->x0 < dispersion)) {
            int barrierWidth = (barriers + i)->width;
            int barrierHeight = (barriers + i)->height;

            for(int w = 0; w < barrierWidth; w++) {
                for(int h = 0; h < barrierHeight; h++) {
                    int cell = *((barriers + i)->picture + w + h * (barriers + i)->width);
                    bool pointRightOfDino = barrierPosition + w > dino->x0;
                    bool pointLeftOfDino = barrierPosition + cell < dino->x0 + dino->width;

                    if (cell != 0) {
                        if (pointRightOfDino && pointLeftOfDino) {
                            bool pointTopOfDino = bs->y0 - h >= dino->y0;
                            bool pointBottomOfDino = bs->y0 - h <= dino->y0 + dino->height;

                            if (pointTopOfDino && pointBottomOfDino) {
                                int x = (barrierPosition + w - dino->x0) / dino->pictureSize;
                                int y = ((barriers + i)->y0 + h - dino->y0) / dino->pictureSize;

                                if (x <= dino->width && y <= dino->height) {
                                    if (*(dino->picture + x + y * dino->height) == 1 ) {
                                        return true;
                                    }
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

static void render(struct Canvas * canvas) {
    SDL_Renderer *renderer = SDL_CreateRenderer(canvas->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    struct timeval start, stop;
    SDL_Event event;
    int size = 3;
    bool isCrossing = false;

    gettimeofday(&start, NULL);

    struct Dino *dino = NULL;
    dino = malloc(sizeof(Dino));
    dino = new_Dino(size, 100, 110);

    struct Row *row = NULL;
    row = malloc(sizeof(Row));
    row = new_Row(800, 1);

    struct BarrierStrip * barrierStrip = NULL;
    barrierStrip = malloc(sizeof(BarrierStrip));
    barrierStrip = new_BarrierStrip(800, 200, 175);

    row->rowStep = 3;
    barrierStrip->speed = 3;

    while(canvas->running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                canvas->running = false;
            }

            if(event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        dino->event = JUMP;
                        break;
                }
            }
        }

        if (!isCrossing) {
            gettimeofday(&stop, NULL);
            canvas->msecs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

            if (canvas->msecs > 1.0 / 60.0) {
                gettimeofday(&start, NULL);
                SDL_RenderClear(renderer);

                row->start(row, renderer);
                barrierStrip->start(barrierStrip, renderer, 200);
                dino->start(dino, renderer);

                if (barrierStrip->firstBarriersPosition < barrierStrip->width) {
                    isCrossing = checkIntersection(
                        barrierStrip,
                        barrierStrip->firstBarriers,
                        barrierStrip->firstBarriersPosition,
                        barrierStrip->counFirstBarriers,
                        dino);
                } else if (barrierStrip->secondBarriersPosition < barrierStrip->width) {
                    isCrossing = checkIntersection(
                        barrierStrip,
                        barrierStrip->secondBarriers,
                        barrierStrip->secondBarriersPosition,
                        barrierStrip->counSecondBarriers,
                        dino);
                }
                
                SDL_RenderPresent(renderer);
            }
        }
    }

    free(dino);
    free(row);
    free(barrierStrip);
    dino = NULL;
    row = NULL;
    barrierStrip = NULL;
    SDL_DestroyRenderer(renderer);
}

Canvas* new_Canvas(SDL_Window *window) {
    Canvas *canvas = NULL;
    canvas = malloc(sizeof(Canvas));

    canvas->running = true;
    canvas->msecs = 0;

    canvas->window = window;
    canvas->render = render;

    return canvas;
}
