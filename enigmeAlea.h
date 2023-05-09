/**
 * @file enigmeAlea.h
*/
#ifndef ENIGMEALEA_H_INCLUDED
#define ENIGMEALEA_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <time.h>
#define SCREEN_H 770
#define SCREEN_W 1366

/**
 * @struct enigme
 * @brief struct for random enigma
 * @param ques question
 * @param rep1 first answer
 * @param rep2 second answer
 * @param rep3 third answer
 * @param nrep correct answer
*/
typedef struct{
    char ques[100];
    char rep1[100];
    char rep2[100];
    char rep3[100];
    int nrep;
}enigme;

/**
 * @struct imageEnig
 * @brief struct for image
 * @param url image path
 * @param pos_img_affiche position of image to display
 * @param pos_img_ecran position of image on screen
 * @param img image
*/
typedef struct {
    char *url;
    SDL_Rect pos_img_affiche;
    SDL_Rect pos_img_ecran;
    SDL_Surface *img;
}imageEnig;

/**
 * @struct texteEnig
 * @brief struct for text
 * @param txt text
 * @param pos_txt position of text
 * @param color_txt color of text
 * @param police font
*/
typedef struct {
    SDL_Surface *txt;
    SDL_Rect pos_txt;
    SDL_Colour color_txt;
    TTF_Font *police;
}texteEnig;

enigme generer();
void afficherenigme(enigme e, SDL_Surface*ecran);
int checkEnigme(enigme e);
void afficher_imageBTNEnig(SDL_Surface *screen, imageEnig imge);
void initialiser_imageBOUTONEnig(imageEnig *imge, int x, int y, int h, int w, char *name);
void initialiser_imageBACKEnig(imageEnig *imge, char *name);
void afficher_imageBMPEnigme(SDL_Surface *screen, imageEnig imge);

#endif
