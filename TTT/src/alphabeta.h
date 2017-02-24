#ifndef ALPHABETA_HEADER
#define ALPHABETA_HEADER

#include "jeu.h"

int IAmax(Grille *Grille, Pion joueur, int profondeur, int alpha, int beta);
int IAmin(Grille *Grille, Pion joueur, int profondeur, int alpha, int beta);

#endif