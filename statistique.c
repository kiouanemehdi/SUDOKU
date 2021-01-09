#include "joueur.h"
#include "sudoku.h"
#include "statistique.h"


//retourne le temps moyen de tous les partie jouer par ce joueur
float get_moyen_temps(char *pseudo)
{
    int k=0,n=0;
    float time;
    char chemin[55];
    int nb_ligne=get_nombre_partie(pseudo);
    float tab[nb_ligne];
    strcpy(chemin,"joueur/");
    strcat(chemin,pseudo);
    strcat(chemin,"/");
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (chemin)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        //pour ne pas afficher les 2 premieres dossier qui : . et ..
        if(k!=0 && k!=1)
        {
            strcat(chemin,ent->d_name);
            FILE *file = fopen(chemin, "r");

            for (int j = 0; j < 82; j++)
            {
            fscanf(file, "%f", &time);
            }
            tab[n]=time;
            n++;

            strcpy(chemin,"joueur/");
            strcat(chemin,pseudo);
            strcat(chemin,"/");
        }
        k++;
      }
      closedir (dir);
    } else {
      // peut ne pas ouvrire le dossier
      perror ("");
      return EXIT_FAILURE;
    }

    float somme=0.0;
    float moyenne=0.0;
    for(int i=0;i<nb_ligne;i++)
    {
        somme+=tab[i];
    }
    moyenne=somme/nb_ligne;
    return moyenne;

}

//retourne le nombre des parties jouer par le joueur
int get_nombre_partie(char *pseudo)
{
    int nb_part=0;
    char chemin[55];
    strcpy(chemin,"joueur/");
    strcat(chemin,pseudo);
    strcat(chemin,"/");
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (chemin)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
         nb_part++;
      }
      closedir (dir);
    } else {
      // peut ne pas ouvrire le dossier
      perror ("");
      return EXIT_FAILURE;
    }


    return nb_part-2;
}


void affiche_statistique(char* pseudo)
{
    printf ("\n\n \t\t ****************************** Statistique **************************** \n");
    printf("\t\t Statistique du joueur : \" %s \" \n\n ",pseudo);

    printf("\t\t Vous avez jouer %d parties \n\n ",get_nombre_partie(pseudo));

    printf("\t\t le temps moyen que vous avez passer dans chaque partie est : %f seconde \n\n ",get_moyen_temps(pseudo));

    printf("\t\t ************************************************************************");
}
