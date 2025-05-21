/***************************
 *						   *
 *   INTERFACE GRAPHIQUE   *
 * (interface_graphique.c) *
 *						   *
 ***************************/

//inclusion des bibliotheques
#include "biblio.h"
#include "constantes.h"
#include "types.h"
#include "Interface_graphique.h"

//allocation dynamique des objets composant une fenetre
void allocationDynGraph(int nbBoitesV, int nbBoitesH, int nbLabels,
		int nbBoutons, int nbImages, int nbEntrees) {
	pApp->nbBoitesV = nbBoitesV;
	pApp->boitesV = (BoiteVerticale*) malloc(
			pApp->nbBoitesV * sizeof(BoiteVerticale));
	pApp->nbBoitesH = nbBoitesH;
	pApp->boitesH = (BoiteHorizontale*) malloc(
			pApp->nbBoitesH * sizeof(BoiteHorizontale));
	pApp->nbLabels = nbLabels;
	pApp->labels = (Label*) malloc(pApp->nbLabels * sizeof(Label));
	pApp->nbBoutons = nbBoutons;
	pApp->boutons = (Bouton*) malloc(pApp->nbBoutons * sizeof(Bouton));
	pApp->nbImages = nbImages;
	pApp->images = (Image*) malloc(pApp->nbImages * sizeof(Image));
	pApp->nbEntrees = nbEntrees;
	pApp->entrees = (Entree*) malloc(pApp->nbEntrees * sizeof(Entree));
}

//procedure de desallocation de la memoire dynamique allouee
void liberationDynamique() {
	if (pApp->nbBoutons != 0)
		free(pApp->boutons);
	if (pApp->nbLabels != 0)
		free(pApp->labels);
	if (pApp->nbImages != 0)
		free(pApp->images);
	if (pApp->nbEntrees != 0)
		free(pApp->entrees);
	if (pApp->nbBoitesV != 0)
		free(pApp->boitesV);
	if (pApp->nbBoitesH != 0)
		free(pApp->boitesH);
}

//procedure detruisant les objets de la fenetre precedente pour
//les remplacer par d'autres
void destructionWidget(void) {
	int i;
	for (i = 0; i < pApp->nbImages; i++)
		gtk_widget_destroy(pApp->images[i]);
	for (i = 0; i < pApp->nbBoutons; i++)
		gtk_widget_destroy(pApp->boutons[i]);
	for (i = 0; i < pApp->nbEntrees; i++)
		gtk_widget_destroy(pApp->entrees[i]);
	for (i = 0; i < pApp->nbLabels; i++)
		gtk_widget_destroy(pApp->labels[i]);
	for (i = 0; i < pApp->nbBoitesV; i++)
		gtk_widget_destroy(pApp->boitesV[i]);
	for (i = 0; i < pApp->nbBoitesH; i++)
		gtk_widget_destroy(pApp->boitesH[i]);
	liberationDynamique();
}

//signal permettant de quitter la boucle d'evenements
//a la fermeture de la fenetre principale
void destruction(PWidget pWidget, gpointer pData) {
	GtkWidget *pAbout;
	Programme *pApp;
	gchar *NosNoms = "Aysel Gunes et Pierre Ramos";
	pApp = (Programme*) pData;
	//Creation de la boite de message
	pAbout = gtk_message_dialog_new(GTK_WINDOW(pApp->fenetre), GTK_DIALOG_MODAL,
			GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
			"%s\nVous remercient d'avoir\nutilise leur programme", NosNoms);
	//Affichage de la boite de message
	gtk_dialog_run(GTK_DIALOG(pAbout));
	//Destruction de la boite de message
	gtk_widget_destroy(pAbout);
	//fermeture de la boucle d'evenements
	gtk_main_quit();
}

//signal permettant de quitter l'application en cliquant sur le bouton quitter
void quitter(PWidget widget, gpointer pData) {
	GtkWidget *pQuestion;
	Programme *pApp;
	pApp = (Programme*) pData;
	//Creation de la boite de message
	pQuestion = gtk_message_dialog_new(GTK_WINDOW(pApp->fenetre),
			GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
			"Voulez vous vraiment\nquitter ce programme?");
	//Affichage et attente d une reponse
	switch (gtk_dialog_run(GTK_DIALOG(pQuestion))) {
	case GTK_RESPONSE_YES:
		//OUI -> on ferme la boucle d'evenements
		gtk_main_quit();
		break;
	case GTK_RESPONSE_NO:
		//NON -> on detruit la boite de message
		gtk_widget_destroy(pQuestion);
		break;
	}
}

//signal permettant l'affichage du menu de choix pour une nouvelle experience
void nouvelleExp(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	pApp = (Programme*) pData;
	//initialisation des variables globales necessaires au jeu
	generEnCours = 0;
	xGener = 0;
	yGener = 0;
	soucheGener = 1;
	//destruction des composants de la fenetre precedente
	destructionWidget();
	//creation des composants de la fenetre
	allocationDynGraph(1, 1, 0, 4, 1, 0);
	pApp->boitesV[0] = gtk_vbox_new(TRUE, 0);
	pApp->boitesH[0] = gtk_hbox_new(TRUE, 0);
	pApp->boutons[0] = gtk_button_new_with_label("Generation Automatique");
	pApp->boutons[1] = gtk_button_new_with_label("Chargement");
	pApp->boutons[2] = gtk_button_new_with_label(
			"Generation par l'utilisateur");
	pApp->boutons[3] = gtk_button_new_with_label("Retour");
	pApp->images[0] = gtk_image_new_from_file("./images/tpj-oneliner-11.gif");
	//association des composans de la fenetre aux boites correspondantes
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[0], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[1], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[2], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[3], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->images[0], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[0], FALSE,
			FALSE, 0);
	//creation du container pour mettre la premiere boite
	gtk_container_add(GTK_CONTAINER(pApp->fenetre), pApp->boitesH[0]);
	//affichage de la fenetre nouvellement creee
	gtk_widget_show_all(pApp->fenetre);
	//association des signaux aux boutons
	g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked",
			G_CALLBACK(generationAuto), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[1]), "clicked",
			G_CALLBACK(chargementGraph), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[2]), "clicked",
			G_CALLBACK(generationUtilisateur), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[3]), "clicked", G_CALLBACK(acceuil),
			(gpointer* ) pApp);
}

//signal permettant l'affichage de l'ecran de saisie des parametres
void parametresGraph(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	char param1[50];
	char param2[50];
	char param3[50];
	pApp = (Programme*) pData;
	//destruction des composants de la fenetre precedente
	destructionWidget();
	//creation des composants de la fenetre
	allocationDynGraph(2, 1, 4, 4, 0, 0);
	pApp->boitesH[0] = gtk_hbox_new(TRUE, 0);
	pApp->boitesV[0] = gtk_vbox_new(TRUE, 0);
	pApp->boitesV[1] = gtk_vbox_new(TRUE, 0);
	pApp->boutons[0] = gtk_button_new_with_label("Taille de l'experience");
	pApp->boutons[1] = gtk_button_new_with_label("Vitesse de l'experience");
	pApp->boutons[2] = gtk_button_new_with_label("Espace de l'experience");
	pApp->boutons[3] = gtk_button_new_with_label("Retour");
	//recuperation des valeurs des parametres pour les affecter
	//aux labels les affichant
	sprintf(param1, "%dx%d", parametres.taille.hauteur,
			parametres.taille.largeur);
	pApp->labels[0] = gtk_label_new(param1);
	switch (parametres.vitesse) {
	case 1:
		strcpy(param2, "Lente");
		break;
	case 2:
		strcpy(param2, "Moyenne");
		break;
	case 3:
		strcpy(param2, "Rapide");
		break;
	}
	pApp->labels[1] = gtk_label_new(param2);
	switch (parametres.espace) {
	case 'T':
		strcpy(param3, "Torique");
		break;
	case 'C':
		strcpy(param3, "Cylindrique");
		break;
	case 'K':
		strcpy(param3, "Carre");
		break;
	}
	pApp->labels[2] = gtk_label_new(param3);
	//ce label n'est present que pour garder l'alignement
	//des boutons et des valeurs correspondantes
	pApp->labels[3] = gtk_label_new(" ");
	//association des composans de la fenetre aux boites correspondantes
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[0], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[1], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[2], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[3], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[0], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[1]), pApp->labels[0], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[1]), pApp->labels[1], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[1]), pApp->labels[2], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[1]), pApp->labels[3], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[1], FALSE,
			FALSE, 0);
	//creation du container pour mettre la premiere boite
	gtk_container_add(GTK_CONTAINER(pApp->fenetre), pApp->boitesH[0]);
	//affichage de la fenetre nouvellement creee
	gtk_widget_show_all(pApp->fenetre);
	//association des signaux aux boutons, prise en compte
	//de plusieurs possibilites selon que la fenetre a ete appellee de l'ecran
	//de pause ou de l'ecran d'acceuil
	if (jeuEnCours == 0) {
		g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked",
				G_CALLBACK(choixTailleExp), (gpointer* ) pApp);
	} else {
		g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked",
				G_CALLBACK(modifTailleImp), (gpointer* ) pApp);
	}
	g_signal_connect(G_OBJECT(pApp->boutons[1]), "clicked",
			G_CALLBACK(choixVitesseExp), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[2]), "clicked",
			G_CALLBACK(choixEspaceExp), (gpointer* ) pApp);
	if (jeuEnCours == 0) {
		g_signal_connect(G_OBJECT(pApp->boutons[3]), "clicked",
				G_CALLBACK(acceuil), (gpointer* ) pApp);
	} else {
		g_signal_connect(G_OBJECT(pApp->boutons[3]), "clicked",
				G_CALLBACK(pauseGraph), (gpointer* ) pApp);
	}
}

//signal affichant une boite de dialogue pour informer l'utilisateur qu'il ne peut
//pas modifier la taille de l'experience pendant que celle ci est en cours
void modifTailleImp(PWidget pWidget, gpointer pData) {
	GtkWidget *pAbout;
	Programme *pApp;
	pApp = (Programme*) pData;
	//creation de la boite de dialogue
	pAbout =
			gtk_message_dialog_new(GTK_WINDOW(pApp->fenetre), GTK_DIALOG_MODAL,
					GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
					"Impossible de modifier la taille de\nl'experience durant son execution");
	//Affichage de la boite de message
	gtk_dialog_run(GTK_DIALOG(pAbout));
	//Destruction de la boite de message
	gtk_widget_destroy(pAbout);
}

//signal permettant l'affichage de la boite de dialogue
//de choix de la taille de l'experience
void choixTailleExp(PWidget pWidget, gpointer pData) {
	GtkWidget *pDialog;
	Programme *pApp;
	int reponse;
	char param[50];
	Taille taille;
	pApp = (Programme*) pData;
	//creation de la boite de dialogue
	pDialog = gtk_dialog_new_with_buttons("Taille de l'experience",
			GTK_WINDOW(pApp->fenetre), GTK_DIALOG_MODAL, "20 par 20", REPONSE1,
			"30 par 30", REPONSE2, "40 par 40", REPONSE3, NULL);
	//recuperation de la reponse de l'utilisateur
	switch (gtk_dialog_run(GTK_DIALOG(pDialog))) {
	case REPONSE1:
		reponse = 2;
		break;
	case REPONSE2:
		reponse = 3;
		break;
	case REPONSE3:
		reponse = 4;
		break;
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_NONE:
	default:
		//destruction de la boite de dialogue
		gtk_widget_destroy(pDialog);
		break;
	}
	sprintf(param, "%dx%d", reponse * 10, reponse * 10);
	//modification de la taille de l'experience
	taille.hauteur = reponse * 10;
	taille.largeur = reponse * 10;
	setTaille(taille);
	//modification de l'affichage dans la fenetre de parametres
	gtk_label_set_text(GTK_LABEL(pApp->labels[0]), param);
	//destruction de de la boite de dialogue
	gtk_widget_destroy(pDialog);
}

//signal permettant l'affichage de la boite de dialogue
//de choix de la vitesse de l'experience
void choixVitesseExp(PWidget pWidget, gpointer pData) {
	GtkWidget *pDialog;
	Programme *pApp;
	int reponse;
	char param[50];
	pApp = (Programme*) pData;
	//creation de la boite de dialogue
	pDialog = gtk_dialog_new_with_buttons("Vitesse de l'experience",
			GTK_WINDOW(pApp->fenetre), GTK_DIALOG_MODAL, "Lente", REPONSE1,
			"Moyenne", REPONSE2, "Rapide", REPONSE3, NULL);
	//recuperation de la reponse de l'utilisateur
	switch (gtk_dialog_run(GTK_DIALOG(pDialog))) {
	case REPONSE1:
		reponse = 1;
		break;
	case REPONSE2:
		reponse = 2;
		break;
	case REPONSE3:
		reponse = 3;
		break;
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_NONE:
	default:
		//destruction de la boite de dialogue
		gtk_widget_destroy(pDialog);
		break;
	}
	//modification du parametre de vitesse et affichage dans la fenetre des parametres
	switch (reponse) {
	case 1:
		strcpy(param, "Lente");
		break;
	case 2:
		strcpy(param, "Moyenne");
		break;
	case 3:
		strcpy(param, "Rapide");
		break;
	}
	setVitesse(reponse);
	gtk_label_set_text(GTK_LABEL(pApp->labels[1]), param);
	//destruction de la boite de dialogue
	gtk_widget_destroy(pDialog);
}

//signal permettant l'affichage de la boite de dialogue
//de choix de l'espace de l'experience
void choixEspaceExp(PWidget pWidget, gpointer pData) {
	GtkWidget *pDialog;
	Programme *pApp;
	char reponse;
	char param[50];
	pApp = (Programme*) pData;
	//creation de la boite de dialogue
	pDialog = gtk_dialog_new_with_buttons("Espace de l'experience",
			GTK_WINDOW(pApp->fenetre), GTK_DIALOG_MODAL, "Torique", REPONSE1,
			"Cylindrique", REPONSE2, "Carre", REPONSE3, NULL);
	//recuperation de la reponse de l'utilisateur
	switch (gtk_dialog_run(GTK_DIALOG(pDialog))) {
	case REPONSE1:
		reponse = 'T';
		break;
	case REPONSE2:
		reponse = 'C';
		break;
	case REPONSE3:
		reponse = 'K';
		break;
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_NONE:
	default:
		//destruction de la boite de dialogue
		gtk_widget_destroy(pDialog);
		break;
	}
	//modification de l'espace et affichage dans la fenetre de parametres
	switch (reponse) {
	case 'T':
		strcpy(param, "Torique");
		break;
	case 'C':
		strcpy(param, "Cylindrique");
		break;
	case 'K':
		strcpy(param, "Carre");
		break;
	}
	setEspace(reponse);
	gtk_label_set_text(GTK_LABEL(pApp->labels[2]), param);
	//destruction de la boite de dialogue
	gtk_widget_destroy(pDialog);
}

//signal permettant l'affichage de l'ecran d'explications du jeu
void explications(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	//affectation des chaines de caracteres a afficher
	char chaine1[] =
			"><  LA PRESENTATION DU JEU DE LA VIE  ><\n-------------------------------\n\n";
	char chaine2[] =
			"> Le jeu de la vie a ete cree par le mathematicien John Horton Conway (ne le 26 decembre 1937 a Liverpool, Angleterre).\n\n> Ce jeu est base sur la creation de populations cellulaires. La naissance et la mort y sont conditionnees par la presence\nsuffisante ou excessive de cellules vivantes dans le voisinage d'une cellule.\n\n";
	char chaine3[] =
			"> Plusieurs souches de cellules peuvent etre utilisees (de 1 a 9 souches) dans une meme experience.\n\n> Generation personnelle ou aleatoire des experiences.\n\n> Chaque case a huit voisins. Une case ne peut contenir qu'une seule cellule et les regles sont celles qui suivent.\n\t1- Si le voisinage d'une case contient trois cellules de meme souche alors une cellule nait de ce type de souche.\n\t2- Si une cellule est entouree de plus de quatre cellules de souches quelconque, elle meurt etouffee.\n\t3- Si une cellule est entouree d'une cellule ou moins, de souche quelconque, elle meurt d'isolement.\n\n> Trois types d'espace:\n\t- un espace torique: ou le haut et la bas se rejoignent, ainsi que la droite et la gauche;\n\t- un espace cyclindrique: ou la droite et la gauche se rejoignent;\n\t- un espace plat: dit carre, un espace en 2 dimensions.\n\n> Trois types de vitesse (plus une supplementaire en mode console) d'evolution de l'experience:\n\t- vitesse d'evolution lente\n\t- vitesse d'evolution normale\n\t- vitesse d'evolution rapide\n\t(- vitesse d'evolution personnelle).\n\n> Taille de l'espace d'evolution variable selon le choix.\n\n> Possibilite de:\n\t- mise en pause\n\t- modification des parametres\n\t- sauvegarde\n\t- chargement.";
	pApp = (Programme*) pData;
	//destruction des elements de la precedente fenetre
	destructionWidget();
	//creation des elements de la fenetre
	allocationDynGraph(1, 0, 3, 1, 0, 0);
	pApp->boitesV[0] = gtk_vbox_new(FALSE, 0);
	pApp->boutons[0] = gtk_button_new_with_label("Retour");
	pApp->labels[0] = gtk_label_new(chaine1);
	gtk_label_set_justify(GTK_LABEL(pApp->labels[0]), GTK_JUSTIFY_CENTER);
	pApp->labels[1] = gtk_label_new(chaine2);
	gtk_label_set_justify(GTK_LABEL(pApp->labels[1]), GTK_JUSTIFY_LEFT);
	pApp->labels[2] = gtk_label_new(chaine3);
	gtk_label_set_justify(GTK_LABEL(pApp->labels[2]), GTK_JUSTIFY_LEFT);
	//insertion des elements dans les boites associees
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[0], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->labels[0], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->labels[1], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->labels[2], FALSE, FALSE,
			0);
	//creatoin du container pour la premiere boite
	gtk_container_add(GTK_CONTAINER(pApp->fenetre), pApp->boitesV[0]);
	//affichage de la fenetre principale et de ses composants
	gtk_widget_show_all(pApp->fenetre);
	//liaison au bouton du signal
	g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked", G_CALLBACK(acceuil),
			(gpointer* ) pApp);
}

//signal permettant l'affichage de l'ecran de pause
void pauseGraph(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	char *chaine;
	pApp = (Programme*) pData;
	//destruction des elements de la precedente fenetre
	destructionWidget();
	//creation des elements de la fenetre
	allocationDynGraph(1, 1, 1, 5, 0, 0);
	//fermeture du timeout lance dans l'algo (duquel on vient pour arriver dans cette fenetre)
	gtk_timeout_remove(idTimeOut);
	pApp->boitesV[0] = gtk_vbox_new(TRUE, 0);
	pApp->boitesH[0] = gtk_hbox_new(TRUE, 0);
	pApp->boutons[0] = gtk_button_new_with_label("Nouvelle Experience");
	pApp->boutons[1] = gtk_button_new_with_label("Sauvegarde");
	pApp->boutons[2] = gtk_button_new_with_label("Modifier les parametres");
	pApp->boutons[3] = gtk_button_new_with_label("Retour");
	pApp->boutons[4] = gtk_button_new_with_label("Quitter");
	chaine = intToCharMatrice(matriceG, parametres.taille);
	pApp->labels[0] = gtk_label_new(chaine);
	//insertion des elements dans les boites associees
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[0], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[1], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[2], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[3], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[4], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->labels[0], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[0], FALSE,
			FALSE, 0);
	//creatoin du container pour la premiere boite
	gtk_container_add(GTK_CONTAINER(pApp->fenetre), pApp->boitesH[0]);
	//affichage de la fenetre principale et de ses composants
	gtk_widget_show_all(pApp->fenetre);
	//liaison de chaque bouton au signal correspondant
	g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked",
			G_CALLBACK(nouvelleExp), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[1]), "clicked",
			G_CALLBACK(sauvegardeGraph), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[2]), "clicked",
			G_CALLBACK(parametresGraph), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[3]), "clicked", G_CALLBACK(algo),
			(gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[4]), "clicked", G_CALLBACK(quitter),
			(gpointer* ) pApp);
}

//fonction permettant l'application de l'algorithme et
//son affichage dans la fenetre prevue a cet effet
gint algo2(gpointer pData) {
	char* chaine;
	//application de l'algorithme
	algorithme();
	//verification d'un etat stationnaire
	if (stationnaire == 0) {
		//affichage de la matrice representant l'experience
		chaine = intToCharMatrice(matriceG, parametres.taille);
		gtk_label_set_text(GTK_LABEL(pApp->labels[0]), chaine);
		gtk_label_set_text(GTK_LABEL(pApp->labels[1]), "Etat Stationnaire");
		//fermeture du timeout permettant l'application periodique de l'algorithme
		gtk_timeout_remove(idTimeOut);
	} else {
		//affichage de la matrice representant l'experience
		chaine = intToCharMatrice(matriceG, parametres.taille);
		gtk_label_set_text(GTK_LABEL(pApp->labels[0]), chaine);
	}
	return (TRUE);
}

//signal permettant l'affichage de la fenetre de l'algorithme
void algo(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	char* chaine;
	pApp = (Programme*) pData;
	//modification des variables globales du jeu
	jeuEnCours = 1;
	generEnCours = 0;
	//destruction des elements de la precedente fenetre
	destructionWidget();
	//creation des elements de la fenetre
	allocationDynGraph(2, 1, 2, 2, 0, 0);
	pApp->boitesH[0] = gtk_hbox_new(TRUE, 0);
	pApp->boitesV[0] = gtk_vbox_new(TRUE, 0);
	pApp->boitesV[1] = gtk_vbox_new(FALSE, 0);
	pApp->boutons[0] = gtk_button_new_with_label("Pause");
	pApp->boutons[1] = gtk_button_new_with_label("Quitter");
	chaine = intToCharMatrice(matriceG, parametres.taille);
	pApp->labels[0] = gtk_label_new(chaine);
	pApp->labels[1] = gtk_label_new(" ");
	//insertion des elements dans les boites associees
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[1]), pApp->labels[0], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[1]), pApp->labels[1], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[0], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[1], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[1], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[0], FALSE,
			FALSE, 0);
	//creatoin du container pour la premiere boite
	gtk_container_add(GTK_CONTAINER(pApp->fenetre), pApp->boitesH[0]);
	//affichage de la fenetre principale et de ses composants
	gtk_widget_show_all(pApp->fenetre);
	//liaison aux boutons des signaux correspondants
	g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked",
			G_CALLBACK(pauseGraph), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[1]), "clicked", G_CALLBACK(quitter),
			(gpointer* ) pApp);
	//lancement du timeout permettant l'application periodique de l'algo et son affichage
	idTimeOut = g_timeout_add((guint32) parametres.vitesse * 400, algo2, NULL);
}

//signal permettant l'affichage de la boite de dialogue
//de chargement d'un fichier
void chargementGraph(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	GtkWidget *pBoite, *pAbout;
	Entree pEntry;
	const gchar *sNom;
	char nomFic[128];
	int i;
	pApp = (Programme*) pData;
	//Creation de la boite de dialogue
	pBoite = gtk_dialog_new_with_buttons("Chargement d'un fichier",
			GTK_WINDOW(pApp->fenetre), GTK_DIALOG_MODAL, GTK_STOCK_OK,
			GTK_RESPONSE_OK,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	//Creation de la zone de saisie
	pEntry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(pEntry),
			"Saisissez le nom du fichier a charger");
	//Insertion de la zone de saisie dans la boite de dialogue
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pEntry, TRUE, FALSE,
			0);
	//Affichage des elements de la boite de dialogue
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	//On lance la boite de dialogue et on recupere la reponse
	switch (gtk_dialog_run(GTK_DIALOG(pBoite))) {
	//L'utilisateur valide
	case GTK_RESPONSE_OK:
		//recuperation du nom du fichier que l'utilisateur veut charger
		sNom = gtk_entry_get_text(GTK_ENTRY(pEntry));
		if (existeFichier((char*) sNom) == TRUE) {
			//chargement du fichier donne par l'utilisateur et initialisation des variables globales
			soucheG = chargement(&nbSouchesG, &parametres, (char*) sNom);
			soucheTempG = (Souche*) malloc(nbSouchesG * sizeof(Souche));
			matriceTempG = (int**) malloc(
					((parametres.taille).hauteur) * sizeof(int*));
			for (i = 0; i < ((parametres.taille).hauteur); i++) {
				matriceTempG[i] = (int*) malloc(
						((parametres.taille).largeur) * sizeof(int));
			}
			matriceG = regroupementSouches(nbSouchesG, soucheG);
			//destruction de la boite de dialogue
			gtk_widget_destroy(pBoite);
			//lancement de l'algorithme
			algo(pApp->fenetre, (gpointer*) pApp);
		} else {
			//affichage d'une boite de dialogue informant que le fichier n'existe pas
			strcpy(nomFic, sNom);
			pAbout = gtk_message_dialog_new(GTK_WINDOW(pApp->fenetre),
					GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
					"le fichier %s n'existe pas", nomFic);
			//destruction de la boite de chargement
			gtk_widget_destroy(pBoite);
			//Affichage de la boite de message
			gtk_dialog_run(GTK_DIALOG(pAbout));
			//Destruction de la boite de message
			gtk_widget_destroy(pAbout);
		}
		break;
		//L'utilisateur annule
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_NONE:
	default:
		//destruction de la boite de dialogue
		gtk_widget_destroy(pBoite);
		break;
	}
}

//signal permettant l'affichage de la boite de dialogue
//de sauvegarde d'un fichier
void sauvegardeGraph(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	GtkWidget *pBoite, *pAbout;
	Entree pEntry;
	const gchar *sNom;
	char nomFic[128];
	pApp = (Programme*) pData;
	//Creation de la boite de dialogue
	pBoite = gtk_dialog_new_with_buttons("Sauvegarde d'un fichier",
			GTK_WINDOW(pApp->fenetre), GTK_DIALOG_MODAL, GTK_STOCK_OK,
			GTK_RESPONSE_OK,
			GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
	//Creation de la zone de saisie
	pEntry = gtk_entry_new();
	gtk_entry_set_text(GTK_ENTRY(pEntry),
			"Saisissez le nom du fichier a charger");
	//Insertion de la zone de saisie dans la boite de dialogue
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(pBoite)->vbox), pEntry, TRUE, FALSE,
			0);
	//Affichage des elements de la boite de dialogue
	gtk_widget_show_all(GTK_DIALOG(pBoite)->vbox);
	//On lance la boite de dialogue et on recupere la reponse
	switch (gtk_dialog_run(GTK_DIALOG(pBoite))) {
	//L'utilisateur valide
	case GTK_RESPONSE_OK:
		//recuperation du nom du fichier que l'utilisateur veut charger
		sNom = gtk_entry_get_text(GTK_ENTRY(pEntry));
		if (existeFichier((char*) sNom) == TRUE) {
			strcpy(nomFic, sNom);
			//un fichier existe deja, on propose a l'utilisateur de l'ecraser
			pAbout = gtk_message_dialog_new(GTK_WINDOW(pApp->fenetre),
					GTK_DIALOG_MODAL, GTK_MESSAGE_QUESTION, GTK_BUTTONS_YES_NO,
					"le fichier %s existe, voulez vous l'ecraser?", nomFic);
			//Affichage et attente d une reponse
			switch (gtk_dialog_run(GTK_DIALOG(pAbout))) {
			case GTK_RESPONSE_YES:
				//sauvegarde de l'experience en ecrasant le fichier
				sauvegarde(nbSouchesG, matriceG, nomFic);
				//destruction de la boite de dialogue
				gtk_widget_destroy(pAbout);
				break;
			case GTK_RESPONSE_NO:
				//destruction de la boite de dialogue
				gtk_widget_destroy(pAbout);
				break;
			}
			//destruction de la boite de dialogue
			gtk_widget_destroy(pBoite);
		} else {
			strcpy(nomFic, sNom);
			//sauvegarde de l'experience
			sauvegarde(nbSouchesG, matriceG, nomFic);
			//destruction de la boite de dialogue
			gtk_widget_destroy(pBoite);
		}
		break;
		//L'utilisateur annule
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_NONE:
	default:
		//destruction de la boite de dialogue
		gtk_widget_destroy(pBoite);
		break;
	}
}

//signal permettant l'affichage de l'ecran permettant le choix
//de l'experience generee automatiquement par le programme
void generationAuto(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	int i;
	//initialisation de la germe
	srand((unsigned) time(NULL));
	//generation d'un nombre aleatoire de souches
	nbSouchesG = (rand() % 9) + 1;
	pApp = (Programme*) pData;
	//destruction des elements de la precedente fenetre
	destructionWidget();
	//creation des elements de la fenetre
	allocationDynGraph(2, 1, 2, 3, 0, 0);
	//initialisation des variables globales necessaires a l'experience
	soucheG = (Souche*) malloc(nbSouchesG * sizeof(Souche));
	soucheTempG = (Souche*) malloc(nbSouchesG * sizeof(Souche));
	matriceTempG = (int**) malloc(((parametres.taille).hauteur) * sizeof(int*));
	for (i = 0; i < ((parametres.taille).hauteur); i++) {
		matriceTempG[i] = (int*) malloc(
				((parametres.taille).largeur) * sizeof(int));
	}
	soucheG = generationPlusieursSouches(nbSouchesG, parametres.taille);
	matriceG = regroupementSouches(nbSouchesG, soucheG);
	pApp->boitesV[0] = gtk_vbox_new(TRUE, 0);
	pApp->boitesV[1] = gtk_vbox_new(FALSE, 0);
	pApp->boitesH[0] = gtk_hbox_new(TRUE, 0);
	pApp->boutons[0] = gtk_button_new_with_label("Regenerer");
	pApp->boutons[1] = gtk_button_new_with_label("Retour");
	pApp->boutons[2] = gtk_button_new_with_label("OK");
	pApp->labels[0] = gtk_label_new("Experience generee");
	pApp->labels[1] = gtk_label_new(
			intToCharMatrice(matriceG, parametres.taille));
	//insertion des elements dans les boites associees
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[0], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[1], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[2], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[1]), pApp->labels[0], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[1]), pApp->labels[1], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[1], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[0], FALSE,
			FALSE, 0);
	//creatoin du container pour la premiere boite
	gtk_container_add(GTK_CONTAINER(pApp->fenetre), pApp->boitesH[0]);
	//affichage de la fenetre principale et de ses composants
	gtk_widget_show_all(pApp->fenetre);
	//liaison aux boutons des signaux correspondant
	g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked",
			G_CALLBACK(generationAuto), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[1]), "clicked",
			G_CALLBACK(nouvelleExp), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[2]), "clicked", G_CALLBACK(algo),
			(gpointer* ) pApp);
}

//signal permettant l'affichage de la fenetre de generation d'une experience par l'utilisateur
void generationUtilisateur(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	char chaine[100];
	int i, j;
	pApp = (Programme*) pData;
	//ce test permet d'eviter l'affichage de certains messages d'erreur dans la console
	if (generEnCours == 0) {
		//destruction des elements de la precedente fenetre
		destructionWidget();
		//creation des elements de la fenetre
		allocationDynGraph(1, 7, 8, 14, 0, 0);
		pApp->boitesH[0] = gtk_hbox_new(TRUE, 0);
		pApp->boitesH[1] = gtk_hbox_new(TRUE, 0);
		pApp->boitesH[2] = gtk_hbox_new(TRUE, 0);
		pApp->boitesH[3] = gtk_hbox_new(TRUE, 0);
		pApp->boitesH[4] = gtk_hbox_new(TRUE, 0);
		pApp->boitesH[5] = gtk_hbox_new(TRUE, 0);
		pApp->boitesH[6] = gtk_hbox_new(TRUE, 0);
		pApp->boitesV[0] = gtk_vbox_new(TRUE, 0);
		pApp->boutons[0] = gtk_button_new_with_label("-10");
		pApp->boutons[1] = gtk_button_new_with_label("-");
		pApp->boutons[2] = gtk_button_new_with_label("+");
		pApp->boutons[3] = gtk_button_new_with_label("+10");
		pApp->boutons[4] = gtk_button_new_with_label("-10");
		pApp->boutons[5] = gtk_button_new_with_label("-");
		pApp->boutons[6] = gtk_button_new_with_label("+");
		pApp->boutons[7] = gtk_button_new_with_label("+10");
		pApp->boutons[8] = gtk_button_new_with_label("-");
		pApp->boutons[9] = gtk_button_new_with_label("+");
		pApp->boutons[10] = gtk_button_new_with_label("Ajouter");
		pApp->boutons[11] = gtk_button_new_with_label("Retirer");
		pApp->boutons[12] = gtk_button_new_with_label("Retour");
		pApp->boutons[13] = gtk_button_new_with_label("Commencer");
		//initialisation de la matrice que l'utilisateur aura a manipuler
		if (jeuEnCours == 0) {
			//initialisation d'une matrice vide
			matriceGener = (int**) malloc(
					((parametres.taille).hauteur) * sizeof(int*));
			for (i = 0; i < ((parametres.taille).hauteur); i++) {
				matriceGener[i] = (int*) malloc(
						((parametres.taille).largeur) * sizeof(int));
			}
			for (i = 0; i < ((parametres.taille).hauteur); i++) {
				for (j = 0; j < ((parametres.taille).largeur); j++) {
					matriceGener[i][j] = 0;
				}
			}
		} else {
			//affichage de la matrice de l'experience en cours
			matriceGener = (int**) malloc(
					((parametres.taille).hauteur) * sizeof(int*));
			for (i = 0; i < ((parametres.taille).hauteur); i++) {
				matriceGener[i] = (int*) malloc(
						((parametres.taille).largeur) * sizeof(int));
			}
			copieMatrice(matriceG, matriceGener, parametres.taille);
		}
		pApp->labels[0] = gtk_label_new(
				intToCharMatrice(matriceGener, parametres.taille));
		pApp->labels[1] = gtk_label_new(
				"Entrez les parametres de\nla souche a ajouter ou supprimer");
		pApp->labels[2] = gtk_label_new("Y");
		pApp->labels[3] = gtk_label_new("X");
		pApp->labels[4] = gtk_label_new("Souche");
		sprintf(chaine, "%d", yGener);
		pApp->labels[5] = gtk_label_new(chaine);
		sprintf(chaine, "%d", xGener);
		pApp->labels[6] = gtk_label_new(chaine);
		sprintf(chaine, "%d", soucheGener);
		pApp->labels[7] = gtk_label_new(chaine);
		//insertion des elements dans les boites associees
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[1]), pApp->labels[1], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[2]), pApp->labels[2], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[2]), pApp->boutons[0], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[2]), pApp->boutons[1], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[2]), pApp->boutons[2], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[2]), pApp->boutons[3], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[2]), pApp->labels[5], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[3]), pApp->labels[3], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[3]), pApp->boutons[4], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[3]), pApp->boutons[5], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[3]), pApp->boutons[6], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[3]), pApp->boutons[7], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[3]), pApp->labels[6], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[4]), pApp->labels[4], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[4]), pApp->boutons[8], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[4]), pApp->boutons[9], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[4]), pApp->labels[7], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[5]), pApp->boutons[10], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[5]), pApp->boutons[11], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[6]), pApp->boutons[12], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[6]), pApp->boutons[13], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boitesH[1], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boitesH[2], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boitesH[3], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boitesH[4], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boitesH[5], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boitesH[6], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->labels[0], FALSE,
				FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[0], FALSE,
				FALSE, 0);
		//creatoin du container pour la premiere boite
		gtk_container_add(GTK_CONTAINER(pApp->fenetre), pApp->boitesH[0]);
		//affichage de la fenetre principale et de ses composants
		gtk_widget_show_all(pApp->fenetre);
		//liaison des signaux aux boutons associes
		g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked",
				G_CALLBACK(moins10X), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[1]), "clicked",
				G_CALLBACK(moinsX), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[2]), "clicked",
				G_CALLBACK(plusX), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[3]), "clicked",
				G_CALLBACK(plus10X), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[4]), "clicked",
				G_CALLBACK(moins10Y), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[5]), "clicked",
				G_CALLBACK(moinsY), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[6]), "clicked",
				G_CALLBACK(plusY), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[7]), "clicked",
				G_CALLBACK(plus10Y), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[8]), "clicked",
				G_CALLBACK(moinsSouche), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[9]), "clicked",
				G_CALLBACK(plusSouche), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[10]), "clicked",
				G_CALLBACK(ajouter), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[11]), "clicked",
				G_CALLBACK(retirer), NULL);
		g_signal_connect(G_OBJECT(pApp->boutons[12]), "clicked",
				G_CALLBACK(nouvelleExp), (gpointer* ) pApp);
		g_signal_connect(G_OBJECT(pApp->boutons[13]), "clicked",
				G_CALLBACK(validMatrice), NULL);
	} else {
		//modification des champs devant changer a chaque rappel de la fonction
		gtk_label_set_text(GTK_LABEL(pApp->labels[0]),
				intToCharMatrice(matriceGener, parametres.taille));
		sprintf(chaine, "%d", xGener);
		gtk_label_set_text(GTK_LABEL(pApp->labels[5]), chaine);
		sprintf(chaine, "%d", yGener);
		gtk_label_set_text(GTK_LABEL(pApp->labels[6]), chaine);
		sprintf(chaine, "%d", soucheGener);
		gtk_label_set_text(GTK_LABEL(pApp->labels[7]), chaine);
	}
	//modificatoin de la variable globale permettant de ne pas
	//avoir des erreurs a chaque rappel de la fonction
	generEnCours = 1;
}

//fonction permettant d'ajouter une cellule dans la matrice que l'utilisateur modifie
void ajouter(PWidget pWidget, gpointer pData) {
	matriceGener[xGener][yGener] = soucheGener;
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction permettant de supprimer une cellule dans la matrice que l'utilisateur modifie
void retirer(PWidget pWidget, gpointer pData) {
	matriceGener[xGener][yGener] = 0;
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction permettant de valider la matrice et de lancer l'algorithme avec les bonnes valeurs
void validMatrice(PWidget pWidget, gpointer pData) {
	int i, j;
	//calcul du nombre de souches
	nbSouchesGener = 1;
	for (i = 0; i < ((parametres.taille).hauteur); i++) {
		for (j = 0; j < ((parametres.taille).largeur); j++) {
			if (matriceGener[i][j] > nbSouchesGener)
				nbSouchesGener = matriceGener[i][j];
		}
	}
	//initialisation des variables globales necessaires au deroulement de l'experience
	soucheG = dispatchMatEnSouches(matriceGener, parametres, nbSouchesGener);
	nbSouchesG = nbSouchesGener;
	soucheTempG = (Souche*) malloc(nbSouchesG * sizeof(Souche));
	matriceTempG = (int**) malloc(((parametres.taille).hauteur) * sizeof(int*));
	for (i = 0; i < ((parametres.taille).hauteur); i++) {
		matriceTempG[i] = (int*) malloc(
				((parametres.taille).largeur) * sizeof(int));
	}
	matriceG = regroupementSouches(nbSouchesG, soucheG);
	//lancement de l'experience
	algo(pApp->fenetre, (gpointer*) pApp);
}

//fonction retirant 10 a la valeur X dans la generation par l'utilisateur
void moins10X(PWidget pWidget, gpointer pData) {
	if (xGener >= 10) {
		xGener = xGener - 10;
	} else {
		xGener = 0;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction retirant 1 a la valeur X dans la generation par l'utilisateur
void moinsX(PWidget pWidget, gpointer pData) {
	if (xGener >= 1) {
		xGener = xGener - 1;
	} else {
		xGener = 0;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction ajoutant 1 a la valeur X dans la generation par l'utilisateur
void plusX(PWidget pWidget, gpointer pData) {
	if (xGener < parametres.taille.largeur - 1) {
		xGener = xGener + 1;
	} else {
		xGener = parametres.taille.largeur - 1;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction ajoutant 10 a la valeur X dans la generation par l'utilisateur
void plus10X(PWidget pWidget, gpointer pData) {
	if (xGener < parametres.taille.largeur - 11) {
		xGener = xGener + 10;
	} else {
		xGener = parametres.taille.largeur - 1;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction retirant 10 a la valeur Y dans la generation par l'utilisateur
void moins10Y(PWidget pWidget, gpointer pData) {
	if (yGener >= 10) {
		yGener = yGener - 10;
	} else {
		yGener = 0;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction retirant 1 a la valeur Y dans la generation par l'utilisateur
void moinsY(PWidget pWidget, gpointer pData) {
	if (yGener >= 1) {
		yGener = yGener - 1;
	} else {
		yGener = 0;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction ajoutant 1 a la valeur Y dans la generation par l'utilisateur
void plusY(PWidget pWidget, gpointer pData) {
	if (yGener < parametres.taille.largeur - 1) {
		yGener = yGener + 1;
	} else {
		yGener = parametres.taille.largeur - 1;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction ajoutant 10 a la valeur Y dans la generation par l'utilisateur
void plus10Y(PWidget pWidget, gpointer pData) {
	if (yGener < parametres.taille.largeur - 11) {
		yGener = yGener + 10;
	} else {
		yGener = parametres.taille.largeur - 1;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction retirant 1 a la valeur souche dans la generation par l'utilisateur
void moinsSouche(PWidget pWidget, gpointer pData) {
	if (soucheGener > 1) {
		soucheGener = soucheGener - 1;
	} else {
		soucheGener = 1;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//fonction ajoutant 1 a la valeur souche dans la generation par l'utilisateur
void plusSouche(PWidget pWidget, gpointer pData) {
	if (soucheGener < 10) {
		soucheGener = soucheGener + 1;
	} else {
		soucheGener = 9;
	}
	//rappel de la fonction d'affichage de la fenetre de generation par l'utilisateur
	generationUtilisateur(pApp->fenetre, (gpointer*) pApp);
}

//affichage de l'ecran d'acceuil
void acceuil(PWidget pWidget, gpointer pData) {
	Programme *pApp;
	pApp = (Programme*) pData;
	jeuEnCours = 0;
	//destruction des objets de la fenetre de parametres
	destructionWidget();
	//creation des elements de la fenetre
	allocationDynGraph(1, 1, 0, 4, 1, 0);
	//creation des boites
	pApp->boitesV[0] = gtk_vbox_new(TRUE, 0);
	pApp->boitesH[0] = gtk_hbox_new(TRUE, 0);
	//creation des images
	pApp->images[0] = gtk_image_new_from_file("./images/life_bw.png");
	//creation des boutons
	pApp->boutons[0] = gtk_button_new_with_label("Nouvelle Experience");
	pApp->boutons[1] = gtk_button_new_with_label("Modifier Parametres");
	pApp->boutons[2] = gtk_button_new_with_label("Explications");
	pApp->boutons[3] = gtk_button_new_from_stock(GTK_STOCK_QUIT);
	//association des boutons et boites aux boites dans lesquels ils doivent s'afficher
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[0], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[1], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[2], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesV[0]), pApp->boutons[3], FALSE,
			FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->images[0], FALSE, FALSE,
			0);
	gtk_box_pack_start(GTK_BOX(pApp->boitesH[0]), pApp->boitesV[0], FALSE,
			FALSE, 0);
	//creatoin du container pour la premiere boite
	gtk_container_add(GTK_CONTAINER(pApp->fenetre), pApp->boitesH[0]);
	//affichage de la fenetre principale et de ses composants
	gtk_widget_show_all(pApp->fenetre);
	//association des signaux aux composants du programme
	g_signal_connect(G_OBJECT(pApp->boutons[0]), "clicked",
			G_CALLBACK(nouvelleExp), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[1]), "clicked",
			G_CALLBACK(parametresGraph), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[2]), "clicked",
			G_CALLBACK(explications), (gpointer* ) pApp);
	g_signal_connect(G_OBJECT(pApp->boutons[3]), "clicked", G_CALLBACK(quitter),
			(gpointer* ) pApp);
}

