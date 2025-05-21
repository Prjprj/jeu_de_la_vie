/*********************
 *					 *
 *   JEU DE LA VIE   *
 * (jeu_de_la_vie.c) *
 *                   *
 *********************/

/* Inclusion des biblioth�ques */
#include"biblio.h"
#include"constantes.h"
#include"types.h"
#include"var_globales.h"
#include"jeu_de_la_vie.h"

/* Fonction permettant de lire un caract�re entr� sur la sortie
 standard et de le transformer en entier */
int litEntier() {
	char s[256];
	fgets(s, 256, stdin);
	return atoi(s);
}

/* Fontion permettant de lire sur la sortie standard le premier
 caract�re tap�, et d'ignorer le reste */
char litPremierCarac() {
	char s[256];
	fgets(s, 255, stdin);
	return s[0];
}

/* Fonction permettant de lire une cha�ne de caract�res entr�e
 sur la sortir standard */
char* litCaractere() {
	char* s;
	s = (char*) malloc(1000);
	fgets(s, 255, stdin);
	return (s);
}

/* Transforme un tableau d'entiers � deux dimensions repr�sentant
 une matice en une chaine de caracteres */
char* intToCharMatrice(int** mat, Taille dim) {
	char* resultat;
	int hauteur, largeur, taille, i, j, k = 0;
	hauteur = dim.hauteur;
	largeur = dim.largeur;
	taille = (hauteur + 1) * (largeur + 1) + 1;

	resultat = (char*) malloc(taille * sizeof(char));
	for (i = 0; i < hauteur; i = i + 1) {
		for (j = 0; j < largeur; j = j + 1) {
			resultat[k] = '0' + (char) mat[i][j];
			k++;
		}
		resultat[k] = '\n';
		k++;
	}
	resultat[k] = '\0';
	return (intToCharMatriceAvecEspace(resultat));
}

/* Remplace les "0" une chaine de caract�res repr�sentant une matrice
 par des "_" */
char* intToCharMatriceAvecEspace(char* chaine) {
	char *resultat;
	int i, longueur;

	longueur = strlen(chaine);
	resultat = (char*) malloc(longueur * sizeof(char));
	for (i = 0; i < longueur - 1; i++) {
		if (chaine[i] != '0') {
			resultat[i] = chaine[i];
		} else {
			resultat[i] = '_';
		}
	}
	resultat[longueur - 1] = '\0';
	return resultat;
}

/* Transforme une chaine de caracteres contenant en fait une matrice
 en un tableau d'entiers � deux dimensions sans retour chariot
 � la fin de chaque ligne de la matrice */
char* intToCharMatriceSansEnter(int** mat, Taille dim) {
	char* resultat;
	int hauteur, largeur, taille, i, j, k = 0;
	hauteur = dim.hauteur;
	largeur = dim.largeur;
	taille = hauteur * largeur + 1;

	resultat = (char*) malloc(taille * sizeof(char));
	for (i = 0; i < hauteur; i = i + 1) {
		for (j = 0; j < largeur; j = j + 1) {
			resultat[k] = '0' + (char) mat[i][j];
			k++;
		}
	}
	resultat[k] = '\0';
	return resultat;
}

/* Transforme une chaine de caracteres contenant en fait une matrice
 en un tableau d'entiers � deux dimensions */
int** charToIntMatrice(char* matrice, Taille dim) {
	int** mat;
	int hauteur, largeur, i, j, k;
	int long valeur;
	char c;
	hauteur = dim.hauteur;
	largeur = dim.largeur;

	mat = (int**) malloc(hauteur * sizeof(int*));
	for (i = 0; i < hauteur; i++) {
		mat[i] = (int*) malloc(largeur * sizeof(int));
	}
	i = 0;
	j = 0;
	k = 0;
	do {
		while (j < largeur) {
			c = matrice[k];
			// strtol covertit une chaine en un entier long
			valeur = strtol(&c, (char **) NULL, 10);
			mat[i][j] = (int) valeur;
			j++;
			k++;
		}
		i++;
		j = 0;
	} while (i < hauteur);
	return mat;
}

/* Fonction permettant de dispatcher une matrice en souches */
Souche* dispatchMatEnSouches(int** matrice, Param param, int nbSouches) {
	int i, j, k, valeur, hauteur, largeur, max = 0;
	Souche* souche;

	hauteur = (param.taille).hauteur;
	largeur = (param.taille).largeur;
	souche = (Souche*) malloc(nbSouches * sizeof(Souche));
	for (i = 0; i < nbSouches; i++) {
		souche[i].hauteur = hauteur;
		souche[i].largeur = largeur;
		souche[i].typeCell = i + 1;
		souche[i].mat = (int**) malloc(hauteur * sizeof(int*));
		for (j = 0; j < hauteur; j++) {
			souche[i].mat[j] = (int*) malloc(largeur * sizeof(int));
		}
		for (k = 0; k < hauteur; k++) {
			for (j = 0; j < largeur; j++) {
				souche[i].mat[k][j] = 0;
			}
		}
	}
	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			if (matrice[i][j] != 0) {
				valeur = matrice[i][j];
				souche[valeur - 1].mat[i][j] = valeur;
			}
		}
	}
	return souche;
}

/* Fonction permettant de retourner la hauteur et la largeur maximales
 parmi diff�rentes souches stock�es � l'aide d'un tableau de Souche */
int* maxHauteurLargeur(int nbSouches, Souche *souche) {
	int i;
	int largeur = souche[0].largeur;
	int hauteur = souche[0].hauteur;
	int* hauteur_largeur = (int*) malloc(2 * sizeof(int));

	for (i = 1; i < nbSouches; i++) {
		if (largeur < souche[i].largeur)
			largeur = souche[i].largeur;
		if (hauteur < souche[i].hauteur)
			hauteur = souche[i].hauteur;
	}
	hauteur_largeur[0] = hauteur;
	hauteur_largeur[1] = largeur;
	return hauteur_largeur;
}

/* Proc�dure permettant de copier une matrice mat1 dans une matrice mat2
 de dimensions taille (hauteur et largeur) */
void copieMatrice(int** mat1, int** mat2, Taille taille) {
	int hauteur, largeur, i, j;
	hauteur = taille.hauteur;
	largeur = taille.largeur;
	for (i = 0; i < hauteur; i = i + 1) {
		for (j = 0; j < largeur; j = j + 1) {
			mat2[i][j] = mat1[i][j];
		}
	}
}

/* Proc�dure permettant de copier un certain nombre de souches cellulaires
 nbSouches, souche1, dans souche2 */
void copieSouche(int nbSouches, Souche *souche1, Souche *souche2) {
	int* hauteur_largeur;
	int largeur, hauteur;
	Taille taille;
	int i, j, k;

	hauteur_largeur = maxHauteurLargeur(nbSouches, souche1);
	hauteur = hauteur_largeur[0];
	largeur = hauteur_largeur[1];
	for (k = 0; k < nbSouches; k++) {
		souche2[k].mat = (int**) malloc(hauteur * sizeof(int*));
		for (i = 0; i < hauteur; i++) {
			souche2[k].mat[i] = (int*) malloc(largeur * sizeof(int));
		}
		for (i = 0; i < hauteur; i++) {
			for (j = 0; j < largeur; j++) {
				souche2[k].mat[i][j] = 0;
			}
		}
		souche2[k].hauteur = souche1[k].hauteur;
		souche2[k].largeur = souche1[k].largeur;
		souche2[k].typeCell = souche1[k].typeCell;
		taille.hauteur = souche1[k].hauteur;
		taille.largeur = souche1[k].largeur;
		copieMatrice(souche1[k].mat, souche2[k].mat, taille);
	}
}

/* Proc�dure permettant d'afficher � la sortie standard une matrice de dimensions
 taille (hauteur et largeur) */
void afficheMatrice(int** mat, Taille taille) {
	int hauteur, largeur, i, j;
	hauteur = taille.hauteur;
	largeur = taille.largeur;
	printf("\t");
	for (i = 0; i < hauteur; i = i + 1) {
		for (j = 0; j < largeur; j = j + 1) {
			if (mat[i][j] != 0) {
				printf("%d", mat[i][j]);
			} else {
				printf("_");
			}
		}
		printf("\n\t");
	}
}

/* Fonction permettant de tester si une cellule (une case de la matrice)
 est vide (c'est-�-dire vaut 0) ou non */
int estCelluleVide(int cellule) {
	if (cellule == 0)
		return TRUE;
	else
		return FALSE;
}

/* Fonction permettant de compter le nombre de cellules voisines
 de type typeCell � une certaine cellule donn�e */
int* comptage(int* compteur, int cellule, int typeCell) {
	int test;
	test = estCelluleVide(cellule);

	if (test == FALSE) {
		compteur[0] = compteur[0] + 1;
		if (cellule == typeCell) {
			compteur[typeCell] = compteur[typeCell] + 1;
		}
	}
	return compteur;
}

/* Fonction permettant de compter le nombre de cellules voisines � une
 cellule se situant dans les diff�rentes matrices d'un certain nombre nbSouches
 de souches donn�es � l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace torique, c'est-�-dire que le haut et le bas, et,
 la gauche et la droite se rejoignent */
int* nbCellVoisinesEspaceTorique(int i, int j, int nbSouches, Souche *souche) {

	// compteur[0]: nb de cellules totales
	// compteur[1]: nb de cellules de type 1ere souche
	// ...
	// compteur[nbSouches]: nb de cellules de type nbSouches
	int* compteur;
	int largeur;
	int hauteur;
	int typeCell;
	int k;

	compteur = (int*) malloc((nbSouches + 1) * sizeof(int*));
	for (k = 0; k < nbSouches + 1; k++) {
		compteur[k] = 0;
	}

	for (k = 0; k < nbSouches; k++) {
		largeur = souche[k].largeur;
		hauteur = souche[k].hauteur;
		typeCell = souche[k].typeCell;

		if ((i != 0) && (j != 0)) {
			compteur = comptage(compteur, souche[k].mat[i - 1][j], typeCell);
			compteur = comptage(compteur, souche[k].mat[i - 1][j - 1],
					typeCell);
			compteur = comptage(compteur,
					souche[k].mat[i - 1][(j + 1) % largeur], typeCell);
			compteur = comptage(compteur, souche[k].mat[i][j], typeCell);
			compteur = comptage(compteur, souche[k].mat[i][j - 1], typeCell);
			compteur = comptage(compteur, souche[k].mat[i][(j + 1) % largeur],
					typeCell);
			compteur = comptage(compteur, souche[k].mat[(i + 1) % hauteur][j],
					typeCell);
			compteur = comptage(compteur,
					souche[k].mat[(i + 1) % hauteur][j - 1], typeCell);
			compteur = comptage(compteur,
					souche[k].mat[(i + 1) % hauteur][(j + 1) % largeur],
					typeCell);
		}

		else {
			if ((i == 0) && (j != 0)) {
				compteur = comptage(compteur, souche[k].mat[hauteur - 1][j],
						typeCell);
				compteur = comptage(compteur, souche[k].mat[hauteur - 1][j - 1],
						typeCell);
				compteur = comptage(compteur,
						souche[k].mat[hauteur - 1][(j + 1) % largeur],
						typeCell);
				compteur = comptage(compteur, souche[k].mat[i][j], typeCell);
				compteur = comptage(compteur, souche[k].mat[i][j - 1],
						typeCell);
				compteur = comptage(compteur,
						souche[k].mat[i][(j + 1) % largeur], typeCell);
				compteur = comptage(compteur,
						souche[k].mat[(i + 1) % hauteur][j], typeCell);
				compteur = comptage(compteur,
						souche[k].mat[(i + 1) % hauteur][j - 1], typeCell);
				compteur = comptage(compteur,
						souche[k].mat[(i + 1) % hauteur][(j + 1) % largeur],
						typeCell);
			}

			else {
				if ((i != 0) && (j == 0)) {
					compteur = comptage(compteur, souche[k].mat[i - 1][j],
							typeCell);
					compteur = comptage(compteur,
							souche[k].mat[i - 1][largeur - 1], typeCell);
					compteur = comptage(compteur,
							souche[k].mat[i - 1][(j + 1) % largeur], typeCell);
					compteur = comptage(compteur, souche[k].mat[i][j],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i][largeur - 1],
							typeCell);
					compteur = comptage(compteur,
							souche[k].mat[i][(j + 1) % largeur], typeCell);
					compteur = comptage(compteur,
							souche[k].mat[(i + 1) % hauteur][j], typeCell);
					compteur = comptage(compteur,
							souche[k].mat[(i + 1) % hauteur][largeur - 1],
							typeCell);
					compteur = comptage(compteur,
							souche[k].mat[(i + 1) % hauteur][(j + 1) % largeur],
							typeCell);
				}

				else {
					compteur = comptage(compteur, souche[k].mat[hauteur - 1][j],
							typeCell);
					compteur = comptage(compteur,
							souche[k].mat[hauteur - 1][largeur - 1], typeCell);
					compteur = comptage(compteur,
							souche[k].mat[hauteur - 1][(j + 1) % largeur],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i][j],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i][largeur - 1],
							typeCell);
					compteur = comptage(compteur,
							souche[k].mat[i][(j + 1) % largeur], typeCell);
					compteur = comptage(compteur,
							souche[k].mat[(i + 1) % hauteur][j], typeCell);
					compteur = comptage(compteur,
							souche[k].mat[(i + 1) % hauteur][largeur - 1],
							typeCell);
					compteur = comptage(compteur,
							souche[k].mat[(i + 1) % hauteur][(j + 1) % largeur],
							typeCell);
				}
			}
		}
	}
	return compteur;
}

/* Fonction permettant de compter le nombre de cellules voisines � une
 cellule se situant dans les diff�rentes matrices d'un certain nombre nbSouches
 de souches donn�es � l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace cylindrique, c'est-�-dire que le haut et le bas
 ne se rejoignent pas, mais que la gauche et la droite se rejoignent */
int* nbCellVoisinesEspaceCylindrique(int i, int j, int nbSouches,
		Souche *souche) {

	// compteur[0]: nb de cellules totales
	// compteur[1]: nb de cellules de type 1ere souche
	// ...
	// compteur[nbSouches]: nb de cellules de type nbSouches
	int* compteur;
	int largeur;
	int hauteur;
	int typeCell;
	int k;

	compteur = (int*) malloc((nbSouches + 1) * sizeof(int*));
	for (k = 0; k < nbSouches + 1; k++) {
		compteur[k] = 0;
	}

	for (k = 0; k < nbSouches; k++) {
		largeur = souche[k].largeur;
		hauteur = souche[k].hauteur;
		typeCell = souche[k].typeCell;

		if ((i != 0) && (i != (hauteur - 1)) && (j != 0)) {
			compteur = comptage(compteur, souche[k].mat[i - 1][j], typeCell);
			compteur = comptage(compteur, souche[k].mat[i - 1][j - 1],
					typeCell);
			compteur = comptage(compteur,
					souche[k].mat[i - 1][(j + 1) % largeur], typeCell);
			compteur = comptage(compteur, souche[k].mat[i][j], typeCell);
			compteur = comptage(compteur, souche[k].mat[i][j - 1], typeCell);
			compteur = comptage(compteur, souche[k].mat[i][(j + 1) % largeur],
					typeCell);
			compteur = comptage(compteur, souche[k].mat[i + 1][j], typeCell);
			compteur = comptage(compteur, souche[k].mat[i + 1][j - 1],
					typeCell);
			compteur = comptage(compteur,
					souche[k].mat[i + 1][(j + 1) % largeur], typeCell);
		}

		else {
			if ((i == 0) && (j != 0)) {
				compteur = comptage(compteur, souche[k].mat[i][j], typeCell);
				compteur = comptage(compteur, souche[k].mat[i][j - 1],
						typeCell);
				compteur = comptage(compteur,
						souche[k].mat[i][(j + 1) % largeur], typeCell);
				compteur = comptage(compteur, souche[k].mat[i + 1][j],
						typeCell);
				compteur = comptage(compteur, souche[k].mat[i + 1][j - 1],
						typeCell);
				compteur = comptage(compteur,
						souche[k].mat[i + 1][(j + 1) % largeur], typeCell);
			}

			else {
				if ((i == (hauteur - 1)) && (j != 0)) {
					compteur = comptage(compteur, souche[k].mat[i][j],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i][j - 1],
							typeCell);
					compteur = comptage(compteur,
							souche[k].mat[i][(j + 1) % largeur], typeCell);
					compteur = comptage(compteur, souche[k].mat[i - 1][j],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i - 1][j - 1],
							typeCell);
					compteur = comptage(compteur,
							souche[k].mat[i - 1][(j + 1) % largeur], typeCell);
				}

				else {
					if ((i != 0) && (i != (hauteur - 1)) && (j == 0)) {
						compteur = comptage(compteur, souche[k].mat[i - 1][j],
								typeCell);
						compteur = comptage(compteur,
								souche[k].mat[i - 1][largeur - 1], typeCell);
						compteur = comptage(compteur,
								souche[k].mat[i - 1][(j + 1) % largeur],
								typeCell);
						compteur = comptage(compteur, souche[k].mat[i][j],
								typeCell);
						compteur = comptage(compteur,
								souche[k].mat[i][largeur - 1], typeCell);
						compteur = comptage(compteur,
								souche[k].mat[i][(j + 1) % largeur], typeCell);
						compteur = comptage(compteur, souche[k].mat[i + 1][j],
								typeCell);
						compteur = comptage(compteur,
								souche[k].mat[i + 1][largeur - 1], typeCell);
						compteur = comptage(compteur,
								souche[k].mat[i + 1][(j + 1) % largeur],
								typeCell);
					}

					else {
						if ((i == 0) && (j == 0)) {
							compteur = comptage(compteur, souche[k].mat[i][j],
									typeCell);
							compteur = comptage(compteur,
									souche[k].mat[i][largeur - 1], typeCell);
							compteur = comptage(compteur,
									souche[k].mat[i][(j + 1) % largeur],
									typeCell);
							compteur = comptage(compteur,
									souche[k].mat[i + 1][j], typeCell);
							compteur = comptage(compteur,
									souche[k].mat[i + 1][largeur - 1],
									typeCell);
							compteur = comptage(compteur,
									souche[k].mat[i + 1][(j + 1) % largeur],
									typeCell);
						}

						else {
							if ((i == (hauteur - 1)) && (j == 0)) {
								compteur = comptage(compteur,
										souche[k].mat[i][j], typeCell);
								compteur = comptage(compteur,
										souche[k].mat[i][largeur - 1],
										typeCell);
								compteur = comptage(compteur,
										souche[k].mat[i][(j + 1) % largeur],
										typeCell);
								compteur = comptage(compteur,
										souche[k].mat[i - 1][j], typeCell);
								compteur = comptage(compteur,
										souche[k].mat[i - 1][largeur - 1],
										typeCell);
								compteur = comptage(compteur,
										souche[k].mat[i - 1][(j + 1) % largeur],
										typeCell);
							}
						}
					}
				}
			}
		}
	}
	return compteur;
}

/* Fonction permettant de compter le nombre de cellules voisines � une
 cellule se situant dans les diff�rentes matrices d'un certain nombre nbSouches
 de souches donn�es � l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace carr�, c'est-�-dire que le haut et le bas, et, 
 la gauche et la droite ne se rejoignent pas */
int* nbCellVoisinesEspaceCarre(int i, int j, int nbSouches, Souche *souche) {

	// compteur[0]: nb de cellules totales
	// compteur[1]: nb de cellules de type 1ere souche
	// ...
	// compteur[nbSouches]: nb de cellules de type nbSouches
	int* compteur;
	int largeur;
	int hauteur;
	int typeCell;
	int k;

	compteur = (int*) malloc((nbSouches + 1) * sizeof(int*));
	for (k = 0; k < nbSouches + 1; k++) {
		compteur[k] = 0;
	}

	for (k = 0; k < nbSouches; k++) {
		largeur = souche[k].largeur;
		hauteur = souche[k].hauteur;
		typeCell = souche[k].typeCell;

		if ((i != 0) && (i != (hauteur - 1)) && (j != 0)
				&& (j != (largeur - 1))) {
			compteur = comptage(compteur, souche[k].mat[i][j], typeCell);
			compteur = comptage(compteur, souche[k].mat[i - 1][j - 1],
					typeCell);
			compteur = comptage(compteur, souche[k].mat[i - 1][j], typeCell);
			compteur = comptage(compteur, souche[k].mat[i - 1][j + 1],
					typeCell);
			compteur = comptage(compteur, souche[k].mat[i][j + 1], typeCell);
			compteur = comptage(compteur, souche[k].mat[i + 1][j + 1],
					typeCell);
			compteur = comptage(compteur, souche[k].mat[i + 1][j], typeCell);
			compteur = comptage(compteur, souche[k].mat[i + 1][j - 1],
					typeCell);
			compteur = comptage(compteur, souche[k].mat[i][j - 1], typeCell);
		}

		else {
			if ((i == 0) && (j != 0) && j != (largeur - 1)) {
				compteur = comptage(compteur, souche[k].mat[i][j], typeCell);
				compteur = comptage(compteur, souche[k].mat[i][j - 1],
						typeCell);
				compteur = comptage(compteur, souche[k].mat[i + 1][j - 1],
						typeCell);
				compteur = comptage(compteur, souche[k].mat[i + 1][j],
						typeCell);
				compteur = comptage(compteur, souche[k].mat[i + 1][j + 1],
						typeCell);
				compteur = comptage(compteur, souche[k].mat[i][j + 1],
						typeCell);
			}

			else {
				if ((i != 0) && (i != (hauteur - 1)) && (j == 0)) {
					compteur = comptage(compteur, souche[k].mat[i][j],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i - 1][j],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i - 1][j + 1],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i][j + 1],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i + 1][j + 1],
							typeCell);
					compteur = comptage(compteur, souche[k].mat[i + 1][j],
							typeCell);
				}

				else {
					if ((i == 0) && (j == 0)) {
						compteur = comptage(compteur, souche[k].mat[i][j],
								typeCell);
						compteur = comptage(compteur, souche[k].mat[i][j + 1],
								typeCell);
						compteur = comptage(compteur,
								souche[k].mat[i + 1][j + 1], typeCell);
						compteur = comptage(compteur, souche[k].mat[i + 1][j],
								typeCell);
					}

					else {
						if ((i == 0) && (j == (largeur - 1))) {
							compteur = comptage(compteur, souche[k].mat[i][j],
									typeCell);
							compteur = comptage(compteur,
									souche[k].mat[i][j - 1], typeCell);
							compteur = comptage(compteur,
									souche[k].mat[i + 1][j - 1], typeCell);
							compteur = comptage(compteur,
									souche[k].mat[i + 1][j], typeCell);
						}

						else {
							if ((i == (hauteur - 1)) && (j == 0)) {
								compteur = comptage(compteur,
										souche[k].mat[i][j], typeCell);
								compteur = comptage(compteur,
										souche[k].mat[i - 1][j], typeCell);
								compteur = comptage(compteur,
										souche[k].mat[i - 1][j + 1], typeCell);
								compteur = comptage(compteur,
										souche[k].mat[i][j + 1], typeCell);
							}

							else {
								if ((i == (hauteur - 1))
										&& (j == (largeur - 1))) {
									compteur = comptage(compteur,
											souche[k].mat[i][j], typeCell);
									compteur = comptage(compteur,
											souche[k].mat[i - 1][j], typeCell);
									compteur = comptage(compteur,
											souche[k].mat[i - 1][j - 1],
											typeCell);
									compteur = comptage(compteur,
											souche[k].mat[i][j - 1], typeCell);
								}

								else {
									if ((i == (hauteur - 1)) && (j != 0)
											&& (j != (largeur - 1))) {
										compteur = comptage(compteur,
												souche[k].mat[i][j], typeCell);
										compteur = comptage(compteur,
												souche[k].mat[i][j - 1],
												typeCell);
										compteur = comptage(compteur,
												souche[k].mat[i - 1][j - 1],
												typeCell);
										compteur = comptage(compteur,
												souche[k].mat[i - 1][j],
												typeCell);
										compteur = comptage(compteur,
												souche[k].mat[i - 1][j + 1],
												typeCell);
										compteur = comptage(compteur,
												souche[k].mat[i][j + 1],
												typeCell);
									}

									else {
										if ((i != 0) && (i != (hauteur - 1))
												&& (j == (largeur - 1))) {
											compteur = comptage(compteur,
													souche[k].mat[i][j],
													typeCell);
											compteur = comptage(compteur,
													souche[k].mat[i - 1][j],
													typeCell);
											compteur = comptage(compteur,
													souche[k].mat[i - 1][j - 1],
													typeCell);
											compteur = comptage(compteur,
													souche[k].mat[i][j - 1],
													typeCell);
											compteur = comptage(compteur,
													souche[k].mat[i + 1][j - 1],
													typeCell);
											compteur = comptage(compteur,
													souche[k].mat[i + 1][j],
													typeCell);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return compteur;
}

/* Fonction permettant de d�cider la mort ou non d'une cellule se situant �
 la ligne i et la colonne j d'une matrice par rapport aux calculs du nombre
 de cellules voisines dans un certain espace */
int celluleDoitMourir(int i, int j, int nbSouches, Souche *souche) {
	int *compteur;
	char espace = parametres.espace;

	switch (espace) {
	case 'T':
		compteur = nbCellVoisinesEspaceTorique(i, j, nbSouches, souche);
		break;
	case 'C':
		compteur = nbCellVoisinesEspaceCylindrique(i, j, nbSouches, souche);
		break;
	case 'K':
		compteur = nbCellVoisinesEspaceCarre(i, j, nbSouches, souche);
		break;
	default:
		printf("Erreur dans le choix de l'espace de l'experence\n");
		exit(-1);
	}
	if (!((compteur[0] == 3) || (compteur[0] == 4))) {
		free(compteur);
		return TRUE;
	} else {
		free(compteur);
		return FALSE;
	}
}

/* Fonction permettant de d�cider la naissance ou non d'une cellule se situant �
 la ligne i et la colonne j d'une matrice par rapport aux calculs du nombre
 de cellules voisines dans un certain espace */
int celluleDoitNaitre(int i, int j, int nbSouches, Souche *souche) {
	int *compteur;
	int k;
	char espace = parametres.espace;

	switch (espace) {
	case 'T':
		compteur = nbCellVoisinesEspaceTorique(i, j, nbSouches, souche);
		break;
	case 'C':
		compteur = nbCellVoisinesEspaceCylindrique(i, j, nbSouches, souche);
		break;
	case 'K':
		compteur = nbCellVoisinesEspaceCarre(i, j, nbSouches, souche);
		break;
	default:
		printf("Erreur dans le choix de l'espace de l'experence\n");
		exit(-1);
	}
	for (k = 0; k < nbSouches + 1; k++) {
		if (compteur[k + 1] == 3) {
			free(compteur);
			return (k + 1);
		}
	}
	free(compteur);
	return 0;
}

/* Fonction permettant de comparer deux matrice. Si elles sont identiques
 alors la fonction retourne vrai (elles sont dans un �tat stationnaire
 sinon elle retourne faux */
int etatStationnaire(int** mat1, int** mat2, Taille taille) {
	int hauteur, largeur, i, j;
	int nbCellules;
	int compteur = 0;
	hauteur = taille.hauteur;
	largeur = taille.largeur;
	nbCellules = largeur * hauteur;

	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			if (mat1[i][j] == mat2[i][j])
				compteur++;
		}
	}
	if (compteur == nbCellules)
		return TRUE;
	else
		return FALSE;
}

/* Fonction permettant de regrouper les matrices d'un certain nombre de souches
 nbSouches dans une seule matrice. Si plusieurs cellules se situent � un m�me
 emplacement alors elles s'entretuent pour obtenir la place. Par cons�quent
 la case correspondante reste vide */
int** regroupementSouches(int nbSouches, Souche *souche) {
	int* hauteur_largeur;
	int largeur, hauteur;
	int i, j, k;
	int** mat_return;

	hauteur_largeur = maxHauteurLargeur(nbSouches, souche);
	hauteur = hauteur_largeur[0];
	largeur = hauteur_largeur[1];
	mat_return = (int**) malloc(hauteur * sizeof(int*));
	for (i = 0; i < hauteur; i++) {
		mat_return[i] = (int*) malloc(largeur * sizeof(int));
	}
	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			mat_return[i][j] = 0;
		}
	}

	/* lors du regroupement des diff�rentes souches, si plusieurs cellules
	 sont plac�es � une m�me place, alors ces cellules s'entretuent pour obtenir la place
	 par cons�quent, la place reste vide
	 */
	for (k = 0; k < nbSouches; k++) {
		for (i = 0; i < hauteur; i++) {
			for (j = 0; j < largeur; j++) {
				if ((mat_return[i][j] == 0) && (souche[k].mat[i][j] != 0))
					mat_return[i][j] = souche[k].mat[i][j];
			}
		}
	}
	free(hauteur_largeur);
	return mat_return;
}

/* Fonction qui initialise une taille (hauteur et largeur) par d�faut */
Taille tailleParDefaut() {
	Taille taille;
	taille.hauteur = 20;
	taille.largeur = 20;
	return taille;
}

/* Proc�dure permettant d'initialiser les parametres aux valeurs par d�faut */
void initParamParDefaut() {
	parametres.espace = ESPACE_PAR_DEFAUT;
	parametres.taille = tailleParDefaut();
	parametres.vitesse = VITESSE_PAR_DEFAUT;
}

/* Proc�dure permettant de modifier l'espace de d�veloppement des cellules */
void setEspace(char espace) {
	parametres.espace = espace;
}

/* Proc�dure permettant de modifier la vitesse de d�veloppement des cellules */
void setVitesse(int vitesse) {
	parametres.vitesse = vitesse;
}

/* Proc�dure permettant de modifier la taille de l'espace de 
 d�veloppement des cellules */
void setTaille(Taille taille) {
	parametres.taille = taille;
}

/* Fonction permettant d'initialiser une souche */
Souche initialisationSouche(Taille taille, int typeCell, int** mat) {
	Souche souche;
	souche.hauteur = taille.hauteur;
	souche.largeur = taille.largeur;
	souche.typeCell = typeCell;
	souche.mat = mat;
	return souche;
}

/* Poc�dure permettant de g�rer le temps, la vitesse d'avancement, d'�volution
 de l'exp�rience */
void tempsAvancement() {
	int attente, i;
	switch (parametres.vitesse) {
	// Rapide
	case 3:
		attente = 300000000;
		break;
		// Normal
	case 2:
		attente = 600000000;
		break;
		// Lent
	case 1:
		attente = 900000000;
		break;
		// Personnel
	case 4:
		attente = 1;
		break;
	default:
		printf("Choix par defaut (P)\n");
	}
	for (i = 0; i < attente; i++)
		;
}

/* Fonction g�n�rant un nombre al�atoire entre 1 et m */
int generer(int m) {
	return ((rand() % (m - 1)) + 1);
}

/* Fonction permettant de g�n�rer une souche al�atoire de taille
 (hauteur et largeur) et type de cellules donn�s */
Souche generationUneSouche(Taille taille, int typeCell) {
	Souche souche;
	int** mat;
	int i, j, k, nbCell, hauteur, largeur;
	hauteur = taille.hauteur;
	largeur = taille.largeur;
	nbCell = generer(hauteur + largeur);
	mat = (int**) malloc(hauteur * sizeof(int*));
	for (i = 0; i < hauteur; i++) {
		mat[i] = (int*) malloc(largeur * sizeof(int));
	}
	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			mat[i][j] = 0;
		}
	}
	souche.hauteur = hauteur;
	souche.largeur = largeur;
	souche.typeCell = typeCell;
	for (k = 0; k < nbCell; k++) {
		i = (generer(hauteur)) - 1;
		j = (generer(largeur)) - 1;
		mat[i][j] = typeCell;
	}
	souche.mat = mat;
	return souche;
}

/* Fonction permettant de g�n�rer al�atoirement un certain nombre de
 souches nbSouches et de taille (hauteur et largeur) donn�es */
Souche* generationPlusieursSouches(int nbSouches, Taille taille) {
	Souche* souche;
	int k, hauteur, largeur;
	hauteur = taille.hauteur;
	largeur = taille.largeur;
	souche = (Souche*) malloc(nbSouches * sizeof(Souche));
	for (k = 0; k < nbSouches; k++) {
		souche[k] = generationUneSouche(taille, k + 1);
	}
	return souche;
}

/* Fonction qui teste si un fichier dont le nom est donn�
 en argument existe. Retourne TRUE (1) s'il existe et
 FALSE (0) sinon */
int existeFichier(char* nomFichier) {
	FILE* fichier;
	int test;

	fichier = fopen(nomFichier, "r");
	if (fichier == NULL) {
		// erreur d'ouverture
		test = FALSE;
	} else {
		test = TRUE;
		fclose(fichier);
	}
	return test;
}

/* Proc�dure permettant de sauvegarder une exp�rience
 en cours dans un fichier */
void sauvegarde(int nbSouches, int** mat, char* nomFichier) {
	FILE *fichier;
	char* matrice;

	/* Test de l'existence de fichier suppos� fait en amont */
	/* Le fichier n'existe pas sous ce nom.
	 Donc la sauvegarde peut se faire.
	 Le mode "w" permet d'ouvrir un fichier en mode �criture
	 si le fichier n'existe pas, il est cr��
	 sinon la longueur du fichier est ramen�e � 0.
	 Le pointeur de flux est plac� au d�but du fichier. */
	fichier = fopen(nomFichier, "w");
	matrice = intToCharMatriceSansEnter(mat, parametres.taille);
	fprintf(fichier, "Nombre de souches: %d\n", nbSouches);
	fprintf(fichier, "Espace de l'experience: %c\n", parametres.espace);
	fprintf(fichier, "Dimensions:\n\t- hauteur: %d\n\t- largeur: %d\n",
			(parametres.taille).hauteur, (parametres.taille).largeur);
	fprintf(fichier, "Vitesse de l'experience: %d\n", parametres.vitesse);
	fprintf(fichier, "Souche cellulaire:\n%s", matrice);
	fclose(fichier);

}

/* Fonction permettant de charger une exp�rience pr�alablement sauvegard�e */
Souche* chargement(int* nbSouches, Param* param, char* nomFichier) {
	FILE *fichier;
	int** mat;
	char* matChar;
	char* phrase;
	int taille;
	char c = '\n';
	int i;
	Souche* souche;

	/* Test de l'existence de fichier suppos� fait en amont */
	/* Ouverture du fichier en mode lecture */
	fichier = fopen(nomFichier, "r");
	fscanf(fichier, "Nombre de souches: %d\n", nbSouches);
	fscanf(fichier, "Espace de l'experience: %c\n", &(param->espace));
	fscanf(fichier, "Dimensions:\n\t- hauteur: %d\n\t- largeur: %d\n",
			&((param->taille).hauteur), &((param->taille).largeur));
	fscanf(fichier, "Vitesse de l'experience: %d\n", &(param->vitesse));
	taille = ((param->taille).hauteur + 1) * ((param->taille).largeur + 1) + 1;
	phrase = (char*) malloc(((param->taille).largeur) * sizeof(char));
	matChar = (char*) malloc(taille * sizeof(char));
	fscanf(fichier, "Souche cellulaire:\n%s", matChar);
	mat = (int**) malloc(((parametres.taille).hauteur) * sizeof(int*));
	for (i = 0; i < ((parametres.taille).hauteur); i++) {
		mat[i] = (int*) malloc(((parametres.taille).largeur) * sizeof(int));
	}
	mat = charToIntMatrice(matChar, param->taille);
	souche = dispatchMatEnSouches(mat, *param, *nbSouches);
	fclose(fichier);
	return (souche);
}

/* Proc�dure permettant de lib�rer la place en m�moire allou�e 
 au pr�alable pour les matrices et souches qui ont �t� n�cessaire
 lors du d�veloppement des cellules */
void liberationAllocation() {
	free(matriceG);
	free(matriceTempG);
	free(soucheG);
	free(soucheTempG);
}

/* Proc�dure correspondant � l'algorithme du jeu de la vie,
 � savoir l'�volution des cellules jusqu'� un �tat stationnaire
 ou un arr�t de la part de l'observateur */
void algorithme(void) {
	int valeur, etat, i, j;
	Taille taille = parametres.taille;

	copieMatrice(matriceG, matriceTempG, taille);
	copieSouche(nbSouchesG, soucheG, soucheTempG);
	for (i = 0; i < taille.hauteur; i = i + 1) {
		for (j = 0; j < taille.largeur; j = j + 1) {
			if (estCelluleVide(matriceG[i][j]) == TRUE) {
				if ((valeur = celluleDoitNaitre(i, j, nbSouchesG, soucheG))
						!= 0) {
					matriceTempG[i][j] = valeur;
					soucheTempG[valeur - 1].mat[i][j] = valeur;
				}
			} else {
				valeur = matriceG[i][j];
				if (celluleDoitMourir(i, j, nbSouchesG, soucheG) == TRUE) {
					matriceTempG[i][j] = 0;
					soucheTempG[valeur - 1].mat[i][j] = 0;
				}
			}
		}
	}
	etat = etatStationnaire(matriceG, matriceTempG, taille);
	if (etat == TRUE) {
		stationnaire = 0;
	} else {
		copieMatrice(matriceTempG, matriceG, taille);
		copieSouche(nbSouchesG, soucheTempG, soucheG);
		stationnaire = 1;
	}
}

/* Exemple de matrice */
int** exempleMat1(Taille taille, int typeCell) {
	int** mat;
	int i, j, hauteur, largeur;
	hauteur = taille.hauteur;
	largeur = taille.largeur;

	mat = (int**) malloc(hauteur * sizeof(int*));
	for (i = 0; i < hauteur; i++) {
		mat[i] = (int*) malloc(largeur * sizeof(int));
	}
	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			mat[i][j] = 0;
		}
	}
	mat[4][5] = typeCell;
	mat[5][5] = typeCell;
	mat[6][5] = typeCell;
	mat[5][6] = typeCell;
	return mat;
}

/* Exemple de matrice */
int** exempleMat2(Taille taille, int typeCell) {
	int** mat;
	int i, j, hauteur, largeur;
	hauteur = taille.hauteur;
	largeur = taille.largeur;

	mat = (int**) malloc(hauteur * sizeof(int*));
	for (i = 0; i < hauteur; i++) {
		mat[i] = (int*) malloc(largeur * sizeof(int));
	}
	for (i = 0; i < hauteur; i++) {
		for (j = 0; j < largeur; j++) {
			mat[i][j] = 0;
		}
	}
	mat[2][3] = typeCell;
	mat[3][3] = typeCell;
	mat[4][3] = typeCell;
	mat[3][4] = typeCell;
	return mat;
}

