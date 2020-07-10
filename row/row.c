#include "SDL2/SDL.h"

typedef struct Row {
    void (*startt)(struct Row *, SDL_Renderer *);
    int rowWidth;
    int size;
    int *rowMas;
    int step;
} Row;

static void createNewRow(struct Row *row) {
    for(int x = 0; x < row->rowWidth / 20; x++) {
        int getRandomRow = rand() % (3 - 1 + 1) + 1;

        for (int y = 0; y < 8; y++) {
            for (int w = 0; w < 20; w++) {
                if (getRandomRow == 1) {
                    *(row->rowMas + x*20 + y * row->rowWidth + w) = row1[y][w];
                } else if (getRandomRow == 2) {
                    *(row->rowMas + x*20 + y * row->rowWidth + w) = row2[y][w];
                } else if (getRandomRow == 3) {
                    *(row->rowMas + x*20 + y * row->rowWidth + w) = row3[y][w];
                }
            }
        }
    }
}

static void startt(struct Row *row, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    drowPicture(renderer, row->rowMas, -row->step, 160, row->size, row->rowWidth, 8);

    if (row->step == row->rowWidth / 2) {

        createNewRow(row);

        row->step = 0;
    }

    row->step++;
}

Row* new_Row(int windowWidth, int size) {
    Row *row = NULL;
    row = malloc(sizeof(Row));

    int koefGostWidth = 2;
    int rowWidth =  windowWidth / size * koefGostWidth + 1;

    int *rowMas = NULL;

    rowMas = malloc(rowWidth * 8 * sizeof(int));

    row->step = 0;
    row->rowMas = rowMas;
    row->rowWidth = rowWidth;
    row->size = size;
    row->startt = startt;

    createNewRow(row);

    return row;
}
