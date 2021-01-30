#include "joueur.h"


Joueur * creerJoueur(char nom[])
{
    Joueur * joueur=NULL;
    joueur=(Joueur*)malloc(sizeof(Joueur));
    strcpy(joueur->pseudo,nom);
    return joueur;
}

char* lire_pseudo()
{
    char* pseudo=malloc(sizeof(char));
    char c;
    printf("Entrer votre pseudo : ");
    scanf(" %s",pseudo);
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir ("joueur\\")) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL)
        {
            //printf(" %s",ent->d_name);
           if (strcmp(pseudo,ent->d_name)==0)
            {
                printf("\n Pseudo trouver\n");
                printf(" Vous voulez Continuer ?(o/n)");
                scanf(" %c",&c);
                if(c=='o')
                    return pseudo;
                else
                {
                    printf("\n Entrer un nouveau pseudo : ");
                    scanf(" %s",pseudo);
                    dir = opendir ("joueur\\");
                }
            }

        }
        return pseudo;
      closedir (dir);
    }
    else {
      // peut ne pas ouvrire le dossier
      perror ("");
      exit(22);
    }
}

void creerDossier(char pseudo[])
{
    char path[255];
    strcpy(path,"joueur/");
    //utilisation de la bibliotheque dirent.h
   // DIR *dir;
    //struct dirent *ent;

   // if ((dir = opendir ("joueur\\")) != NULL) {
      /* print all the files and directories within directory */
     /* while ((ent = readdir (dir)) != NULL)
        {
           if (strcmp(pseudo,ent->d_name)==0)
            {
                printf("Pseudo deja existe\n");
                break;
            }

        }
      closedir (dir);
    }
    else {
      // peut ne pas ouvrire le dossier
      perror ("");
      return EXIT_FAILURE;
    }
    if(!flag)
    {*/
        strcat(path,pseudo);
        pseudo[strlen(pseudo)+1]='\0';
        CreateDirectory(path,NULL);
    //}
}
