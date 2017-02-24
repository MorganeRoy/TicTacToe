#include "jeu.h"

#include <assert.h>

static bool sousQuiGagne(const Plateau *plateau, Pion pion)
{
	if ((*plateau)[0] == pion && (*plateau)[1] == pion && (*plateau)[2] == pion) return true;
	if ((*plateau)[3] == pion && (*plateau)[4] == pion && (*plateau)[5] == pion) return true;
	if ((*plateau)[6] == pion && (*plateau)[7] == pion && (*plateau)[8] == pion) return true;
	if ((*plateau)[0] == pion && (*plateau)[3] == pion && (*plateau)[6] == pion) return true;
	if ((*plateau)[1] == pion && (*plateau)[4] == pion && (*plateau)[7] == pion) return true;
	if ((*plateau)[2] == pion && (*plateau)[5] == pion && (*plateau)[8] == pion) return true;
	if ((*plateau)[0] == pion && (*plateau)[4] == pion && (*plateau)[8] == pion) return true;
	if ((*plateau)[2] == pion && (*plateau)[4] == pion && (*plateau)[6] == pion) return true;
	return false;
}

static void sousAfficheGrille(const Plateau *plateau, int ligne)
{
	int startIndex = ligne * 3;
	for (int i = 0; i < 3; ++i)
	{
		switch((*plateau)[startIndex + i])
		{
			case X:
				printf("%c ", 'X');
				break;
			case O:
				printf("%c ", 'O');
				break;
			case None:
				printf("%c ", '_');
				break;
		}
	}
	printf(" ");
}

Pion quiGagne(const Grille *Grille)
{
	for (int i = 0; i < TAILLE_JEU; ++i)
	{
		if (sousQuiGagne(&Grille->plateau[i], X)) return X;
		if (sousQuiGagne(&Grille->plateau[i], O)) return O;
	}
	return None;
}

Grille creerGrille(int commencerGrille)
{
	assert(commencerGrille >= 0 && commencerGrille < TAILLE_JEU);

	Grille Grille;
	Grille.actionCpt = TAILLE_JEU * TAILLE_JEU;
	Grille.plateauSuivant = commencerGrille;
	for (int i = 0; i < TAILLE_JEU; ++i)
	{
		for (int j = 0; j < TAILLE_JEU; ++j)
		{
			Grille.plateau[i][j] = None;
		}
	}

	return Grille;
}

void afficheGrille(const Grille *Grille)
{
	sousAfficheGrille(&Grille->plateau[0], 0); sousAfficheGrille(&Grille->plateau[1], 0); sousAfficheGrille(&Grille->plateau[2], 0); printf("\n");
	sousAfficheGrille(&Grille->plateau[0], 1); sousAfficheGrille(&Grille->plateau[1], 1); sousAfficheGrille(&Grille->plateau[2], 1); printf("\n");
	sousAfficheGrille(&Grille->plateau[0], 2); sousAfficheGrille(&Grille->plateau[1], 2); sousAfficheGrille(&Grille->plateau[2], 2); printf("\n");

	printf("\n");

	sousAfficheGrille(&Grille->plateau[3], 0); sousAfficheGrille(&Grille->plateau[4], 0); sousAfficheGrille(&Grille->plateau[5], 0); printf("\n");
	sousAfficheGrille(&Grille->plateau[3], 1); sousAfficheGrille(&Grille->plateau[4], 1); sousAfficheGrille(&Grille->plateau[5], 1); printf("\n");
	sousAfficheGrille(&Grille->plateau[3], 2); sousAfficheGrille(&Grille->plateau[4], 2); sousAfficheGrille(&Grille->plateau[5], 2); printf("\n");

	printf("\n");
	
	sousAfficheGrille(&Grille->plateau[6], 0); sousAfficheGrille(&Grille->plateau[7], 0); sousAfficheGrille(&Grille->plateau[8], 0); printf("\n");
	sousAfficheGrille(&Grille->plateau[6], 1); sousAfficheGrille(&Grille->plateau[7], 1); sousAfficheGrille(&Grille->plateau[8], 1); printf("\n");
	sousAfficheGrille(&Grille->plateau[6], 2); sousAfficheGrille(&Grille->plateau[7], 2); sousAfficheGrille(&Grille->plateau[8], 2); printf("\n");

	printf("\n");
}

bool plusDAction(const Grille *Grille)
{
	if (Grille->actionCpt == 0) return true;
	return false;
}

bool peutJouer(const Grille *Grille, const Action *action)
{
	if (plusDAction(Grille)) return false;
	if (Grille->plateau[Grille->plateauSuivant][action->position] != None) return false;
    if (action->position > 8 || action->position < 0) return false;//
	return true;
}

void jouer(Grille *Grille, Action *action)
{
	assert(peutJouer(Grille, action));
	Grille->actionCpt--;
	action->plateauJoue = Grille->plateauSuivant;
	Grille->plateau[Grille->plateauSuivant][action->position] = action->pion;
	Grille->plateauSuivant = action->position;
}

void pasJouer(Grille *grille, const Action *action)
{

	grille->actionCpt++;
	grille->plateauSuivant = action->plateauJoue; 
	grille->plateau[grille->plateauSuivant][action->position] = None;
}
