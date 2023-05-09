/**
 * @file entity.c
 * @brief Implementation of the Entity struct and related functions.
 */
#include "entity.h"
/**
 * @brief Initializes the Entity struct with default values and sprites.
 *
 * @param e Pointer to the Entity struct to be initialized.
 * @return Nothing
 */
void init_e(Entity *e,int level)
{
    int levelsx[]={3000,1000,1000};
    const char *eleft[] = {"entities_sprites/run_1.png", "entities_sprites/run_2.png", "entities_sprites/run_3.png", "entities_sprites/run_4.png", "entities_sprites/run_5.png", "entities_sprites/run_6.png"};
    const char *eright[] = {"entities_sprites/run_1.png", "entities_sprites/run_2.png", "entities_sprites/run_3.png", "entities_sprites/run_4.png", "entities_sprites/run_5.png", "entities_sprites/run_6.png"};
    const char *eidle[] = {"entities_sprites/ready_1.png", "entities_sprites/ready_2.png", "entities_sprites/ready_3.png", "entities_sprites/ready_4.png", "entities_sprites/ready_5.png", "entities_sprites/ready_6.png"};
    init_entity(e, levelsx[level], 650, 1, 10, 100, 100, eidle);
    init_eleft(e, eleft);
    init_eright(e, eright);
}
/**
 * @brief Initializes the Entity struct with the given parameters.
 *
 * @param e Pointer to the Entity struct to be initialized.
 * @param x X-coordinate of the entity's position.
 * @param y Y-coordinate of the entity's position.
 * @param v Velocity of the entity.
 * @param maxv Maximum velocity of the entity.
 * @param hp Health points of the entity.
 * @param maxhp Maximum health points of the entity.
 * @param sprite_paths Array of strings containing the file paths of the entity's sprites.
 * @return Nothing
 */
void init_entity(Entity *e, int x, int y, int v, int maxv, int hp, int maxhp, const char *sprite_paths[])
{
        e->rect.w = 33;
    e->rect.h = 140;
    e->rect.x = x;
    e->rect.y = y-e->rect.h;


    e->velocity = v;
    e->maximumvelocity = maxv;

    e->health = hp;
    e->max_health = maxhp;

    e->direction = 0;

    for (int i = 0; i < 6; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(sprite_paths[i]);
        if (temp_surface == NULL)
        {

            fprintf(stderr, "Error: unable to load entity sprite; %s\n", IMG_GetError());
            exit(1);
        }
        e->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (e->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: unable to load entity sprite; %s\n", IMG_GetError());
            exit(1);
        }
        SDL_SetColorKey(e->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(e->sprite[i]->format, 0, 0, 0));
    }
    e->current_frame[0] = 0;
}

/**
 * @brief Initializes the right-facing sprites of the entity.
 *
 * @param e Pointer to the Entity struct whose right-facing sprites are to be initialized.
 * @param path Array of strings containing the file paths of the entity's right-facing sprites.
 * @return Nothing
 */
void init_eright(Entity *e, const char *path[])
{
    int j = 0;
    for (int i = 6; i < 12; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        e->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (e->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize e sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(e->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(e->sprite[i]->format, 0, 0, 0));
    }
    e->current_frame[1] = 0;
}

/**
 * @brief Initializes the left-facing sprites of the entity.
 *
 * @param e Pointer to the Entity struct whose left-facing sprites are to be initialized.
 * @param path Array of strings containing the file paths of the entity's left-facing sprites.
 * @return Nothing
 */
void init_eleft(Entity *e, const char *path[])
{
    int j = 0;
    int i;
    for (i = 12; i < 18; i++)
    {
        SDL_Surface *temp_surface = IMG_Load(path[j]);
        j++;
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        e->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (e->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize e sprite. %s\n", SDL_GetError());
            exit(1);
        }
        SDL_SetColorKey(e->sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(e->sprite[i]->format, 0, 0, 0));
    }
}

/**
 * @brief Prints the current sprite of the entity onto the screen.
 *
 * @param e Pointer to the Entity struct to be printed.
 * @param screen Pointer to the SDL_Surface object representing the screen.
 * @param entity_moving Flag indicating whether the entity is moving or not.
 * @param camera Pointer to the SDL_Rect object representing the camera position.
 * @return Nothing
 */
void print_entity(Entity *e, SDL_Surface *screen, int entity_moving,SDL_Rect camera)
{
    if (e->sprite[e->current_frame[entity_moving]] == NULL)
    {
        printf("Error: sprite[%d] is NULL\n", e->current_frame[entity_moving]);
        return;
    }
    int moving = e->current_frame[entity_moving];
    SDL_Rect dest_rect = {e->rect.x, e->rect.y, e->rect.w, e->rect.h};
    dest_rect.x-=camera.x;
    SDL_BlitSurface(e->sprite[moving], NULL, screen, &dest_rect);
}
/**
 * @brief Updates the animation frame of the entity.
 *
 * @param e Pointer to the Entity struct to be updated.
 * @param current_time Current time in milliseconds.
 * @param entity_moving Flag indicating whether the entity is moving or not.
 * @return Nothing
 */
void update_entity_animation(Entity *e, Uint32 current_time, int entity_moving)
{
    Uint32 frame_duration = 100;
    Uint32 last_frame_time = e->last_frame_time[entity_moving];
    Uint32 elapsed_time = current_time - last_frame_time;
    int current_frame = e->current_frame[entity_moving];

    if (elapsed_time > frame_duration)
    {
        switch (entity_moving)
        {
        case 0:
            current_frame = (current_frame + 1) % 6;
            e->last_frame_time[entity_moving] = current_time;
            break;
        case 1:
            current_frame = ((current_frame - 6 + 1) % 6) + 6;
            e->last_frame_time[entity_moving] = current_time;
            break;
        case 2:
            current_frame = (current_frame - 6 + 1) % 6 + 12;
            e->last_frame_time[entity_moving] = current_time;
            break;
        }
        e->current_frame[entity_moving] = current_frame;
    }
}

/**
 * @brief Moves the enemy entity
 * @param e Pointer to the entity struct
 * @param player Player entity
 * @return Nothing
*/
void move_enemy(Entity *e, SDL_Rect player,int x1,int x2)
{
    if (e->rect.x > player.x)
        e->direction = 2;
    if (e->rect.x < player.x )
        e->direction = 1;
    if (player.x < x1)
        e->direction = 0;
    if (player.x > x2)
        e->direction = 0;
    switch (e->direction)
    {
    case 1:
        e->rect.x += e->velocity;
        break;
    case 2:
        e->rect.x -= e->velocity;
        break;
    default:
        break;
    }
}

/**
 * @brief Checks collision with entity
 * @param e entity 
 * @param player player
*/
int collisionBB(SDL_Rect e, SDL_Rect player)
{
    int collision;
    if ((player.x + player.w < e.x) || (player.x > e.x + e.w) ||
        (player.y + player.h < e.y) || (player.y > e.y + e.h))
        collision = 0;
    else
        collision = 1;
    return collision;
}
void init_moving_trap(const char* spritepath[],int x,int y,int w,int h,int frameNumber,trap *t)
{
    t->pos.x=x;
    t->pos.y=y;
    t->pos.w=w;
    t->pos.h=h;
    t->direction=1;
    t->frameNumber = frameNumber;
    t->current_frame = 0;
    for (int i=0 ;i<frameNumber;i++)
    {
        SDL_Surface *temp_surface = IMG_Load(spritepath[i]);
        if (temp_surface == NULL)
        {
            fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
            exit(1);
        }
        t->sprite[i] = SDL_DisplayFormat(temp_surface);
        SDL_FreeSurface(temp_surface);
        if (t->sprite[i] == NULL)
        {
            fprintf(stderr, "Error: Unable to optimize e sprite. %s\n", SDL_GetError());
            exit(1);
        }
        //SDL_SetColorKey(t.sprite[i], SDL_SRCCOLORKEY, SDL_MapRGB(t.sprite[i]->format, 0, 0, 0));
    }
}
void move_trap(trap *t,int x,int X2)
{
    if (t->direction == 1 && t->pos.x<X2)
    {
        t->pos.x+=2;
    }
    else if (t->direction == 1 && t->pos.x>=X2)
    {
        t->direction = 2;
        t->pos.x-=2;
    }
    else if (t->direction == 2 && t->pos.x>x)
    {
        t->pos.x-=2;
    }
    else if (t->direction == 2 && t->pos.x<=x)
    {
        t->direction = 1;
        t->pos.x+=2;
    }
}
void animate_trap(trap *t, Uint32 current_time)
{
    uint32_t frame_duration = 100  ,   lastframetime = t->last_frame_time  ,   elapsedtime = current_time - lastframetime;
    int current_frame = t->current_frame;
    if (elapsedtime > frame_duration)
    {
        current_frame = (current_frame + 1) % t->frameNumber;
        t->last_frame_time = current_time;
        t->current_frame = current_frame;
    }
}
void print_trap(trap t,SDL_Surface *screen,SDL_Rect camera)
{
    SDL_Rect dest_rect = {t.pos.x, t.pos.y, t.pos.w, t.pos.h};
    dest_rect.x-=camera.x;
    SDL_BlitSurface(t.sprite[t.current_frame], NULL, screen, &dest_rect);
}
void init_coin(char spritepath[],int x,int y,int w,int h,int frameNumber,coin *c)
{
    c->collected = 0;
    c->pos.x=x;
    c->pos.y=y;
    c->pos.w=w;
    c->pos.h=h;
    c->frameNumber = frameNumber;
    c->current_frame = 0;
    SDL_Surface *temp_surface = IMG_Load(spritepath);
    if (temp_surface == NULL)
    {
        fprintf(stderr, "Error: Unable to load sprite image. %s\n", SDL_GetError());
        exit(1);
    }
    c->sprite = SDL_DisplayFormat(temp_surface);
    SDL_FreeSurface(temp_surface);
    if (c->sprite == NULL)
    {
        fprintf(stderr, "Error: Unable to optimize e sprite. %s\n", SDL_GetError());
        exit(1);
    }
    SDL_SetColorKey(c->sprite, SDL_SRCCOLORKEY, SDL_MapRGB(c->sprite->format, 0, 0, 0));
}
void animate_coin(coin *c, Uint32 current_time)
{
    uint32_t frame_duration = 100  ,   lastframetime = c->last_frame_time  ,   elapsedtime = current_time - lastframetime;
    int current_frame = c->current_frame;
    if (elapsedtime > frame_duration)
    {
        current_frame = (current_frame + 1) % c->frameNumber;
        c->last_frame_time = current_time;
        c->current_frame = current_frame;
    }
}
void print_coin(coin c, SDL_Surface* screen, SDL_Rect camera) {
    SDL_Rect src_rect = {c.current_frame * 20, 0, 20, 20}; // position and size of the coin in the image
    SDL_Rect dest_rect = {c.pos.x - camera.x, c.pos.y - camera.y, 20, 20}; // position and size of the coin on the screen
    SDL_BlitSurface(c.sprite, &src_rect, screen, &dest_rect);
}
