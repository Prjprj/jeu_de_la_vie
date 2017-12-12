/***************************
 *						   *
 *   INTERFACE GRAPHIQUE   *
 * (interface_graphique.h) *
 *						   *
 ***************************/

//inclusion des bibliotheques necessaires a l'interface graphique
#include<gtk/gtk.h>
#include"var_globales.h"
#include"jeu_de_la_vie.h"

//creation des types de donnees
typedef GtkWidget* Fenetre;
typedef GtkWidget* Label;
typedef GtkWidget* Bouton;
typedef GtkWidget* BoiteHorizontale;
typedef GtkWidget* BoiteVerticale;
typedef GtkWidget* Image;
typedef GtkWidget* Entree;
typedef GtkWidget* PWidget;

//creation du type programme, compose d'une fenetre et
//d'un nombre a choisir de labels, boutons, boites, images et entrees
typedef struct {
	Fenetre fenetre;
	Label* labels;
	Bouton* boutons;
	BoiteVerticale* boitesV;
	BoiteHorizontale* boitesH;
	Image* images;
	Entree* entrees;
	int nbLabels;
	int nbBoutons;
	int nbBoitesV;
	int nbBoitesH;
	int nbImages;
	int nbEntrees;
} Programme;

//definition de la variable globale necessaire a l'interface graphique
Programme *pApp;

//definition des prototypes des fonctions de l'interface graphique
void allocationDynGraph(int, int, int, int, int, int);

void liberationDynamique(void);

void destructionWidget(void);

void destruction(PWidget, gpointer);

void quitter(PWidget, gpointer);

void nouvelleExp(PWidget, gpointer);

void parametresGraph(PWidget, gpointer);

void explications(PWidget, gpointer);

void acceuil(PWidget, gpointer);

void chargementGraph(PWidget, gpointer);

void generationAuto(PWidget, gpointer);

void generationUtilisateur(PWidget, gpointer);

void choixTailleExp(PWidget, gpointer);

void choixVitesseExp(PWidget, gpointer);

void choixEspaceExp(PWidget, gpointer);

void algo(PWidget, gpointer);

void sauvegardeGraph(PWidget, gpointer);

void moins10X(PWidget, gpointer);

void moinsX(PWidget, gpointer);

void plusX(PWidget, gpointer);

void plus10X(PWidget, gpointer);

void moins10Y(PWidget, gpointer);

void moinsY(PWidget, gpointer);

void plusY(PWidget, gpointer);

void plus10Y(PWidget, gpointer);

void moinsSouche(PWidget, gpointer);

void plusSouche(PWidget, gpointer);

void ajouter(PWidget, gpointer);

void retirer(PWidget, gpointer);

void validMatrice(PWidget, gpointer);

void modifTailleImp(PWidget, gpointer);

void pauseGraph(PWidget, gpointer);

gint algo2(gpointer);
