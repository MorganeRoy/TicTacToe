#ifndef JEU_HEADER
#define JEU_HEADER

#include <stdio.h>
#include <stdbool.h>

#define TAILLE_JEU 9

typedef enum{X, O, None} Pion;

//Une grille de TTT
typedef Pion Plateau[TAILLE_JEU]; 

//Toutes les grilles
typedef struct {
	size_t actionCpt;
	int plateauSuivant;
	Plateau plateau[TAILLE_JEU]; 
} Grille;


typedef struct {
	int plateauJoue;
	int position;
	Pion pion;
} Action;


Pion quiGagne(const Grille *grille);
Grille creerGrille(int demarerPlateau);
void afficheGrille(const Grille *grille);
bool plusDAction(const Grille *grille);
bool peutJouer(const Grille *grille, const Action *actiob);
void jouer(Grille *grille, Action *action);
void pasJouer(Grille *grille, const Action *action);

#endif