#ifndef _LISTES_H
#define _LISTES_H
#include "arbres.h"

typedef struct liste liste_t;
/* Type de liste à compléter selon votre besoin. */

typedef char* string;

struct cellule {
	string val;
	struct cellule* suivant;
};
typedef struct cellule_noeud cellule_n;

struct cellule_noeud {
	noeud* nd;
	int hauteur; 
	struct cellule_noeud* suivant;
};
typedef struct cellule cellule_t;

struct liste_noeud {
	cellule_n *tete;
	cellule_n *queue;
};

struct liste {
	cellule_t *tete;
	cellule_t *queue;
};

typedef struct liste liste_t;
typedef struct liste_noeud liste_n;


/* cree une nouvelle liste, initialement vide */
void init_liste_vide(liste_t* L);
void init_liste_vide_n(liste_n* L);

cellule_t *init_cellule_vide();
cellule_n *init_cellule_vide_n();


int ajouter_tete(liste_t* L, string c);
/* Ajouter une nouvelle cellule contenant c
 * en tête de la liste L.
 * Si l'ajout est réussi, le résultat est 0,
 * et 1 sinon (échec de l'ajout)
 */
void ajouter_en_queue(liste_t *L, string c);
cellule_t *pop(liste_t *L);

int ajouter_tete_n(liste_n* L, noeud* n, int h);
void ajouter_en_queue_n(liste_n *L, noeud *n, int h);
cellule_n *pop_n(liste_n *L);

void afficher_liste_n(liste_n *L);

#endif /* _LISTES_H */


