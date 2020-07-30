#include <SDL2/SDL.h>

#include "../canvas/canvas.h"
#include "../viwe/numbers/numbers.h"

typedef struct Counter {
    int count;
    void (*start)(struct Counter*, SDL_Renderer*);
} Counter;

static int* getImgForNumber(int num) {
    switch (num) {
        case 0:
            return *zero;
        case 1:
            return *one;
        case 2:
            return *two;
        case 3:
            return *three;
        case 4:
            return *four;
        case 5:
            return *five;
        case 6:
            return *six;
        case 7:
            return *seven;
        case 8:
            return *eight;
        case 9:
            return *nine;
    }
}

static void start(struct Counter*  this, SDL_Renderer* renderer) {
    
    if (this->count > 9999) {
        int num = (this->count / 10000) % 10;
        drowPicture(renderer, getImgForNumber(num), 0, 0, 3, 4, 5);
    }
    if (this->count > 999) {
        int num = (this->count / 1000) % 10;
        drowPicture(renderer, getImgForNumber(num), 15, 0, 3, 4, 5);
    }
    if (this->count > 99) {
        int num = (this->count / 100) % 10;
        drowPicture(renderer, getImgForNumber(num), 30, 0, 3, 4, 5);
    }
    if (this->count > 9) {
        int num = (this->count / 10) % 10;
        drowPicture(renderer, getImgForNumber(num), 45, 0, 3, 4, 5);
    }

    int num = this->count % 10;
    drowPicture(renderer, getImgForNumber(num), 60, 0, 3, 4, 5);

    this->count++;
}

Counter* new_Counter() {
    Counter* counter = NULL;
    counter = malloc(sizeof(Counter));

    counter->start = start;
    counter->count = 0;

    return counter;
}