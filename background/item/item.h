#include <SDL2/SDL.h>

typedef struct Item {
  int width;
  int height;
  int *picture;
  int x0;
  int y0;
} Item;

Item *new_Item(int size);