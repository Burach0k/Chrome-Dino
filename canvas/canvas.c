#include "SDL2/SDL.h"
#include "../dino/dino.c"

typedef struct {
    void (*init)();
    void (*render)(SDL_Window *window);
} Canvas;

static void init() { }

static void render(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    struct timeval start, stop;
    bool running = true;
    double msecs = 0;
    SDL_Event event;

    gettimeofday(&start, NULL);

    Dino *dino = new_Dino();

    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }

        gettimeofday(&stop, NULL);
        msecs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

        if (msecs > 1.0 / 5.0) {
            gettimeofday(&start, NULL);
            SDL_RenderClear(renderer);

            dino->start(dino, renderer);

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderPresent(renderer);
        }
    }

    free(dino);
    SDL_DestroyRenderer(renderer);
}

Canvas new_Canvas() {
    Canvas c;

    c.init = init;
    c.render = render;

    return c;
}
