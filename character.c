/**
 * @file character.c
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "character.h"
#include <math.h>
#include "minimap.h"

/**
 * @brief Initializes the player sprites and calls the init functions for each direction
 * @param player player one to initialize
 * @param playerTwo player two to initialize
 * @return Nothing
 */
void init_players(Player *player, Player *playerTwo)
{
    const char *idle[8] = {"sprites/i1.png", "sprites/i2.png", "sprites/i3.png", "sprites/i4.png", "sprites/i5.png", "sprites/i6.png", "sprites/i7.png", "sprites/i8.png"};
    const char *idleleft[8] = {"sprites/li1.png", "sprites/li2.png", "sprites/li3.png", "sprites/li4.png", "sprites/li5.png", "sprites/li6.png", "sprites/li7.png", "sprites/li8.png"};
    const char *right[8] = {"sprites/wr1.png", "sprites/wr2.png", "sprites/wr3.png", "sprites/wr4.png", "sprites/wr5.png", "sprites/wr6.png", "sprites/wr7.png", "sprites/wr8.png"};
    const char *left[8] = {"sprites/wl1.png", "sprites/wl2.png", "sprites/wl3.png", "sprites/wl4.png", "sprites/wl5.png", "sprites/wl6.png", "sprites/wl7.png", "sprites/wl8.png"};
    const char *runright[8] = {"sprites/rr1.png", "sprites/rr2.png", "sprites/rr3.png", "sprites/rr4.png", "sprites/rr5.png", "sprites/rr6.png", "sprites/rr7.png", "sprites/rr8.png"};
    const char *runleft[8] = {"sprites/rl1.png", "sprites/rl2.png", "sprites/rl3.png", "sprites/rl4.png", "sprites/rl5.png", "sprites/rl6.png", "sprites/rl7.png", "sprites/rl8.png"};
    const char *jumpleft[4] = {"sprites/jl1.png",
                               "sprites/jl2.png",
                               "sprites/jl3.png",
                               "sprites/jl4.png"};
    const char *fallleft[5] = {"sprites/jl5.png",
                               "sprites/jl6.png",
                               "sprites/jl7.png",
                               "sprites/jl8.png",
                               "sprites/jl9.png"};
    const char *jumpright[4] = {"sprites/jr1.png",
                                "sprites/jr2.png",
                                "sprites/jr3.png",
                                "sprites/jr4.png"};
    const char *fallright[5] = {"sprites/jr5.png",
                                "sprites/jr6.png",
                                "sprites/jr7.png",
                                "sprites/jr8.png",
                                "sprites/jr9.png"};
    const char *attackleft[4] = {"sprites/al1.png", "sprites/al2.png", "sprites/al3.png", "sprites/al4.png"};
    const char *attackright[4] = {"sprites/ar1.png", "sprites/ar2.png", "sprites/ar3.png", "sprites/ar4.png"};
    init_player(player, 100, 350, 1, 10, 3, 3, idle);
    init_lidle(player, idleleft);
    init_right(player, right);
    init_left(player, left);
    init_rright(player, runright);
    init_rleft(player, runleft);
    init_jleft(player, jumpleft);
    init_fleft(player, fallleft);
    init_jright(player, jumpright);
    init_fright(player, fallright);
    init_aleft(player, attackleft);
    init_aright(player, attackright);

    // playertwo

    init_player(playerTwo, 150, 300, 1, 10, 1000, 1000, idle);
    init_right(playerTwo, right);
    init_left(playerTwo, left);
    init_rright(playerTwo, runright);
    init_rleft(playerTwo, runleft);
    init_jleft(playerTwo, jumpleft);
    init_fleft(playerTwo, fallleft);
    init_jright(playerTwo, jumpright);
    init_fright(playerTwo, fallright);
    init_aleft(playerTwo, attackleft);
    init_aright(playerTwo, attackright);
}

/**
 * @brief Initializes right movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_right(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 8; i < 16; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[1] = 0;
}

/**
 * @brief Initializes left movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_left(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 16; i < 24; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[2] = 0;
}

/**
 * @brief Initializes run right movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_rright(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 24; i < 32; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[3] = 0;
}

/**
 * @brief Initializes run left movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_rleft(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 32; i < 40; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[4] = 0;
}

/**
 * @brief Initializes jump left movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_jleft(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 40; i < 44; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[5] = 0;
}

/**
 * @brief Initializes fall left movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_fleft(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 44; i < 49; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[6] = 0;
}

/**
 * @brief Initializes jump right movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_jright(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 49; i < 53; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[7] = 0;
}

/**
 * @brief Initializes fall right movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_fright(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 53; i < 58; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[8] = 0;
}

/**
 * @brief Initializes attack right movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_aright(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 58; i < 62; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[9] = 0;
}

/**
 * @brief Initializes attack left movement sprites
 * @param player player to initialize
 * @param path path to sprites
 * @return Nothing
 */
void init_aleft(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 62; i < 66; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[10] = 0;
}

/**
 * @brief Initializes left idle movement sprites
 * 
 * @param player 
 * @param path 
 * @return Nothing
 */
void init_lidle(Player *player, const char *path[])
{
    int j = 0;
    for (int i = 66; i < 74; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    player->current_frame[11] = 0;
}

/**
 * @brief Initializes player in idle position
 * @param player player to initialize
 * @param x x coordinate
 * @param y y coordinate
 * @param velocity velocity
 * @param maximumvelocity maximum velocity
 * @param health health
 * @param max_health maximum health
 * @param sprite_paths paths to sprites
 * @return Nothing
 */
void init_player(Player *player, int x, int y, int velocity, int maximumvelocity, int health, int max_health, const char *sprite_paths[])
{
    // Initialize the player's rectangle
    player->rect.x = x;
    player->actualx = x;
    player->rect.y = y;
    player->rect.w = 230;
    player->rect.h = 160;
    player->direction = 0;
    // Set the player's velocity
    player->velocity = velocity;
    player->maximumvelocity = maximumvelocity;

    // Set the player's health
    player->health = health;
    player->max_health = max_health;
    player->score = 0;

    // Load the player's sprites
    for (int i = 0; i < 8; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(sprite_paths[i]);
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load player sprite. %s\n", IMG_GetError());
            exit(1);
        }
        player->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (player->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize player sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(player->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(player->sprite[i]->format, 0, 0, 0));
    }
    // Set the player's current frame
    player->current_frame[0] = 0;
}

/**
 * @brief updates player animation as is needed
 * @param player player to update
 * @param current_time current time in ticks
 * @param player_moving checks if player is moving
 * @return Nothing
 */
void update_player_animation(Player *player, Uint32 current_time, int player_moving)
{
    Uint32 frame_duration = 100;
    Uint32 last_frame_time = player->last_frame_time[player_moving];
    Uint32 elapsed_time = current_time - last_frame_time;
    int current_frame = player->current_frame[player_moving];
    if (elapsed_time > frame_duration)
    {
        switch (player_moving)
        {
        case 0:
            current_frame = (current_frame + 1) % 8;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 1:
            current_frame = ((current_frame - 8 + 1) % 8) + 8;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 2:
            current_frame = (current_frame - 8 + 1) % 8 + 16;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 3:
            current_frame = (current_frame - 8 + 1) % 8 + 24;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 4:
            current_frame = (current_frame - 8 + 1) % 8 + 32;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 5:
            current_frame = ((current_frame - 8 + 1) % 4 + 4) % 4 + 40;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 6:
            current_frame = ((current_frame - 8 + 1) % 5 + 5) % 5 + 44;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 7:
            current_frame = ((current_frame - 8 + 1) % 4 + 4) % 4 + 49;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 8:
            current_frame = ((current_frame - 8 + 1) % 5 + 5) % 5 + 53;
            player->last_frame_time[player_moving] = current_time;
            break;
        case 9:
            current_frame = ((current_frame - 8 + 1) % 4 + 58);
            player->last_frame_time[player_moving] = current_time;
            break;
        case 10: 
            current_frame = ((current_frame - 8 + 1) % 4 + 62);
            player->last_frame_time[player_moving] = current_time;
            break;
        case 11:
            current_frame = ((current_frame - 8 + 1) % 8 + 66);
            player->last_frame_time[player_moving] = current_time;
            break;
        }
        player->current_frame[player_moving] = current_frame;
    }
}

/**
 * @brief prints player on screen
 * @param player player to print
 * @param screen_surface screen surface
 * @param player_moving checks if player is moving
 * @return Nothing
 */
void print_player(Player *player, SDL_Surface *screen_surface, int player_moving)
{
    if (player->sprite[player->current_frame[player_moving]] == NULL)
    {
        printf("Error: sprite[%d] is NULL\n", player->current_frame[player_moving]);
        return;
    }
    int moving = player->current_frame[player_moving];
    SDL_Rect dest_rect = {player->rect.x, player->rect.y, player->rect.w, player->rect.h};
    SDL_BlitSurface(player->sprite[moving], NULL, screen_surface, &dest_rect);
}

/**
 * @brief controls player movement
 * @param event event to check
 * @param player player to move
 * @param njump checks if player is jumping
 * @param nplayer checks if number of players is getting changed
 * @return playermoving returns if player is moving
 */
int playerOneMovement(SDL_Event *event, Player *player, int *njump, int *nplayer)
{
    int playermoving = 0;
    switch (event->type)
    {
    case SDL_QUIT:
        // Quit the game
        SDL_Quit();
        return 0;
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_RIGHT:
            if (player->direction != 7)
            {
                // Move right
                player->velocity += 1;
                if (player->velocity > player->maximumvelocity)
                {
                    player->velocity = player->maximumvelocity;
                }
                player->direction = 1;
            }
            if (SDL_GetKeyState(NULL)[SDLK_RSHIFT])
            {
                // Move right
                player->velocity += 3;
                if (player->velocity > player->maximumvelocity)
                {
                    player->velocity = player->maximumvelocity;
                }
                player->direction = 3;
            }
            if (SDL_GetKeyState(NULL)[SDLK_UP])
            {
                *njump = 0;
                player->direction = 7;
            }
            playermoving = 1;

            break;
        case SDLK_LEFT:
            // Move left
            if (player->direction != 5)
            {
                player->velocity += 1;
                if (player->velocity < -player->maximumvelocity)
                {
                    player->velocity = -player->maximumvelocity;
                }
                player->direction = 2;
            }
            if (SDL_GetKeyState(NULL)[SDLK_UP])
            {
                player->direction = 5;
            }
            if (SDL_GetKeyState(NULL)[SDLK_RSHIFT])
            {
                // Move right
                player->velocity += 3;
                if (player->velocity > player->maximumvelocity)
                {
                    player->velocity = player->maximumvelocity;
                }
                player->direction = 4;
            }
            playermoving = 2;

            break;
        case SDLK_UP:
            if (player->direction != 7)
            {
                *njump = 1;
                player->velocity += 1;
                if (player->velocity < -player->maximumvelocity)
                {
                    player->velocity = -player->maximumvelocity;
                }
                player->direction = 7;
            }
            if (SDL_GetKeyState(NULL)[SDLK_RIGHT])
            {
                player->direction = 7;
                *njump = 0;
                playermoving = 1;
            }
            if (SDL_GetKeyState(NULL)[SDLK_LEFT])
            {
                player->direction = 5;
                playermoving = 2;
            }
            break;
        case SDLK_SPACE:
            if (player->direction == 0)
            {
                player->direction = 9;
            }
            if (player->direction == 11) {
                player->direction = 10;
            }
            break;
        case SDLK_l:
            *nplayer = 0;
            break;
        case SDLK_m:
            *nplayer = 1;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event->key.keysym.sym)
        {
        case SDLK_LEFT:
            player->direction = 11;
            player->velocity = 1;
            break;
        case SDLK_RIGHT:
            player->direction = 0;
            player->velocity = 1;
            break;
        case SDLK_UP:
            player->velocity = 1;
            player->direction = 8;
            break;
        case SDLK_SPACE:
            if (player->direction == 9) {
            player->direction = 0;
            }
            if (player->direction == 10) {
                player->direction = 11;
            }
            break;
        }
        break;
    }

    return playermoving;
}

/**
 * @brief controls second player movement
 * @param event event to check
 * @param player player to move
 * @param njump checks if player is jumping
 * @param nplayer checks if number of players is getting changed
 * @return playermoving returns if player is moving
 */
int playerTwoMovement(SDL_Event *event, Player *player, int *njump, int *nplayer)
{
    switch (event->type)
    {
    case SDL_QUIT:
        // Quit the game
        SDL_Quit();
        return 0;
    case SDL_KEYDOWN:
        switch (event->key.keysym.sym)
        {
        case SDLK_d:
            if (player->direction != 7)
            {
                // Move right
                player->velocity += 1;
                if (player->velocity > player->maximumvelocity)
                {
                    player->velocity = player->maximumvelocity;
                }
                player->direction = 1;
            }
            if (SDL_GetKeyState(NULL)[SDLK_LSHIFT])
            {
                // Move right
                player->velocity += 3;
                if (player->velocity > player->maximumvelocity)
                {
                    player->velocity = player->maximumvelocity;
                }
                player->direction = 3;
            }
            if (SDL_GetKeyState(NULL)[SDLK_UP])
            {
                *njump = 0;
                player->direction = 7;
            }
            break;
        case SDLK_q:
            // Move left
            if (player->direction != 5)
            {
                player->velocity += 1;
                if (player->velocity < -player->maximumvelocity)
                {
                    player->velocity = -player->maximumvelocity;
                }
                player->direction = 2;
            }
            if (SDL_GetKeyState(NULL)[SDLK_UP])
            {
                player->direction = 5;
            }
            if (SDL_GetKeyState(NULL)[SDLK_LSHIFT])
            {
                // Move right
                player->velocity += 3;
                if (player->velocity > player->maximumvelocity)
                {
                    player->velocity = player->maximumvelocity;
                }
                player->direction = 4;
            }
            break;
        case SDLK_z:
            if (player->direction != 7)
            {
                *njump = 1;
                player->velocity += 1;
                if (player->velocity < -player->maximumvelocity)
                {
                    player->velocity = -player->maximumvelocity;
                }
                player->direction = 7;
            }
            if (SDL_GetKeyState(NULL)[SDLK_d])
            {
                player->direction = 7;
                *njump = 0;
            }
            if (SDL_GetKeyState(NULL)[SDLK_q])
            {
                player->direction = 5;
            }
            break;
        case SDLK_LCTRL:
            player->direction = 9;
            break;
        case SDLK_l:
            *nplayer = 0;
            break;
        case SDLK_m:
            *nplayer = 1;
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event->key.keysym.sym)
        {
        case SDLK_q:
            player->direction = 0;
            player->velocity = 1;
            break;
        case SDLK_d:
            player->direction = 0;
            player->velocity = 1;
            break;
        case SDLK_z:
            player->velocity = 1;
            player->direction = 8;
            break;
        case SDLK_LCTRL:
            player->direction = 0;
            break;
        }
        break;
    }

    return 1;
}

/**
 * @brief updates player position on screen
 * @param playerRect rectangle of player
 * @param direction direction of player
 * @param velocity velocity of player
 * @param initialy initial y position of player
 * @param njump checks if player is jumping
 * @param actualplayer actual player coords
 * @param mask background mask
 * @return Nothing
 */
void updatePlayerPosition(SDL_Rect *playerRect, int *direction, int velocity, int *initialy, int *njump, SDL_Rect actualplayer, SDL_Surface *mask)
{
    if (playerRect->x < 50)
    {
        playerRect->y = 50;
    }
    switch (*direction)
    {
    case -1:
        if (playerRect->y != *initialy)
        {
            playerRect->y = *initialy;
        }
        *initialy = playerRect->y;
    case 0:
        if (playerRect->y != *initialy)
        {
            playerRect->y = *initialy;
        }
        *initialy = playerRect->y;
        break;
    case 1:
        playerRect->x += velocity;
        if (playerRect->y != *initialy)
        {
            playerRect->y = *initialy;
        }
        *initialy = playerRect->y;
        break;
    case 2:
        playerRect->x -= velocity;
        if (playerRect->y != *initialy)
        {
            playerRect->y = *initialy;
        }
        *initialy = playerRect->y;
        break;
    case 3:
        playerRect->x += velocity;
        if (playerRect->y != *initialy)
        {
            playerRect->y = *initialy;
        }
        *initialy = playerRect->y;
        break;
    case 4:
        playerRect->x -= velocity;
        if (playerRect->y != *initialy)
        {
            playerRect->y = *initialy;
        }
        *initialy = playerRect->y;
        break;
    case 5:
        playerRect->x -= velocity;
        playerRect->y -= velocity;
        if (playerRect->y < *initialy - 100)
        {
            *direction = 6;
        }
        break;
    case 6:
        playerRect->y += velocity + 1;
        if (playerRect->y > *initialy)
        {
            *direction = 0;
        }
        break;
    case 7:
        if (*njump == 0)
        {
            playerRect->x += velocity;
        }
        playerRect->y -= velocity;
        if (playerRect->y < *initialy - 100)
        {
            *direction = 8;
        }
        break;
    case 8:

        playerRect->y += velocity + 1;
        if (playerRect->y > *initialy)
        {
            *direction = 0;
        }
        break;
    }
}

/**
 * @brief checks if player is dead
 * @param player player
 * @param gameover checks if game is over
 * @return Nothing
 */
void checkIfPlayerIsDead(Player *player, int *gameover, int *level, int *upZero, int *upOne, int *upTwo)
{
    if (player->rect.y > 900)
    {
        player->health = 0;
    }
    if (player->health == 0)
    {
        *gameover = 1;
        player->health = player->max_health;
        *level = 0;
        *upZero = 0;
        *upOne = 0;
        *upTwo = 0;
    }
}
