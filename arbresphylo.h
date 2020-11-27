#ifndef ARBRESPHYLO_H
#define ARBRESPHYLO_H

#include "listes.h"


/* Analyse un arbre: doit mettre à jour le nombre d'espèces et de 
 * caractéristiques.
 */
void analyse_arbre(arbre racine, int* nb_esp, int* nb_carac);
void analyse_arbre_rec(arbre racine, int* nb_esp, int* nb_carac);


void seq_print(liste_t* seq);
int rechercher_rec (arbre racine, char *espece, liste_t *seq);
/* Recherche une espèce dans l'arbre et remplit seq avec la séquence de ses 
 * caractéristiques.
 *
 * Doit retourner 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq);


int ajouter_espece (arbre* racine, char *espece, cellule_t* seq);


#endif
