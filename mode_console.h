/********************
 *					*
 *   MODE CONSOLE   *
 * (mode_console.h) *
 *					*
 ********************/

/* Fonction permettant d'afficher la page de garde et le sommaire
 et de demander de faire un choix */
int PagePresentation(void);

/* Proc�dure d'affichage de fin de jeu */
void AffichageFinJeu(void);

/* Proc�dure permettant de lancer le choix demand� par l'utilisateur */
void lancementDuChoix(int, int);

/* Proc�dure permettant d'effectuer la selection des parametres
 pour debuter l'exp�rience */
void selectionParametres(void);

/* Fonction retournant le type d'espace choisi */
char selectionEspace(void);

/* Fonction retournant la vitesse de deroulement de l'experience */
int selectionVitesse(void);

/* Fonction retournant la Taille de l'espace de deroulement de l'experience */
Taille selectionTaille(void);

/* Proc�dure pour la selection de l'initialisation des souches */
void selectionSouches(int);

/* Fonction permettant d'initialiser une matrice */
int** initialisationMatrice(Taille, int);

/* Proc�dure permettant de lancer l'experience */
void lancementDuJeu();

/* Fonction qui reprend la boucle de l'algorithme du jeu de la vie */
char boucle(void);

/* Proc�dure permettant de sauvegarder une experience */
void choixSauvegarde(char);

/* Proc�dure permettant de charger une experience pr�existante */
void choixChargement(void);

/* Procedure permettant de proposer les options du cas "pause" */
void choixPause(void);

/* Proc�dure permettant de choisir le lancement de l'experience.
 A savoir un chargement ou une nouvelle experience */
void choixExperience(void);

/* Proc�dure permettant de lancer le mode_console */
void mode_console(void);

/* Proc�dure permettant de faire defiler le texte contenu
 dans la fenetre en tapant ENTREE */
void printEntree(void);

/* Proc�dure permettant d'ouvrir en lecture et d'afficher
 le contenu d'un fichier */
void ouvrirLecture(char*);

