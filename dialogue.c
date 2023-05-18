#include "dialogue.h"

void levelDlg(SDL_Surface *screen, Background *dialogue, int *dialogueCheck, int *i, int maxframe)
{
    printf("Func entry\n");
    int inDialogue = 1;
    SDL_Event event;
    while (inDialogue)
    {
        SDL_WaitEvent(&event);
        afficherDialogue(*dialogue, screen, *i);
        printf("i = %d\n", *i);
        SDL_Flip(screen);
        if (*i >= maxframe) // end of dialogue
        {
            SDL_Delay(2500);
            *i = *(i) + 1;
            *dialogueCheck = 1;
            inDialogue = 0;
        }
        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Quit();
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE: // skip dialogue
                *dialogueCheck = 1;
                inDialogue = 0;
                *i = maxframe + 1;
                break;
            case SDLK_RIGHT:
                *i = *(i) + 1;
                break;
            }
        }
    }
}

void afficherDialogue(Background b, SDL_Surface *screen, int i)
{
    SDL_BlitSurface(b.images[i], &b.camera_pos, screen, &b.rect);
}