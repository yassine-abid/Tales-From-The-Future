/**
 * @file main.c
 */
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "character.h"
#include "menufunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bg.h"
#include "entity.h"
#include "minimap.h"
#include "enigmeFichier.h"
#include "enigmeAlea.h"
#include "pause.h"
#include "sauv.h"
#include "arduino.h"
#include "dialogue.h"
#include <time.h>
#include "menufunctions.h"
#include "pong.h"
/**
 * @brief main functions, calls all necessary game functions
 * @return 0
 */
int main(int argc, char *argv[])

{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1)
    {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        return -1;
    }
    SDL_Surface *screen_surface = SDL_SetVideoMode(1366, 770, 32, SDL_HWSURFACE || SDL_DOUBLEBUF);
    if (screen_surface == NULL)
    {
        fprintf(stderr, "Error: Unable to set video mode. %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption("TALES FROM THE FUTURE", NULL);
    int prog = 1;
    while (prog)
    {
        int inputs[8];
        Uint32 arduinotime = 0;
        int serial_port;
        int collision = 0;
        int controlChoice = 1;
        Minimap m;
        int initialy, initialx;
        // Initialize SDL
        int level = 0;
        int updatedLevelZero = 0;
        int updatedLevelOne = 0;
        int updatedLevelTwo = 0;
        SDL_Color levelMaskColors[] = {{0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}, {0, 255, 0}};

        // Create a window

        int game = mainmenu(screen_surface, 0, 0);
        if (game >= 1)
        {
            SDL_Rect level1traps[] = {{1618, 636, 100, 10}, {2060, 636, 100, 10}, {2544, 636, 100, 20}, {7750, 636, 100, 10}, {8140, 636, 100, 10}, {9092, 636, 200, 10}, {11270, 636, 200, 10}};
            pauseBackground pause[6];
            Background b[10], mask[10], gameoverimg;
            Background dialogue[10];
            int dialogueOnecheck = 0;
            Background choice;
            int ctrlChoice;
            int choosing = 1;
            // Initialize the player
            Player player;
            Player playerTwo;
            Entity e;
            image IMGOptOne, IMGOptOneAlt, IMGOptTwo, IMGOptTwoAlt, IMGOptThree, IMGOptThreeAlt, IMGOptFour, IMGOptFourAlt;
            init_minimap(&m);
            initPauseBack(&pause[0], screen_surface, "imgs/pauseOne.png", 1);
            int offset = -600;
            initialiser_imageBOUTON(&IMGOptOne, (SCREEN_W / 2) + offset, -175, 224, 508, "oResume.png");
            initialiser_imageBOUTON(&IMGOptOneAlt, (SCREEN_W / 2) + offset, -175, 224, 508, "oResumeAlt.png");
            initialiser_imageBOUTON(&IMGOptTwo, (SCREEN_W / 2) + offset, -160, 224, 508, "oRetry.png");
            initialiser_imageBOUTON(&IMGOptTwoAlt, (SCREEN_W / 2) + offset, -160, 224, 508, "oRetryAlt.png");
            initialiser_imageBOUTON(&IMGOptThree, (SCREEN_W / 2) + offset, -145, 224, 508, "oOptions.png");
            initialiser_imageBOUTON(&IMGOptThreeAlt, (SCREEN_W / 2) + offset, -145, 224, 508, "oOptionsAlt.png");
            initialiser_imageBOUTON(&IMGOptFour, (SCREEN_W / 2) + offset, -130, 224, 508, "oQuit.png");
            initialiser_imageBOUTON(&IMGOptFourAlt, (SCREEN_W / 2) + offset, -130, 224, 508, "oQuitAlt.png");
            const char *level1[] = {"imgs/level1_1.png", "imgs/level1_2.png", "imgs/level1_3.png", "imgs/level1_4.png", "imgs/level1_5.png", "imgs/level1_6.png", "imgs/level1_7.png", "imgs/level1_8.png", "imgs/level1_9.png", "imgs/level1_10.png"};
            const char *level1mask[] = {"imgs/level 1Mask.png"};
            const char *level2[] = {"imgs/level2_1.png"};
            const char *level2partTwo[] = {"imgs/level2_2.png"};
            const char *level2mask[] = {"imgs/level 2Mask.png"};
            const char *gameoverpic[] = {"imgs/gameover.png"};
            const char *choicepic[] = {"imgs/controls.png"};
            const char *level3[] = {"imgs/level3_1.png", "imgs/level3_2.png", "imgs/level3_3.png", "imgs/level3_4.png"};
            const char *level3mask[] = {"imgs/level 3Mask.png"};
            const char *level4[] = {"imgs/level4_1.png", "imgs/level4_2.png", "imgs/level4_3.png", "imgs/level4_4.png"};
            const char *level4mask[] = {"imgs/level 4Mask.png"};
            const char *levelOneDialogue[] = {"dialogue/d1.png", "dialogue/d2.png", "dialogue/d3.png", "dialogue/d4.png", "dialogue/d5.png"};
            initBack(&gameoverimg, screen_surface, gameoverpic, 1);
            initBack(&b[0], screen_surface, level1, 10);
            initBack(&mask[0], screen_surface, level1mask, 1);
            initBack(&b[1], screen_surface, level2, 1);
            initBack(&b[2], screen_surface, level2partTwo, 1);
            initBack(&b[3], screen_surface, level3, 4);
            initBack(&b[4], screen_surface, level4, 4);
            initBack(&mask[3], screen_surface, level3mask, 1);
            initBack(&mask[1], screen_surface, level2mask, 1);
            initBack(&mask[2], screen_surface, level1mask, 1);
            initBack(&mask[4], screen_surface, level4mask, 1);
            initBack(&dialogue[0], screen_surface, levelOneDialogue, 4);
            initBack(&choice, screen_surface, choicepic, 1);
            init_players(&player, &playerTwo);
            init_e(&e, level);
            player.rect.w = 120;
            SDL_Event event;
            Uint32 last_update_time = SDL_GetTicks();
            Uint32 current_time;
            Uint32 elapsed_time;
            initialy = player.rect.y;
            SDL_Rect playerCollionCheck;
            int njump = 1;
            int dialogueframe = 0;
            int njumptwo = 1;
            int nplayer = 0;
            int playermoving;
            int isPaused = 0;
            int gameover = 0;
            int mouseX, mouseY;
            int buttonOneHovered = 0, buttonTwoHovered = 0, buttonThreeHovered = 0, buttonFourHovered = 0;
            // collision test text
            TTF_Init();
            SDL_Color textColor = {255, 255, 255};
            SDL_Surface *textSurface = NULL;
            SDL_Rect textLocation = {1000, 0, 0, 0};
            TTF_Font *font = TTF_OpenFont("04B_08__.TTF", 28);
            int intialx = 50;
            SDL_Rect actualPlayer = player.rect;
            actualPlayer.w -= 110;
            int obstacleCollision = 0;
            // b.images[0]= IMG_Load("imgs/level 1.png");
            Background levelPassed, damage;
            /*Dialogue will be transferred into a seperate function eventually*/
            int dialogueOneCheck = 0;
            // const char *dialogueOne[] = {"dialogue/dialogueOne.png"};
            // initBack(&dialogue[0], screen_surface, dialogueOne, 1);
            /*End of dialogue*/
            const char *levelPassedPic[] = {"imgs/levelpassed.png"};
            initBack(&levelPassed, screen_surface, levelPassedPic, 1);
            const char *damagePic[] = {"imgs/damage.png"};
            initBack(&damage, screen_surface, damagePic, 1);
            Mix_Chunk *mus;
            trap t1;
            const char *trap1[] = {"moving_traps/tile000.png", "moving_traps/tile001.png", "moving_traps/tile002.png", "moving_traps/tile003.png", "moving_traps/tile004.png", "moving_traps/tile005.png", "moving_traps/tile006.png", "moving_traps/tile007.png"};
            Uint32 last_damage = SDL_GetTicks();
            init_moving_trap(trap1, 1100, 610, 32, 32, 8, &t1);
            coin c[20];
            int i;
            for (i = 0; i < 20; i++)
                init_coin("imgs/coin.png", 400 + (i * 500), 570, 20, 20, 9, &c[i]);
            char score[100];
            if (game == 2)
                charger(&player, &b[level], "save.txt", &level);
            int showmp = 1;
            Uint32 animation_time = 0, start_time = SDL_GetTicks();
            int elapsed = 0;
            int levlsframeNumber[] = {9, 1, 1, 4, 4};
            cntrlChoice(&ctrlChoice, screen_surface, choice);
            // initializes arduino if ctrlchoice is 2
            if (ctrlChoice == 2)
            {
                printf("Arduino is initializing...\n");
                setup_arduino(&serial_port);
            }
            int stopScrolling = 0;
            int levelBounds[] = {15000, 12878};
            while (game >= 1)
            {

                elapsed = SDL_GetTicks() - animation_time;
                if (elapsed >= 100)
                {
                    animation_time = SDL_GetTicks();
                    animerBack(&b[level], levlsframeNumber[level]);
                }
                // SDL_BlitSurface(t1.sprite[t1.current_frame],NULL,screen_surface,&t1.pos);
                //  printf("Current level: %d", level);

                // printf("Current level: %d", level);
                if (actualPlayer.x >= 14700 && level == 0)
                {
                    afficherBack(levelPassed, screen_surface);
                    SDL_Flip(screen_surface);
                    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
                    mus = Mix_LoadWAV("game_sound/missionPassed.wav");
                    int ch = Mix_PlayChannel(-1, mus, 0);
                    SDL_Delay(10000);
                    level = 1;
                }
                // getInputs(inputs,serial_port);
                Mix_CloseAudio();
                // arduino();
                switch (level)
                {
                case 0:
                    afficherBack(b[level], screen_surface);
                    if (updatedLevelZero == 0)
                    {
                        initialy = player.rect.y;
                        initialx = player.rect.x;
                        updatedLevelZero = 1;
                        if ((level == 0) && (dialogueOneCheck == 0))
                        {
                            levelOneDlg(screen_surface, dialogue, &dialogueOneCheck, &dialogueframe,3);
                        }
                    }
                    break;
                case 1:
                    if (updatedLevelOne == 0)
                    {
                        player.rect.y = 290;
                        actualPlayer.y = 290;
                        player.rect.x = 50;
                        actualPlayer.x = 50;
                        initialy = player.rect.y;
                        initialx = player.rect.x;
                        updatedLevelOne = 1;
                    }
                    afficherBack(b[level], screen_surface);
                    break;
                case 2:
                    afficherBack(b[level], screen_surface);
                    break;
                case 3:
                    afficherBack(b[level], screen_surface);
                    break;
                case 4:
                    afficherBack(b[level], screen_surface);
                    break;
                }
                // SDL_BlitSurface(b.images[0],NULL,screen_surface,NULL);
                move_enemy(&e, actualPlayer, 2000, 4000);
                // afficher_minimap(m,screen_surface);

                MAJMinimap(player.rect, &m, b[level].camera_pos, 50);
                handlePlayerEnemyCollision(actualPlayer, e, &last_damage, &player, damage, screen_surface, t1);         // handles collision
                checkIfPlayerIsDead(&player, &gameover, &level, &updatedLevelZero, &updatedLevelOne, &updatedLevelTwo); // checks for death
                isGameOver(&gameover, &game, gameoverimg, screen_surface);

                switch (nplayer)
                {
                case 0:
                    if (ctrlChoice == 1)
                    {
                        while (SDL_PollEvent(&event))
                        {
                            switch (event.type)
                            {
                            case SDL_KEYUP:
                                switch (event.key.keysym.sym)
                                {
                                case SDLK_o:
                                    Enigme(screen_surface);
                                    break;
                                case SDLK_p:
                                    aleaMain(screen_surface);
                                    break;
                                case SDLK_i:
                                    if (showmp == 1)
                                        showmp = 0;
                                    else
                                        showmp = 1;
                                    break;
                                case SDLK_g:
                                    int a = pong(screen_surface);
                                    break;
                                case SDLK_ESCAPE:
                                    // affiherBack(pause[0], screen_surface);

                                    isPaused = 1;
                                    SDL_Flip(screen_surface);
                                    break;
                                }
                                break;
                            }

                            pauseGame(player, b[level], screen_surface, &isPaused, &event, &game, IMGOptOne, IMGOptTwo, IMGOptThree, IMGOptFour, IMGOptOneAlt, IMGOptTwoAlt, IMGOptThreeAlt, IMGOptFourAlt,
                                      mouseX, mouseY, &buttonOneHovered, &buttonTwoHovered, &buttonThreeHovered, &buttonFourHovered, pause[0], &level);
                            playermoving = playerOneMovement(&event, &player, &njump, &nplayer);
                        }
                    }
                    else if (ctrlChoice == 2)
                    {
                        while (SDL_GetTicks() - arduinotime < 20)
                            getInputs(inputs, serial_port);
                        arduinotime = SDL_GetTicks();

                        for (i = 0; i < 8; i++)
                        {
                            printf("%d", inputs[i]);
                        }
                        printf("\n");
                        playermoving = joystickMovement(inputs, &player, &njump);
                        printf("Njump outside %d\n", njump);
                    }

                    handleScrolling(playermoving, level, &player, b); // Handles scrolling
                    if (player.rect.x > 980 - 50 && stopScrolling == 0)
                        player.rect.x = 980 - 50;
                    if (player.rect.x < 50)
                    {
                        player.rect.x = 50;
                    }
                    updatePlayerPosition(&player.rect, &player.direction, player.velocity, &initialy, &njump, actualPlayer, mask[level].images[0]);
                    /*Needs to transfer into a function*/
                    if (!collisionPP(actualPlayer, mask[level].images[0], levelMaskColors[level]) && (player.direction == 0 || player.direction == 1 || player.direction == 2 || player.direction == 3 || player.direction == 4))
                    {
                        initialy += 1;
                        collision = 0;
                    }
                    if (collisionPP(actualPlayer, mask[level].images[0], levelMaskColors[level]))
                    {
                        collision = 1;
                        initialy = player.rect.y;
                    }
                    /**/
                    switch (player.direction)
                    {
                    case 1:
                        playerCollionCheck = actualPlayer;
                        playerCollionCheck.x = actualPlayer.x;
                        playerCollionCheck.y -= 20;
                        if (collisionPP(playerCollionCheck, mask[level].images[0], levelMaskColors[level]))
                        {
                            player.rect.x -= (player.velocity + 5);
                            scrolling(&b[level], LEFT, player.velocity + 5);
                        }
                        break;

                    case 2:
                        playerCollionCheck = actualPlayer;
                        playerCollionCheck.x = actualPlayer.x;
                        playerCollionCheck.y -= 20;
                        if (collisionPP(playerCollionCheck, mask[level].images[0], levelMaskColors[level]))
                        {
                            player.rect.x += (player.velocity + 5);
                            scrolling(&b[level], RIGHT, player.velocity + 5);
                        }
                        break;
                    case 3:
                        playerCollionCheck = actualPlayer;
                        playerCollionCheck.x = actualPlayer.x;
                        playerCollionCheck.y -= 20;
                        if (collisionPP(playerCollionCheck, mask[level].images[0], levelMaskColors[level]))
                        {
                            player.rect.x -= (player.velocity + 5);
                            scrolling(&b[level], LEFT, player.velocity + 5);
                        }
                        break;
                    case 4:
                        playerCollionCheck.x = actualPlayer.x;
                        playerCollionCheck.y -= 20;
                        if (collisionPP(playerCollionCheck, mask[level].images[0], levelMaskColors[level]))
                        {
                            player.rect.x += player.velocity + 5;
                            scrolling(&b[level], RIGHT, player.velocity + 5);
                        }
                        break;
                    }

                    if (player.rect.x < 50)
                        player.rect.x = 50;
                    // printf("collision : %d collisionPP %d player direction : %d\n", collision, collisionPP(actualPlayer, mask.images[0]), player.direction);
                    update_entity_animation(&e, SDL_GetTicks(), e.direction);
                    update_player_animation(&player, SDL_GetTicks(), player.direction);
                    // update_player_animation(&player, SDL_GetTicks());
                    if (level == 0)
                    {
                        for (i = 0; i < 20; i++)
                        {
                            if (collisionBB(c[i].pos, actualPlayer) && c[i].collected == 0)
                            {
                                c[i].collected = 1;
                                player.score += 10;
                                Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
                                mus = Mix_LoadWAV("game_sound/coin.wav");
                                int ch = Mix_PlayChannel(-1, mus, 0);
                            }
                            if (c[i].collected == 0)
                            {
                                animate_coin(&c[i], SDL_GetTicks());
                                print_coin(c[i], screen_surface, b[level].camera_pos);
                            }
                        }
                        for (i = 0; i < 7; i++)
                        {
                            if (level == 0)
                            {
                                if (collisionBB(level1traps[i], actualPlayer) && SDL_GetTicks() - last_damage > 1000)
                                {
                                    last_damage = SDL_GetTicks();
                                    player.health -= 1;
                                    /* if (b[level].camera_pos.x > 400)
                                    b[level].camera_pos.x -=400;
                             else b[level].camera_pos.x = 0; */
                                    afficherBack(damage, screen_surface);
                                    SDL_Flip(screen_surface);
                                    SDL_Delay(100);
                                }
                            }
                        }
                    }
                    if (showmp == 0)
                        afficher_minimap(m, screen_surface);
                    sprintf(score, "Score : %d", player.score);
                    textSurface = TTF_RenderText_Solid(font, score, textColor);
                    SDL_BlitSurface(textSurface, NULL, screen_surface, &textLocation);
                    print_player(&player, screen_surface, player.direction);
                    if (player.direction == 9 && (actualPlayer.x < (e.rect.x) && actualPlayer.x > e.rect.x - 200))
                        e.health -= 1;
                    // printf("%d %d entity direction direction : %d\n", actualPlayer.x, e.rect.x, e.direction);
                    // printf("%d\n", e.health);
                    if (e.health > 0 && level == 0)
                        print_entity(&e, screen_surface, e.direction, b[level].camera_pos);

                    animate_trap(&t1, SDL_GetTicks());
                    move_trap(&t1, 1000, 1200);
                    if (level == 0)
                        print_trap(t1, screen_surface, b[level].camera_pos);

                    draw_hearts(screen_surface, player.health);
                    Uint32 elapsedGameTime = SDL_GetTicks() - start_time;
                    affichertemps(elapsedGameTime / 1000);
                    actualPlayer.x = player.rect.x + b[level].camera_pos.x + 55;
                    actualPlayer.y = player.rect.y - 25;

                    // Update the screen
                    SDL_Flip(screen_surface);
                    // Delay to cap the frame rate
                    current_time = SDL_GetTicks();
                    elapsed_time = current_time - last_update_time;
                    if (elapsed_time < 16)
                    {
                        SDL_Delay(16 - elapsed_time);
                    }
                    last_update_time = current_time;
                    break;
                case 1: // Two players, bit of a mess for now
                    while (SDL_PollEvent(&event))
                    {
                        playerOneMovement(&event, &player, &njump, &nplayer);
                        playerTwoMovement(&event, &playerTwo, &njumptwo, &nplayer);
                    }
                    updatePlayerPosition(&player.rect, &player.direction, player.velocity, &initialy, &njump, actualPlayer, mask[level].images[0]);
                    updatePlayerPosition(&playerTwo.rect, &playerTwo.direction, playerTwo.velocity, &initialy, &njumptwo, actualPlayer, mask[level].images[0]);

                    update_player_animation(&player, SDL_GetTicks(), player.direction);
                    update_player_animation(&playerTwo, SDL_GetTicks(), playerTwo.direction);

                    // update_player_animation(&player, SDL_GetTicks());
                    print_player(&player, screen_surface, player.direction);

                    // update_playerTwo_animation(&playerTwo, SDL_GetTicks());
                    print_player(&playerTwo, screen_surface, playerTwo.direction);

                    // Update the screen
                    SDL_Flip(screen_surface);
                    // Delay to cap the frame rate
                    current_time = SDL_GetTicks();
                    elapsed_time = current_time - last_update_time;
                    if (elapsed_time < 16)
                    {
                        SDL_Delay(16 - elapsed_time);
                    }
                    last_update_time = current_time;
                    break;
                }
            }

            for (int i = 0; i < 66; i++)
            {
                SDL_FreeSurface(player.sprite[i]);
            }

            for (int i = 0; i < 66; i++)
            {
                SDL_FreeSurface(playerTwo.sprite[i]);
            }
        }
    }
    return 0;
}
