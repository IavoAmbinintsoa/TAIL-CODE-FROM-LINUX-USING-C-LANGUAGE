#include "file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void option(int argc,char *argv[])
{   
    FILE *file;
    int dernier = 10; //Par defaut (les 10 derniers ligne)
    int nombre;
    int i;
    if(argc == 1 )
    {
        printf("Veillez indiquer le chemin vers le fichier\n");
        exit(EXIT_FAILURE);
    }
    if((strcmp(argv[1],"--version") == 0))
    {
        version();
    }
    if(strcmp(argv[1],"--help") == 0)
    {
        help();
        exit(EXIT_SUCCESS);
    }
    file = fopen(argv[argc-1],"r"); //recuperer l'argument
    if(file == NULL)
    {
        printf("Erreur lors de l'ouverture\n");
        exit(EXIT_FAILURE);
    }
    for(i = 1;i<argc;i++)
    {
        if(strcmp(argv[i],"-n") == 0)
        {
            dernier = atoi(argv[i+1]);
        }
        if((strcmp(argv[i],"--bytes") == 0) || (strcmp(argv[i],"-c") == 0))
        {
            bytes(argv[i+1],file);
        }
        if(strcmp(argv[i],"-v") == 0)
        {
            verbose(file,argv[argc-1],dernier);
        }
        if((strcmp(argv[i],"-f") == 0))
        {
            flux(argv[argc-1],dernier);
        }
        if((strcmp(argv[i],"-q") == 0) || (strcmp(argv[i],"--quiet") == 0))
        {
            quiet(file,dernier);
        }
    }
    nombre = NombreDeLigne(file);
    afficher(file,nombre,dernier);
    fclose(file);
}
void quiet(FILE *file,int dernier)
{
    int nombre = NombreDeLigne(file);
    afficher(file,nombre,dernier);
    exit(EXIT_SUCCESS);
}
void flux(char *argv,int dernier)
{
    FILE *file = fopen(argv,"r");
    int nombre = NombreDeLigne(file);
    int nombreactuel;
    afficher(file,nombre,dernier);
    rewind(file);
    while(1)
    {
        nombreactuel = NombreDeLigne(file);
        if(nombre != nombreactuel)
        {
            printf("==========> fichier Modifier\n");
            afficher(file,nombreactuel,dernier);
            rewind(file);
            nombre = nombreactuel;
        }
        //POUR ACTUALISE LE FICHIER
        fclose(file);
        file = fopen(argv,"r");
    }
}
void verbose(FILE *file,char argv[],int dernier)
{
    printf("==> %s <== \n",argv);
    int nombre = NombreDeLigne(file);
    afficher(file,nombre,dernier);
    exit(EXIT_SUCCESS);
}
void help()
{
    printf("Utilisation : tail [OPTION]... [FICHIER]...\n");
    printf("Afficher les 10 dernieres lignes de chaque FICHIER sur la sortie standard.\n");
    printf("Avec plusieurs FICHIERs, ecrire un en-tête donnant le nom avant chaque fichier.\n");
    printf("Sans FICHIER ou quand FICHIER est -, afficher une demande.\n\n");
    printf("Les arguments disponible :\n");
    printf("-c, --bytes=[+]N ,-b        afficher les N derniers octets ; -c +N peut aussi\n");
    printf("                            être utilise pour afficher les octets a partir du\n");
    printf("                            Nieme de chaque fichier\n");
    printf(" -f, --follow[={name|descriptor}]\n");
    printf("                         afficher les donnees ajoutees au fur et a mesure\n");
    printf("                             que le fichier grandit ; sans argument, c’est\n");
    printf("                             equivalent a 'descriptor'\n");
    printf(" -n, --lines=[+]N         afficher les N dernieres lignes, au lieu des 10\n");

    printf("                             dernieres, -n +N pour afficher a partir de la Nieme\n");
    printf("-q, --quiet,    ne jamais afficher l'en-tête donnant les noms\n");
    printf("                             de fichiers\n");
    printf(" -v, --verbose            afficher toujours les en-têtes des noms de fichier\n");
    printf("                             du saut de ligne\n");
    printf("     --help     afficher l'aide et quitter\n");
    printf("--version  afficher des informations de version et quitter\n\n");
    printf("Aide en ligne de GNU coreutils : <https://www.gnu.org/software/coreutils/>\n");
    printf("Signalez les problemes de traduction de « tail » a : <traduc@traduc.org>\n");
    printf("Documentation complete a : <https://www.gnu.org/software/coreutils/tail>\n");
    printf("ou disponible localement via: info '(coreutils) tail invocation'\n");
    exit(EXIT_SUCCESS);
}
void version()
{
    printf("==> CE CODE EST UNE CODE EN C QUI EST TIREE DE LA VERSION DE TAIL : \n\n");
    printf("\ttail (GNU coreutils) 8.32\n");
    printf("\tCopyright (C) 2020 Free Software Foundation, Inc.\n");
    printf("\tLicense GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n");
    printf("\tThis is free software: you are free to change and redistribute it.\n");
    printf("\tThere is NO WARRANTY, to the extent permitted by law.\n");
    printf("\tWritten by Paul Rubin, David MacKenzie, Ian Lance Taylor,\n");
    printf("\tand Jim Meyering.\n\n");
    printf("==> Ce code est fait par RAMANDIAMANANA Iavonirina Ambinintsoa \n");
    exit(EXIT_SUCCESS);
}
void afficher(FILE* file,int nombre,int dernier)
{
    char ligne[3000];
    int i;
    rewind(file);   //Repointer le pointeur vers le debut du fichier
    for(i = 0;fgets(ligne,1500,file) != 0;i++)
    {
        if(i >= nombre - dernier)
        {   
            printf("%s",ligne);
        }
    }
}
int NombreDeLigne(FILE *file)
{
    int nombre = 0;
    char ligne[3000];
    while(fgets(ligne,1500,file) != 0)
    {
        nombre++;
    }
    return (nombre);
}
void bytes(char *argv2,FILE* file)
{
    int i = 0;
    int c;
    int nombre;
    int dernier;
    dernier = atoi(argv2);
    nombre = NombreDeCaractere(file);
    rewind(file);
    while(1)
    {
        c = fgetc(file);
        if(c == EOF)
        {
            break;
        }
        if(i >= nombre - dernier)
        {
            printf("%c",c);
        }
        i++;
    }
    fclose(file);
    exit(EXIT_SUCCESS);
}
int NombreDeCaractere(FILE *file)
{
    int nombre = 0;
    while(fgetc(file) != EOF)
    {
        nombre++;
    }
    return (nombre);
}