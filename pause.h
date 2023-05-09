#ifndef PAUSE_H_INCLUDED
#define PAUSE_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <math.h>
#include "character.h"
#include "bg.h"
#include "sauv.h"
#define SCREEN_H 770
#define SCREEN_W 1366

typedef struct {
    SDL_Rect rect;
    SDL_Surface *images[4];
    int currentImageIndex;
    SDL_Rect camera_pos;
    SDL_Rect posBack1;
    int direction;
    SDL_Rect posScreen1;
    SDL_Rect posBack2;
}pauseBackground;

void afficher_imageOPTBTN(SDL_Surface **screen, image imge);

void afficherPauseBack(pauseBackground b, SDL_Surface *screen);

void initPauseBack(pauseBackground* b, SDL_Surface* screen, const char* paths, int numImages);

void display_button_images(SDL_Surface** screen_surface, 
                           image button_one, image button_one_alt, int button_one_hovered,
                           image button_two, image button_two_alt, int button_two_hovered,
                           image button_three, image button_three_alt, int button_three_hovered,
                           image button_four, image button_four_alt, int button_four_hovered);

void pauseGame(Player p, Background b, SDL_Surface* screen_sruface, int *isPaused, SDL_Event *event, int *game, image IMGOptOne, image IMGOptTwo, image IMGOptThree, image IMGOptFour, 
                image IMGOptOneAlt, image IMGOptTwoAlt, image IMGOptThreeAlt, image IMGOptFourAlt ,int mouseX, int mouseY,
                int *pressedOne, int *pressedTwo, int *pressedThree, int *pressedFour, pauseBackground pause,int *level);

#endif