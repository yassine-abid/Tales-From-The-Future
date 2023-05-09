#include "sauv.h"

void sauvegarder(Player p, Background b, char *nomfichier, int level)
{
	FILE *f;

	f = fopen(nomfichier, "w");
	fprintf(f, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", p.rect.x, p.rect.y, p.health, p.score, b.rect.x, b.rect.y, b.camera_pos.x, b.camera_pos.y, b.posBack1.x, b.posBack1.y, b.direction, b.posScreen1.x, b.posScreen1.y, b.posBack2.x, b.posBack2.y,level);

	fclose(f);
}

int charger(Player *p, Background *b, char *nomfichier,int *level)
{

	FILE *f = fopen(nomfichier, "r");
	if (f == NULL)
	{
		printf("Erreur !");
	}
	else
	{
		printf("loading");
		fscanf(f, "%hd %hd %d %d %hd %hd %hd %hd %hd %hd %d %hd %hd %hd %hd %d\n", &p->rect.x, &p->rect.y, &p->health, &p->score, &b->rect.x, &b->rect.y, &b->camera_pos.x, &b->camera_pos.y, &b->posBack1.x, &b->posBack1.y, &b->direction, &b->posScreen1.x, &b->posScreen1.y, &b->posBack2.x, &b->posBack2.y,level);
	}
	fclose(f);
}
