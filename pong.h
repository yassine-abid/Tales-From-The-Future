

#ifndef PONG_H
#define PONG_H




#define BAR_W 15
#define BAR_H 120
#include <time.h>

#define LINE_W 2

#define BALL_X 100
#define BALL_Y 100
#define BALL_SIZE 10
#define BALL_SPEED 5

#define SCORE_D 30


void resetBall(SDL_Rect *position,int *x,int *y);
int pong(SDL_Surface *screen);

#endif
