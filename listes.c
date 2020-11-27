#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"


liste_t* init_liste_vide() {
    liste_t *L = malloc(sizeof(liste_t));
    L->tete = NULL;
    return L;
}

cellule_t* init_cellule_vide() {
    cellule_t *cel = malloc(sizeof(cellule_t));
    cel->suivant = NULL;
    return cel;
}


/* retourne 0 si OK, 1 sinon  */
int ajouter_tete(liste_t* L, string c) { 
    printf("ajouter\n");
    if (L == NULL){
        return 1;
    }
    cellule_t *new_cel = init_cellule_vide();
    new_cel->val = c;
    new_cel->suivant = L->tete;
    L->tete = new_cel;
    return 0;
}

cellule_t *pop(liste_t *L){
    cellule_t *ret = init_cellule_vide();
    ret = L->tete;
    L->tete = L->tete->suivant;
    return ret;    
}


