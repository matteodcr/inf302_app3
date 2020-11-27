#ifndef _LISTES_H
#define _LISTES_H

typedef struct liste liste_t;
/* Type de liste à compléter selon votre besoin. */

typedef char* string;

struct cellule {
	string val;
	struct cellule* suivant;
};

typedef struct cellule cellule_t;

struct liste {
	cellule_t *tete;
};

typedef struct liste liste_t;

/* cree une nouvelle liste, initialement vide */
liste_t* init_liste_vide();

cellule_t *init_cellule_vide();

int ajouter_tete(liste_t* L, string c);
/* Ajouter une nouvelle cellule contenant c
 * en tête de la liste L.
 * Si l'ajout est réussi, le résultat est 0,
 * et 1 sinon (échec de l'ajout)
 */

cellule_t *pop(liste_t *L);

#endif /* _LISTES_H */

