#include <SDL2/SDL.h>

#include "./item/item.h"
#include "../canvas/canvas.h"
#include "../viwe/cloud/cloud.h"

typedef struct Background {
    void (*start)(struct Background *, SDL_Renderer *);
    struct Item *item;
    int speed;
    int height, width;
} Background;

static void start(struct Background *this, SDL_Renderer* renderer) {

    for (int i = 0; i < 3; i++) {
        Item *cloud = (this->item + i);

        if(cloud->x0 + cloud->width < 0) {
            int randomX = rand() % (1000 - 800) + 800;
            cloud->x0 = randomX;
        }

        drowPicture(renderer, cloud->picture, cloud->x0, cloud->y0, 3, cloud->width, cloud->height);
    }

    if (this->speed == 10) {
        for (int i = 0; i < 3; i++) {
            (this->item + i)->x0--;
        }

        this->speed = 0;
    }

    this->speed++;
}

Background* new_Background(int windowWidth, int pictureSize) {
    Background *background = NULL;
    background = malloc(sizeof(Background));

    background->item = NULL;
    background->item = malloc(sizeof(Item) * 3);
    
    for (int i = 0; i < 3; i++) {
        int randomX = rand() % ((i + 1) * 200 - (i + 1) * 100) + (i + 1) * 100;
        int randomY = rand() % (80 - 1) + 1;

        (background->item + i)->x0 = randomX;
        (background->item + i)->y0 = randomY;
        (background->item + i)->height = 10;
        (background->item + i)->width = 15;
        (background->item + i)->picture = *cloud;
    }

    background->width = windowWidth;
    background->height = 600;
    background->start = start;
    background->speed = 0;

    return background;
}
