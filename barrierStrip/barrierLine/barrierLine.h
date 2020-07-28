#include <SDL2/SDL.h>

typedef struct BarrierLine {
    struct Barrier * barriers;
    int x0;
    int coun;
} BarrierLine;

BarrierLine* new_BarrierLine();