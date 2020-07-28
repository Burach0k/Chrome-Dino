#include <SDL2/SDL.h>

#include "./barrier/barrier.h"
#include "./barrierLine/barrierLine.h"
#include "../viwe/cactus/cactus.h"
#include "../canvas/canvas.h"


typedef struct BarrierStrip {
    struct BarrierLine *firstLine;
    struct BarrierLine *secondLine;

    int width;
    int maxWidthForBarrier;
    int distance;
    int y0;
    int size;

    float speed;

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

static void renderBarriers(struct BarrierLine *bl, int size, SDL_Renderer* renderer) {
    for (int i = 0; i < bl->coun; i++) {
        drowPicture(
            renderer,
            (bl->barriers + i)->picture,
            bl->x0 + (bl->barriers + i)->x0,
            (bl->barriers + i)->y0,
            size,
            (bl->barriers + i)->width,
            (bl->barriers + i)->height);
    }
}

static void setBarrierValues(struct BarrierLine* bl, int width, int minWidth, int y0) {
    int randomDistance = minWidth + rand() % (100 - 1 + 1) + 1;

    if (bl->x0 <= width && bl->x0 - (randomDistance + 20) > 0) {
        Barrier rb = getRandomBarrier();
        *(bl->barriers + bl->coun) = rb;
        (bl->barriers + bl->coun)->x0 = width - bl->x0 + randomDistance;
        (bl->barriers + bl->coun)->y0 = y0 - (bl->barriers + bl->coun)->height * 2;

        bl->coun++;

    } else if (bl->x0 <= -width) {
        bl->x0 = width;
        bl->coun = 0;
    }
}

static void generateBarriers(struct BarrierStrip* this, int minWidth) {
    if (this->distance >= minWidth) {
        setBarrierValues(this->firstLine, this->width, minWidth, this->y0);
        setBarrierValues(this->secondLine, this->width, minWidth, this->y0);

        this->distance = 0;
    } else {
        this->distance += this->speed;
    }
}

static void start(struct BarrierStrip*  this, SDL_Renderer* renderer, int minWidth) {
    generateBarriers(this, minWidth);
    renderBarriers(this->firstLine, this->size, renderer);
    renderBarriers(this->secondLine, this->size, renderer);

    this->firstLine->x0 -= this->speed;
    this->secondLine->x0 -= this->speed;
}

BarrierStrip* new_BarrierStrip(int width, int maxWidthForBarrier, int y0) {
    BarrierStrip* barrierStrip = NULL;
    barrierStrip = malloc(sizeof(BarrierStrip));

    barrierStrip->firstLine = new_BarrierLine();
    barrierStrip->secondLine = new_BarrierLine();

    barrierStrip->firstLine->barriers = new_Barrier(sizeof(Barrier) * maxWidthForBarrier / 20);
    barrierStrip->secondLine->barriers = new_Barrier(sizeof(Barrier) * maxWidthForBarrier / 20);

    barrierStrip->width = width;
    barrierStrip->speed = 3.0;
    barrierStrip->distance = 0;
    barrierStrip->start = start;
    barrierStrip->y0 = y0;
    barrierStrip->size = 2;

    barrierStrip->firstLine->x0 = width;
    barrierStrip->firstLine->coun = 0;

    barrierStrip->secondLine->x0 = 2 * width;
    barrierStrip->secondLine->coun = 0;

    return barrierStrip;
}