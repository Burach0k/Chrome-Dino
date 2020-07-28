#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct Canvas{
    void (*render)(struct Canvas *);
    bool running;
    int width, height;
    double msecs;
    SDL_Window *window;
    SDL_Event event;
} Canvas;

void drowPicture(SDL_Renderer *renderer, const int *picture, int x0, int y0, int h, int sizex, int sizey);

Canvas* new_Canvas(SDL_Window *window);
