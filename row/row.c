#include "SDL2/SDL.h"

typedef struct Row {
    void (*startt)(struct Row *, SDL_Renderer *);
    int rowWidth;
    int size;
    int *rowMas;
} Row;


static void createRow() {

}

static void startt(struct Row *row, SDL_Renderer* renderer) {
    // SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    // drowPicture(renderer, row->rowMas, 100, 100, 2, 20, 20);
}

Row* new_Row(int windowWidth, int size) {
    Row *row = NULL;
    row = malloc(sizeof(Row));
    // int rowWidth =  windowWidth / size + 1;
    // int *rowMas[2];

    // int i = 0;
    // for(i = 0; i < 2; i++) {
        // rowMas[0] = *row1;
        // (*rowMas)[1] = *row1;
    // }

    // row->rowMas = rowMas;
    // row->rowWidth = rowWidth;
    // row->size = size;
    row->startt = startt;

    return row;
}
