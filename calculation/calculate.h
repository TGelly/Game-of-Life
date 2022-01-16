#ifndef HEADER_CALCULATE_INCLUDED
#define HEADER_CALCULATE_INCLUDED

int livingNeighbors(int** grid, int x, int y, int length, int width);
int** allocateGrid(int length, int width);
void freeGrid(int** grid, int length, int width);
void passGrid(int** grid, int length, int width, int** newgrid);
int** update(int** grid, int length, int width);

#endif 
