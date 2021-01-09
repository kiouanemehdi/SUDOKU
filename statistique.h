#ifndef STATISTIQUE_H_INCLUDED
#define STATISTIQUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <dirent.h>

float get_time(char *pseudo);
int get_nombre_partie(char *pseudo);
void affiche_statistique(char* pseudo);

#endif // STATISTIQUE_H_INCLUDED
