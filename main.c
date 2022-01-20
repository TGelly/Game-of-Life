//          normal comment
//*         highlighted comment
//!         critical comment
//?         interrogation comment
//TODO      comment to do later

#include "calculations/compute.h"

//! Cette fonction afficheMatrice est vouée à disparaître lorsque l'affichage en SDL sera fonctionnel.
void afficheMatrice(cell** matrix, int length, int width){
    for(int i=0; i<width; i++){
        for(int j=0; j<length; j++){
            printf("%d ", matrix[i][j].value);
        }
        printf("\n");
    }
    printf("\n");
}



int main(){

    //TODO il faut créer une structure cell, utiliser uniquement des tableaux de cette struture et utiliser les coordonnées de ces cellules
    //TODO pour localiser à quelle case correspond chaque clic.

    // There should be a menu here.
    // The user will be able to choose the size of the grid and then fill as many cells as they want.

    int length = 8, width = 8;

    //! Cette portion de code permet de tester la fonction update en attendant que la partie display soit fonctionnelle
    cell** matrix = allocateGrid(length, width);
    matrix[1][2].value = 1;
    matrix[2][2].value = 1;
    matrix[3][2].value = 1;
    //on joue juste deux ticks de jeu
    afficheMatrice(matrix, length, width);
    matrix = update(matrix, length, width);
    afficheMatrice(matrix, length, width);
    matrix = update(matrix, length, width);
    afficheMatrice(matrix, length, width);

    //* here comes the code that uses the SDL
    
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else{
        //Create window
        window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 900, SDL_WINDOW_SHOWN);
        if(window == NULL){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);
            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
            //Update the surface
            SDL_UpdateWindowSurface(window);

            int run=1 ;
            SDL_Event event ;
            while(run){
                SDL_PollEvent(&event) ;
                switch(event.type){
                    case SDL_QUIT:
                        run = 0;
                        break;
                    case SDLK_SPACE:
                        printf(" The spacebar was pressed.\n");
                        matrix = update(matrix, length, width);
                        afficheMatrice(matrix, length, width);
                        run = 0;
                        break;
                    case SDLK_DOWN:
                        printf("The down arrow key was pressed.\n");
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        mousePress(event.button);
                        break;
                    default :
                        break;
                run= 1 ;
                }
            }
        }
    }

    //Destroy window
    SDL_DestroyWindow(window);
    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}