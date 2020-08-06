CC = gcc
32 = i686-w64-mingw32-gcc -lmingw32
64 = x84_64-w64-mingw32-gcc
CFLAGS = -I /usr/include/SDL2 -L "lib" -fPIC -Wall `pkg-config --cflags --libs sdl2` -fms-extensions

all:
	$(CC) $(CFLAGS) main.c ./counter/counter.c ./viwe/numbers/numbers.c ./barrierStrip/barrier/barrier.c ./barrierStrip/barrierLine/barrierLine.c ./canvas/canvas.c ./dino/dino.c ./row/row.c ./barrierStrip/barrierStrip.c ./viwe/dino/viweDino.c ./viwe/row/row.c ./viwe/cactus/cactus.c ./viwe/cloud/cloud.c ./background/background.c -lSDL2main -lSDL2 -ltinfo -lncurses -lm

createForWindow:
	$(32) $(CFLAGS) main.c ./counter/counter.c ./viwe/numbers/numbers.c ./barrierStrip/barrier/barrier.c ./barrierStrip/barrierLine/barrierLine.c ./canvas/canvas.c ./dino/dino.c ./row/row.c ./barrierStrip/barrierStrip.c ./viwe/dino/viweDino.c ./viwe/row/row.c ./viwe/cactus/cactus.c -lSDL2main -lSDL2 -ltinfo -lncurses -lm

clean:
	rm -rf *.o
	rm -rf *.out