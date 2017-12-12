/*********************
 *					 *
 *   JEU DE LA VIE   *
 * (jeu_de_la_vie.h) *
 *                   *
 *********************/

/* Fonction permettant de lire un caract�re entr� sur la sortie
 standard et de le transformer en entier */
int litEntier(void);

/* Fontion permettant de lire sur la sortie standard le premier
 caract�re tap�, et d'ignorer le reste */
char litPremierCarac(void);

/* Fonction permettant de lire une cha�ne de caract�res entr�e
 sur la sortir standard */
char* litCaractere(void);

/* Transforme un tableau d'entiers � deux dimensions en une chaine 
 de caract�res */
char* intToCharMatrice(int**, Taille);

/* Remplace les "0" une chaine de caract�res repr�sentant une matrice
 par des "_" */
char* intToCharMatriceAvecEspace(char*);

/* Transforme une chaine de caracteres contenant en fait une matrice
 en un tableau d'entiers � deux dimensions sans retour chariot
 � la fin de chaque ligne de la matrice */
char* intToCharMatriceSansEnter(int**, Taille);

/* Transforme une chaine de caracteres contenant en fait une matrice
 en un tableau d'entiers � deux dimensions */
int** charToIntMatrice(char*, Taille);

/* Fonction permettant de dispatcher une matrice en souches */
Souche* dispatchMatEnSouches(int**, Param, int);

/* Fonction permettant de retourner la hauteur et la largeur maximales
 parmi diff�rentes souches stock�es � l'aide d'un tableau de Souche */
int* maxHauteurLargeur(int, Souche*);

/* Proc�dure permettant de copier une matrice mat1 dans une matrice mat2
 de dimensions taille (hauteur et largeur) */
void copieMatrice(int**, int**, Taille);

/* Proc�dure permettant de copier un certain nombre de souches cellulaires
 nbSouches, souche1, dans souche2 */
void copieSouche(int, Souche*, Souche*);

/* Proc�dure permettant d'afficher � la sortie standard une matrice de dimensions
 taille (hauteur et largeur) */
void afficheMatrice(int**, Taille);

/* Fonction permettant de tester si une cellule (une case de la matrice)
 est vide (c'est-�-dire vaut 0) ou non */
int estCelluleVide(int);

/* Fonction permettant de compter le nombre de cellules voisines
 de type typeCell � une certaine cellule donn�e */
int* comptage(int*, int, int);

/* Fonction permettant de compter le nombre de cellules voisines � une
 cellule se situant dans les diff�rentes matrices d'un certain nombre nbSouches
 de souches donn�es � l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace torique, c'est-�-dire que le haut et le bas, et,
 la gauche et la droite se rejoignent */
int* nbCellVoisinesEspaceTorique(int, int, int, Souche*);

/* Fonction permettant de compter le nombre de cellules voisines � une
 cellule se situant dans les diff�rentes matrices d'un certain nombre nbSouches
 de souches donn�es � l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace cylindrique, c'est-�-dire que le haut et le bas
 ne se rejoignent pas, mais que la gauche et la droite se rejoignent */
int* nbCellVoisinesEspaceCylindrique(int, int, int, Souche*);

/* Fonction permettant de compter le nombre de cellules voisines � une
 cellule se situant dans les diff�rentes matrices d'un certain nombre nbSouches
 de souches donn�es � l'intersection de la ligne i et la colonne j.
 Ce calcul se fait dans un espace carr�, c'est-�-dire que le haut et le bas, et, 
 la gauche et la droite ne se rejoignent pas */
int* nbCellVoisinesEspaceCarre(int, int, int, Souche*);

/* Fonction permettant de d�cider la mort ou non d'une cellule se situant �
 la ligne i et la colonne j d'une matrice par rapport aux calculs du nombre
 de cellules voisines dans un certain espace */
int celluleDoitMourir(int, int, int, Souche*);

/* Fonction permettant de d�cider la naissance ou non d'une cellule se situant �
 la ligne i et la colonne j d'une matrice par rapport aux calculs du nombre
 de cellules voisines dans un certain espace */
int celluleDoitNaitre(int, int, int, Souche*);

/* Fonction permettant de comparer deux matrice. Si elles sont identiques
 alors la fonction retourne vrai (elles sont dans un �tat stationnaire
 sinon elle retourne faux */
int etatStationnaire(int**, int**, Taille);

/* Fonction permettant de regrouper les matrices d'un certain nombre de souches
 nbSouches dans une seule matrice. Si plusieurs cellules se situent � un m�me
 emplacement alors elles s'entretuent pour obtenir la place. Par cons�quent
 la case correspondante reste vide */
int** regroupementSouches(int, Souche*);

/* Fonction qui initialise une taille (hauteur et largeur) par d�faut */
Taille tailleParDefaut(void);

/* Proc�dure permettant d'initialiser les parametres */
void initParamParDefaut(void);

/* Proc�dure permettant de modifier l'espace de d�veloppement des cellules */
void setEspace(char);

/* Proc�dure permettant de modifier la vitesse de d�veloppement des cellules */
void setVitesse(int);

/* Proc�dure permettant de modifier la taille de l'espace de 
 d�veloppement des cellules */
void setTaille(Taille);

/* Fonction permettant d'initialiser une souche */
Souche initialisationSouche(Taille, int, int**);

/* Fonction permettant de g�rer le temps, la vitesse d'avancement, d'�volution
 de l'exp�rience */
void tempsAvancement(void);

/* Fonction g�n�rant un nombre al�atoire entre 1 et m */
int generer(int);

/* Fonction permettant de g�n�rer une souche al�atoire de taille
 (hauteur et largeur) et type de cellules donn�s */
Souche generationUneSouche(Taille, int);

/* Fonction permettant de g�n�rer al�atoirement un certain nombre de
 souches nbSouches et de taille (hauteur et largeur) donn�es */
Souche* generationPlusieursSouches(int, Taille);

/* Fonction qui teste si un fichier dont le nom est donn�
 en argument existe. Retourne TRUE (1) s'il existe et
 FALSE (0) sinon */
int existeFichier(char*);

/* Proc�dure permettant de sauvegarder une exp�rience
 en cours dans un fichier */
void sauvegarde(int, int**, char*);

/* Fonction permettant de charger une exp�rience pr�alablement sauvegard�e */
Souche* chargement(int*, Param*, char*);

/* Proc�dure permettant de lib�rer la place en m�moire allou�e 
 au pr�alable pour les matrices et souches qui ont �t� n�cessaire
 lors du d�veloppement des cellules */
void liberationAllocation();

/* Proc�dure correspondant � l'algorithme du jeu de la vie,
 � savoir l'�volution des cellules jusqu'� un �tat stationnaire
 ou un arr�t de la part de l'observateur */
void algorithme();

/* Des exemples de matrices */
int** exempleMat1(Taille, int);
int** exempleMat2(Taille, int);

