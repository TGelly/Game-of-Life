# Game-of-Life

A game of life written in C.

The display of the grid is done through the SDL lib.

To compile with SDL:

`gcc -o test main.c calculations/compute.c $(sdl2-config --cflags --libs)`