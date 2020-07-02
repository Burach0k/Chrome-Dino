# c

gcc `pkg-config --cflags gtk+-3.0` -lcurl -o main main.c `pkg-config --libs gtk+-3.0` -lcurl
gcc main.c `pkg-config --cflags --libs sdl2`