#include "SDL2/SDL.h"

typedef struct Canvas{
    void (*render)(struct Canvas *);
    SDL_Window *window;
    bool running;
    double msecs;
} Canvas;

void drowPicture(SDL_Renderer *renderer, const int *picture, int x0, int y0, int h, int sizex, int sizey);

Canvas* new_Canvas(SDL_Window *window);
