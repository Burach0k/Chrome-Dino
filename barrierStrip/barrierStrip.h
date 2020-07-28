#include <SDL2/SDL.h>

#include "./barrier/barrier.h"
#include "./barrierLine/barrierLine.h"

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

BarrierStrip* new_BarrierStrip(int width, int maxWidthForBarrier, int y0);