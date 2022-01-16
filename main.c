//          normal comment
//!         critical comment
//?         interrogation comment
//TODO      comment to do later

#include "calculation/calculate.h"
#include "display/display.h"

//! Cette fonction afficheMatrice est vouée à disparaître lorsque l'affichage en SDL sera fonctionnel.

void afficheMatrice(int** matrix, int length, int width){
    for(int i=0; i<width; i++){
        for(int j=0; j<length; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}



int main(){

    // There should be a menu here.
    // The user will be able to choose the size of the grid and then fill as many cells as they want.

    int** matrix = allocateGrid(4, 4);
    
    matrix[0][2] = 1;
    matrix[1][2] = 1;
    matrix[2][2] = 1;

    //! Cette portion de code permet de tester la fonction update en attendant que la partie display soit fonctionnelle
    
    //on joue juste deux ticks de jeu
    afficheMatrice(matrix, 4, 4);
    matrix = update(matrix, 4, 4);
    afficheMatrice(matrix, 4, 4);
    matrix = update(matrix, 4, 4);
    afficheMatrice(matrix, 4, 4);

    return 0;
}