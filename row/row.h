#include <SDL2/SDL.h>

typedef struct Row {
    void (*start)(struct Row *, SDL_Renderer *);
    int pictureSize;
    int *firstRow, *secondRow;
    int stepForFirstRow, stepForSecondRow;
    int height, width;
    float step;
} Row;

Row* new_Row(int windowWidth, int pictureSize);
