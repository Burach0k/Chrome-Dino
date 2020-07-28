#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>

#include "./canvas/canvas.h"

static const int width = 800;
static const int height = 600;

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Dino", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    srand(time(NULL));

    Canvas *canvas = new_Canvas(window);

    canvas->render(canvas);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
