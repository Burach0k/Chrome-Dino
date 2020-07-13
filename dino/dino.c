#include "SDL2/SDL.h"
#include "../viwe/dino/viweDino.h"
#include "../canvas/canvas.h"

typedef enum Event {
    RUN,
    JUMP
} Event;

typedef struct Dino {
    void (*start)(struct Dino *, SDL_Renderer *);
    void (*jump)(struct Dino *);
    int step;
    int pictureSize;
    int x0;
    int y0;
    int speed;
    float jumpValue;
    Event event;
} Dino;

static void start(struct Dino *dino, SDL_Renderer* renderer) {
    if (dino->event == JUMP) {
        dino->jump(dino);
    }

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

static void jump(struct Dino *dino) {
    dino->y0 = dino->jumpValue * dino->jumpValue + dino->jumpValue;

    if (dino->jumpValue >= 10) {
        dino->jumpValue = -10;
        dino->event = RUN;
    } else {
        dino->jumpValue += 0.5;
    }
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
    dino->jump = jump;
    dino->jumpValue = -10;
    dino->event = RUN;

    return dino;
}
