/**
 * @file enigmeFichier.c
*/
#include "enigmeFichier.h"
#include "character.h"

/**
 * @brief Generates an Enigma
 * @param e the Enigma file
 * @param NomFichier file name
 * @return Nothing
*/
void genererEnigmeFichier(char *NomFichier, enigmeFichier *e)
{

    int compteur_ligne = 1;
    int test = 0;

    /////////////////////////////////// generation de numero question
    srand(time(NULL));
    int question_random_number = (rand() % 6) + 1;
    // int question_random_number = 1;

    printf("Random number: %d\n", question_random_number);

    /////////////////////////////////////////////////////////////////
    FILE *fp = fopen(NomFichier, "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
    }
    else
    {
        printf("opened \n");

        while (test == 0)
        {
            fscanf(fp, "%[^?]? %[^.]. %[^.]. %[^.]. %d \n", e->question, e->choix1, e->choix2, e->choix3, &(e->reponse));
            if (compteur_ligne == question_random_number)
            {
                test = 1;
            }
            else
            {
                compteur_ligne++;
            }
        }

        fclose(fp);
    }
    printf("Question: %s\n", e->question);
    printf("Choix 1: %s\n", e->choix1);
    printf("Choix 2: %s\n", e->choix2);
    printf("Choix 3: %s\n", e->choix3);
    printf("Reponse: %d\n", e->reponse);

    strcat(e->question, "?");

    e->font = TTF_OpenFont("Pixeboy.ttf", 40);
    if (e->font == NULL)
    {
        printf("Can't open font:  %s\n", SDL_GetError());
    }
    e->color1.r = 255;
    e->color1.g = 0;
    e->color1.b = 0;

    e->color2.r = 255;
    e->color2.g = 255;
    e->color2.b = 255;

    e->SurfaceQuestion = TTF_RenderText_Solid(e->font, e->question, e->color2);

    e->SurfaceChoix1 = TTF_RenderText_Solid(e->font, e->choix1, e->color1);
    e->SurfaceChoix2 = TTF_RenderText_Solid(e->font, e->choix2, e->color1);
    e->SurfaceChoix3 = TTF_RenderText_Solid(e->font, e->choix3, e->color1);

    // loading image
    e->background = IMG_Load("QuizBg.png");
    e->Choixbackground = IMG_Load("buttonoff.png");
    e->ChoixbackgroundSelected = IMG_Load("buttonOn.png");

    e->posBackground.x = 0;
    e->posBackground.y = 0;

    e->posQuestion.x = SCREEN_W / 2 - 400;
    e->posQuestion.y = 300;
    //////////////////////////////////////////////////////////// choix 1
    e->posChoix1.x = SCREEN_W / 3 + 170 - 350;
    e->posChoix1.y = SCREEN_H / 2 + 125;
    e->posbutton1.x = SCREEN_W / 3 - 350;
    e->posbutton1.y = SCREEN_H / 2 + 100;

    ////////////////////////////////////////////////////// choix 2
    e->posChoix2.x = SCREEN_W * 2 / 3 + 170 - 275;
    e->posChoix2.y = SCREEN_H / 2 + 125;
    e->posbutton2.x = SCREEN_W * 2 / 3 - 275;
    e->posbutton2.y = SCREEN_H / 2 + 100;

    /////////////////////////////////////////// choix3
    e->posChoix3.x = SCREEN_W / 2 + 170 - 350;
    e->posChoix3.y = SCREEN_H / 2 + 225;
    e->posbutton3.x = SCREEN_W / 2 - 350;
    e->posbutton3.y = SCREEN_H / 2 + 200;

    e->mouse = 0;
    e->choix = -1;
    e->posResultat.x = SCREEN_W / 2 - 200 ; 
    e->posResultat.y = SCREEN_H / 2 + 100 ;

    e->animation = IMG_Load("lmogala.png");
    e->posanimation.x = SCREEN_W / 15 ; 
    e->posanimation.y = SCREEN_H / 4 ; 
    e->posSourceAnimation.x = 0 ; 
    e->posSourceAnimation.y = 0 ; 
    e->posSourceAnimation.w = 11520 / 45 ; 
    e->posSourceAnimation.h = 256 ;  
}

/**
 * @brief Shows background
 * @param e the Enigma file
 * @param screen screen
 * @return nothing
*/
void afficherBackground(enigmeFichier e , SDL_Surface * screen )
{
    SDL_BlitSurface(e.background, NULL, screen, &e.posBackground);

}

/**
 * @brief Shows the result
 * @param e the Enigma file
 * @param screen screen
 * @return Nothing
*/
void afficherResultat(enigmeFichier e ,SDL_Surface * screen)
{
    SDL_BlitSurface(e.SurfaceResultat, NULL, screen, &e.posResultat); 

}

/**
 * @brief Shows the enigma file
 * @param e the Enigma file
 * @param screen screen
 * @return Nothing
*/
void afficherEnigmeFichier(enigmeFichier e, SDL_Surface *screen)
{
    SDL_BlitSurface(e.SurfaceQuestion, NULL, screen, &e.posQuestion);

    switch (e.mouse)
    {
    case 0:
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton1);
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton2);
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton3);
        break;

    case 1:
        SDL_BlitSurface(e.ChoixbackgroundSelected, NULL, screen, &e.posbutton1);
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton2);
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton3);
        break;

    case 2:
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton1);
        SDL_BlitSurface(e.ChoixbackgroundSelected, NULL, screen, &e.posbutton2);
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton3);
        break;

    case 3:
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton1);
        SDL_BlitSurface(e.Choixbackground, NULL, screen, &e.posbutton2);
        SDL_BlitSurface(e.ChoixbackgroundSelected, NULL, screen, &e.posbutton3);
        break;
    }
    SDL_BlitSurface(e.SurfaceChoix1, NULL, screen, &e.posChoix1);

    SDL_BlitSurface(e.SurfaceChoix2, NULL, screen, &e.posChoix2);

    SDL_BlitSurface(e.SurfaceChoix3, NULL, screen, &e.posChoix3);
}

/**
 * @brief Animation function
 * @param e the Enigma file
 * @param screen screen
 * @return Nothing
*/
void animation(enigmeFichier * e , SDL_Surface * screen )
{
    if (e->posSourceAnimation.x <= 11520)
    {
        e->posSourceAnimation.x += 11520/45 ; 
    }
    else 
    e->posSourceAnimation.x = 0 ; 

    
    SDL_BlitSurface(e->animation , &(e->posSourceAnimation) , screen , &(e->posanimation));

}
