#include <stdio.h>
#include <stdlib.h>
#include "calculate.h"

int livingNeighbors(int** grid, int x, int y, int length, int width){
    int result = 0;

    //first, we scan the connected sides of our cell
    if(x != 0){if (grid[x-1][y] == 1){result ++;}}              //if the scanned cell is not at the top, scan top
    if(x != width-1){if (grid[x+1][y] == 1){result ++;}}        //if the scanned cell is not at the bottom, scan bottom
    if(y != 0){if (grid[x][y-1] == 1){result ++;}}              //if the scanned cell is not at the left, scan left
    if(y != length-1){if (grid[x][y+1] == 1){result ++;}}       //if the scanned cell is not at the right, scan right

    //then, we scan the diagonals
    if(x != 0 && y != 0){if(grid[x-1][y-1] == 1){result ++;}}               //if the scanned cell is not at the top or left border, scan the top left diagonal
    if(x != 0 && y != length-1){if(grid[x-1][y+1] == 1){result ++;}}        //if the scanned cell is not at the top or right border, scan the top right diagonal
    if(x != width-1 && y != length-1){if(grid[x+1][y+1] == 1){result ++;}}  //if the scanned cell is not at the bottom or right border, scan the bottom right diagonal
    if(x != width-1 && y != 0){if(grid[x+1][y-1] == 1){result ++;}}         //if the scanned cell is not at the bottom or left border, scan the bottom left diagonal

    return result;
}

int** allocateGrid(int length, int width){
    int** grid = malloc(width*sizeof(int*));
    for(int i=0; i<width; i++){
        grid[i] = malloc(length*sizeof(int));
        for(int j=0; j<length; j++){
            grid[i][j] = 0;
        }
    }
    return grid;
}

void freeGrid(int** grid, int length, int width){
    for(int i=0; i<width; i++){
        free(grid[i]);
    }
    free(grid);
}

void passGrid(int** grid, int length, int width, int** newGrid){
    for(int i = 0; i<width; i++){
        for(int j = 0; j<length; j++){
            newGrid[i][j] = grid[i][j];
        }
    }
}

int** update(int** grid, int length, int width){

    //create a new grid the same size as the first one
    int** newGrid = allocateGrid(length, width);
    //copy the first grid into the new one
    passGrid(grid, length, width, newGrid);

    for(int i=0; i<width; i++){
        for(int j=0; j<length; j++){

            //count the number of neighbor cells
            int neighborCells = livingNeighbors(grid, i, j, length, width);

            //if the cell is already alive:
            if(grid[i][j] == 1){
                //if it has less than 2 or more than 3 living neighbors:
                if(neighborCells < 2 || neighborCells > 3){
                    //the cell dies
                    newGrid[i][j] = 0;
                }
            }
            //if the cell is not alive:
            else{
                //if the cell is surrounded by exactly 3 living neighbors:
                if(neighborCells == 3){
                    //it comes to life
                    newGrid[i][j] = 1;
                }
            }
        }
    }
    freeGrid(grid, length, width);
    return newGrid;
}