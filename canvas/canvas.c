#include "SDL2/SDL.h"
#include "../dino/dino.c"
#include "../row/row.c"

typedef struct Canvas{
    void (*render)(struct Canvas *);
    SDL_Window *window;
    bool running;
    double msecs;
} Canvas;

static void render(struct Canvas * canvas) {
    SDL_Renderer *renderer = SDL_CreateRenderer(canvas->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    struct timeval start, stop;
    SDL_Event event;

    gettimeofday(&start, NULL);

    struct Dino *dino = NULL;
    dino = malloc(sizeof(Dino));
    dino = new_Dino();

    struct Row *row = NULL;
    row = malloc(sizeof(Row));
    row = new_Row(800, 2);

    while(canvas->running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                canvas->running = false;
            }
        }

        gettimeofday(&stop, NULL);
        canvas->msecs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

        if (canvas->msecs > 1.0 / 5.0) {
            gettimeofday(&start, NULL);
            SDL_RenderClear(renderer);

            dino->start(dino, renderer);
            row->startt(row, renderer);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
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
