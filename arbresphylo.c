#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

void analyse_arbre(arbre racine, int* nb_esp, int* nb_carac){
    *nb_esp = 0;
    *nb_carac = 0;
    analyse_arbre_rec(racine, nb_esp, nb_carac);
}


void analyse_arbre_rec (arbre racine, int* nb_esp, int* nb_carac){
    if (racine != NULL){
        if ((racine->droit == NULL)&&(racine->gauche == NULL)) {
            *nb_esp += 1;
        }

        else if ((racine->droit != NULL)||(racine->gauche != NULL)) {
            analyse_arbre_rec(racine->droit, nb_esp, nb_carac);
            analyse_arbre_rec(racine->gauche, nb_esp, nb_carac);
            *nb_carac += 1;
        }
    }
}


/* ACTE II */
int rechercher_rec (arbre racine, char *espece, liste_t *seq){
    if (racine==NULL){
        return 1;
    }
    
    if (strcmp(racine->valeur,espece)==0) {
        printf("val\n");
        return 0;
    }

    int a = rechercher_rec(racine->gauche, espece, seq);
    int b = rechercher_rec(racine->droit, espece, seq);

    if (b==0){
        ajouter_tete(seq, racine->valeur);
        return 0;
    }

    if (a==0){
        return 0;
    }
    return 1;
}


void seq_print(liste_t* seq){
    assert(seq);
    
    cellule_t* cel = seq->tete;

    while (cel != NULL) {
        printf("%s ",cel->val);
        cel = cel->suivant;
    }
}


int rechercher_espece (arbre racine, char *espece, liste_t* seq){
    int x = rechercher_rec(racine, espece, seq);
    if (x==1){
        return 1;
    }
    seq_print(seq);
    return 0;
}


/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {

    return 1;
}

