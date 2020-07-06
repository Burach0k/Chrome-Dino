#include "SDL2/SDL.h"

typedef struct {
    void (*start)(struct Dino *, SDL_Renderer *);
    void (*init)(struct Dino *);
    void (*render)(SDL_Renderer *);
    int step;
} Dino;

void drowPicture(SDL_Renderer *renderer, const int *picture, int x0, int y0, int h, int sizex, int sizey) {
    for (int i = 0; i < sizey; i++)
        for (int j = 0; j < sizex; j++)
            if(*(picture + i*sizey + j) == 1) {
                SDL_Rect rect = { x0 + j + j*h, y0 + i + i*h, h, h };
                SDL_RenderFillRect(renderer, &rect);
            }
}

static int step = 0;

static void start(Dino *dino, SDL_Renderer* renderer) {
    int *dinoMotion = *stayDino;

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    if (dino->step == 0) {
        dinoMotion = *stayDino;
    } else if (dino->step == 1) {
        dinoMotion = *runDino1;
    } else {
        dinoMotion = *runDino2;
        dino->step = 0;
    }

    drowPicture(renderer, dinoMotion, 100, 100, 2, 20, 20);
    dino->step++;
}

Dino* new_Dino() {
    Dino *dino;

    void render(SDL_Renderer* renderer) {}

    dino->start = start;
    dino->step = step;
    dino->render = render;

    return dino;
}
