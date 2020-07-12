#include "SDL2/SDL.h"

typedef struct Row {
    void (*start)(struct Row *, SDL_Renderer *);
    int rowWidth;
    int pictureSize;
    int *firstRow;
    int *secondRow;
    int stepForFirstRow;
    int stepForSecondRow;
    int rowHeight;
    int rowStep;
} Row;

Row* new_Row(int windowWidth, int pictureSize);
