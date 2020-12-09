#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

void init_liste_vide(liste_t* L) {
    L->tete = NULL;
}

cellule_t* init_cellule_vide() {
    cellule_t *cel = malloc(sizeof(cellule_t));
    cel->suivant = NULL;
    return cel;
}


/* retourne 0 si OK, 1 sinon  */
int ajouter_tete(liste_t* L, string c) { 
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

void ajouter_en_queue(liste_t *L, string c){
    if (L->tete == NULL){
        ajouter_tete(L,c);
    }
    else if(L->queue == NULL){
        L->queue->val = c;
    }
    else{
        cellule_t *cel = init_cellule_vide();
        cel->val = c;
        L->queue->suivant = cel;
        L->queue = L->queue->suivant;
    }
}
