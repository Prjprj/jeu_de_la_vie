/*********************
 *					 *
 *   JEU DE LA VIE   *
 * (jeu_de_la_vie.h) *
 *                   *
 *********************/

/* Fonction permettant de lire un caractère entré sur la sortie
 standard et de le transformer en entier */
int litEntier(void);

/* Fontion permettant de lire sur la sortie standard le premier
 caractère tapé, et d'ignorer le reste */
char litPremierCarac(void);

/* Fonction permettant de lire une chaîne de caractères entrée
 sur la sortir standard */
char* litCaractere(void);

/* Transforme un tableau d'entiers à deux dimensions en une chaine 
 de caractères */
char* intToCharMatrice(int**, Taille);

/* Remplace les "0" une chaine de caractères représentant une matrice
 par des "_" */
char* intToCharMatriceAvecEspace(char*);

/* Transforme une chaine de caracteres contenant en fait une matrice
 en un tableau d'entiers à deux dimensions sans retour chariot
 à la fin de chaque ligne de la matrice */
char* intToCharMatriceSansEnter(int**, Taille);

/* Transforme une chaine de caracteres contenant en fait une matrice
 en un tableau d'entiers à deux dimensions */
int** charToIntMatrice(char*, Taille);

/* Fonction permettant de dispatcher une matrice en souches */
Souche* dispatchMatEnSouches(int**, Param, int);

/* Fonction permettant de retourner la hauteur et la largeur maximales
 parmi différentes souches stockées à l'aide d'un tableau de Souche */
int* maxHauteurLargeur(int, Souche*);

/* Procédure permettant de copier une matrice mat1 dans une matrice mat2
 de dimensions taille (hauteur et largeur) */
void copieMatrice(int**, int**, Taille);

/* Procédure permettant de copier un certain nombre de souches cellulaires
 nbSouches, souche1, dans souche2 */
void copieSouche(int, Souche*, Souche*);

/* Procédure permettant d'afficher à la sortie standard une matrice de dimensions
 taille (hauteur et largeur) */
void afficheMatrice(int**, Taille);

/* Fonction permettant de tester si une cellule (une case de la matrice)
 est vide (c'est-à-dire vaut 0) ou non */
int estCelluleVide(int);

/* Fonction permettant de compter le nombre de cellules voisines
 de type typeCell à une certaine cellule donnée */
int* comptage(int*, int, int);

/* Fonction permettant de compter le nombre de cellules voisines à une
 cellule se situant dans les différentes matrices d'un certain nombre nbSouches
 de souches données à l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace torique, c'est-à-dire que le haut et le bas, et,
 la gauche et la droite se rejoignent */
int* nbCellVoisinesEspaceTorique(int, int, int, Souche*);

/* Fonction permettant de compter le nombre de cellules voisines à une
 cellule se situant dans les différentes matrices d'un certain nombre nbSouches
 de souches données à l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace cylindrique, c'est-à-dire que le haut et le bas
 ne se rejoignent pas, mais que la gauche et la droite se rejoignent */
int* nbCellVoisinesEspaceCylindrique(int, int, int, Souche*);

/* Fonction permettant de compter le nombre de cellules voisines à une
 cellule se situant dans les différentes matrices d'un certain nombre nbSouches
 de souches données à l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace carré, c'est-à-dire que le haut et le bas, et, 
 la gauche et la droite ne se rejoignent pas */
int* nbCellVoisinesEspaceCarre(int, int, int, Souche*);

/* Fonction permettant de décider la mort ou non d'une cellule se situant à
 la ligne i et la colonne j d'une matrice par rapport aux calculs du nombre
 de cellules voisines dans un certain espace */
int celluleDoitMourir(int, int, int, Souche*);

/* Fonction permettant de décider la naissance ou non d'une cellule se situant à
 la ligne i et la colonne j d'une matrice par rapport aux calculs du nombre
 de cellules voisines dans un certain espace */
int celluleDoitNaitre(int, int, int, Souche*);

/* Fonction permettant de comparer deux matrice. Si elles sont identiques
 alors la fonction retourne vrai (elles sont dans un état stationnaire
 sinon elle retourne faux */
int etatStationnaire(int**, int**, Taille);

/* Fonction permettant de regrouper les matrices d'un certain nombre de souches
 nbSouches dans une seule matrice. Si plusieurs cellules se situent à un même
 emplacement alors elles s'entretuent pour obtenir la place. Par conséquent
 la case correspondante reste vide */
int** regroupementSouches(int, Souche*);

/* Fonction qui initialise une taille (hauteur et largeur) par défaut */
Taille tailleParDefaut(void);

/* Procédure permettant d'initialiser les parametres */
void initParamParDefaut(void);

/* Procédure permettant de modifier l'espace de développement des cellules */
void setEspace(char);

/* Procédure permettant de modifier la vitesse de développement des cellules */
void setVitesse(int);

/* Procédure permettant de modifier la taille de l'espace de 
 développement des cellules */
void setTaille(Taille);

/* Fonction permettant d'initialiser une souche */
Souche initialisationSouche(Taille, int, int**);

/* Fonction permettant de gérer le temps, la vitesse d'avancement, d'évolution
 de l'expérience */
void tempsAvancement(void);

/* Fonction générant un nombre aléatoire entre 1 et m */
int generer(int);

/* Fonction permettant de générer une souche aléatoire de taille
 (hauteur et largeur) et type de cellules donnés */
Souche generationUneSouche(Taille, int);

/* Fonction permettant de générer aléatoirement un certain nombre de
 souches nbSouches et de taille (hauteur et largeur) données */
Souche* generationPlusieursSouches(int, Taille);

/* Fonction qui teste si un fichier dont le nom est donné
 en argument existe. Retourne TRUE (1) s'il existe et
 FALSE (0) sinon */
int existeFichier(char*);

/* Procédure permettant de sauvegarder une expérience
 en cours dans un fichier */
void sauvegarde(int, int**, char*);

/* Fonction permettant de charger une expérience préalablement sauvegardée */
Souche* chargement(int*, Param*, char*);

/* Procédure permettant de libérer la place en mémoire allouée 
 au préalable pour les matrices et souches qui ont été nécessaire
 lors du développement des cellules */
void liberationAllocation();

/* Procédure correspondant à l'algorithme du jeu de la vie,
 à savoir l'évolution des cellules jusqu'à un état stationnaire
 ou un arrêt de la part de l'observateur */
void algorithme();

/* Des exemples de matrices */
int** exempleMat1(Taille, int);
int** exempleMat2(Taille, int);

