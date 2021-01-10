#include "sudoku.h"
#include "joueur.h"
/*un fichier contient des fonctions pour ajouter des couleurs dans la consoles
car la bibliotheque conio.h ne marche pas avec le compilateur Migw de codeblocks*/
#include "rlutil/rlutil.h"

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

//pour verifier les cases qui sont deja rempli dans le sudoku
//qui ne doivent pas etre changer
//si la case choisi par l'utilisateur ne peut pas etre changer la fonction retourn true sinon false

bool case_deja_rempli(int sudoku[9][9],int l,int c)
{
    int position_case[2][81];
    int i,j;
    int k=0;
    bool etat=false;
    //on stoque les indices des cases qui sont deja rempli dans un tableau position_case
    //l'indices de la ligne dans position_case[i] et l'indices de la colonne dans position_case[j]
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if (sudoku[i][j]!=0)
            {
                position_case[0][k]=i;
                position_case[1][k]=j;
                k++;
            }
        }
    }
// pour verifier si la ligne et la colonne choisi par l'utilisateur existe deja dans le tableau position_case
    for(int e=0;e<81;e++)
    {
        if((position_case[0][e]==l) && (position_case[1][e]==c))
        {
            etat=true;
        }
    }

    /*for(int e=0;e<2;e++)
    {

        for(int h=0;h<k;h++)
        {
            printf(" %d ",position_case[e][h]);
        }
        printf("\n");
    }*/
    return etat;
   // return position_case;

}

//une fonction pour afficher le sudoku
void affiche(int sudoku[9][9],char*niveau)
{
    int i,j;
    setColor(YELLOW);
    printf("\nNiveau: %s",niveau);
    setColor(12);
    printf("\t\t\t\t Appuyer sur [-1] pour revenir au menu");
    //setColor(YELLOW);
    //printf("\nTemps: 00:00:00");
    setColor(12);
    printf("\n  \t  \t  S U D O K U \n");
    for (i = 0; i < 9; i++)
    {setColor(10);
        if(!(i%3))
                //printf("\t-------------------------------\n");
                printf("\t*******************************\n");
        printf("\t");
        for (j = 0; j < 9; j++)
        {
            if(!(j%3))
                printf("|");

           printf(" %d ", sudoku[i][j]);
        }
        printf("|\n");
    }
    printf("\t*******************************\n");
   // printf("\t-------------------------------\n");
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
//fonction pour copier le sudoku d'un fichier.txt a un tableau
void import_sudoku(int sudoku[9][9],char *fichier)
{
    FILE *myFile;
    //ouuvrir le fichier qui contient le sudoku non complet en mode de lecture
    myFile = fopen(fichier, "r");

    //lire le fichier dans le tableau sudoku[][]
    int i,j;
    if (myFile == NULL){
        printf("Error Reading File\n");
        exit (0);
    }
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
        fscanf(myFile, "%d", &sudoku[i][j]);
        }
    }
}
//pour calculer le nombre des fichier dans le dossier facile ou difficile ou moyen
//pour calculer le nombre des sudokus qu'on a
int get_nombre_fichier(char *niveau)
{
    int nb_fichier=0;
    char chemin[55];
    strcpy(chemin,"niveau/");
    strcat(chemin,niveau);
    strcat(chemin,"/");
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (chemin)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
         nb_fichier++;
      }
      closedir (dir);
    } else {
      // peut ne pas ouvrire le dossier
      perror ("");
      return EXIT_FAILURE;
    }


    return nb_fichier-2;
}
//fonction pour choisir le chemin du fichier dans le quelle le sudoku est stocker
char* choix_sudoku(char *niveau)
{
    char chemin[255],sud[10]="sudoku";
    int num;char cnum[5];
    int nb_sudoku=get_nombre_fichier(niveau);
    //num=rand()%10;
    do
    {
        printf("\n entrer le numero de sudoku que vous voulez (entre 1 et %d): ",nb_sudoku);
        scanf("%d",&num);
    }while(num<1 || num>nb_sudoku);

    itoa(num, cnum, 10);
    //cnum[strlen(cnum)]='\0';
    //char cnum=num + '0';
    printf("\n cnum = %s \n",cnum);
    strcpy(chemin,"niveau");
    strcat(chemin,"/");
    strcat(chemin,niveau);
    strcat(chemin,"/");
    strcat(chemin,sud);
    strcat(chemin,cnum);
    //strncat(chemin, &cnum, 1);
    strcat(chemin,".txt");
    int fin=strlen(chemin);
    chemin[fin]='\0';

    //printf("chemin = %s",chemin);
    char * string_chemin;
    strcpy(string_chemin,chemin);

    return string_chemin;
}
// fonction pour creer le chemin apres importer le sudoku
void create_sudoku(int sudoku[9][9],char *niveau )
{
    char*level=choix_sudoku(niveau);
    import_sudoku(sudoku,level);
}
//fonction pour demander a l'utilisateur de choisir le niveur et on le repere dans la variable nv
void choix_niveau(int sudoku[9][9]/*,char *nv[]*/)
{
    char* pseudo =lire_pseudo();
    player=creerJoueur(pseudo);
    creerDossier(pseudo);
    system("cls");
    int n;
    printf("\n veuillez choisir un niveau : \n \t -Facile (1) \n \t -Moyen (2) \n \t -Difficile (3)");
    do{
    printf("\n entrer un nombre : ");
    scanf("%d",&n);
    }while(n<1 || n>3);
    switch (n)
    {
        case 1:
            create_sudoku(sudoku,"facile");
            //*nv="Facile";
            level="Facile";
        break;
        case 2:
            create_sudoku(sudoku,"moyen");
            //*nv="Moyen";
            level="Moyen";
        break;
        case 3:
            create_sudoku(sudoku,"difficile");
            //*nv="Difficile";
            level="Difficile";
        break;
    }

}
void creer_menu(int sudoku[9][9])
{
    int n;
    printf("\n veuillez definir votre choix :"
          " \n \t -(1) Lancer une partie"
          " \n \t -(2) Reprendre un partie"
          " \n \t -(3) Acceder aux  statistique de temps"
          " \n \t -(4) Aide"
          " \n \t -(5) Quitter");
    do{
    printf("\n entrer un nombre : ");
    scanf("%d",&n);
    }while(n<1 || n>5);
    switch (n)
    {
        case 1:
            system("cls");
            choix_niveau(sudoku);
            break;
        case 2:
            system("cls");
            reprendre(sudoku);
            break;
        case 3:
            system("cls");
            char* pseudo = lire_pseudo();
            system("cls");
            affiche_statistique(pseudo);
            creer_menu(sudoku);
            break;
        case 4:
            system("cls");
            Affiche_Aide();
            creer_menu(sudoku);
            break;
        case 5:
            exit(30);
            break;
    }
}

//fonction pour remplir le sudoku par l'utilisateur
void remplir_sudoku(int sudoku[9][9])
{
    int l,c,v,i,j;
    int sudoku_origine[9][9];
    //on stock les cases deja predefinis dans le sudoku dans un tableau sudoku_origine
    //pour ne pas perdre les indices apres l'interaction avec l'utilisateur
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            sudoku_origine[i][j]=sudoku[i][j];
        }
    }

    /*************************/
    clock_t debut, fin;

    /*****************************/
    debut =clock(); //le temps de debut
    //tanque le sudoku n'est pas rempli
    while((!is_empty(sudoku)))
    {
        affiche(sudoku,level);
        //tanque la case les coordonnees de la case entrer par l'utilisateur ne peuvent pas etre changer repete
        do
        {
            do
            {
               printf("\n entrer num de ligne : ");
               scanf("%d",&l);
               if(l == -1)
                  {
                      fin=clock();//le temps de fin
                      temps_de_jeu =(((double)(fin - debut))/CLOCKS_PER_SEC);
                      sauvegarder(sudoku);
                      break;
                  }
            }while(l>9 || l<1);
            do
            {
                if(l!=-1)
                {
                    printf("\n entrer num de colonne : ");
                    scanf("%d",&c);
                    if(c == -1)
                      {
                          fin=clock();//le temps de fin
                          temps_de_jeu =(((double)(fin - debut))/CLOCKS_PER_SEC);
                          sauvegarder(sudoku);
                          break;
                      }
                }

            }while(c>9 || c<1 );

        }while(case_deja_rempli(sudoku_origine,l-1,c-1)||(l>9));
        do
        {
            if(c!=-1)
            {
                printf("\n entrer la valeur de la case : ");
                scanf("%d",&v);
                if(v == -1)
                {
                    fin=clock();//le temps de fin
                    temps_de_jeu =(((double)(fin - debut))/CLOCKS_PER_SEC);
                    sauvegarder(sudoku);
                    break;

                }
            }
        }while(v>9 || v<1);

        //stocke la valeur entrer par l'utilisateur dans le tableau sudoku
        sudoku[l-1][c-1]=v;
        //pour effacer la console pour un bon affichage
        system("cls");
    }

    fin=clock();//le temps de fin
    temps_de_jeu =(((double)(fin - debut))/CLOCKS_PER_SEC); //la difference entre le temps de debut et de fin en secondes
    //printf("\n temps = %f",temps_de_jeu);
}
//une fonction pour sauvegarder le sudoku dans un fichier .txt dans le dossier sauvegarder
void sauvegarder(int sudoku[9][9])
{
    char c;
    char nom_fichier[30],nom_fichier2[30],chemin[50],chemin2[50];
    do
    {
        printf("\n Est ce que vous voulez sauvegarder? (o/n): ");
        scanf(" %c",&c);
    }while(c!='o' && c!='n');
    if(c=='n')
    {
        system("cls");
        creer_menu(sudoku);
    }
    else
    {
        system("cls");
        printf("entrer un nom pour le sauvegarder : ");
        scanf("%s",&nom_fichier);

        //strcpy(nom_fichier2,nom_fichier);
        strcat(nom_fichier,".txt");

        strcpy(chemin,"joueur/");
        strcat(chemin,player->pseudo);
        strcat(chemin,"/");
        //strcpy(chemin,"sauvegard/grille/");
        //strcat(chemin,"/grille");
        strcat(chemin,nom_fichier);
        FILE *myFile,*myFile_temps;
        //ouuvrir le fichier qui contient le sudoku non complet en mode de lecture
        myFile = fopen(chemin, "w");

        /*strcat(nom_fichier2,"_temps.txt");
        strcpy(chemin2,"sauvegard/temps/");
        //strcat(chemin2,"/");
        strcat(chemin2,nom_fichier2);
        myFile_temps = fopen(chemin2, "w");
         if (myFile_temps == NULL){
            printf("Error opening File\n");
            exit (0);
        }
        fprintf(myFile_temps,"%f ",temps_de_jeu);*/


        //lire le fichier dans le tableau sudoku[][]
        int i,j;
        if (myFile == NULL){
            printf("Error opening File\n");
            exit (0);
        }
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
              fprintf(myFile,"%d ", sudoku[i][j]);
            }
            fprintf(myFile,"%s" ,"\n");
        }
        fprintf(myFile,"%f ",temps_de_jeu);

        printf("\n Vous avez bien sauvegarder votre partie");


        fclose(myFile);
        //fclose(myFile_temps);
        delay(2500);
        system("cls");
        creer_menu(sudoku);
    }

}
//fonction pour ajouter un delai de temps avant une instruction (utilisez dans l'affichage)
void delay(int milli_secondes)
{
    // enregistrer le temps de debut
    clock_t start_time = clock();
    // repeter tanque le temps requis n'est pas atteint
    while (clock() < start_time + milli_secondes);
}
//on verifie le sudoku si il est juste ou faux
void afficher_resulat(int sudoku[9][9])
{
    //setColor(12);
    printf("\n \n temps ecoule : %f",temps_de_jeu);
    if(estValide(sudoku)==81)
    {
        printf("\n Vous avez gagne \n");
        sauvegarder(sudoku);
    }
    else
    {
        printf("\n Vous avez perdu \n");
        delay(2500);
        system("cls");
        creer_menu(sudoku);
        //sauvegarder(sudoku);
    }

}
//fonction qui affiche les noms des fichiers enregistrer dans le dossier sauvegard apres l'utilisateur doit entrer le nom du fichier
//si le nom existe on affiche le sudoku enregistree dans ce fichier
void reprendre(int sudoku[9][9])
{
    char* pseudo =lire_pseudo();
    char chemin[50];
    strcpy(chemin,"joueur/");
    strcat(chemin,pseudo);
    strcat(chemin,"/");
    //utilisation de la bibliotheque dirent.h
    DIR *dir;
    struct dirent *ent;

    int k=0;
    char tab[20][50];
    system("cls");
    printf("\n les parties deja sauvegarder sont:\n\n");
    /* D:\\TP C\\Sudoku_tests\\test\\sauv test\\ */
    //ouvrire le dossier sauvegard qui se trouve dans le meme dossier du projet
    if ((dir = opendir (chemin)) != NULL) {
      /* print all the files and directories within directory */
      while ((ent = readdir (dir)) != NULL) {
        //pour ne pas afficher les 2 premieres dossier qui : . et ..
        if(k!=0 && k!=1)
            printf ("\t %s\n", ent->d_name);

        strcpy(tab[k],ent->d_name);
        k++;
      }
      closedir (dir);
    } else {
      // peut ne pas ouvrire le dossier
      perror ("");
      return EXIT_FAILURE;
    }
    char part[50];

    int count=0;

    printf("\n entrer le nom de la partie souhaiter: ");
    scanf(" %s",part);

    for(int i=0;i<k;i++)
    {
        if(strcmp(tab[i],part)==0)
            count++;
    }
   // char*path;
    if(count==1)
    {
        printf("\n fichier trouver");
        strcat(chemin,part);
        //strcpy(path,"sauvegard");
        //strcat(path,"/grille/");
        //strcat(path,part);
        system("cls");
        import_sudoku(sudoku,chemin);
        //affiche(sudoku,level);
        remplir_sudoku(sudoku);
    }

    else
    {
        printf("\n fichier non trouver");
        delay(1500);
        system("cls");
        creer_menu(sudoku);
    }

}

void Affiche_Aide()
{
    char ligne[100]="";
    FILE *file;
    file = fopen("Aide.txt","r");

    if(file==NULL)
    {
        printf("\n erreur ");
        fclose(ligne);
    }


    while(fgets(ligne,sizeof(ligne),file) != NULL)
    {
        printf("\t %s",ligne);
    }
    printf("\n\n");
    fclose(file);

  /*  printf("Appuzez sur 1 pour revenir au menu : ");
    int n;
    scanf("%d",&n);
    while(n!=1)
    {
        printf("Appuzez sur 1 pour revenir au menu : ");
        scanf("%d",&n);
    }
    if(n==1)
        creer_menu();*/
}
