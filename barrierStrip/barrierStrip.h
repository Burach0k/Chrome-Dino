#include <SDL2/SDL.h>

#include "../barrier/barrier.h"

typedef struct BarrierLine {
    struct Barrier * barriers;
    int x0;
    int coun;
} BarrierLine;

typedef struct BarrierStrip {
    struct BarrierLine *firstLine;
    struct BarrierLine *secondLine;

    int width;
    int speed;
    int maxWidthForBarrier;
    int distance;
    int y0;
    int size;

    void (*start)(struct BarrierStrip*, SDL_Renderer*, int maxWidth);
} BarrierStrip;

BarrierStrip* new_BarrierStrip(int width, int maxWidthForBarrier, int y0);