/**
 * @file enigmeAlea.c
*/
#include "enigmeAlea.h"

/**
 * @brief Generates random enigma
 * @return e enigma
*/
enigme generer()
{

    enigme e;
    int x, y;

    int s, w, a;

    srand(time(NULL));

    e.nrep = rand() % 3;
    int z = 1 + rand() % 4;
    int n = 1 + rand() % 4;
    x = rand() % 101;
    y = 1 + rand() % 101;

    s = (x) + (y);
    w = s - z;
    a = s + n;
    sprintf(e.ques, "calculer %d + %d : ", x, y);
    switch (e.nrep)
    {
    case 0:
        sprintf(e.rep1, "Reponse 1 : %.1f",(float) s);
        sprintf(e.rep2, "Reponse 2 : %.1f",(float) w);
        sprintf(e.rep3, "Reponse 3 : %.1f",(float) a);
        break;
    case 1:
        sprintf(e.rep1, "Reponse 1 : %.1f",(float) w);
        sprintf(e.rep2, "Reponse 2 : %.1f",(float) s);
        sprintf(e.rep3, "Reponse 3 : %.1f",(float) a);
        break;
    case 2:
        sprintf(e.rep1, "Reponse 1 : %.1f",(float) a);
        sprintf(e.rep2, "Reponse 2 : %.1f",(float) w);
        sprintf(e.rep3, "Reponse 3 : %.1f",(float) s);
        break;
    }
    return e;


}

/**
 * @brief initializes text
 * @param ques question
 * @param rep1 first answer
 * @param rep2 second answer
 * @param rep3 third answer
 * @return nothing
*/
void initialiser_texteEnig (texteEnig *ques,texteEnig *rep1,texteEnig *rep2,texteEnig *rep3){
    TTF_Init ();
     ques -> police =TTF_OpenFont ("OpenSans-Bold.ttf",45);
    ques -> color_txt.r=255;
    ques -> color_txt.g=255;
    ques -> color_txt.b=255;

    ques -> pos_txt.x=210;
    ques -> pos_txt.y=0;

    rep1 -> police =TTF_OpenFont ("OpenSans-Bold.ttf",45);
    rep1 -> color_txt.r=255;
    rep1 -> color_txt.g=255;
    rep1 -> color_txt.b=255;

    rep1 -> pos_txt.x=210;
    rep1 -> pos_txt.y=50;


    rep2 -> police =TTF_OpenFont ("OpenSans-Bold.ttf",45);
    rep2 -> color_txt.r=255;
    rep2 -> color_txt.g=255;
    rep2 -> color_txt.b=255;

    rep2 -> pos_txt.x=210;
    rep2 -> pos_txt.y=100;

    rep3 -> police =TTF_OpenFont ("OpenSans-Bold.ttf",45);
    rep3 -> color_txt.r=255;
    rep3 -> color_txt.g=255;
    rep3 -> color_txt.b=255;

    rep3 -> pos_txt.x=210;
    rep3 -> pos_txt.y=150;
}


/**
 * @brief displays text
 * @param screen screen
 * @param ques question
 * @param rep1 first answer
 * @param rep2 second answer
 * @param rep3 third answer
 * @return nothing
*/
void afficher_texteEnig (SDL_Surface *screen,texteEnig ques,texteEnig rep1,texteEnig rep2, texteEnig rep3){
    SDL_BlitSurface (ques.txt,NULL,screen,&ques.pos_txt);
    SDL_BlitSurface (rep1.txt,NULL,screen,&rep1.pos_txt);
    SDL_BlitSurface (rep2.txt,NULL,screen,&rep2.pos_txt);
    SDL_BlitSurface (rep3.txt,NULL,screen,&rep3.pos_txt);
}

/**
 * @brief frees text
 * @param ques question
 * @param rep1 first answer
 * @param rep2 second answer
 * @param rep3 third answer
 * @return nothing
*/
void liberer_texteEnig (texteEnig ques , texteEnig rep1, texteEnig rep2, texteEnig rep3){
    TTF_CloseFont(ques.police);
     TTF_CloseFont(rep1.police);
    TTF_CloseFont(rep2.police);
    TTF_CloseFont(rep3.police);

}

/**
 * @brief displays enigma
 * @param e enigma
 * @param ecran screen
 * @return nothing
*/
void afficherenigme(enigme e, SDL_Surface *ecran)
{
    texteEnig q,r1,r2,r3;
    initialiser_texteEnig(&q,&r1,&r2,&r3);
    q.txt = TTF_RenderText_Solid(q.police,e.ques,q.color_txt);
    r1.txt = TTF_RenderText_Solid(r1.police,e.rep1,q.color_txt);
    r2.txt = TTF_RenderText_Solid(r2.police,e.rep2,q.color_txt);
    r3.txt = TTF_RenderText_Solid(r3.police,e.rep3,q.color_txt);
    afficher_texteEnig(ecran,q,r1,r2,r3);

}

/**
 * @brief checks answer
 * @param e enigma
 * @return 1 if answer is correct, 0 if not
*/
int checkEnigme(enigme e)
{
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type)
        {
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym)
            {
            case SDLK_w:
                if (e.nrep == 0)
                {
                    return 1; 
                }
                else
                {
                    return 0;
                }
                break;
            case SDLK_x:
                if (e.nrep == 1)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
                break;
            case SDLK_c:    
                if (e.nrep == 2)
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
                break;
            }
            break;
        
        }
    }
    return -1;

    
}

/**
 * @brief displays image
 * @param screen screen
 * @param imge image
 * @return nothing
*/
void afficher_imageBTNEnig(SDL_Surface *screen, imageEnig imge)
{
    SDL_BlitSurface(imge.img, NULL, screen, &imge.pos_img_ecran);
}


/**
 * @brief initializes image
 * @param imge image
 * @param x x coordinate
 * @param y y coordinate
 * @param h height
 * @param w width
 * @param name image name
 * @return nothing
*/
void initialiser_imageBOUTONEnig(imageEnig *imge, int x, int y, int h, int w, char *name)
{
    char link[50];
    strcpy(link, "imgs/");
    strcat(link, name);
    imge->url = (link);
    imge->img = IMG_Load(imge->url);
    if (imge->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
        return;
    }
    imge->pos_img_ecran.x = x;
    imge->pos_img_ecran.y = y;
    imge->pos_img_affiche.w = h;
    imge->pos_img_affiche.h = w;
    imge->pos_img_affiche.x = x;
    imge->pos_img_affiche.y = y;
}

/**
 * @brief initializes background image
 * @param imge image
 * @param name image name
 * @return nothing
*/
void initialiser_imageBACKEnig(imageEnig *imge, char *name)
{
    char link[50];
    strcpy(link, "imgs/");
    strcat(link, name);
    imge->url = (link);
    imge->img = IMG_Load(imge->url);
    if (imge->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
        return;
    }
    imge->pos_img_ecran.x = 0;
    imge->pos_img_ecran.y = 0;
    imge->pos_img_affiche.x = 0;
    imge->pos_img_affiche.y = 0;
    imge->pos_img_affiche.h = SCREEN_H;
    imge->pos_img_affiche.w = SCREEN_W;
}

/**
 * @brief displays background
 * @param screen screen
 * @param imge image
 * @return nothing
*/
void afficher_imageBMPEnigme(SDL_Surface *screen, imageEnig imge)
{
    SDL_BlitSurface(imge.img, &imge.pos_img_affiche, screen, &imge.pos_img_ecran);
}

void cntrlChoice(int* ctrlChoice, SDL_Surface* screen_surface, Background choice) {
    int choosing = 1;
    SDL_Event event;

    while (choosing) {
        afficherBack(choice, screen_surface);
        SDL_Flip(screen_surface);
        SDL_WaitEvent(&event);
        
        switch (event.type) {
            case SDL_QUIT:
                choosing = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_k:
                        *ctrlChoice = 1;
                        choosing = 0;
                        break;
                    case SDLK_j:
                        *ctrlChoice = 2;
                        choosing = 0;
                        break;
                }
                break;
        }
    }
}
