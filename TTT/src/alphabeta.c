#include "alphabeta.h"

#include <stdlib.h>

static const size_t pronfondeurLimit = 10;
//Profondeur optimal niveau vitesse/qualité de jeu : 12

static bool estTerminal(Grille *grille, Pion joueur, int pronfondeur, int *returnValue)
{
	Pion gagnant = quiGagne(grille);
	if (gagnant != None)
	{
		*returnValue = (gagnant == joueur) ? 1 : -1;
		return true;
	}
	if (plusDAction(grille))
	{
		*returnValue = 0;
		return true;
	}
	if (pronfondeur >= pronfondeurLimit)
	{
		*returnValue = (rand() % 3) - 1;
		return true;
	}
	return false;
} 


int IAmax(Grille *grille, Pion joueur, int pronfondeur, int alpha, int beta)
{
	int returnValue;
	if(estTerminal(grille, joueur, pronfondeur, &returnValue)) return returnValue;

	Action action;
	action.pion = joueur;
	int tmp;
	for (size_t i = 0; i < TAILLE_JEU; ++i)
	{
		action.position = i;
		if (!peutJouer(grille, &action)) continue;

		jouer(grille, &action);
		tmp = IAmin(grille, joueur, pronfondeur + 1, alpha, beta);
		pasJouer(grille, &action);
		if (tmp > alpha)
			alpha = tmp;
		if (alpha >= beta)
			break;
	}
	return alpha;
}

int IAmin(Grille *grille, Pion joueur, int pronfondeur, int alpha, int beta)
{
	int returnValue;
	if(estTerminal(grille, joueur, pronfondeur, &returnValue)) return returnValue;

	Action action;
	action.pion = (joueur == X) ? O : X;
	int tmp;
	for (size_t i = 0; i < TAILLE_JEU; ++i)
	{
		action.position = i;
		if (!peutJouer(grille, &action)) continue;

		jouer(grille, &action);
		tmp = IAmax(grille, joueur, pronfondeur + 1, alpha, beta);
		pasJouer(grille, &action);
		if (tmp < beta)
			beta = tmp;
		if (beta <= alpha)
			break;
	}
	return beta;
}