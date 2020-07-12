#include "SDL2/SDL.h"
#include "../viwe/dino/viweDino.h"

typedef struct Dino {
    void (*start)(struct Dino *, SDL_Renderer *);
    int step;
    int pictureSize;
    int x0;
    int y0;
    int speed;
} Dino;

static void start(struct Dino *dino, SDL_Renderer* renderer) {
    if (dino->step < dino->speed) {
        drowPicture(renderer, *stayDino, dino->x0, dino->y0, dino->pictureSize, 20, 20);
    } else if (dino->step < dino->speed * 2) {
        drowPicture(renderer, *runDino1, dino->x0, dino->y0, dino->pictureSize, 20, 20);
    } else if (dino->step < dino->speed * 3) {
        drowPicture(renderer, *runDino2, dino->x0, dino->y0, dino->pictureSize, 20, 20);

        if (dino->step == dino->speed * 3 - 1) {
            dino->step = 0;
        }
    }

    dino->step++;
}

Dino* new_Dino(int pictureSize, int x0, int y0) {
    Dino *dino = NULL;
    dino = malloc(sizeof(Dino));

    dino->pictureSize = pictureSize;
    dino->start = start;
    dino->step = 0;
    dino->x0 = x0;
    dino->y0 = y0;
    dino->speed = 5;

    return dino;
}
