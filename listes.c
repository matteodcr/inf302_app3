#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

void init_liste_vide(liste_t* L) {
    L->tete = NULL;
}

void init_liste_vide_n(liste_n* L) {
    L->tete = NULL;
}

cellule_t* init_cellule_vide() {
    cellule_t *cel = malloc(sizeof(cellule_t));
    cel->suivant = NULL;
    return cel;
}

cellule_n* init_cellule_vide_n() {
    cellule_n *cel = malloc(sizeof(cellule_n));
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
        L->queue = L->tete;
    }
    else{
        cellule_t *cel = init_cellule_vide();
        cel->val = c;
        L->queue->suivant = cel;
        L->queue = L->queue->suivant;
    }
}

//Prend une liste de noeud en argument
cellule_n *pop_n(liste_n *L){
    cellule_n *ret = init_cellule_vide_n();
    if (L->tete != NULL){
        ret = L->tete;
        L->tete = L->tete->suivant; 
    }
    return ret;
}

int ajouter_tete_n(liste_n* L, noeud* n, int h) {
    if (L == NULL){
        return 1;
    }
    cellule_n *new_cel = init_cellule_vide_n();
    new_cel->nd = n;
    new_cel->hauteur = h;
    new_cel->suivant = L->tete;
    L->tete = new_cel;
    return 0;
}

//Prend une liste de noeud en argument

void ajouter_en_queue_n(liste_n *L, noeud *n, int h){

     if (L->tete == NULL){
        ajouter_tete_n(L,n,h);
        L->queue = L->tete;
    }
    else{
        cellule_n *cel = init_cellule_vide_n();
        cel->nd = n;
        cel->hauteur = h;
        L->queue->suivant = cel;
        L->queue = L->queue->suivant;
    }
}

void afficher_liste_n(liste_n *L){
    cellule_n *cell = L->tete;

    while (cell!=NULL){
        printf("===========\n");
        printf("NOEUD : %s \n", cell->nd->valeur);
        afficherParenthese(cell->nd);
        printf("\nHAUTEUR : %d\n", cell->hauteur);
        cell = cell->suivant;
    }
}
