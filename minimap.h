/**
 * @file minimap.h
*/
#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

/**
 * @struct Minimap
 * @brief A struct representing the minimap, including the player's image and position.
 * @param mini_image The minimap image
 * @param mini_position The position of the minimap on the screen
 * @param player_image the image of the player on the minimap
 * @param player_position the position of the player on the minimap
 * @param minimap_player_position the position of the player on the minimap relative to the minimap image
 */
typedef struct {
    SDL_Surface* mini_image;
    SDL_Rect mini_position;
    SDL_Surface* player_image;
    SDL_Rect player_position;
    SDL_Rect minimap_player_position; 
    SDL_Rect camera;
    
} Minimap;


void init_minimap(Minimap* m);
void MAJMinimap(SDL_Rect posJoueur,  Minimap * m, SDL_Rect camera, int redimensionnement);
void afficher_minimap(Minimap m, SDL_Surface* screen);
void liberer_minimap(Minimap* m);

SDL_Color GetPixel(SDL_Surface* pSurface, int x, int y);
int collisionPP(SDL_Rect player_pos, SDL_Surface* background,SDL_Color color);

void affichertemps(int temps);
void animerMinimap(Minimap* m);

void affichertempsen(Uint32 startTime);

#endif


