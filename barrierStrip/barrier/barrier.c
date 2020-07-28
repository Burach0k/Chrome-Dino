#include <SDL2/SDL.h>

typedef struct Barrier {
  int width;
  int height;
  int *picture;
  int x0;
  int y0;
} Barrier;

Barrier* new_Barrier(int size) {
    Barrier *barrier = NULL;
    barrier = malloc(size);

    return barrier;
}