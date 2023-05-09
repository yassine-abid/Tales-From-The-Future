/**
 * @file enigmeAleaMain.c
*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "enigmeAlea.h"
#include <string.h>
#include <time.h>
#include "minimap.h"
/**
 * @brief Calls all the random enigma functions
 * @return 0
*/
int aleaMain()
{
    int r = 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("Can't init SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    imageEnig bg, correct, wrong;
    SDL_Surface *ecran;
    // INITIALISATION
    ecran = SDL_SetVideoMode(1366, 770, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // lancement de fenétre
    enigme e = generer();
    initialiser_imageBACKEnig(&bg, "enigme.png");
    initialiser_imageBOUTONEnig(&correct, SCREEN_W / 2-  300, SCREEN_H / 2-  400, 788, 940, "correct.png");
    initialiser_imageBOUTONEnig(&wrong, SCREEN_W / 2 - 200, SCREEN_H / 2-  200, 512, 512, "wrong.png");
    Uint32 starttime=SDL_GetTicks();
    while (1)
    {
        afficher_imageBMPEnigme(ecran,bg);
        afficherenigme(e, ecran);
        affichertempsen(starttime);
        r = checkEnigme(e);
        if (r == 1)
        {
            afficher_imageBTNEnig(ecran, correct);
            SDL_Flip(ecran);
            SDL_Delay(3000);
            break;
        }
        else if (r == 0)
        {
            afficher_imageBTNEnig(ecran, wrong);
            SDL_Flip(ecran);
            SDL_Delay(3000);
        }
        SDL_Flip(ecran);
    }
    return 0;
}