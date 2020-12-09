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

int est_feuille(arbre a){
    return (a->gauche == NULL)&&(a->droit == NULL);
}

int avoir_cara(arbre* a, cellule_t* seq){
    return (seq != NULL) && (0 == strcmp((*a)->valeur, seq->val));
}

void parcours_arbre_rec(arbre* a, char *espece, cellule_t* seq){
    if (avoir_cara(a, seq)){
        ajouter_espece(&(*a)->droit, espece, seq->suivant);
        }
    else{
        ajouter_espece(&(*a)->gauche, espece, seq);
    }
}

void construire_arbre(noeud *noeud_courant, noeud *noeud_espece, cellule_t *cellule){
    while (cellule){
            noeud *noeud_suivant = nouveau_noeud();
            noeud_suivant->valeur = cellule->val;

            noeud_courant->droit = noeud_suivant;
            noeud_courant = noeud_suivant;
            cellule = cellule->suivant;
        }
    noeud_courant->droit = noeud_espece;
}

int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {

    if ((*a!=NULL)&&(!est_feuille(*a))){
        parcours_arbre_rec(a, espece, seq);
    }

    else{
        if (seq == NULL){
            fprintf(stderr, "Ne peut ajouter %s: possède les mêmes caractères que %s", espece, (*a)->valeur);
            return 1;  
        }
         //Initialisation du noeud "de départ"
        noeud *noeud_caractere = nouveau_noeud();
        noeud_caractere->valeur = seq->val;
        noeud_caractere->gauche = *a;
        
        //Initialisation du noeud "final"
        noeud *noeud_espece = nouveau_noeud();
        noeud_espece->valeur = espece;

        cellule_t *cellule = seq->suivant;
        noeud* noeud_courant = noeud_caractere;
        
        construire_arbre(noeud_courant, noeud_espece, cellule);
        
        *a = noeud_caractere;
    }
    return 0;
}



/* Besoin d'une pile*/

int afficher_carac(arbre a){

    liste_t *file = NULL;
    init_liste_vide(file);

    ajouter_en_queue(file, a->valeur);

    while (file->tete != NULL){

        cellule_t *m = pop(file);

        if (m == NULL){
            printf("Erreur pop\n");
            return 1;
        }

        if (a->gauche != NULL && (a->gauche->gauche != NULL || a->gauche->droit != NULL)){
            ajouter_en_queue(file, a->gauche->valeur);
            printf("%s", a->gauche->valeur);
        }

        if (a->droit != NULL && (a->droit->gauche != NULL || a->droit->droit != NULL)){
            ajouter_en_queue(file, a->droit->valeur);
            printf("%s", a->droit->valeur);
        }
    }
    return 0;
}