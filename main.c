/***********************
 *					   *
 * FONCTION PRINCIPALE *
 *        MAIN         *
 *      (main.c)	   *
 *                     *
 ***********************/

// Inclusion des bibliothèques
#include"biblio.h"
#include"constantes.h"
#include"types.h"
#include"var_globales.h"
#include"jeu_de_la_vie.h"
#include"Interface_graphique.h"
#include"mode_console.h"

int main(int argc, char** argv) {
	if (argc == 2) {
		if (strcmp(argv[1], "console") == 0) {
			mode_console();
		} else {
			printf("argument incorrect\n");
			//initialisation de la fenetre
			gtk_init(&argc, &argv);
			//allocation de la memoire associee au programme
			pApp = g_malloc(sizeof(Programme));
			//creation de la fenetre principale
			pApp->fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
			gtk_window_set_default_size(GTK_WINDOW(pApp->fenetre), 800, 600);
			gtk_window_set_title(GTK_WINDOW(pApp->fenetre), "Le jeu de la vie");
			initParamParDefaut();
			g_signal_connect(G_OBJECT(pApp->fenetre), "destroy",
					G_CALLBACK(destruction), (gpointer* ) pApp);
			acceuil(pApp->fenetre, (gpointer*) pApp);
			//lancement de la boucle d'evenements
			gtk_main();
			//liberation de la memoire après la fin de la boucle d'evenements
			g_free(pApp);
		}
	} else {
		if (argc > 2)
			printf("nombre d'arguments incorrect\n");
		else {
			//initialisation de la fenetre
			gtk_init(&argc, &argv);
			//allocation de la memoire associee au programme
			pApp = g_malloc(sizeof(Programme));
			//creation de la fenetre principale
			pApp->fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
			gtk_window_set_default_size(GTK_WINDOW(pApp->fenetre), 800, 600);
			gtk_window_set_title(GTK_WINDOW(pApp->fenetre), "Le jeu de la vie");
			initParamParDefaut();
			g_signal_connect(G_OBJECT(pApp->fenetre), "destroy",
					G_CALLBACK(destruction), (gpointer* ) pApp);
			acceuil(pApp->fenetre, (gpointer*) pApp);
			//lancement de la boucle d'evenements
			gtk_main();
			//liberation de la memoire après la fin de la boucle d'evenements
			g_free(pApp);
		}
	}
	liberationAllocation();
	return 0;
}
