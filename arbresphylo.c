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

int non_feuille(arbre a){
    return (a->gauche != NULL || a->droit != NULL);
}

/* 
 * Construit une liste constituée chaque noeud de l'arbre et leur hauteur
 */
int retour_ligne(arbre a, liste_n* seq){
    if(a == NULL){return 1;}

    //Liste temporaire
    liste_n L;
    init_liste_vide_n(&L);

    cellule_n *cel = init_cellule_vide_n();
    arbre racine = nouveau_noeud();

    int h = 0;
    ajouter_en_queue_n(&L, a, h);

    while (L.tete != NULL){
        cel = pop_n(&L);
        racine = cel->nd;
        h = cel->hauteur + 1;

        ajouter_en_queue_n(seq, racine, h);

        if ((racine->gauche != NULL) && (non_feuille(racine->gauche))){
            ajouter_en_queue_n(&L, racine->gauche, h);
        }
        if ((racine->droit != NULL) && (non_feuille(racine->droit))){
            ajouter_en_queue_n(&L, racine->droit, h);

        }
    }
    return 0;
}
/* 
 * Construit une liste constituée de la cellule la plus à droite 
 * de chaque hauteur
 */

void tri_hauteur(liste_n *L){
    cellule_n* cell = L->tete;

    liste_n new_L;
    init_liste_vide_n(&new_L);

    while (cell){
        if ((cell->suivant == NULL)||(cell->hauteur != cell->suivant->hauteur)){
            ajouter_en_queue_n(&new_L, cell->nd, cell->hauteur);
        }
        cell = cell->suivant;
    }
    *L = new_L;
}

void afficher_par_niveau(arbre a, FILE *fsortie){
    if (a != NULL){
        // Liste "principale" parcourue en largeur
        liste_n file;
        init_liste_vide_n(&file);
        ajouter_en_queue_n(&file, a, 0);

        //Liste constituée des noeuds les plus à droite pour chaque hauteur
        liste_n seq;
        init_liste_vide_n(&seq);
        retour_ligne(a, &seq);
        tri_hauteur(&seq);
        
        while(file.tete != NULL){
            cellule_n *cel = pop_n(&file);
            arbre racine = cel->nd;

            fprintf(fsortie,"%s " ,racine->valeur);

            if((racine->gauche != NULL) && (non_feuille(racine->gauche))){
                ajouter_en_queue_n(&file, racine->gauche, 0);
            }

            if((racine->droit != NULL) && (non_feuille(racine->droit))){
                ajouter_en_queue_n(&file, racine->droit, 0);
            }

            if(strcmp(racine->valeur, seq.tete->nd->valeur)==0){
                fprintf(fsortie,"\n");
                seq.tete = seq.tete->suivant;
            }
        }
    }
} 