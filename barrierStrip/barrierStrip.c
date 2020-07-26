#include <SDL2/SDL.h>

#include "../barrier/barrier.h"
#include "../viwe/cactus/cactus.h"
#include "../canvas/canvas.h"

typedef struct BarrierStrip {
    struct Barrier * firstBarriers;
    int firstBarriersPosition;
    int counFirstBarriers;

    struct Barrier * secondBarriers;
    int secondBarriersPosition;
    int counSecondBarriers;

    int width;
    int speed;
    int maxWidthForBarrier;
    int distance;
    int y0;

    void (*start)(struct BarrierStrip*, SDL_Renderer*, int maxWidth);
} BarrierStrip;

static struct Barrier getRandomBarrier() {
    Barrier b;
    int randomFigure = rand() % (2 - 0 + 0) + 0;

    switch(randomFigure) {
        case 0:
            b.width = 20;
            b.height = 20;
            b.picture = *cactus1;
            break;
        case 1:
            b.width = 10;
            b.height = 10;
            b.picture = *cactus2;
            break;
        case 2:
            b.width = 5;
            b.height = 5;
            b.picture = *cactus3;
            break;
    }

    return b;
}

static void renderBarriers(struct BarrierStrip*  this, SDL_Renderer* renderer) {
    for (int i = 0; i < this->counFirstBarriers; i++) {
        drowPicture(
            renderer,
            (this->firstBarriers + i)->picture,
            this->firstBarriersPosition + (this->firstBarriers + i)->x0,
            (this->firstBarriers + i)->y0,
            2,
            (this->firstBarriers + i)->width,
            (this->firstBarriers + i)->height);
    }

    for (int i = 0; i < this->counSecondBarriers; i++) {
        drowPicture(
            renderer,
            (this->secondBarriers + i)->picture,
            this->secondBarriersPosition + (this->secondBarriers + i)->x0,
            (this->secondBarriers + i)->y0,
            2,
            (this->secondBarriers + i)->width,
            (this->secondBarriers + i)->height);
    }
}

static void generateBarriers(struct BarrierStrip*  this, int minWidth) {
    if (this->distance >= minWidth) {
        int randomDistance = minWidth + rand() % (100 - 1 + 1) + 1;

        if (this->firstBarriersPosition - (randomDistance + 20) > 0) {
            Barrier bb = getRandomBarrier();
            *(this->firstBarriers + this->counFirstBarriers) = bb;
            (this->firstBarriers + this->counFirstBarriers)->x0 = this->width - this->firstBarriersPosition + randomDistance;
            (this->firstBarriers + this->counFirstBarriers)->y0 = this->y0 - (this->firstBarriers + this->counFirstBarriers)->height * 2;

            this->counFirstBarriers++;

        } else if (this->firstBarriersPosition <= -this->width) {
            this->firstBarriersPosition = this->width;
            this->counFirstBarriers = 0;
        }

        if (this->secondBarriersPosition - (randomDistance + 20) > 0) {
            Barrier bb = getRandomBarrier();
            *(this->secondBarriers + this->counSecondBarriers) = bb;
            (this->secondBarriers + this->counSecondBarriers)->x0 = this->width - this->secondBarriersPosition + randomDistance;
            (this->secondBarriers + this->counSecondBarriers)->y0 = this->y0 - (this->secondBarriers + this->counSecondBarriers)->height * 2;

            this->counSecondBarriers++;

        } else if (this->secondBarriersPosition <= -this->width) {
            this->secondBarriersPosition = this->width;
            this->counSecondBarriers = 0;
        }

        this->distance = 0;
    } else {
        this->distance += this->speed;
    }
}

static void start(struct BarrierStrip*  this, SDL_Renderer* renderer, int minWidth) {

    generateBarriers(this, minWidth);
    renderBarriers(this, renderer);

    this->firstBarriersPosition -= this->speed;
    this->secondBarriersPosition -= this->speed;
}

BarrierStrip* new_BarrierStrip(int width, int maxWidthForBarrier, int y0) {
    BarrierStrip* barrierStrip = NULL;
    barrierStrip = malloc(sizeof(BarrierStrip));

    barrierStrip->firstBarriers = NULL;
    barrierStrip->firstBarriers = malloc(sizeof(Barrier) * maxWidthForBarrier / 20);

    barrierStrip->secondBarriers = NULL;
    barrierStrip->secondBarriers = malloc(sizeof(Barrier) * maxWidthForBarrier / 20);

    barrierStrip->width = width;
    barrierStrip->speed = 1;
    barrierStrip->distance = 0;
    barrierStrip->firstBarriersPosition = width;
    barrierStrip->secondBarriersPosition = 2 * width; 
    barrierStrip->counFirstBarriers = 0;
    barrierStrip->counSecondBarriers = 0;
    barrierStrip->start = start;
    barrierStrip->y0 = y0;

    return barrierStrip;
}