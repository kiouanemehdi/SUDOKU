#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//pour verifier si le sudoku contient encore des 0
//si il a trouver un seul 0 il retourn false sinon true
bool is_empty(int sudoku[9][9])
{
    bool etat=true;
    int i,j;
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if(sudoku[i][j]== 0)
            {

                etat=false;
            }
        }
    }
    return etat;
}
 /***********************************************************/
 //fonction pour verifier si la valeur asbent sur la ligne l dans le tableau sudoku
 //s'il existe return true sinon false
 bool absentSurLigne (int valeur, int sudoku[9][9], int l)
{
    int count=1;
    for (int i=0; i < 9; i++)
    {
        if (sudoku[l][i] == valeur)
            count--;
    }
    if(count==0)
            return true;
    return false;
}

 //fonction pour verifier si la valeur asbent sur la colonne c dans le tableau sudoku
 //s'il existe return true sinon false
bool absentSurColonne (int valeur, int sudoku[9][9], int c)
{
    int count=1;
    for (int i=0; i < 9; i++)
    {
        if (sudoku[i][c] == valeur)
            count--;
    }

    if(count==0)
        return true;
    return false;
}
 //fonction pour verifier si la valeur asbent sur le bloc dans lequel existe la case determiner
 //par la ligne l et la colonne c dans le tableau sudoku
 //s'il existe return true sinon false
bool absentSurBloc (int valeur, int sudoku[9][9], int l, int c)
{
    int count=1;
    int i = 3*(l/3), j = 3*(c/3); // ou encore : _i = i-(i%3), _j = j-(j%3);
    for (l=i; l < i+3; l++)
    {
        for (c=j; c < j+3; c++)
        {
            if (sudoku[l][c] == valeur)
                count--;
        }

    }

    if(count==0)
        return true;
    return false;
}

//fonction pour verifier si le sudoku et just
//il incremente count a chaque fois la case tester est juste
//si count a la fin egale 81(le nombre total des cases) donc le sudoku est juste
int estValide (int sudoku[9][9])
{
    int count=0;
    for (int i=0; i < 9; i++)
    {
        for (int j=0; j < 9; j++)
        {

            if ((absentSurLigne(sudoku[i][j],sudoku,i)) && (absentSurColonne(sudoku[i][j],sudoku,j)) && (absentSurBloc(sudoku[i][j],sudoku,i,j)))
            {
                count++;
            }
        }

    }
    return count;
}
