#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "enigmeAlea.h"

int enigmeAlea(SDL_Surface* screen)
{
  // Initialisation de police
  TTF_Init();
  TTF_Font *font = TTF_OpenFont("Bebas-Regular.ttf", 30);

  // Initialisation de l'enigme
  enigme e = initEnigme();
  enigmeData ed = genererEnigme(e);

  // Affichage de l'enigme
  afficherenigme(ed, screen, e);
  SDL_Flip(screen);

  // Résolution de l'enigme
  int result = 0;
  SDL_Event event;
  while (!result)
  {

    SDL_WaitEvent(&event);

    switch (event.type)
    {
        case SDL_QUIT:
            result = 1;
            break;

        default:
            result = resolutionEnigme(ed, event, screen, font);
            break;
    }
  }

  // liberer
  fclose(e.f);
  SDL_FreeSurface(e.back);
  SDL_FreeSurface(screen);
  TTF_CloseFont(font);
  TTF_Quit();
  return 0;
}
