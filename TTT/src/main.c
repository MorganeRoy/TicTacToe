#include "alphabeta.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void humainJoue(Grille *grille, Pion pion)
{

	Action action;
	int position;
	action.pion = pion;
	do {
		printf("C'est ton tour, tu dois jouer sur le plateau %d \n", grille->plateauSuivant);
		scanf("%d", &position);
        viderBuffer(); // Sert a eviter les problemes avec des entrées non reconnues
		action.position = position;
	} while (!peutJouer(grille, &action));

	jouer(grille, &action);
}

void ordiJoue(Grille *grille, Pion pion)
{
	printf("\e[1;1H\e[2J");
	if (plusDAction(grille)) return;
	if (quiGagne(grille) != None) return;

	Action action;
	action.pion = pion;

	Action actionFinal; 
	actionFinal.pion = pion;
	actionFinal.position = -1;

	int tmp;
	int alpha = -2;
	int beta = 2;
    for (size_t i = 0; i < TAILLE_JEU; ++i)
    {
    	action.position = i;
    	if (!peutJouer(grille, &action)) continue;

    	jouer(grille, &action);
    	tmp = IAmin(grille, pion, 0, alpha, beta);
    	pasJouer(grille, &action);

		if (tmp > alpha)
		{
			alpha = tmp;
			actionFinal.position = i;
		}
		if (alpha >= beta)
			break;
    }

	jouer(grille, &actionFinal);
	return;
    
}

void StartGame(Grille *grille, Pion humainPion, Pion ordiPion)
{
	assert(humainPion != ordiPion);
	assert(humainPion != None);
	assert(ordiPion != None);
	bool humainTour = (humainPion == X) ? true : false;
	afficheGrille(grille);
	Pion winner;
	while ((winner = quiGagne(grille)) == None) {
		if (humainTour == true) {
			humainJoue(grille, humainPion);
			humainTour = false;
		}
		else {
			ordiJoue(grille, ordiPion);
			humainTour = true;
			afficheGrille(grille);
		}
	}
	printf("\e[1;1H\e[2J");
	afficheGrille(grille);

	switch (winner)
	{
		case X:
			printf("Tu as gagné !\n");
			break;
		case O:
			printf("Tu as perdu , tu es nul!\n");
			break;
		default:
			printf("Match nul !\n");
			break;
	}
}

int main(void)
{
	srand((unsigned int)time(0));

	int commencer;
    printf("\e[1;1H\e[2J");
	printf("Sur quel plateau veux-tu commencer ?\n");
	scanf("%d", &commencer);
	Grille grille = creerGrille(commencer);
    printf("\e[1;1H\e[2J");
	StartGame(&grille, X, O);

	return 0;
}
