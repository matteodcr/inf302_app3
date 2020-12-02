#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"


int creer_dot_rec(arbre a, FILE *f){

    if (a == NULL){
        fprintf(f, "}");
        return 0;
    }
    
    if (a->gauche != NULL){
        fprintf(f, "%s -> %s [label = \"non\"]", a->valeur, a->gauche->valeur);
        fprintf(f,"\n");
        creer_dot_rec(a->gauche, f);
    }
    if (a->droit != NULL){
        fprintf(f, "%s", a->valeur);
        fprintf(f, " -> ");
        fprintf(f, "%s", a->droit->valeur);
        fprintf(f, " [label = \"oui\"]\n");
        fprintf(f,"\n");
        creer_dot_rec(a->droit, f);
    }
    
    return 1;
}

int main(int argc, char* argv[]){
    if (argc != 3){
        printf("Nombre d'arguments souhaités : 2");
        return 1;
    }

    char *nom_fichier = argv[1];
    char *sortie = argv[2];
    
    FILE *f = fopen(nom_fichier, "r");
    arbre a = lire_arbre(f);
    fclose(f);

    FILE *out = fopen(sortie, "w");
    fprintf(out, "digraph arbre{\n");
    
    if (a->gauche == NULL && a->droit == NULL){
        fprintf(out, "%s", a->valeur);
        fprintf(out, "}");
        return 0;
    }
    
    creer_dot_rec(a, out);
    fprintf(out, "}");
    fclose(out);
return 0;    
}

