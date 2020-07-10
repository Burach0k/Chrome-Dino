#include "SDL2/SDL.h"

typedef struct Dino {
    void (*start)(struct Dino *, SDL_Renderer *);
    void (*init)(struct Dino *);
    int step;
    int size;
} Dino;

void drowPicture(SDL_Renderer *renderer, const int *picture, int x0, int y0, int h, int sizex, int sizey) {
    for (int i = 0; i < sizey; i++)
        for (int j = 0; j < sizex; j++)
            if(*(picture + i*sizex + j) == 1) {
                SDL_Rect rect = { x0  + j*h, y0  + i*h, h, h };
                SDL_RenderFillRect(renderer, &rect);
            }
}

static int step = 0;

static void start(struct Dino *dino, SDL_Renderer* renderer) {
    int *dinoMotion = *stayDino;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int speed = 3;
    if (dino->step < speed) {
        dinoMotion = *stayDino;
    } else if (dino->step < speed*2) {
        dinoMotion = *runDino1;
    } else if (dino->step < speed*3) {
        dinoMotion = *runDino2;
    } else {
        dino->step = 0;
    }

    drowPicture(renderer, dinoMotion, 100, 100, dino->size, 20, 20);
    dino->step++;
}

Dino* new_Dino(int size) {
    Dino *dino = NULL;
    dino = malloc(sizeof(Dino));

    dino->size = size;
    dino->start = start;
    dino->step = step;

    return dino;
}
