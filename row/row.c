#include <SDL2/SDL.h>
#include <math.h>

#include "../viwe/row/row.h"
#include "../canvas/canvas.h"

typedef struct Row {
    void (*start)(struct Row *, SDL_Renderer *);
    int pictureSize;
    int *firstRow, *secondRow;
    int stepForFirstRow, stepForSecondRow;
    int height, width;
    float step;
} Row;

static void createNewRow(struct Row *row, int * focusRow) {
    for(int x = 0; x < row->width / 20; x++) {
        int getRandomRow = rand() % (3 - 1 + 1) + 1;

        for (int y = 0; y < row->height; y++) {
            for (int w = 0; w < 20; w++) {
                int cellPosition = x * 20 + y * row->width + w;

                if (getRandomRow == 1) {
                    *(focusRow + cellPosition) = row1[y][w];
                } else if (getRandomRow == 2) {
                    *(focusRow + cellPosition) = row2[y][w];
                } else if (getRandomRow == 3) {
                    *(focusRow + cellPosition) = row3[y][w];
                }
            }
        }
    }
}

static void start(struct Row *row, SDL_Renderer* renderer) {
    drowPicture(renderer, row->firstRow, row->stepForFirstRow, 160, row->pictureSize, row->width, row->height);
    drowPicture(renderer, row->secondRow, row->stepForSecondRow, 160, row->pictureSize, row->width, row->height);

    if (row->stepForFirstRow <= - row->width) {
        createNewRow(row, row->firstRow);
        row->stepForFirstRow = row->width;
    }

    if (row->stepForSecondRow <= - row->width) {
        createNewRow(row, row->secondRow);
        row->stepForSecondRow = row->width;
    }

    if (row->stepForFirstRow <= 0) {
        row->stepForFirstRow -= row->step + 1;
    } else {
        row->stepForFirstRow -= row->step;
    }

    if (row->stepForSecondRow <= 0) {
        row->stepForSecondRow -= row->step + 1;
    } else {
        row->stepForSecondRow -= row->step;
    }
}

Row* new_Row(int windowWidth, int pictureSize) {
    Row *row = NULL;
    row = malloc(sizeof(Row));

    int width =  windowWidth / pictureSize + 1;

    int *firstRow = NULL;
    int *secondRow = NULL;

    row->height = 15;
    firstRow = malloc(width * row->height * sizeof(int));
    secondRow = malloc(width * row->height * sizeof(int));

    row->stepForFirstRow = 0;
    row->stepForSecondRow = width;
    row->step = 3.0;
    row->firstRow = firstRow;
    row->secondRow = secondRow;
    row->width = width;
    row->pictureSize = pictureSize;
    row->start = start;

    createNewRow(row, row->firstRow);
    createNewRow(row, row->secondRow);

    return row;
}
