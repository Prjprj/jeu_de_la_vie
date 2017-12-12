/********************
 *					*
 *   MODE CONSOLE   *
 * (mode_console.h) *
 *					*
 ********************/

/* Fonction permettant d'afficher la page de garde et le sommaire
 et de demander de faire un choix */
int PagePresentation(void);

/* Procédure d'affichage de fin de jeu */
void AffichageFinJeu(void);

/* Procédure permettant de lancer le choix demandé par l'utilisateur */
void lancementDuChoix(int, int);

/* Procédure permettant d'effectuer la selection des parametres
 pour debuter l'expérience */
void selectionParametres(void);

/* Fonction retournant le type d'espace choisi */
char selectionEspace(void);

/* Fonction retournant la vitesse de deroulement de l'experience */
int selectionVitesse(void);

/* Fonction retournant la Taille de l'espace de deroulement de l'experience */
Taille selectionTaille(void);

/* Procédure pour la selection de l'initialisation des souches */
void selectionSouches(int);

/* Fonction permettant d'initialiser une matrice */
int** initialisationMatrice(Taille, int);

/* Procédure permettant de lancer l'experience */
void lancementDuJeu();

/* Fonction qui reprend la boucle de l'algorithme du jeu de la vie */
char boucle(void);

/* Procédure permettant de sauvegarder une experience */
void choixSauvegarde(char);

/* Procédure permettant de charger une experience préexistante */
void choixChargement(void);

/* Procedure permettant de proposer les options du cas "pause" */
void choixPause(void);

/* Procédure permettant de choisir le lancement de l'experience.
 A savoir un chargement ou une nouvelle experience */
void choixExperience(void);

/* Procédure permettant de lancer le mode_console */
void mode_console(void);

/* Procédure permettant de faire defiler le texte contenu
 dans la fenetre en tapant ENTREE */
void printEntree(void);

/* Procédure permettant d'ouvrir en lecture et d'afficher
 le contenu d'un fichier */
void ouvrirLecture(char*);

