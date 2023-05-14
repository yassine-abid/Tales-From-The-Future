#include "pause.h"

void afficher_imageOPTBTN(SDL_Surface **screen, image imge)
{
    SDL_BlitSurface(imge.img, NULL, *screen, &imge.pos_img_ecran);
}

void display_button_images(SDL_Surface **screen_surface,
                           image button_one, image button_one_alt, int button_one_hovered,
                           image button_two, image button_two_alt, int button_two_hovered,
                           image button_three, image button_three_alt, int button_three_hovered,
                           image button_four, image button_four_alt, int button_four_hovered)
{

    if (button_one_hovered)
    {
        afficher_imageOPTBTN(&(*screen_surface), button_one_alt);
    }
    else
    {
        afficher_imageOPTBTN(&(*screen_surface), button_one);
    }

    if (button_two_hovered)
    {
        afficher_imageOPTBTN(&(*screen_surface), button_two_alt);
    }
    else
    {
        afficher_imageOPTBTN(&(*screen_surface), button_two);
    }

    if (button_three_hovered)
    {
        afficher_imageOPTBTN(&(*screen_surface), button_three_alt);
    }
    else
    {
        afficher_imageOPTBTN(&(*screen_surface), button_three);
    }

    if (button_four_hovered)
    {
        afficher_imageOPTBTN(&(*screen_surface), button_four_alt);
    }
    else
    {
        afficher_imageOPTBTN(&(*screen_surface), button_four);
    }
    SDL_Flip(*screen_surface);
}

void initPauseBack(pauseBackground *b, SDL_Surface *screen, const char *paths, int numImages)
{
    SDL_Surface *temp = NULL;
    for (int i = 0; i < numImages; i++)
    {
        temp = IMG_Load(paths);
        b->images[i] = SDL_DisplayFormatAlpha(temp);
    }
    b->rect.x = 0;
    b->rect.y = 0;

    b->rect.w = screen->w;
    b->rect.h = screen->h;

    b->camera_pos.x = 0;
    b->camera_pos.y = 0;
    b->camera_pos.h = b->rect.h;
    b->camera_pos.w = b->rect.w;

    b->direction = 0;

    b->currentImageIndex = 0;
}

void afficherPauseBack(pauseBackground b, SDL_Surface *screen)
{
    SDL_BlitSurface(b.images[b.currentImageIndex], &b.camera_pos, screen, &b.rect);
}

void pauseGame(Player p, Background b, SDL_Surface *screen_surface, int *isPaused, SDL_Event *event, int *game, image IMGOptOne, image IMGOptTwo, image IMGOptThree, image IMGOptFour,
               image IMGOptOneAlt, image IMGOptTwoAlt, image IMGOptThreeAlt, image IMGOptFourAlt, int mouseX, int mouseY,
               int *pressedOne, int *pressedTwo, int *pressedThree, int *pressedFour, pauseBackground pause,int *level)
{
    int xOneLowOffset = 475, yOneLowOffset = 430, xOneHighOffset = 777, yOneHighOffset = 485;
    int xTwoLowOffset = 528, yTwoLowOffset = 545, xTwoHighOffset = 727, yTwoHighOffset = 600;
    int xThreeLowOffset = 472, yThreeLowOffset = 650, xThreeHighOffset = 762, yThreeHighOffset = 695;
    int xFourLowOffset = 387, yFourLowOffset = 770, xFourHighOffset = 907, yFourHighOffset = 830;
    int options;
    while (*isPaused)
    {
        afficherPauseBack(pause, screen_surface);
        display_button_images(&screen_surface, IMGOptOne, IMGOptOneAlt, *pressedOne,
                              IMGOptTwo, IMGOptTwoAlt, *pressedTwo,
                              IMGOptThree, IMGOptThreeAlt, *pressedThree,
                              IMGOptFour, IMGOptFourAlt, *pressedFour);
        while (SDL_PollEvent(event))
        {
            switch (event->type)
            {
            case SDL_KEYUP:
                switch (event->key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    *isPaused = 0;
                    break;
                }
                break;
            case SDL_QUIT:
                *isPaused = 0;
                *game = 0;
                break;
            case SDL_MOUSEBUTTONDOWN: // mouse click
                /*printf("CLICK\n");
                printf("Button position: %d, %d\n", IMGOptOne.pos_img_ecran.x, IMGOptOne.pos_img_ecran.y);
                printf("Button Two position: %d, %d\n", IMGOptTwo.pos_img_ecran.x, IMGOptTwo.pos_img_ecran.y);
                printf("Button Three position: %d, %d\n", IMGOptThree.pos_img_ecran.x, IMGOptThree.pos_img_ecran.y);
                printf("Button Four position: %d, %d\n", IMGOptFour.pos_img_ecran.x, IMGOptFour.pos_img_ecran.y);
                printf("%d <= xOne <= %d\n", IMGOptOne.pos_img_ecran.x + xOneLowOffset, IMGOptOne.pos_img_ecran.x + xOneHighOffset);
                printf("%d <= yOne <= %d\n", IMGOptOne.pos_img_ecran.y + yOneLowOffset, IMGOptOne.pos_img_ecran.y + yOneHighOffset);
                printf("%d <= xTwo <= %d\n", IMGOptTwo.pos_img_ecran.x + xTwoLowOffset, IMGOptTwo.pos_img_ecran.x + xTwoHighOffset);
                printf("%d <= yTwo <= %d\n", IMGOptTwo.pos_img_ecran.y + yTwoLowOffset, IMGOptTwo.pos_img_ecran.y + yTwoHighOffset);
                printf("%d <= xThree <= %d\n", IMGOptThree.pos_img_ecran.x + xThreeLowOffset, IMGOptThree.pos_img_ecran.x + xThreeHighOffset);
                printf("%d <= yThree <= %d\n", IMGOptThree.pos_img_ecran.y + yThreeLowOffset, IMGOptThree.pos_img_ecran.y + yThreeHighOffset);
                printf("%d <= xFour <= %d\n", IMGOptFour.pos_img_ecran.x + xFourLowOffset, IMGOptFour.pos_img_ecran.x + xFourHighOffset);
                printf("%d <= yFour <= %d\n", IMGOptFour.pos_img_ecran.y + yFourLowOffset, IMGOptFour.pos_img_ecran.y + yFourHighOffset);*/
                if (event->button.button == SDL_BUTTON_LEFT &&
                    event->motion.y <= IMGOptOne.pos_img_ecran.y + yOneHighOffset &&
                    event->motion.y >= IMGOptOne.pos_img_ecran.y + yOneLowOffset &&
                    event->motion.x <= IMGOptOne.pos_img_ecran.x + xOneHighOffset && event->motion.x >= IMGOptOne.pos_img_ecran.x + xOneLowOffset)
                {
                    //printf("Button one pressed\n");
                    *isPaused = 0;
                    return;
                }
                if (event->button.button == SDL_BUTTON_LEFT &&
                    event->motion.y <= IMGOptTwo.pos_img_ecran.y + yTwoHighOffset &&
                    event->motion.y >= IMGOptTwo.pos_img_ecran.y + yTwoLowOffset &&
                    event->motion.x <= IMGOptTwo.pos_img_ecran.x + xTwoHighOffset && event->motion.x >= IMGOptTwo.pos_img_ecran.x + xTwoLowOffset)
                {
                    //printf("Button two pressed\n");
                    return;
                }
                if (event->button.button == SDL_BUTTON_LEFT &&
                    event->motion.y <= IMGOptThree.pos_img_ecran.y + yThreeHighOffset &&
                    event->motion.y >= IMGOptThree.pos_img_ecran.y + yThreeLowOffset &&
                    event->motion.x <= IMGOptThree.pos_img_ecran.x + xThreeHighOffset && event->motion.x >= IMGOptThree.pos_img_ecran.x + xThreeLowOffset)
                {
                    options = mainmenu(screen_surface, 2, *isPaused);
                    if (options == -1)
                    {
                        *isPaused = 1;
                    }
                    return;
                }
                if (event->button.button == SDL_BUTTON_LEFT &&
                    event->motion.y <= IMGOptFour.pos_img_ecran.y + yFourHighOffset &&
                    event->motion.y >= IMGOptFour.pos_img_ecran.y + yFourLowOffset &&
                    event->motion.x <= IMGOptFour.pos_img_ecran.x + xFourHighOffset && event->motion.x >= IMGOptFour.pos_img_ecran.x + xFourLowOffset)
                {
                    //printf("Button four pressed\n");
                    sauvegarder(p,b,"save.txt",*level);
                    *isPaused = 0;
                    *game = 0;
                    return;
                }

                break;
            case SDL_MOUSEMOTION:
                mouseX = event->motion.x;
                mouseY = event->motion.y;
                //printf("Current mouse position: %d, %d\n", mouseX, mouseY);
                if (event->motion.y <= IMGOptOne.pos_img_ecran.y + yOneHighOffset &&
                    event->motion.y >= IMGOptOne.pos_img_ecran.y + yOneLowOffset &&
                    event->motion.x <= IMGOptOne.pos_img_ecran.x + xOneHighOffset && event->motion.x >= IMGOptOne.pos_img_ecran.x + xOneLowOffset)
                {
                    // printf("Button one Hovered\n");
                    *pressedOne = 1;
                }
                else
                {
                    *pressedOne = 0;
                }
                if (event->motion.y <= IMGOptTwo.pos_img_ecran.y + yTwoHighOffset &&
                    event->motion.y >= IMGOptTwo.pos_img_ecran.y + yTwoLowOffset &&
                    event->motion.x <= IMGOptTwo.pos_img_ecran.x + xTwoHighOffset && event->motion.x >= IMGOptTwo.pos_img_ecran.x + xTwoLowOffset)
                {
                    // printf("Button two Hovered\n");
                    *pressedTwo = 1;
                }
                else
                {
                    *pressedTwo = 0;
                }
                if (event->motion.y <= IMGOptThree.pos_img_ecran.y + yThreeHighOffset &&
                    event->motion.y >= IMGOptThree.pos_img_ecran.y + yThreeLowOffset &&
                    event->motion.x <= IMGOptThree.pos_img_ecran.x + xThreeHighOffset && event->motion.x >= IMGOptThree.pos_img_ecran.x + xThreeLowOffset)
                {
                    // printf("Button three Hovered\n");
                    *pressedThree = 1;
                }
                else
                {
                    *pressedThree = 0;
                }
                if (event->motion.y <= IMGOptFour.pos_img_ecran.y + yFourHighOffset &&
                    event->motion.y >= IMGOptFour.pos_img_ecran.y + yFourLowOffset &&
                    event->motion.x <= IMGOptFour.pos_img_ecran.x + xFourHighOffset && event->motion.x >= IMGOptFour.pos_img_ecran.x + xFourLowOffset)
                {
                    // printf("Button four Hovered\n");
                    *pressedFour = 1;
                }
                else
                {
                    *pressedFour = 0;
                }
                break;
            }
            SDL_Flip(screen_surface);
        }
    }
}

void isGameOver(int* gameover, int* game, Background gameoverimg, SDL_Surface* screen_surface) {
    if (*gameover)
    {
        *game = 0;
        afficherBack(gameoverimg, screen_surface);
        SDL_Flip(screen_surface);
        SDL_Delay(5000);
        *gameover = 0;
        // *game = mainmenu(screen_surface, 0, isPaused);
    }
}
