					/******************************
					 *							  *
					 * DEFINITIONS DES STRUCTURES *
					 *         DE DONNEES         *
					 *		    (types.h)         *
					 *							  *
					 ******************************/


	/* Enregistrement contenant les composantes d'une souche cellulaire,
	   à savoir la hauteur, la largeur, le type de cellules, et l'emplacement
	   des cellules de la souche stockées dans une matrice */
typedef struct{
	int** mat;
	int largeur;
	int hauteur;
	int typeCell;
}SoucheCellulaire;

typedef SoucheCellulaire Souche;


	/* Enregistrement contenant les iinformations sur la taille d'une matrice,
	   à savoir sa hauteur et sa largeur */
typedef struct{
	int hauteur;
	int largeur;
} TailleMatrice;

typedef TailleMatrice Taille;

	/* Enregistrement contenant les paramètres d'une souche multi-cellulaire,
	   à savoir le type d'espace, la taille et la vitesse de l'expérience */ 
typedef struct{
	char espace;
	Taille taille;
	int vitesse;
}Parametres;

typedef Parametres Param;
