#ifndef SAUV_H_INCLUDED
#define SAUV_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "character.h"
#include "bg.h"

void sauvegarder(Player p, Background b, char *nomfichier,int level);
int charger (Player *p, Background *b , char * nomfichier,int *level);

#endif
