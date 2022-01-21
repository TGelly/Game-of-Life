//          normal comment
//*         highlighted comment
//!         critical comment
//?         interrogation comment
//TODO      comment to do later

#include "calculations/compute.h"

//! Cette fonction afficheMatrice est vouée à disparaître lorsque l'affichage en SDL sera fonctionnel.
void afficheMatrice(cell** grid, int length, int height){
    for(int i=0; i<height; i++){
        for(int j=0; j<length; j++){
            printf("%d ", grid[i][j].value);
        }
        printf("\n");
    }
    printf("\n");
}



int main(){

    // There should be a menu here.
    // The user will be able to choose the size of the grid and then fill as many cells as they want.

    int length = 8, height = 8;
    //in upper case, the size of the window (in px)
    //in lower case, the size of the grid (in cells)
    int cellSize = LENGTH/length;

    //! Cette portion de code permet de tester la fonction update en attendant que la partie display soit fonctionnelle
    cell** grid = allocateGrid(length, height);
    grid[1][2].value = 1;
    grid[2][2].value = 1;
    grid[3][2].value = 1;
    //on joue juste deux ticks de jeu
    afficheMatrice(grid, length, height);
    grid = update(grid, length, height);
    afficheMatrice(grid, length, height);
    grid = update(grid, length, height);
    afficheMatrice(grid, length, height);

    //* here comes the code that uses the SDL
    
    //The window we'll be rendering to
    SDL_Window* window = NULL;
    //The renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //The surface contained by the window
    SDL_Surface* screenSurface = NULL;
    //The surfaces and textures of the empty or full cells
    SDL_Surface* fc = IMG_Load("images/fullcell.png");
    SDL_Texture* fullcell = SDL_CreateTextureFromSurface(renderer, fullcell); 
    SDL_Surface* ec = IMG_Load("images/emptycell.png");
    SDL_Texture* emptycell = SDL_CreateTextureFromSurface(renderer, emptycell);
    //The Rect of where these textures should go
    SDL_Rect destination;

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Initialize SDL
    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else{
        //Create window
        window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LENGTH, HEIGTH, SDL_WINDOW_SHOWN);
        if(window == NULL){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);
            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            int run=1 ;
            SDL_Event event ;
            while(run){

                SDL_PollEvent(&event) ;
                switch(event.type){
                    case SDL_QUIT:
                        run = 0;
                        break;
                    case SDLK_SPACE:
                        //? ne fonctionne pas, je n'arrive pas à savoir pourquoi
                        printf(" The spacebar was pressed.\n");
                        grid = update(grid, length, height);
                        afficheMatrice(grid, length, height);
                        run = 0;
                        break;
                    case SDLK_DOWN:
                        printf("The down arrow key was pressed.\n");
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        mousePress(event.button, grid, cellSize);
                        afficheMatrice(grid, length, height);
                        break;
                    default :
                        break;
                }
                for(int i=0; i<height; i++){
                    for(int j=0; j<length; j++){

                        //update the coordinates of the Blit
                        destination.x = j*cellSize;
                        destination.y = i*cellSize;
                        destination.h = cellSize;
                        destination.w = cellSize;

                        if(grid[i][j].value == 1){
                            //afficher l'image fullcell

                            SDL_Surface* rectangle= SDL_CreateRGBSurface(SDL_SWSURFACE, cellSize, cellSize, 32, 0, 0, 0, 0);
                            SDL_UpdateWindowSurface(window);
                            SDL_BlitSurface(rectangle, NULL, screenSurface, &destination);
                        }
                        else{
                            //afficher l'image emptycell
                        }
                    }
                }
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    //Destroy renderer
    SDL_DestroyRenderer(renderer);
    //Destroy window
    SDL_DestroyWindow(window);
    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}