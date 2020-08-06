#include <SDL2/SDL.h>

#include "../viwe/dino/viweDino.h"
#include "../canvas/canvas.h"

typedef enum Event {
    RUN,
    JUMP,
    BENT_RUN
} Event;

typedef struct Dino {
    void (*start)(struct Dino *, SDL_Renderer *);
    void (*jump)(struct Dino *);
    void (*defaultRun)(struct Dino *);
    int step;
    int pictureSize;
    int speed;
    int x0, y0;
    int height, width;
    int* picture;
    float jumpValue;
    Event event;
} Dino;

static void start(struct Dino *dino, SDL_Renderer* renderer) {

    switch(dino->event) {
        case JUMP:
            dino->jump(dino);
            break;

        case BENT_RUN:
        
        default:
            dino->defaultRun(dino);
    }

    drowPicture(renderer, dino->picture, dino->x0, dino->y0, dino->pictureSize, 20, 20);

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

    dino->picture = *stayDino;
    dino->step = 0;
}

static void defaultRun(struct Dino *dino) {
    if (dino->step < dino->speed) {
            dino->picture = *stayDino;
        } else if (dino->step < dino->speed * 2) {
            dino->picture = *runDino1;
        } else if (dino->step < dino->speed * 3) {
            dino->picture = *runDino2;

            if (dino->step == dino->speed * 3 - 1) {
                dino->step = 0;
            }
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
    dino->height = 20 * pictureSize;
    dino->width = 20 * pictureSize;
    dino->speed = 5;
    dino->jump = jump;
    dino->jumpValue = -10;
    dino->event = RUN;
    dino->picture = *stayDino;
    dino->defaultRun = defaultRun;

    return dino;
}
