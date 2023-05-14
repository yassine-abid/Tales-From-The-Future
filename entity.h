/**
 * @file entity.h
 * @brief This header file defines the Entity struct and related functions.
 */
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "minimap.h"
#include "character.h"
#include "bg.h"


/**
 * @struct Entity
 * @brief A struct that represents a game entity.
 *
 * This struct contains information about the entity's position, velocity, health,
 * movement direction, score, and animation.
 */
typedef struct {
    SDL_Rect rect;                  /**< The position and size of the entity */
    int velocity;                   /**< The current velocity of the entity */
    int maximumvelocity;            /**< The maximum velocity of the entity */
    int health;                     /**< The current health of the entity */
    int max_health;                 /**< The maximum health of the entity */
    int direction;                  /**< The direction the entity is facing */
    SDL_Surface* sprite[40];        /**< Array of movement sprites */
    int current_frame[5];           /**< The current frame of the animation */
    int last_frame_time[5];         /**< The time the last frame was displayed */
} Entity;
typedef struct 
{
    SDL_Rect pos;
    SDL_Surface *sprite[10];
    int direction;
    int current_frame;
    int last_frame_time;
    int frameNumber;
}trap;
typedef struct 
{
    SDL_Rect pos;
    SDL_Surface *sprite;
    int current_frame;
    int last_frame_time;
    int frameNumber;
    int collected;
}coin;


void init_e(Entity *e,int level);
void init_entity(Entity *e,int x,int y,int v,int maxv,int hp,int maxhp,const char *sprite_paths[]);
void update_entity_animation(Entity *e,Uint32 current_time,int entity_moving);
void print_entity(Entity *e,SDL_Surface *screen,int entity_moving,SDL_Rect camera);
void init_eleft(Entity *e, const char *path[]);
void init_eright(Entity *e, const char *path[]);
void move_enemy(Entity *e,SDL_Rect player,int x1,int x2);
int collisionBB(SDL_Rect e,SDL_Rect player);
void init_moving_trap(const char* spritepath[],int x,int y,int w,int h,int frameNumber,trap *t);
void move_trap(trap *t,int x,int X2);
void animate_trap(trap *t, Uint32 current_time);
void print_trap(trap t,SDL_Surface *screen,SDL_Rect camera);
void init_coin(char spritepath[],int x,int y,int w,int h,int frameNumber,coin *c);
void animate_coin(coin *c, Uint32 current_time);
void print_coin(coin c,SDL_Surface *screen,SDL_Rect camera);
void handlePlayerEnemyCollision(SDL_Rect actualPlayer, Entity e, int* last_damage, Player* player, Background damage, SDL_Surface* screen_surface, trap t1);
#endif