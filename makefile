			####################
			#                  #
			# LE JEU DE LA VIE #
			#     MAKEFILE     #
			#                  #
			####################


#librairies
GTK_LIB = `pkg-config --cflags --libs gtk+-2.0`
GTK_INC = /usr/include/gtk-2.0
SRC_PATH = src
TMP_PATH = tmp
OUT_PATH = dist

main: jeu_de_la_vie.o interface_graphique.o mode_console.o jeu_de_la_vie.o $(SRC_PATH)/main.c
	@echo Edition des liens
	@gcc -o $(OUT_PATH)/main $(SRC_PATH)/main.c $(TMP_PATH)/interface_graphique.o $(TMP_PATH)/mode_console.o $(TMP_PATH)/jeu_de_la_vie.o -Wall $(GTK_LIB)

mainConsole: mode_console.o jeu_de_la_vie.o $(SRC_PATH)/mainConsole.c
	@echo Edition des liens
	@gcc -o $(OUT_PATH)/mainConsole $(SRC_PATH)/mainConsole.c $(TMP_PATH)/mode_console.o $(TMP_PATH)/jeu_de_la_vie.o

jeu_de_la_vie.o: init $(SRC_PATH)/jeu_de_la_vie.c $(SRC_PATH)/jeu_de_la_vie.h
	@echo Compilation de jeu_de_la_vie.c
	@gcc -c $(SRC_PATH)/jeu_de_la_vie.c -o $(TMP_PATH)/jeu_de_la_vie.o

interface_graphique.o: $(SRC_PATH)/interface_graphique.c $(SRC_PATH)/interface_graphique.h jeu_de_la_vie.o
	@echo Compilation de interface_graphique.c
	@echo Les warnings qui suivent cette compilation sont presents car l edition des liens n est pas faite
	@gcc -c $(SRC_PATH)/interface_graphique.c -o $(TMP_PATH)/interface_graphique.o -Wall $(GTK_LIB)

mode_console.o: $(SRC_PATH)/mode_console.c $(SRC_PATH)/mode_console.h jeu_de_la_vie.o
	@echo Compilation de mode_console.c
	@gcc -c $(SRC_PATH)/mode_console.c -o $(TMP_PATH)/mode_console.o

init:
	-mkdir -p dist
	-mkdir -p tmp

clean:
	-rm -rf *.o
	-rm -f main 
	-rm -f mainConsole
	-rm -rf tmp
	-rm -rf dist
