

#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "pong.h"

int pong(SDL_Surface *screen)
{
	srand(time(NULL));

	int BAR_SPEED = 1;

	int running = 1;
	int xBall = 0, yBall = 0;

	char scoreP1_s[10];
	char scoreP2_s[10];

	int scoreP1 = 0, scoreP2 = 0;

	SDL_Surface *bar = NULL, *ball = NULL, *ligne = NULL;
	SDL_Rect posBar1, posBar2, posBall, posLigne, posScore1, posScore2;
	SDL_Event event;

	TTF_Font *font;
	SDL_Color couleurScore;
	SDL_Surface *score1 = NULL, *score2 = NULL;

	ligne = SDL_CreateRGBSurface(SDL_HWSURFACE, LINE_W, screen->h, 32, 0, 0, 0, 0);
	SDL_FillRect(ligne, NULL, SDL_MapRGB(ligne->format, 100, 100, 100));

	bar = SDL_CreateRGBSurface(SDL_HWSURFACE, BAR_W, BAR_H, 32, 0, 0, 0, 0);
	SDL_FillRect(bar, NULL, SDL_MapRGB(bar->format, 255, 255, 255));

	ball = SDL_CreateRGBSurface(SDL_HWSURFACE, BALL_SIZE, BALL_SIZE, 32, 0, 0, 0, 0);
	SDL_FillRect(ball, NULL, SDL_MapRGB(ball->format, 255, 255, 255));

	TTF_Init();

	font = TTF_OpenFont("DS-DIGI.TTF", 30);

	couleurScore.r = 255;
	couleurScore.g = 255;
	couleurScore.b = 255;

	posScore1.x = screen->w / 2 - 100;
	posScore1.y = SCORE_D;

	posScore2.x = screen->w / 2 + 100;
	posScore2.y = SCORE_D;

	SDL_EnableKeyRepeat(10, 50);

	posBar1.x = 50;
	posBar1.y = screen->h / 2 - BAR_H / 2;

	posBar2.x = screen->w - 50 - BAR_W;
	posBar2.y = screen->h / 2 - BAR_H / 2;

	resetBall(&posBall, &xBall, &yBall);

	posLigne.x = screen->w / 2 - LINE_W / 2;
	posLigne.y = 0;

	while (running)
	{

		if (scoreP1 == 5)
		{

			SDL_Surface *player1_image = IMG_Load("winner.jpg");
			SDL_BlitSurface(player1_image, NULL, screen, NULL);
			SDL_Flip(screen);
			SDL_Delay(5000);
			SDL_FreeSurface(player1_image);
			running = 0;
		}
		else if (scoreP2 == 5)
		{

			SDL_Surface *player2_image = IMG_Load("gameover.jpg");
			SDL_BlitSurface(player2_image, NULL, screen, NULL);
			SDL_Flip(screen);
			SDL_Delay(5000);
			SDL_FreeSurface(player2_image);
			running = 0;
		}

		sprintf(scoreP1_s, "%d", scoreP1);
		sprintf(scoreP2_s, "%d", scoreP2);

		score1 = TTF_RenderText_Solid(font, scoreP1_s, couleurScore);
		score2 = TTF_RenderText_Solid(font, scoreP2_s, couleurScore);

		if (posBall.y <= 0)
			yBall = BALL_SPEED;
		if (posBall.y >= screen->h)
			yBall = -BALL_SPEED;

		if (posBall.x <= 0)
		{
			resetBall(&posBall, &xBall, &yBall);
			scoreP2++;
		}
		if (posBall.x + BALL_SIZE > screen->w)
		{
			resetBall(&posBall, &xBall, &yBall);
			scoreP1++;
		}

		int rand_num = rand() % 100;
		if (rand_num < 40)
		{

			while (posBar2.y + BAR_H / 2 < posBall.y)
			{
				posBar2.y += BAR_SPEED;
			}

			while (posBar2.y + BAR_H / 2 > posBall.y)
			{
				posBar2.y -= BAR_SPEED;
			}
		}

		if (posBall.x <= posBar1.x + BAR_W && posBall.x > posBar1.x)
		{

			if (posBall.y >= posBar1.y && posBall.y <= posBar1.y + BAR_H)
				xBall = BALL_SPEED;
		}

		if (posBall.x >= posBar2.x && posBall.x < posBar2.x + BAR_W / 2)
		{

			if (posBall.y >= posBar2.y && posBall.y <= posBar2.y + BAR_H)
				xBall = -BALL_SPEED;
		}

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = 0;
					break;
				case SDLK_z:
					if (posBar1.y >= 20)
						posBar1.y -= 20;
					break;
				case SDLK_s:
					if (posBar1.y <= screen->h - BAR_H - 20)
						posBar1.y += 20;
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		}

		posBall.x += xBall;
		posBall.y += yBall;

		posScore1.w = score1->w;
		posScore1.h = score1->h;

		posScore2.w = score2->w;
		posScore2.h = score2->h;

		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		SDL_BlitSurface(ligne, NULL, screen, &posLigne);

		SDL_BlitSurface(ball, NULL, screen, &posBall);
		SDL_BlitSurface(bar, NULL, screen, &posBar1);
		SDL_BlitSurface(bar, NULL, screen, &posBar2);

		SDL_BlitSurface(score1, NULL, screen, &posScore1);
		SDL_BlitSurface(score2, NULL, screen, &posScore2);

		SDL_Flip(screen);
		SDL_Delay(10);
	}

	SDL_FreeSurface(score1);
	SDL_FreeSurface(score2);
	SDL_FreeSurface(ligne);
	SDL_FreeSurface(ball);
	TTF_CloseFont(font);

	SDL_FreeSurface(screen);
}

void resetBall(SDL_Rect *position, int *x, int *y)
{
	position->x = BALL_X;
	position->y = BALL_Y;
	*x = BALL_SPEED;
	*y = BALL_SPEED;
}
