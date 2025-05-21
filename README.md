# Jeu de la vie
Projet Universitaire réalisé en 2005.

Implémentation du jeu de la vie de Conway en C avec une interface graphique en GTK

## Compilation et exécution
### Sous Windows avec WSL et VS Code
#### Config IDE
- Installer le plugin WSL
- Installer le plugin Makefile
- Démarrer le projet dans WSL (Version 2)
- Configurer le plugin makefile pour exécuter le goal main

#### Config WSL
- Installer les éléments pour permettre la compilation
```bash
sudo apt-get install build-essential gdb
```
- Installer la librairie GTK 2
```bash
apt-get install libgtk2.0-dev
```

#### Compilation
- Lancer le goal main avec le plugin makefile

#### Execution
- Installer X11
```bash
sudo apt-get install x11-apps
```
- Ajouter dans la session les paramètres de serveur X :
```bash
export LIBGL_ALWAYS_INDIRECT=1export DISPLAY=$(ip route | awk '/^default/{print $3; exit}'):0
```
- Installer MobaXterm
- Lancer MobaXterm et activer le serveur X
- Lancer le programme compilé main
- Accepter dans MobaXterm la connexion distante
- Le jeu démarre