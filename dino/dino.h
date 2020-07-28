#include "SDL2/SDL.h"

typedef enum Event {
    RUN,
    JUMP
} Event;

typedef struct Dino {
    void (*start)(struct Dino *, SDL_Renderer *);
    void (*jump)(struct Dino *);
    int step;
    int pictureSize;
    int speed;
    int x0, y0;
    int height, width;
    int* picture;
    float jumpValue;
    Event event;
} Dino;

Dino* new_Dino(int pictureSize, int x0, int y0);