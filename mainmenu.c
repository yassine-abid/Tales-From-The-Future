#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "menufunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// main function
int mainmenu(SDL_Surface *screen, int menu, int isPaused)
{
    int frame = 0;
    int volume = MIX_MAX_VOLUME - 76;
    image IMAGE_BTN1, IMAGE_BTN2, IMAGE_BTN1_alt, IMAGE_BTN2_alt;
    image IMAGE_BTN3, IMAGE_BTN4, IMAGE_BTN3_alt, IMAGE_BTN4_alt;
    image IMAGE_BTN5, IMAGE_BTN5_alt;
    image LOGO;
    image IMGCREDITS;
    image labelVol, labelScreen;
    image IMAGE[8];
    image gameSelect;
    image IMAGElevelOne, IMAGESPLASH;
    image IMAGERETURN;
    image sndButton[5];
    image sndCtrlButton[4];
    image screenCtrlButton[4];
    Mix_Music *music;
    Mix_Chunk *mus;
    texte txte;
    SDL_Event event;
    TTF_Font *font;
    int channel;
    TTF_Init();
    font = TTF_OpenFont("OpenSans-Bold.ttf", 100);
    int mouseX = 0;
    int mouseY = 0;
    int boucle = 1;
    int sfxPlayedOne = 0, sfxPlayedTwo = 0, sfxPlayedThree = 0, sfxPlayedFour = 0, sfxPlayedFive = 0;
    int buttonOneHovered = 0; // 0 = normal, 1 = hovered (for button one)
                              // Initialization, if it fails program exits
    int buttonTwoHovered = 0; // same as button One but for button two
    int buttonThreeHovered = 0;
    int buttonFourHovered = 0;
    int buttonFiveHovered = 0;
    int volPlusHovered = 0;
    int volMinusHovered = 0;
    int fsnHovered = 0;
    int wndHovered = 0;

    // initialization function calls
    char buttonOne[25], buttonOneAlt[25], buttonTwo[25], buttonTwoAlt[25], buttonThree[25], buttonThreeAlt[25], buttonFour[25], buttonFourAlt[25];
    SDL_Rect buttonsHitbox[5] = {{100, 370, 250, 30}, {100, 430, 250, 30}, {100, 490, 250, 30}, {100, 550, 250, 30}, {100, 610, 250, 30}};
    // Calling for the following function should include the image variable, x,y,h,w, and the image name
    initialiser_imageBOUTON(&IMAGE_BTN1, 0, 0, 224, 508, "newgame.png");
    initialiser_imageBOUTON(&IMAGE_BTN2, 0, 0, 224, 508, "LOADGAME.png");
    initialiser_imageBOUTON(&IMAGE_BTN3, 0, 0, 224, 508, "options.png");
    initialiser_imageBOUTON(&IMAGE_BTN4, 0, 0, 224, 508, "credits.png");
    initialiser_imageBOUTON(&IMAGE_BTN5, 0, 0, 224, 508, "Exit.png");
    initialiser_imageBOUTON(&LOGO, 0, 0, 224, 508, "logo.png");
    initialiser_imageBOUTON(&IMAGE_BTN1_alt, 0, 0, 224, 508, "newgameAlt.png");
    initialiser_imageBOUTON(&IMAGE_BTN2_alt, 0, 0, 224, 508, "loadGameAlt.png");
    initialiser_imageBOUTON(&IMAGE_BTN3_alt, 0, 0, 224, 508, "optionsAlt.png");
    initialiser_imageBOUTON(&IMAGE_BTN4_alt, 0, 0, 224, 508, "creditsAlt.png");
    initialiser_imageBOUTON(&IMAGE_BTN5_alt, 0, 0, 224, 508, "ExitAlt.png");
    initialiser_imageBOUTON(&IMAGERETURN, 0, 0, 112, 200, "return.png");
    initialiser_imageBOUTON(&sndButton[0], SCREEN_H - 470, SCREEN_W - 966, 77, 384, "frame_0_delay-0.2s.png");
    initialiser_imageBOUTON(&sndButton[1], SCREEN_H - 470, SCREEN_W - 966, 77, 384, "frame_1_delay-0.2s.png");
    initialiser_imageBOUTON(&sndButton[2], SCREEN_H - 470, SCREEN_W - 966, 77, 384, "frame_2_delay-0.2s.png");
    initialiser_imageBOUTON(&sndButton[3], SCREEN_H - 470, SCREEN_W - 966, 77, 384, "frame_3_delay-0.2s.png");
    initialiser_imageBOUTON(&sndButton[4], SCREEN_H - 470, SCREEN_W - 966, 77, 384, "frame_4_delay-0.2s.png");
    initialiser_imageBOUTON(&sndCtrlButton[0], SCREEN_H - 70, SCREEN_W - 966, 77, 160, "plus.png");
    initialiser_imageBOUTON(&sndCtrlButton[1], SCREEN_H - 70, SCREEN_W - 966, 77, 160, "plusAlt.png");
    initialiser_imageBOUTON(&sndCtrlButton[2], SCREEN_H + 100, SCREEN_W - 966, 77, 160, "minus.png");
    initialiser_imageBOUTON(&sndCtrlButton[3], SCREEN_H + 100, SCREEN_W - 966, 77, 160, "minusAlt.png");
    initialiser_imageBOUTON(&screenCtrlButton[0], SCREEN_H - 470, SCREEN_W - 966 - 100, 83, 164, "fullscreen.png");
    initialiser_imageBOUTON(&screenCtrlButton[1], SCREEN_H - 470, SCREEN_W - 966 - 100, 83, 164, "fullscreenAlt.png");
    initialiser_imageBOUTON(&screenCtrlButton[2], SCREEN_H - 470 + 200, SCREEN_W - 966 - 100, 83, 164, "windowed.png");
    initialiser_imageBOUTON(&screenCtrlButton[3], SCREEN_H - 470 + 200, SCREEN_W - 966 - 100, 83, 164, "windowedAlt.png");
    initialiser_imageBOUTON(&labelVol, 0, SCREEN_W - 966, 83, 310, "volume.png");
    initialiser_imageBOUTON(&labelScreen, 0, SCREEN_W - 966 - 100, 83, 310, "dsiplay.png");

    // The following functions initialize background images
    initialiser_imageBACK(&IMAGE[0], "bg1.png");
    initialiser_imageBACK(&IMAGE[1], "bg2.png");
    initialiser_imageBACK(&IMAGE[2], "bg3.png");
    initialiser_imageBACK(&IMAGE[3], "bg4.png");
    initialiser_imageBACK(&IMAGE[4], "bg5.png");
    initialiser_imageBACK(&IMAGE[5], "bg6.png");
    initialiser_imageBACK(&IMAGE[6], "bg7.png");
    initialiser_imageBACK(&IMAGE[7], "bg8.png");
    initialiser_imageBACK(&gameSelect, "gameSelect.png");
    initialiser_imageBACK(&IMAGESPLASH, "splash.png");       // initializes the splash art screen
    initialiser_imageBACK(&IMGCREDITS, "creditsSplash.png"); // initializes the credit screen
    initialiser_levelOne(&IMAGElevelOne);                    // initializes first level
    // initialiser_audio(music); (this function includes the playing of the sound, therefore it will be in the loop until we seperate them in two different functions)
    image gameSplash[100];
    image teamSplash[245];
    char link[100];
    initialiser_texte(&txte); // initializes the title
    if (menu == 0)
    {
        // afficher_imageBMP(screen, IMAGESPLASH); // initializes the team's splash art
        Uint32 splashtime = 0;
        /*for (int i = 0; i < 100; i++)
        {
            sprintf(link, "intro/%04d.png", i + 1);
            initialiser_imageBACK(&gameSplash[i], link);
            afficher_imageBMP(screen, gameSplash[i]);
            SDL_Flip(screen);
            liberer_image(gameSplash[i]);
        }
        for (int i = 0; i < 245; i++)
        {
            sprintf(link, "tintro/intro%04d.png", i + 1);
            initialiser_imageBACK(&teamSplash[i], link);
            afficher_imageBMP(screen, teamSplash[i]);
            SDL_Flip(screen);
            liberer_image(teamSplash[i]);
        }*/
    }

    SDL_Flip(screen);
    SDL_Delay(1500);
    // main loop
    while (boucle)
    {
        switch (menu) // Switch controls screen printings
        {
        case 0: // case 0 is the main menu
            // PrintMousePosition(screen, font, mouseX, mouseY); // These two lines show mouse positioning, commment if not needed
            // SDL_UpdateRect(screen, 0, 0, 0, 0);               // Line two
            if (Mix_PlayingMusic() == 0) // Checks if the music is not playing, if not it plays it
            {
                initialiser_audio(music);
            }
            printBG(screen, IMAGE, &frame); // Does the animation for the background
            //afficher_texte(screen, txte);   // Prints the game's title
            afficher_imageBTN(screen, LOGO); // Prints the play button
            // The following if, else section handles the hovering mechanic of the buttons
            if (buttonOneHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN1);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN1_alt);
            }
            if (buttonTwoHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN2);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN2_alt);
            }
            if (buttonThreeHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN3);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN3_alt);
            }
            if (buttonFourHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN4);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN4_alt);
            }
            if (buttonFiveHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN5);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN5_alt);
            }

            // second loop, reads events
            while (SDL_PollEvent(&event))
            {
                // different options for menu
                switch (event.type)
                {
                case SDL_QUIT: // quits the game
                    boucle = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN: // mouse click
                    if (event.button.button == SDL_BUTTON_LEFT &&
                        event.motion.y <= buttonsHitbox[4].y + buttonsHitbox[4].h &&
                        event.motion.y >= buttonsHitbox[4].y &&
                        event.motion.x <= buttonsHitbox[4].x + buttonsHitbox[4].w && event.motion.x >= buttonsHitbox[4].x)
                    {
                        boucle = 0;
                    }
                    if (event.button.button == SDL_BUTTON_LEFT &&
                        event.motion.y <= buttonsHitbox[0].y + buttonsHitbox[0].h &&
                        event.motion.y >= buttonsHitbox[0].y &&
                        event.motion.x <= buttonsHitbox[0].x + buttonsHitbox[0].w && event.motion.x >= buttonsHitbox[0].x)
                    {
                        menu = 1;
                    }
                    if (event.button.button == SDL_BUTTON_LEFT &&
                        event.motion.y <= buttonsHitbox[2].y + buttonsHitbox[2].h &&
                        event.motion.y >= buttonsHitbox[2].y &&
                        event.motion.x <= buttonsHitbox[2].x + buttonsHitbox[2].w && event.motion.x >= buttonsHitbox[2].x)
                    {
                        menu = 2;
                    }
                    if (event.button.button == SDL_BUTTON_LEFT &&
                        event.motion.y <= buttonsHitbox[3].y + buttonsHitbox[3].h &&
                        event.motion.y >= buttonsHitbox[3].y &&
                        event.motion.x <= buttonsHitbox[3].x + buttonsHitbox[3].w && event.motion.x >= buttonsHitbox[3].x)
                    {
                        menu = 3;
                    }
                    if(event.button.button == SDL_BUTTON_LEFT &&
                        event.motion.y <= buttonsHitbox[1].y + buttonsHitbox[1].h &&
                        event.motion.y >= buttonsHitbox[1].y &&
                        event.motion.x <= buttonsHitbox[1].x + buttonsHitbox[1].w && event.motion.x >= buttonsHitbox[1].x)
                    {
                        menu = 4;
                    }
                    // Mouse button clicks on specific regions, proceeds elsewhere
                    break;
                case SDL_MOUSEMOTION: // mouse moving
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    if (event.motion.y <= buttonsHitbox[0].y + buttonsHitbox[0].h &&
                        event.motion.y >= buttonsHitbox[0].y &&
                        event.motion.x <= buttonsHitbox[0].x + buttonsHitbox[0].w && event.motion.x >= buttonsHitbox[0].x)
                    {
                        buttonOneHovered = 1;
                        if (sfxPlayedOne == 0)
                        {
                            channel = initialiser_audiobref(mus, "Hover.wav");
                            sfxPlayedOne = 1;
                        }
                    }
                    else
                    {
                        sfxPlayedOne = 0;
                        buttonOneHovered = 0;
                    }
                    if (event.motion.y <= buttonsHitbox[1].y + buttonsHitbox[1].h &&
                        event.motion.y >= buttonsHitbox[1].y &&
                        event.motion.x <= buttonsHitbox[1].x + buttonsHitbox[1].w && event.motion.x >= buttonsHitbox[1].x)
                    {
                        buttonTwoHovered = 1;
                        if (sfxPlayedTwo == 0)
                        {
                            channel = initialiser_audiobref(mus, "Hover.wav");
                            sfxPlayedTwo = 1;
                        }
                    }
                    else
                    {
                        sfxPlayedTwo = 0;
                        buttonTwoHovered = 0;
                    }
                    if (event.motion.y <= buttonsHitbox[2].y + buttonsHitbox[2].h &&
                        event.motion.y >= buttonsHitbox[2].y &&
                        event.motion.x <= buttonsHitbox[2].x + buttonsHitbox[2].w && event.motion.x >= buttonsHitbox[2].x)
                    {
                        buttonThreeHovered = 1;
                        if (sfxPlayedThree == 0)
                        {
                            channel = initialiser_audiobref(mus, "Hover.wav");
                            sfxPlayedThree = 1;
                        }
                    }
                    else
                    {
                        sfxPlayedThree = 0;
                        buttonThreeHovered = 0;
                    }
                    if (event.motion.y <= buttonsHitbox[3].y + buttonsHitbox[3].h &&
                        event.motion.y >= buttonsHitbox[3].y &&
                        event.motion.x <= buttonsHitbox[3].x + buttonsHitbox[3].w && event.motion.x >= buttonsHitbox[3].x)
                    {
                        buttonFourHovered = 1;
                        if (sfxPlayedFour == 0)
                        {
                            channel = initialiser_audiobref(mus, "Hover.wav");
                            sfxPlayedFour = 1;
                        }
                    }
                    else
                    {
                        sfxPlayedFour = 0;
                        buttonFourHovered = 0;
                    }
                    if(event.motion.y <= buttonsHitbox[4].y + buttonsHitbox[4].h &&
                        event.motion.y >= buttonsHitbox[4].y &&
                        event.motion.x <= buttonsHitbox[4].x + buttonsHitbox[4].w && event.motion.x >= buttonsHitbox[4].x)
                    {
                        buttonFiveHovered = 1;
                        if (sfxPlayedFive == 0)
                        {
                            channel = initialiser_audiobref(mus, "Hover.wav");
                            sfxPlayedFive = 1;
                        }
                    }
                    else
                    {
                        sfxPlayedFive = 0;
                        buttonFiveHovered = 0;
                    }
                    // mouse hovers over specific regions, plays sound
                    break;
                }
            }
            SDL_Flip(screen); // Updates the screen
            break;
        case 1:               // Case 1 is the game's window
            Mix_CloseAudio(); // Turns off the menu's music, later on there will be the level's music added
            return 1;         // Returns 1 to the main function, which will then start the game    
            break;
        case 2:                                     // Case 2 is the setting's window
            afficher_imageBMP(screen, IMAGE[0]);    // Setting's background
            afficher_imageBTN(screen, IMAGERETURN); // Return button
            // the if else section controls the hovering effect over the plus, the minus buttons and the full screen and windowed buttons
            if (volPlusHovered == 0)
                afficher_imageBTN(screen, sndCtrlButton[0]);
            else
                afficher_imageBTN(screen, sndCtrlButton[1]);
            if (volMinusHovered == 0)
                afficher_imageBTN(screen, sndCtrlButton[2]);
            else
                afficher_imageBTN(screen, sndCtrlButton[3]);
            // full screen buttons (WIP)
            if (fsnHovered == 0)
                afficher_imageBTN(screen, screenCtrlButton[0]);
            else
                afficher_imageBTN(screen, screenCtrlButton[1]);
            if (wndHovered == 0)
                afficher_imageBTN(screen, screenCtrlButton[2]);
            else
                afficher_imageBTN(screen, screenCtrlButton[3]);
            // this if else section handles the volume slider
            if (volume >= 0 && volume < 20)
            {
                afficher_imageBTN(screen, sndButton[0]);
                SDL_Delay(200);
            }
            else if (volume >= 20 && volume < 40)
            {
                afficher_imageBTN(screen, sndButton[1]);
                SDL_Delay(200);
            }
            else if (volume >= 40 && volume < 60)
            {
                afficher_imageBTN(screen, sndButton[2]);
                SDL_Delay(200);
            }
            else if (volume >= 60 && volume < 80)
            {
                afficher_imageBTN(screen, sndButton[3]);
                SDL_Delay(200);
            }
            else if (volume >= 80 && volume <= 100)
            {
                afficher_imageBTN(screen, sndButton[4]);
                SDL_Delay(200);
            }
            afficher_imageBTN(screen, labelVol);
            afficher_imageBTN(screen, labelScreen);

            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_MOUSEBUTTONDOWN: // clicking on buttons
                    if (event.button.button == SDL_BUTTON_LEFT && event.motion.x >= 0 && event.motion.x <= 200 && event.motion.y >= 0 && event.motion.y <= 112)
                    {
                        if (isPaused)
                        {
                            return -1;
                        }
                        else
                        {
                            menu = 0;
                        }
                    }
                    if (event.button.button == SDL_BUTTON_LEFT && event.motion.x >= SCREEN_H - 70 && event.motion.x <= SCREEN_H - 70 + 160 &&
                        event.motion.y >= 375 && event.motion.y <= 450)
                        increaseVolume(&volume); // volume increase

                    if (event.button.button == SDL_BUTTON_LEFT && event.motion.x >= SCREEN_H + 100 && event.motion.x <= SCREEN_H + 100 + 160 &&
                        event.motion.y >= 375 && event.motion.y <= 450)
                        decreaseVolume(&volume); // volume decrease

                    if (event.button.button = SDL_BUTTON_LEFT && event.motion.x >= screenCtrlButton[0].pos_img_ecran.x && event.motion.x <= screenCtrlButton[0].pos_img_ecran.x + 164 &&
                                              event.motion.y >= screenCtrlButton[0].pos_img_ecran.y && event.motion.y <= screenCtrlButton[0].pos_img_ecran.y + 86)
                    {
                        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                    }
                    if (event.button.button = SDL_BUTTON_LEFT && event.motion.x >= screenCtrlButton[2].pos_img_ecran.x && event.motion.x <= screenCtrlButton[2].pos_img_ecran.x + 164 &&
                                              event.motion.y >= screenCtrlButton[2].pos_img_ecran.y && event.motion.y <= screenCtrlButton[2].pos_img_ecran.y + 86)
                    {
                        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                    }
                    break;
                case SDL_QUIT: // quits game
                    boucle = 0;
                    break;
                case SDL_MOUSEMOTION: // mouse moving
                    if (event.motion.x >= SCREEN_H - 70 && event.motion.x <= SCREEN_H - 70 + 160 &&
                        event.motion.y >= 375 && event.motion.y <= 450)
                        volPlusHovered = 1;
                    else
                        volPlusHovered = 0;

                    if (event.motion.x >= SCREEN_H + 100 && event.motion.x <= SCREEN_H + 100 + 160 &&
                        event.motion.y >= 375 && event.motion.y <= 450)
                        volMinusHovered = 1;
                    else
                        volMinusHovered = 0;

                    if (event.button.button = SDL_BUTTON_LEFT && event.motion.x >= screenCtrlButton[0].pos_img_ecran.x && event.motion.x <= screenCtrlButton[0].pos_img_ecran.x + 164 &&
                                              event.motion.y >= screenCtrlButton[0].pos_img_ecran.y && event.motion.y <= screenCtrlButton[0].pos_img_ecran.y + 86)
                        fsnHovered = 1;
                    else
                        fsnHovered = 0;

                    if (event.button.button = SDL_BUTTON_LEFT && event.motion.x >= screenCtrlButton[2].pos_img_ecran.x && event.motion.x <= screenCtrlButton[2].pos_img_ecran.x + 164 &&
                                              event.motion.y >= screenCtrlButton[2].pos_img_ecran.y && event.motion.y <= screenCtrlButton[2].pos_img_ecran.y + 86)
                        wndHovered = 1;
                    else
                        wndHovered = 0;

                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case (SDLK_ESCAPE): // returns to main menu
                        if (isPaused)
                        {
                            return -1;
                        }
                        else
                        {
                            menu = 0;
                        }
                        break;
                    }
                    break;
                }
            }
            SDL_Flip(screen);
            break;
        case 3:                                    // Credits window
            Mix_CloseAudio();                      // Closing audio for the credits menu, in the future a credits song will play
            afficher_imageBMP(screen, IMGCREDITS); // Credits img (WIP)
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    boucle = 0; // quits game
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case (SDLK_ESCAPE):
                        menu = 0; // returns to main menu
                        break;
                    }
                    break;
                }
            }
            SDL_Flip(screen);
            break;
        case 4:
            Mix_CloseAudio();
            return 2;
            break;
        }
    }

    // free functions
    liberer_image(IMAGE[0]);
    liberer_image(IMAGE[1]);
    liberer_image(IMAGE[2]);
    liberer_image(IMAGE[3]);
    liberer_image(IMAGE[4]);
    liberer_image(IMAGE[5]);
    liberer_image(IMAGE[6]);
    liberer_image(IMAGE[7]);
    liberer_image(IMAGE_BTN1);
    liberer_image(IMAGE_BTN2);
    liberer_image(IMAGE_BTN3);
    liberer_image(IMAGE_BTN4);
    liberer_image(IMAGE_BTN1_alt);
    liberer_image(IMAGE_BTN2_alt);
    liberer_image(IMAGE_BTN3_alt);
    liberer_image(IMAGE_BTN4_alt);
    liberer_image(IMGCREDITS);

    // liberer_musique(music); //Free music causes a seg error, unknown why
    // liberer_musiquebref(mus);

    liberer_texte(txte);

    SDL_Quit();

    return menu;
}
