			####################
			#                  #
			# LE JEU DE LA VIE #
			#     MAKEFILE     #
			#                  #
			####################


#librairies
GTK_LIB = `pkg-config --cflags --libs gtk+-2.0`
GTK_INC = /usr/include/gtk-2.0

main: jeu_de_la_vie.o Interface_graphique.o mode_console.o jeu_de_la_vie.o main.c
	@echo Edition des liens
	@gcc -o main main.c Interface_graphique.o mode_console.o jeu_de_la_vie.o -Wall $(GTK_LIB)

mainConsole: mode_console.o jeu_de_la_vie.o mainConsole.c
	@echo Edition des liens
	@gcc -o mainConsole mainConsole.c mode_console.o jeu_de_la_vie.o

jeu_de_la_vie.o: jeu_de_la_vie.c jeu_de_la_vie.h
	@echo Compilation de jeu_de_la_vie.c
	@gcc -c jeu_de_la_vie.c

Interface_graphique.o: Interface_graphique.c Interface_graphique.h jeu_de_la_vie.o
	@echo Compilation de Interface_graphique.c
	@echo Les warnings qui suivent cette compilation sont presents car l edition des liens n est pas faite
	@gcc -c Interface_graphique.c -Wall $(GTK_LIB)

mode_console.o: mode_console.c mode_console.h jeu_de_la_vie.o
	@echo Compilation de mode_console.c
	@gcc -c mode_console.c

clean:
	-rm -rf *.o
	-rm -f main 
	-rm -f mainConsole
