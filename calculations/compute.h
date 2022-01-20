#ifndef HEADER_COMPUTE_INCLUDED
#define HEADER_COMPUTE_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

struct cell{
    int x;      // x coordinate of the cell
    int y;      // y coordinate of th cell
    int value;  //value of the cell (1 or 0)
}; typedef struct cell cell;
int livingNeighbors(cell** grid, int x, int y, int length, int width);
cell** allocateGrid(int length, int width);
void freeGrid(cell** grid, int length, int width);
void passGrid(cell** grid, int length, int width, cell** newgrid);
cell** update(cell** grid, int length, int width);
void mousePress(SDL_MouseButtonEvent b);

#endif