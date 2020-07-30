CC = gcc
CFLAGS = -I /usr/include/SDL2 -L "lib" -fPIC -Wall `pkg-config --cflags --libs sdl2` -fms-extensions

all:
	$(CC) $(CFLAGS) main.c ./counter/counter.c ./viwe/numbers/numbers.c ./barrierStrip/barrier/barrier.c ./barrierStrip/barrierLine/barrierLine.c ./canvas/canvas.c ./dino/dino.c ./row/row.c ./barrierStrip/barrierStrip.c ./viwe/dino/viweDino.c ./viwe/row/row.c ./viwe/cactus/cactus.c -lSDL2main -lSDL2 -ltinfo -lncurses -lm

clean:
	rm -rf *.o
	rm -rf *.out