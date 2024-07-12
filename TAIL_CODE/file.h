#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int NombreDeLigne(FILE *file);
void afficher(FILE* file,int nombre,int dernier);
void option(int argc,char *argv[]);
void help();
void bytes(char *argv2,FILE* file);
int NombreDeCaractere(FILE *file);
void verbose(FILE *file,char argv[],int dernier);
void flux(char *argv,int dernier);
void quiet(FILE *file,int dernier);
void version();
