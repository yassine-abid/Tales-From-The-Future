#ifndef DIALOGUE_H
#define DIALOGUE_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "bg.h"

void levelOneDlg(SDL_Surface *screen, Background* dialogue, int* dialogueCheck,int *i,int maxframe);
void afficherDialogue(Background b, SDL_Surface *screen, int i);

#endif