#include <SDL2/SDL.h>

#include "./item/item.h"

typedef struct Background {
    void (*start)(struct Background *, SDL_Renderer *);
    Item *item;
    int speed;
    int height, width;
} Background;

Background* new_Background(int windowWidth, int pictureSize);
