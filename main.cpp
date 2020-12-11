#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include "jeu.c"



int main ( int argc, char** argv )
{
    SDL_Surface *ecran = NULL, *menu = NULL;
    SDL_Rect positionMenu;
    SDL_Event event;

    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetIcon(IMG_Load("joueurNoir.png"), NULL);
    ecran = SDL_SetVideoMode(520, 520, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Tablut MOHAMED AIT DAHANE 1GI", NULL);

    menu = IMG_Load("menu.jpg");
    positionMenu.x = 0;
    positionMenu.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);   /// On attend que un événement
        switch(event.type)
        {
            case SDL_QUIT:   /// Si on clique sur fermer
                continuer = 0;
                break;
            case SDL_KEYDOWN:  /// Si on clique sur un boutton du clavier
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:  /// Si "echap" on sort de la boucle
                        {
                            continuer = 0;
                            break;
                        }
                    case SDLK_KP1:  ///Si "1" on affiche le menu secondaire
                    {
                        menuSecondaire(ecran);
                        break;
                    }
                    case SDLK_KP2:  ///Si "2" on affiche les règles
                     {
                        regles(ecran);
                        break;
                     }
                }
                break;
        }


        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(menu);
    SDL_Quit();

    return EXIT_SUCCESS;
}

