/**
 * @file minimap.c
*/
#include<stdio.h>
#include"SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <time.h>
#include "minimap.h"

/**
* @brief Initializes the minimap with images and positions
* @param m pointer to a Minimap struct
* @return Nothing
*/
void init_minimap(Minimap* m) {
    
    m->mini_image = IMG_Load("imgs/mini.png");
    m->mini_position.x = 400; 
    m->mini_position.y = 0;
    m->mini_position.w = 180;
    m->mini_position.h = 330;
    m->camera.x = 0;
    m->camera.y = 0;
    m->camera.w = 180;
    m->camera.h = 330;
   
    m->player_image = IMG_Load("imgs/resized.png");
    m->player_position.x = 300;
    m->player_position.y = 10;
    m->minimap_player_position.x = m->mini_position.x + m->player_position.x; 
    m->minimap_player_position.y = m->mini_position.y + m->player_position.y;
   
    

    
}

/**
* @brief Updates the minimap to reflect the current player position and camera
* @param posJoueur The current player position
* @param m A pointer to a Minimap struct
* @param camera The current camera position
* @param redimensionnement The current scaling factor for the minimap
* @return Nothing
*/
void MAJMinimap(SDL_Rect posJoueur,  Minimap * m, SDL_Rect camera, int redimensionnement)
{
    SDL_Rect posJoueurABS;
    posJoueurABS.x = 0;
    posJoueurABS.y = 0;
    posJoueurABS.x = posJoueur.x + camera.x;
    posJoueurABS.y = posJoueur.y + camera.y;


    m->minimap_player_position.x = (posJoueurABS.x * redimensionnement/100) + m->mini_position.x;
    m->minimap_player_position.y = (posJoueurABS.y * redimensionnement/100) + m->mini_position.y;
} 

/**
* @brief Displays the minimap on the screen
* @param m A Minimap struct
* @param screen The SDL_Surface on which to display the minimap
* @return Nothing
*/
void afficher_minimap(Minimap m, SDL_Surface* screen) {
    
    SDL_BlitSurface(m.mini_image, NULL, screen, &m.mini_position);
    
    
    SDL_BlitSurface(m.player_image, NULL, screen, &m.minimap_player_position); 
    
}

/**
* @brief Frees the surfaces used in the minimap
* @param m A pointer to a Minimap struct
* @return Nothing
*/
void liberer_minimap(Minimap* m) {
    
    SDL_FreeSurface(m->mini_image);
    SDL_FreeSurface(m->player_image);
}

/**
* @brief Gets the color of a pixel in an SDL_Surface
* @param pSurface The SDL_Surface containing the pixel
* @param x The x-coordinate of the pixel
* @param y The y-coordinate of the pixel
* @return The color of the pixel
*/
SDL_Color GetPixel(SDL_Surface* pSurface, int x, int y) {
    SDL_Color color;
    Uint32 col = 0;
    char* pPosition = (char*) pSurface->pixels;
    pPosition += (pSurface->pitch * y);
    pPosition += (pSurface->format->BytesPerPixel * x);
    memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
    return color;
}  

/**
 * @brief Checks for collision between a player's position and the background surface.
 *
 * @param player_pos The position of the player as an SDL_Rect.
 * @param background A pointer to the SDL_Surface representing the background.
 * @return Returns 1 if there is a collision, 0 otherwise.
 */
int collisionPP(SDL_Rect player_pos, SDL_Surface* background,SDL_Color color) {
   
    int posX[8] = {player_pos.x, player_pos.x + player_pos.w / 2, player_pos.x + player_pos.w, player_pos.x, player_pos.x, player_pos.x + player_pos.w / 2, player_pos.x + player_pos.w, player_pos.x + player_pos.w};
    int posY[8] = {player_pos.y, player_pos.y, player_pos.y, player_pos.y + player_pos.h / 2, player_pos.y + player_pos.h, player_pos.y + player_pos.h, player_pos.y + player_pos.h, player_pos.y + player_pos.h / 2};

    
    for (int i = 0; i < 8; i++) {
        SDL_Color pixelColor = GetPixel(background, posX[i], posY[i]);
        if (pixelColor.r == color.r && pixelColor.g == color.g && pixelColor.b == color.b) {
            
            return 1;
        }
    }

    
    return 0;
} 

/**
 * @brief Displays the elapsed time 
 * @param temps The time in seconds as an integer.
 * @return Nothing
 */
void affichertemps(int temps)
{
    SDL_Color color_temp = {255, 255, 255};
    TTF_Font* police_time = NULL;
    police_time = TTF_OpenFont("04B_08__.TTF",24);
    char temp[100];
    int heures = temps / 3600;
    int minutes = (temps % 3600) / 60;
    int secondes = temps % 60;
    sprintf(temp, "%02d:%02d:%02d", heures, minutes, secondes);
    SDL_Surface* temps_surface = TTF_RenderText_Solid(police_time, temp, color_temp);
    SDL_Rect pos_temp;
    pos_temp.x = 600;
    pos_temp.y = 0;
    SDL_BlitSurface(temps_surface, NULL, SDL_GetVideoSurface(), &pos_temp);
    TTF_CloseFont(police_time);
    SDL_FreeSurface(temps_surface);
}  

/**
 * @brief Animates the minimap 
 * @param m A pointer to the Minimap structure.
 * @return Nothing
 */
void animerMinimap(Minimap* m) {
    SDL_Surface* surface = m->mini_image;

    
    Uint32 color;
    static int frame = 0;
    frame++;
    if (frame % 50 < 25) {
        color = SDL_MapRGB(surface->format, 255, 0, 0); 
    } else {
        color = SDL_MapRGB(surface->format, 0, 255, 0); 
    }

    
    SDL_Rect point_rect = { 300,180 , 15, 15  };

    
    SDL_FillRect(surface, &point_rect, color);

   
    SDL_UpdateRect(surface, 0, 0, 0, 0);
}

/**
 * @brief Displays a countdown timer
 * @param startTime The start time in milliseconds as a Uint32.
 * @return Nothing
 */
void affichertempsen(Uint32 startTime)
{
    SDL_Color color_temp = {0, 0, 0};
    TTF_Font* police_time = NULL;
    police_time = TTF_OpenFont("04B_08__.TTF",23);
    char temp[100];
    int temps = 30000 - (SDL_GetTicks() - startTime); 
    if(temps<0)
    {
    temps=0;}
    int secondes = temps / 1000;
    sprintf(temp, "%02d:%02d", 0, secondes); 

    SDL_Surface* temps_surface = NULL;
    temps_surface = TTF_RenderText_Solid(police_time, temp, color_temp);
    SDL_Rect pos_temp;
    pos_temp.x = 20;
    pos_temp.y = 20;

    SDL_BlitSurface(temps_surface, NULL, SDL_GetVideoSurface(), &pos_temp);
    
    TTF_CloseFont(police_time);
    SDL_FreeSurface(temps_surface);
}

