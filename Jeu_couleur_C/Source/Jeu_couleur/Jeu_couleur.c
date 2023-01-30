#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* "constantes" */
#define Taille 12
#define Nombre_couleurs 6
#define Nombre_tries 22

#define decalage_avant 30
#define decalage_arriere 40

/* type de donnees */
typedef enum {

	noir = 0, rouge, vert, jaune, bleu, magenta, cyan, blanc
} 

codeCouleur;

/* prototypes */
codeCouleur ** creerGrille (int);

void detruireGrille (codeCouleur ***, int);
void afficherCouleur (int, int, char);
void afficherGrille (codeCouleur **, int);
void grilleAleatoire (codeCouleur **, int, int);

int inonder (codeCouleur **, int);

void propager (codeCouleur **, int, codeCouleur);
void propagation_recursif (codeCouleur **, int, codeCouleur, codeCouleur, int, int);
void jouer (int, int, int);


/* implementations */
codeCouleur ** creerGrille (int taille) {

	int i;

	codeCouleur ** Grille;

	Grille = (codeCouleur **) malloc (taille * sizeof (codeCouleur *));

	for (i = 0; i < taille; ++i) {

		Grille [i] = (codeCouleur *) malloc (taille * sizeof (codeCouleur));
	}

	return Grille;
}

void detruireGrille (codeCouleur *** Grille, int taille) {

	int i;

	for (i = 0; i < taille; ++i) {

		free ((* Grille) [i]);
		free (* Grille);

		* Grille = NULL;
	}
}

void afficherCouleur (int avant, int arriere, char couleur) {

	printf ("\033[%d;%dm%c\033[m",decalage_avant + avant, decalage_arriere + arriere, couleur);
}

void afficherGrille (codeCouleur ** Grille, int taille) {

	int i, j;

	for (i = 0; i < taille; ++i) {

		for (j = 0; j < taille; ++j) {

			afficherCouleur (blanc, noir + Grille [i][j], '0' + Grille [i][j]);
		}

		printf ("\n");
	}
}

void grilleAleatoire (codeCouleur ** Grille, int taille, int nombre) {

	int i, j;

	for (i = 0; i < taille; ++i) {

		for (j = 0; j < taille; ++j) {

			Grille [i][j] = rand() % nombre;
		}
	}
}

int inonder (codeCouleur ** Grille, int taille) {

	int i, j;

	codeCouleur couleur = Grille [0][0];

	for (i = 0; i < taille; ++i) {

		for (j = 0; j < taille; ++j) {

			if (Grille [i][j] != couleur) {

				return 0;
			}
		}
	}

	return 1;
}

void propager (codeCouleur ** Grille, int taille, codeCouleur couleur) {

	if (couleur != Grille [0][0]) {

		propagation_recursif (Grille, taille, Grille [0][0], couleur, 0, 0);
	}
}

void propagation_recursif (codeCouleur ** Grille, int taille, codeCouleur ancienne_couleur, codeCouleur nouvelle_couleur, int i, int j) {

	Grille [i][j] = nouvelle_couleur;

	/* à gauche */
	if ((j > 0) && (Grille [i][j - 1] == ancienne_couleur)) {

		propagation_recursif (Grille, taille, ancienne_couleur, nouvelle_couleur, i, j - 1);
	}

	/* en bas */
	if ((i < taille - 1) && (Grille [i + 1][j] == ancienne_couleur)) {

		propagation_recursif (Grille, taille, ancienne_couleur, nouvelle_couleur, i + 1, j);
	}

	/* à droite */
	if ((j < taille - 1) && (Grille [i][j + 1] == ancienne_couleur)) {

		propagation_recursif (Grille, taille, ancienne_couleur, nouvelle_couleur, i, j + 1);
	}

	/* en haut */
	if ((i > 0) && (Grille [i - 1][j] == ancienne_couleur)) {

		propagation_recursif (Grille, taille, ancienne_couleur, nouvelle_couleur, i - 1, j);
	}
}

void jouer (int taille, int nombre_colonne, int nombre) {

	codeCouleur ** Grille;

	int i, couleur;

	/* initialisation */
	Grille = creerGrille (taille);

	grilleAleatoire (Grille, taille, nombre_colonne);

	afficherGrille (Grille, taille);

	/* boucle principale */
	i = 0;

	while ((i < nombre) && (! inonder (Grille, taille))) {

		printf ("reste %d coups \n choisir une couleur [0 .. %d, - 1 = stop] :", nombre - i, nombre_colonne - 1);

		couleur = - 1;

		do {

			if (! scanf ("%d", &couleur)) {

				break;
			}
		}

		while ((couleur != - 1) && ((couleur < 0) && (couleur >= nombre_colonne)));

		if (couleur == - 1) {

			break;
		}

		propager (Grille, taille, couleur);

		afficherGrille (Grille, taille);

		++i;
	}

	/* résultat */
	if (couleur == -1) {

		printf ("Bye ! \n");

	} else if (inonder (Grille, taille)) {

		printf ("GAGNE ! \n");


	} else {

		printf ("PERDU ! \n");
	}

	/* nettoie la mémoire */
	detruireGrille (&Grille, taille);
}

int main () {

	jouer (Taille, Nombre_couleurs, Nombre_tries);

	return EXIT_SUCCESS;
}
