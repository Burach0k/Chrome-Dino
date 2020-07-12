CC = gcc
CFLAGS = -I /usr/include/SDL2 -L "lib" -fPIC -Wall `pkg-config --cflags --libs sdl2`

all:
	$(CC) $(CFLAGS) main.c ./canvas/canvas.c ./dino/dino.c ./row/row.c ./viwe/dino/viweDino.c ./viwe/row/row.c -lSDL2main -lSDL2

clean:
	rm -rf *.o