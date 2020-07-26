#include <SDL2/SDL.h>

#include "../barrier/barrier.h"

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

BarrierStrip* new_BarrierStrip(int width, int maxWidthForBarrier, int y0);