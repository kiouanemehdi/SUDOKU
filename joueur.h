#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <dirent.h>


typedef struct joueur
{
     char pseudo[55];

}Joueur;

Joueur *player;

Joueur * creerJoueur(char nom[]);
char* lire_pseudo();
void creerDossier(char pseudo[]);



#endif // JOUEUR_H_INCLUDED
