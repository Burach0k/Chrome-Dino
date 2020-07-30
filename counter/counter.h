#include <SDL2/SDL.h>

typedef struct Counter {
    int count;
    void (*start)(struct Counter*, SDL_Renderer*);
} Counter;

Counter* new_Counter();