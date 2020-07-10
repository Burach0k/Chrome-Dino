#include "SDL2/SDL.h"

typedef struct Row {
    void (*startt)(struct Row *, SDL_Renderer *);
    int rowWidth;
    int size;
    int *rowMas;
    int step;
} Row;

static void startt(struct Row *row, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    drowPicture(renderer, row->rowMas, -row->step, 160, row->size, row->rowWidth, 8);

    if (row->step == row->rowWidth / 2) {

        int a = 0;
        for(int w = 0; w < 8; w++) {
            for(int m = 0; m < row->rowWidth / 20; m++) {
                for(int h = 0; h < 20; h++) {
                    *(row->rowMas + a) = row2[w][h];
                    a++;
                }
            }
        }

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

    int a = 0;
    for(int w = 0; w < 8; w++) {
        for(int m = 0; m < rowWidth / 20; m++) {
            for(int h = 0; h < 20; h++) {
                *(rowMas + a) = row2[w][h];
                a++;
            }
        }
    }

    row->step = 0;
    row->rowMas = rowMas;
    row->rowWidth = rowWidth;
    row->size = size;
    row->startt = startt;

    return row;
}
