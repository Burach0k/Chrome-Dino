#include "SDL2/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <conio.h>

#include "./move/renderDino.h"
#include "./move/renderDino.c"

static const int width = 800;
static const int height = 600;

void drowPicture(SDL_Renderer *renderer, const int picture[][20], int x0, int y0, int h) {
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
            if(picture[i][j] == 1) {
                SDL_Rect rect = { x0 + j + j*h, y0 + i + i*h, h, h };
                SDL_RenderFillRect(renderer, &rect);
            }
}

void mainRender(SDL_Window *window) {
    bool running = true;
    SDL_Event event;

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int step = 0;
    struct timeval start, stop;
    double msecs = 0;
    gettimeofday(&start, NULL);

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
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

            if (step == 0) {
                drowPicture(renderer, stayDino, 100, 100, 2);
            } else if (step == 1) {
                drowPicture(renderer, runDino1, 100, 100, 2);
            } else {
                drowPicture(renderer, runDino2, 100, 100, 2);
                step = 0;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderPresent(renderer);
            step++;
        }
    }

    SDL_DestroyRenderer(renderer);
}



int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Dino", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
 
    mainRender(window);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
