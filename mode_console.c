					/********************
					 *					*
					 *   MODE CONSOLE   *
					 * (mode_console.c) *
					 *					*
					 ********************/


	/* Inclusion des bibliothèques */
#include"biblio.h"
#include"constantes.h"
#include"types.h"
#include"var_globales.h"
#include"jeu_de_la_vie.h"
#include"mode_console.h"


	/* Fonction permettant d'afficher la page de garde et le sommaire
       et de demander de faire un choix */
int PagePresentation () {
	int choix;
	printf("\n\t\t\t* * * * * * * * * * * *\n");
	printf("\t\t\t*                     *\n");
	printf("\t\t\t*  LE JEU DE LA VIE   *\n");
	printf("\t\t\t*                     *\n");
	printf("\t\t\t* * * * * * * * * * * *\n");
	printf("\n\n\nSOMMAIRE\n");
	printf("********\n\n");
	printf("\t1- Presentation du Jeu de la Vie\n");
	printf("\t2- Debuter une experience\n");
	printf("\t3- Quitter\n");
	printf("\n\nQue desirez-vous?\n");
	choix = litEntier();
	printf("--------------------------------------------------------\n\n\n");
	return(choix);
}


	/* Procédure d'affichage de fin de jeu */
void AffichageFinJeu () {
	printf("\n\n\n\n\n\t\t* * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t*                                                 *\n");
	printf("\t\t*           Gunes Aysel et RAMOS Pierre           *\n");
	printf("\t\t*  vous remercient d'avoir utilise ce programme.  *\n");
	printf("\t\t*                                                 *\n");
	printf("\t\t*             ><     A BIENTOT     ><             *\n");
	printf("\t\t*                                                 *\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
}


	/* Procédure permettant de lancer le choix demandé par l'utilisateur */
void lancementDuChoix (int choix, int compteur) {
	int test, choixBis;
	char temp;

	switch (choix) {
		// Presentation
		case 1 :
			test = existeFichier("presentation");
			if (test == TRUE) {
				ouvrirLecture("presentation");
				printf("\n\n._._._._._._._._._._._._._._._._._._._._._._._._._._._._.\n\n");
				printf("Veuillez taper sur \"ENTREE\" pour retourner au sommaire.\n");
				do {
					scanf("%c", &temp);
				} while (temp != '\n');
				printf("Retour au sommaire.\n");
				printf("._._._._._._._._._._._._._._._._._._._._._._._._._._._._.\n\n");
				mode_console();
			}
			else {
				printf("Erreur d'ouverture du fichier\n");
				printf("\nVeuillez formuler un autre choix\n");
				choixBis = litEntier();
				lancementDuChoix(choixBis, 0);
			}
			break;
	
		// Debuter l'experience
		case 2:
			lancementDuJeu();
			break;

		// Quitter
		case 3:
			AffichageFinJeu();
			exit(0);

		default:
			printf("Votre choix n'est pas valide.\nVeuillez refaire votre choix\n");
			choixBis = litEntier();
			compteur++;
			if(compteur < 3)
				lancementDuChoix(choixBis, compteur);
			else { 
				printf("Nous sommes desoles, vos demandes ne sont toujours pas correctes.\n");
				AffichageFinJeu();
				exit(0);
			}
	}
}


	/* Procédure permettant d'effectuer la selection des parametres
	   pour debuter l'expérience */
void selectionParametres () {
	char choixEspace;
	int choixVitesse, choix;
	Taille choixTaille;

	printf("\n\n\n>> SELECTION DES PARAMETRES <<\n");
	printf("Voulez vous une selection personnelle(1) ou automatique(2)?\n");
	choix = litEntier();
	initParamParDefaut();
	
	switch (choix) {
		// Personnelle
		case 1:
			choixEspace = selectionEspace();
			choixVitesse = selectionVitesse();
			choixTaille = selectionTaille();
			setEspace(choixEspace);
			setVitesse(choixVitesse);
			setTaille(choixTaille);
			break;

		// Automatique (par defaut)
		case 2:
			break;

		default:
			printf("Votre selection n'est correcte.\nNous considerons donc les parametres par defaut.\n");
	}
}


	/* Fonction retournant le type d'espace choisi */
char selectionEspace () {
	char c;
	int choix;
	printf("\t- - Type d'espace:\n\t\t");
	printf("> 1- Espace Torique\n\t\t");
	printf("> 2- Espace Cylindrique\n\t\t");
	printf("> 3- Espace Carre en 2D\n");
	printf("choix: ");
	choix = litEntier();
	switch (choix) {
		// Esapce Torique
		case 1:
			c = 'T';
			break;

		// Espace Cylindrique
		case 2:
			c = 'C';
			break;

		// Espace Carre 2D
		case 3:
			c = 'K';
			break;

		// Quitter
		case 0:
			printf("Votre choix a ete de quitter.\n");
			AffichageFinJeu();
			exit(0);
			
		default:
			printf("Votre selection n'est pas correcte.\nVeuillez reprendre ou taper 0 pour quitter.\n");
			c = selectionEspace();
	}
	return c;
}


	/* Fonction retournant la vitesse de deroulement de l'experience */
int selectionVitesse () {
	int choix;
	printf("\t- Vitesse d'evolution:\n\t\t");
	printf("> 1- Lente\n\t\t");
	printf("> 2- Normale\n\t\t");
	printf("> 3- Rapide\n\t\t");
	printf("> 4- Personnelle\n");
	printf("choix: ");
	choix = litEntier();
	if (choix == 0) {
		printf("Votre choix a ete de quitter.\n");
		AffichageFinJeu();
		exit(0);
	}
	if (choix!=1 && choix!=2 && choix!=3 && choix!=4) {
		printf("Votre selection n'est pas correcte.\nVeuillez reprendre ou taper 0 pour quitter.\n");
		choix = selectionVitesse();
	}
	return choix;
}		


	/* Fonction retournant la Taille de l'espace de deroulement de l'experience */
Taille selectionTaille () {
	int choixHauteur, choixLargeur;
	Taille taille;
	printf("\t- Taille de l'espace:\n\t");
	printf("   Les valeurs de la hauteur et de la largeur doivent\n\t   etre comprises entre 10 et 30.\n");
	printf("\t\t> Hauteur: ");
	choixHauteur = litEntier();
	printf("\t\t> Largeur: ");
	choixLargeur = litEntier();
	if (choixHauteur == 0 && choixLargeur == 0) {
		printf("Votre choix a ete de quitter.\n");
		AffichageFinJeu();
		exit(0);
	}
	else {
		if (choixHauteur < 10 || choixHauteur > 30) {
			printf("Votre selection pour la taille de la HAUTEUR n'est pas correcte.\n");
			printf("Veuillez reprendre ou taper 0 pour la hauteur et 0 pour la largeur pour quitter.\n");
			taille = selectionTaille();
		}
		if (choixLargeur < 10 || choixLargeur > 30) {
			printf("Votre selection pour la taille de la LARGEUR n'est pas correcte.\n");
			printf("Veuillez reprendre ou taper 0 pour la hauteur et 0 pour la largeur pour quitter.\n");
			taille = selectionTaille();
		}
	}
	taille.hauteur = choixHauteur;
	taille.largeur = choixLargeur;
	return taille;
}	


	/* Procédure pour la selection de l'initialisation des souches */
void selectionSouches (int compteur) {
	int i, hauteur, largeur, emplacement;

	printf("\n\n\n>> SELECTION DES SOUCHES <<\n");
	printf("Nombre de souches souhaite pour l'experience: ");
	nbSouchesG = litEntier();
	
	while((nbSouchesG<1 || nbSouchesG>9) && compteur<3) {
		printf("Votre selection est incorrecte.\n");
		printf("Veuillez entrer un nombre entre 1 et 9.\n");
		printf("Nombre de souches: ");
		nbSouchesG = litEntier();
		compteur++;
	}
	if (compteur==3) {
		printf("Nous sommes desoles, vos selections ne sont toujours pas correctes.\n");
		AffichageFinJeu();
		exit(0);
	}

	printf("\nEn ce qui concerne l'emplacement des cellules de la (ou des) souche(s),\nsouhaitez-vous:\n\t");
	printf("1- un emplacement aleatoire ?\n\t");
	printf("2- un emplacement personnel ?\nchoix: ");
	emplacement = litEntier();
	switch (emplacement) {
		// aleatoire
		case 1:
			soucheG = generationPlusieursSouches(nbSouchesG, parametres.taille);
			break;

		// personnel
		case 2:
			hauteur = (parametres.taille).hauteur;
			largeur = (parametres.taille).largeur;
			soucheG = (Souche*) malloc(nbSouchesG*sizeof(Souche));
			for(i=0; i<nbSouchesG; i++) {
				soucheG[i].hauteur = hauteur;
				soucheG[i].largeur = largeur;
				soucheG[i].typeCell = i+1;
				printf("\nSouche numero: %d\n", i+1);
				soucheG[i].mat = initialisationMatrice(parametres.taille, i+1);
			}
			break;

		default:
			printf("Votre selection n'est pas correcte.\n");
			printf("Nous considerons donc un emplacement aleatoire.\n");
			soucheG = generationPlusieursSouches(nbSouchesG, parametres.taille);
	}
}


	/* Fonction permettant d'initialiser une matrice manuellement */
int** initialisationMatrice (Taille taille, int typeCell) {
	int** mat;
	int i, j, hauteur, largeur;
	char caractere;
	hauteur = taille.hauteur;
	largeur = taille.largeur;

	mat = (int**) malloc(hauteur*sizeof(int*));
	for(i=0; i<hauteur; i++) {
		mat[i] = (int*) malloc(largeur*sizeof(int));
	}
	for(i=0; i<hauteur; i++) {
		for(j=0; j<largeur; j++) {
			mat[i][j] = 0;
		}
	}
	printf("Veuillez entrer les coordonnees de l'emplacement de chacune\nde vos cellules de la maniere suivante: \"x,y\".\n");
	printf("L'abscisse x doit etre comprise entre 1 et la largeur de l'espace.\n");
	printf("L'ordonnee y doit etre comprise entre 1 et la hauteur de l'espace.\n\n");
	printf("\tVeuillez taper sur ENTREE pour commencer.\n\tUne fois terminee, veuillez taper \"f\" pour fin.\n\n");
	caractere = litPremierCarac();
	if (caractere != 'f' && caractere != 'F') {
		do {
			printf("> ");
			scanf("%d,%d", &j, &i);
			if (i>0 && i<=hauteur && j>0 && j<=largeur)
				mat[i-1][j-1] = typeCell;
			else {
				if (caractere != 'f' && caractere != 'f') 
					printf("Erreur de syntaxe.\nVeuillez reprendre.\n\n");
			}
			caractere = litPremierCarac();
		} while((caractere != 'f') && (caractere != 'F'));
	}
	printf("\nVoici la souche initialisee:\n\n");
	afficheMatrice(mat, taille);
	return mat;
}


	/* Procédure permettant de lancer l'experience */
void lancementDuJeu () {
	int i;
	char rep, c;

	// initialisation de la germe
	srand((unsigned)time(NULL));
	
	choixExperience();
	matriceG = regroupementSouches(nbSouchesG, soucheG);
	soucheTempG = (Souche*) malloc(nbSouchesG*sizeof(Souche));
	matriceTempG = (int**) malloc(((parametres.taille).hauteur)*sizeof(int*));
	for(i=0; i<((parametres.taille).hauteur); i++) {
		matriceTempG[i] = (int*) malloc(((parametres.taille).largeur)*sizeof(int));
	}
	
	printf("\n--------------------------------------------------------\n\n\n");
	printf("\t\t--------------------------\n");
	printf("\t\t DEBUT  DE  L' EXPERIENCE\n");
	printf("\t\t--------------------------\n");
	
	while (parametres.vitesse == 4) {
		rep = boucle();
		if (rep=='Q' || rep=='q') {
			printf("\nVous avez demande a arreter le deoulement de l'experience.\n");
			printf("Voulez-vous sauvegarder l'experience actuelle (o/n)?\n");
			c = litPremierCarac();
			choixSauvegarde(c);
			AffichageFinJeu();
			exit(0);
		}
		 if (rep=='P' || rep=='p') {
			choixPause();
		}
	}
	
	if (parametres.vitesse != 4) {
		rep = boucle();
	}
}


	/* Fonction qui reprend la boucle de l'algorithme */
char boucle () {
	char rep;
	int choix, compteur=0;

	do {
		printf("\n\n");
		afficheMatrice(matriceG, parametres.taille);
		algorithme();
		if (stationnaire == 0) {
			printf("\nEtat Stationnaire\n\n");
			printf("Retour au sommaire\n\n");
			choix = PagePresentation();
			lancementDuChoix(choix, compteur);
		}
		if (parametres.vitesse == 4) {
			rep = litPremierCarac();
		}
		else {
			tempsAvancement();
		}
	} while(1 && rep!='Q' && rep!='q' && rep !='P' && rep !='p');
	return rep;
}


	/* Procédure permettant de sauvegarder une experience */
void choixSauvegarde (char c) {
	char* chaine;
	int choix, compteur = 0, test;

	if (c=='o' || c=='O') {
		printf("\n\n\tSAUVEGARDE DE L'EXPERIENCE\n");
		printf("Veuillez entrer le nom sous lequel vous souhaitez\n\teffectuer la sauvegarde:\n>> ");
		chaine = litCaractere();
		chaine[strlen(chaine)-1] = 0;
		test = existeFichier(chaine);
		if (test == FALSE) {
			sauvegarde(nbSouchesG, matriceG, chaine);
		}
		else {
			printf("Le fichier specifie existe deja. Voulez-vous:\n");
			printf("> 1- L'ecraser\n\t");
			printf("> 2- Le renommer\n\t");
			printf("> 3- Quitter?\n choix: ");
			choix = litEntier();
			if (choix == 1) {
				sauvegarde(nbSouchesG, matriceG, chaine);
			}
			if (choix == 2) {
				printf("Veuillez entrer le nom sous lequel vous souhaitez\n\teffectuer la sauvegarde:\n>> ");
				chaine = litCaractere();
				chaine[strlen(chaine)-1] = 0;
				test = existeFichier(chaine);
				if (test == FALSE) {
					sauvegarde(nbSouchesG, matriceG, chaine);
				}
				else {
					printf("Ce fichier specifie existe aussi.\n");
				}
			}
			if (choix == 3) {
				AffichageFinJeu();
				exit(0);
			}
		}
	}
	else {
		printf("Vous n'avez pas acceptez la sauvegarde.\n");
	}
	printf("\nVoulez-vous retourner au sommaire(1) ou quitter(2)?\nchoix: ");
	choix = litEntier();
	if (choix == 1) {
		choix = PagePresentation();
		lancementDuChoix(choix, compteur);
	}
	else {
		AffichageFinJeu();
		exit(0);
	}
}


	/* Procédure permettant de charger une experience préexistante */
void choixChargement() {
	char* chaine;
	int test;

	printf("\n\n\tCHARGEMENT D'UNE EXPERIENCE.\n");
	printf("Veuillez entrer le nom de votre experience a charger:\n>> ");
	chaine = litCaractere();
	chaine[strlen(chaine)-1] = 0;
	test = existeFichier(chaine);
	if (test == TRUE) {
		soucheG = chargement(&nbSouchesG, &parametres, chaine);
	}
	else{
		printf("Chargement impossible. Le fichier n'existe pas.\n");
		printf("Retour au sommaire\n");
		mode_console();
	}
}


	/* Procedure permettant de proposer les options du cas "pause" */
void choixPause () {
	int choix, choixVitesse;
	char choixEspace;
	
	printf("\n\n\tPAUSE DE L'EXPERIENCE.\n");
	printf("Souhaitez-vous effectuer:\n\t");
	printf("> 1- Des modifications dans les parametres\n\t");
	printf("> 2- Sauvegarder l'experience en cours\n\t");
	printf("> 3- Quitter?\nchoix: ");
	choix = litEntier();
	if (choix == 2) {
		choixSauvegarde('o');
	}
	if (choix == 1) {
		printf("\n\n\n>> MODIFICATION DES PARAMETRES <<\n");
		printf("Remarque: la taille de l'espace ne peut etre modifiee.\n");
		printf("--------\n");
		printf("Voulez vous une selection personnelle(1) ou automatique(2)?\n");
		choix = litEntier();
		switch (choix) {
			// Personnelle
			case 1:
				choixEspace = selectionEspace();
				choixVitesse = selectionVitesse();
				setEspace(choixEspace);
				setVitesse(choixVitesse);
				break;

			// Automatique (par defaut)
			case 2:
				setEspace(ESPACE_PAR_DEFAUT);
				setVitesse(VITESSE_PAR_DEFAUT);
				break;

			default:
				printf("Votre selection n'est correcte.\nNous considerons donc les parametres par defaut.\n");
		}
	}
	if (choix!=1 && choix!=2 && choix!=3) {
		printf("Mauvaise selection.\nNous considerons que vous voulez quitter\n");
		AffichageFinJeu();
		exit(0);
	}
	printf("Retour a l'experience\n");
}


	/* Procédure permettant de choisir le lancement de l'experience.
	   A savoir un chargement ou une nouvelle experience */
void choixExperience() {
	int choix, compteur=0;

	printf("\n\t\t>< LANCEMENT D'UNE EXPERIENCE ><\n");
	printf("\t\t   --------------------------\n");
	printf("\nSouhaitez-vous lancer l'experience a partir d':\n\t");
	printf("> 1- Une experience preexistante\n\t");
	printf("> 2- Une nouvelle experience?\nchoix: ");
	choix = litEntier();
	if (choix == 1) {
		choixChargement();
	}
	else {
		if (choix!=2) {
			printf("Votre choix est incorrect.\n");
			printf("Nous coniderons donc le choix d'une nouvelle experience.\n");
		}
		selectionParametres();
		selectionSouches(compteur);
	}
}


	/* Procédure permettant de lancer le mode_console */
void mode_console () {
	int choix, compteur=0;	
	choix = PagePresentation();
	lancementDuChoix(choix, compteur);
}
	

		/* Procédure permettant de faire defiler le texte contenu
	   dans la fenetre en tapant ENTREE */
void printEntree () {
	int i;
	for(i=0; i<2; i++) {
		printf("\n");
	}
	printf("\n\t---------------- Taper ENTREE pour continuer ----------------");
	(void)litPremierCarac();
}			


	/* Procédure permettant d'ouvrir en lecture et d'afficher
	   le contenu d'un fichier */
void ouvrirLecture(char* nomFichier) {
	FILE* fichier;
	char c;

	/* Test de l'existence de fichier supposé fait en amont */
	/* Ouverture en mode lecture */	
	fichier = fopen(nomFichier, "r");
	do {
		c = fgetc(fichier);
		if (c!='/' && c!='*')
			printf("%c", (char)c);
		else {
			if(c!='*')
				printEntree();
		}
	} while (c != '*');
	/* Sous Linux, demander l'affichage de tous les caractères contenus dans
	   un fichier tant que le caractère lu soit différent de "EOF"
	   "while(c!=EOF)" engendre l'apparition d'un caractère spécial à la fin
	   de l'affichage à la sortie standrad qui doit représenter le retour chariot.
	   Ainsi, dans cette procédure nous afficherons tous les caratères
	   jusqu'à ce qu'il soit rencontré le caractère '*'. */
	fclose(fichier);
}





