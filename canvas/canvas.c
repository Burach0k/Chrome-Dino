#include "SDL2/SDL.h"
#include "../dino/dino.h"
#include "../row/row.h"
#include <stdbool.h>

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

static void render(struct Canvas * canvas) {
    SDL_Renderer *renderer = SDL_CreateRenderer(canvas->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    struct timeval start, stop;
    SDL_Event event;
    int size = 3;

    gettimeofday(&start, NULL);

    struct Dino *dino = NULL;
    dino = malloc(sizeof(Dino));
    dino = new_Dino(size, 100, 110);

    struct Row *row = NULL;
    row = malloc(sizeof(Row));
    row = new_Row(800, 1);

    while(canvas->running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                canvas->running = false;
            }
        }

        gettimeofday(&stop, NULL);
        canvas->msecs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

        if (canvas->msecs > 1.0 / 60.0) {
            gettimeofday(&start, NULL);
            SDL_RenderClear(renderer);

            row->start(row, renderer);
            dino->start(dino, renderer);

            SDL_RenderPresent(renderer);
        }
    }

    free(dino);
    free(row);
    dino = NULL;
    row = NULL;
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
