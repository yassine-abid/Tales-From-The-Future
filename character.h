/**
 * @file character.h
*/
#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <math.h>
#include "menufunctions.h"
#define SCREEN_H 770
#define SCREEN_W 1366

/**
 * @struct Player;
 * @brief Structure for the player
 * @param rect Player's rect
 * @param velocity Player's velocity
 * @param health Player's Health
 * @param direction player's current direction
 * @param score player's score
 * @param sprite Array with player's different sprites
 * @param current_frame Array of current frames for player depending on direction
 * @param last_frame_time Array of last frame times in ticks
 * @param actualx player's actual x coordinatte
*/
typedef struct {
    SDL_Rect rect;
    int velocity;
    int maximumvelocity;
    int health;
    int max_health;
    int direction;
    int score;
    SDL_Surface* sprite[80];  // movement sprites
    int current_frame[10];
    int last_frame_time[10];
    int actualx;
} Player;

/**
 * @struct image;
 * @brief Structure for the image
*/


int mainmenu(SDL_Surface* Screen, int menu, int isPaused);
void init_players(Player* player, Player* playerTwo);
void update_player_animation(Player *player, Uint32 current_time, int player_moving);
void init_player(Player* player, int x, int y, int velocity, int maximumvelocity, int health, int max_health, const char* sprite_paths[]);
void init_lidle(Player *player, const char *path[]);
void print_player(Player *player, SDL_Surface *screen_surface, int player_moving);
void init_right(Player *player, const char *idle_sprite_paths[]);
void init_left(Player *player, const char *path[]);
void init_rleft(Player *player, const char *path[]);
void init_rright(Player *player, const char *path[]);
void init_fright(Player *player, const char *path[]);
void init_jright(Player *player, const char *path[]);
void init_fleft(Player *player, const char *path[]);
void init_jleft(Player *player, const char *path[]);
void init_aright(Player *player, const char *path[]);
void init_aleft(Player *player, const char *path[]);
int playerOneMovement(SDL_Event* event, Player* player, int* njump, int* nplayer);
int playerTwoMovement(SDL_Event* event, Player* player, int* njump, int* nplayer);
void updatePlayerPosition(SDL_Rect *playerRect, int *direction, int velocity, int *initialy, int *njump,SDL_Rect actualplayer,SDL_Surface *mask);
void checkIfPlayerIsDead(Player *player, int* gameover, int* level, int* upZero, int* upOne, int* upTwo);
void initialiser_imageBOUTON(image *imge, int x, int y, int h, int w, char *name);
void afficher_imageBTN(SDL_Surface *screen,image imge);
int aleaMain();
int joystickMovement(int* inputs, Player* player, int* njump);

#endif