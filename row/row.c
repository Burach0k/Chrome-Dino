#include "SDL2/SDL.h"
#include "../viwe/row/row.h"

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

static void createNewRow(struct Row *row, int * focusRow) {
    for(int x = 0; x < row->rowWidth / 20; x++) {
        int getRandomRow = rand() % (3 - 1 + 1) + 1;

        for (int y = 0; y < row->rowHeight; y++) {
            for (int w = 0; w < 20; w++) {
                int cellPosition = x * 20 + y * row->rowWidth + w;

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
    drowPicture(renderer, row->firstRow, row->stepForFirstRow, 160, row->pictureSize, row->rowWidth, row->rowHeight);
    drowPicture(renderer, row->secondRow, row->stepForSecondRow, 160, row->pictureSize, row->rowWidth, row->rowHeight);

    if (row->stepForFirstRow == - row->rowWidth) {
        createNewRow(row, row->firstRow);
        row->stepForFirstRow = row->rowWidth;
    }

    if (row->stepForSecondRow == - row->rowWidth) {
        createNewRow(row, row->secondRow);
        row->stepForSecondRow = row->rowWidth;
    }

    row->stepForFirstRow--;
    row->stepForSecondRow--;
}

Row* new_Row(int windowWidth, int pictureSize) {
    Row *row = NULL;
    row = malloc(sizeof(Row));

    int rowWidth =  windowWidth / pictureSize + 1;

    int *firstRow = NULL;
    int *secondRow = NULL;

    row->rowHeight = 15;
    firstRow = malloc(rowWidth * row->rowHeight * sizeof(int));
    secondRow = malloc(rowWidth * row->rowHeight * sizeof(int));

    row->stepForFirstRow = 0;
    row->stepForSecondRow = rowWidth;
    row->rowStep = 1;
    row->firstRow = firstRow;
    row->secondRow = secondRow;
    row->rowWidth = rowWidth;
    row->pictureSize = pictureSize;
    row->start = start;

    createNewRow(row, row->firstRow);
    createNewRow(row, row->secondRow);

    return row;
}
