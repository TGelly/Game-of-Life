#include "compute.h"

int livingNeighbors(cell** grid, int x, int y, int length, int width){
    int result = 0;

    //first, we scan the connected sides of our cell
    if(x != 0){if (grid[x-1][y].value == 1){result ++;}}              //if the scanned cell is not at the top, scan top
    if(x != width-1){if (grid[x+1][y].value == 1){result ++;}}        //if the scanned cell is not at the bottom, scan bottom
    if(y != 0){if (grid[x][y-1].value == 1){result ++;}}              //if the scanned cell is not at the left, scan left
    if(y != length-1){if (grid[x][y+1].value == 1){result ++;}}       //if the scanned cell is not at the right, scan right

    //then, we scan the diagonals
    if(x != 0 && y != 0){if(grid[x-1][y-1].value == 1){result ++;}}               //if the scanned cell is not at the top or left border, scan the top left diagonal
    if(x != 0 && y != length-1){if(grid[x-1][y+1].value == 1){result ++;}}        //if the scanned cell is not at the top or right border, scan the top right diagonal
    if(x != width-1 && y != length-1){if(grid[x+1][y+1].value == 1){result ++;}}  //if the scanned cell is not at the bottom or right border, scan the bottom right diagonal
    if(x != width-1 && y != 0){if(grid[x+1][y-1].value == 1){result ++;}}         //if the scanned cell is not at the bottom or left border, scan the bottom left diagonal

    return result;
}

cell** allocateGrid(int length, int width){
    cell** grid = malloc(width*sizeof(cell*));
    for(int i=0; i<width; i++){
        grid[i] = malloc(length*sizeof(cell));
        for(int j=0; j<length; j++){
            grid[i][j].value = 0;
            grid[i][j].x = i;
            grid[i][j].y = j;
        }
    }
    return grid;
}

void freeGrid(cell** grid, int length, int width){
    for(int i=0; i<width; i++){
        free(grid[i]);
    }
    free(grid);
}

void passGrid(cell** grid, int length, int width, cell** newGrid){
    for(int i = 0; i<width; i++){
        for(int j = 0; j<length; j++){
            newGrid[i][j] = grid[i][j];
        }
    }
}

cell** update(cell** grid, int length, int width){

    //create a new grid the same size as the first one
    cell** newGrid = allocateGrid(length, width);
    //copy the first grid into the new one
    passGrid(grid, length, width, newGrid);

    for(int i=0; i<width; i++){
        for(int j=0; j<length; j++){

            //count the number of neighbor cells
            int neighborCells = livingNeighbors(grid, i, j, length, width);

            //if the cell is already alive:
            if(grid[i][j].value == 1){
                //if it has less than 2 or more than 3 living neighbors:
                if(neighborCells < 2 || neighborCells > 3){
                    //the cell dies
                    newGrid[i][j].value = 0;
                }
            }
            //if the cell is not alive:
            else{
                //if the cell is surrounded by exactly 3 living neighbors:
                if(neighborCells == 3){
                    //it comes to life
                    newGrid[i][j].value = 1;
                }
            }
        }
    }
    freeGrid(grid, length, width);
    return newGrid;
}

//this function is called when a mouse button is clicked.
void mousePress(SDL_MouseButtonEvent b){
    if(b.button == SDL_BUTTON_LEFT){
        int x, y;
        SDL_GetMouseState(&x, &y);
        printf("%d, %d", x, y);
        SDL_Delay(500);
    }
}