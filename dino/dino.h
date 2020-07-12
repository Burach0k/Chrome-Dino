#include "SDL2/SDL.h"

typedef struct Dino {
    void (*start)(struct Dino *, SDL_Renderer *);
    int step;
    int pictureSize;
    int x0;
    int y0;
    int speed;
} Dino;

Dino* new_Dino(int pictureSize, int x0, int y0);