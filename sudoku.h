#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <dirent.h>

//variable globale pour stocker le niveau de jeu facile ou moyen ou difficile
char* level;
//variable globale pour enregitrer le temps pour resoudre le sudoku
double temps_de_jeu;

//pour verifier si le sudoku contient encore des 0
//si il a trouver un seul 0 il retourn false sinon true
bool is_empty(int sudoku[9][9]);

//pour verifier les cases qui sont deja rempli dans le sudoku
//qui ne doivent pas etre changer
//si la case choisi par l'utilisateur ne peut pas etre changer la fonction retourn true sinon false
bool case_deja_rempli(int sudoku[9][9],int l,int c);

//une fonction pour afficher le sudoku
void affiche(int sudoku[9][9],char*niveau);

 //fonction pour verifier si la valeur asbent sur la ligne l dans le tableau sudoku
 //s'il existe return true sinon false
 bool absentSurLigne (int valeur, int sudoku[9][9], int l);

  //fonction pour verifier si la valeur asbent sur la colonne c dans le tableau sudoku
 //s'il existe return true sinon false
bool absentSurColonne (int valeur, int sudoku[9][9], int c);

 //fonction pour verifier si la valeur asbent sur le bloc dans lequel existe la case determiner
 //par la ligne l et la colonne c dans le tableau sudoku
 //s'il existe return true sinon false
bool absentSurBloc (int valeur, int sudoku[9][9], int l, int c);

//fonction pour verifier si le sudoku et just
//il incremente count a chaque fois la case tester est juste
//si count a la fin egale 81(le nombre total des cases) donc le sudoku est juste
int estValide (int sudoku[9][9]);

//fonction pour copier le sudoku d'un fichier.txt a un tableau
void import_sudoku(int sudoku[9][9],char *fichier);

//fonction pour choisir le chemin du fichier dans le quelle le sudoku est stocker
char* choix_sudoku(char *niveau);

// fonction pour creer le chemin apres importer le sudoku
void create_sudoku(int sudoku[9][9],char *niveau );

//fonction pour demander a l'utilisateur de choisir le niveur et on le repere dans la variable nv
void choix_niveau(int sudoku[9][9]/*,char *nv[]*/);

void creer_menu(int sudoku[9][9]);

//fonction pour remplir le sudoku par l'utilisateur
void remplir_sudoku(int sudoku[9][9]);

//une fonction pour sauvegarder le sudoku dans un fichier .txt dans le dossier sauvegarder
void sauvegarder(int sudoku[9][9]);

//fonction pour ajouter un delai de temps avant une instruction (utilisez dans l'affichage)
void delay(int milli_secondes);

//on verifie le sudoku si il est juste ou faux
void afficher_resulat(int sudoku[9][9]);

//fonction qui affiche les noms des fichiers enregistrer dans le dossier sauvegard apres l'utilisateur doit entrer le nom du fichier
//si le nom existe on affiche le sudoku enregistree dans ce fichier
void reprendre(int sudoku[9][9]);

//pour calculer le nombre des fichier dans le dossier facile ou difficile ou moyen
//pour calculer le nombre des sudokus qu'on a
int get_nombre_fichier(char *niveau);

void Affiche_Aide();

#endif // SUDOKU_H_INCLUDED
