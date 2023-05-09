/**
 * @file enigmeFichier.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
/**
 * @struct EnigmeFichier
 * @brief Struct for file enigme
 * @param Background Surface
 * @param Choixbackground Surface
 * @param ChoixbackgroundSelected Surface
 * @param SurfaceQuetion Surface
 * @param SurfaceChoix1 Surface
 * @param SurfaceChoix2 Surface
 * @param SurfaceChoix3 Surface
 * @param surfaceResultat Surface
 * @param posQuesion Rectangle
 * @param PosChoix1 Rectangle
 * @param PosChoix2 Rectangle
 * @param posChoix3 Rectangle
 * @param posBackground Rectangle
 * @param posbutton1 Rectangle
 * @param posbutton2 Rectangle
 * @param posbutton3 Rectangle
 * @param posResultat Rectangle
 * @param font Font
 * @param color1 Color
 * @param color2 Color
 * @param mouse mouse position
 * @param choix choice 
 * @param animation Surface
 * @param posanimation Rectangle
 * @param posSourceAnimation Rectangle
*/
typedef struct
{
    char question[256], choix1[256], choix2[256], choix3[256];
    int reponse;
    //////////////////// image
    SDL_Surface *background;
    SDL_Surface *Choixbackground;
    SDL_Surface *ChoixbackgroundSelected;
    /////////////////////////////////
    SDL_Surface *SurfaceQuestion;
    SDL_Surface *SurfaceChoix1;
    SDL_Surface *SurfaceChoix2;
    SDL_Surface *SurfaceChoix3;
    SDL_Surface *SurfaceResultat;

    SDL_Rect posQuestion, posChoix1, posChoix2, posChoix3, posBackground, posbutton1, posbutton2, posbutton3 , posResultat;
    TTF_Font *font;
    SDL_Color color1;
    SDL_Color color2;
    int mouse;
    int choix;

    SDL_Surface * animation ;
    SDL_Rect posanimation ; 
    SDL_Rect posSourceAnimation ;

} enigmeFichier;

void genererEnigmeFichier(char *NomFichier, enigmeFichier *e);
void afficherBackground(enigmeFichier e , SDL_Surface * screen );
void afficherResultat(enigmeFichier e ,SDL_Surface * screen);
void afficherEnigmeFichier(enigmeFichier e, SDL_Surface *screen);
void animation(enigmeFichier * e , SDL_Surface * screen );
int Enigme(SDL_Surface*  screen);