/**
 * @file mainEnigme.c
*/
#include "enigmeFichier.h"
#include "minimap.h"

/**
 * @brief runs the file Enigme minigame
 * @param screen screen
 * @return 0
*/
int Enigme(SDL_Surface*  screen)
{

    //SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    if (TTF_Init() == -1)
    {
        printf("TTf init failed %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    enigmeFichier e;
    genererEnigmeFichier("questions.txt", &e);

    SDL_Event event;

    int continuer = 1;
    int mx;
    int my;
    Uint32 starttime = SDL_GetTicks(),white = SDL_MapRGB(screen->format, 255, 255, 255);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = screen->w;
    rect.h = screen->h;
    while (continuer)
    {
        SDL_FillRect(screen, &rect, white);
        afficherBackground(e, screen);
        animation(&e, screen);
        affichertempsen(starttime);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_a:
                    e.mouse = 1;
                    break;
                case SDLK_z:
                    e.mouse = 2;
                    break;
                case SDLK_e:
                    e.mouse = 3;
                    break;
                case SDLK_RETURN:
                    switch (e.mouse)
                    {
                    case 1:
                        e.choix = 1;
                        break;
                    case 2:
                        e.choix = 2;

                        break;
                    case 3:
                        e.choix = 3;

                        break;
                    }
                    break;
                }
                break;
            case SDL_MOUSEMOTION:
                mx = event.motion.x;
                my = event.motion.y;
                if (mx > e.posbutton1.x && mx < e.posbutton1.x + 554 && my > e.posbutton1.y && my < e.posbutton1.y + 81)
                {
                    e.mouse = 1;
                }
                else if (mx > e.posbutton2.x && mx < e.posbutton2.x + 554 && my > e.posbutton2.y && my < e.posbutton2.y + 81)
                {
                    e.mouse = 2;
                }
                else if (mx > e.posbutton3.x && mx < e.posbutton3.x + 554 && my > e.posbutton3.y && my < e.posbutton3.y + 81)
                {
                    e.mouse = 3;
                }
                else
                {
                    e.mouse = 0;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (e.mouse)
                {
                case 1:
                    e.choix = 1;
                    break;
                case 2:
                    e.choix = 2;

                    break;
                case 3:
                    e.choix = 3;

                    break;
                }
                break;
            }
        }

        // partie traitement
        if (e.choix != -1)
        {

            if (e.choix == e.reponse)
            {
                e.SurfaceResultat = TTF_RenderText_Blended(e.font, " VOUS AVEZ GAGNE ", e.color2);
            }
            else
            {
                e.SurfaceResultat = TTF_RenderText_Blended(e.font, " VOUS AVEZ PERDU ", e.color2);
            }
            afficherResultat(e, screen);
            SDL_Flip(screen);
            SDL_Delay(5000);
            continuer = 0;
        }
        else
        {
            afficherEnigmeFichier(e, screen);
        }
        SDL_Flip(screen);
        // SDL_Delay(1);
    }
}