typedef struct Barrier {
  int width;
  int height;
  int *picture;
  int x0;
  int y0;
} Barrier;

Barrier* new_Barrier(int size);