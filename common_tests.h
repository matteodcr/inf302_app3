#ifndef COMMON_TEST_H
#define COMMON_TEST_H
#include "listes.h"
#include "arbres.h"
#include "arbresphylo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

size_t trimwhitespace(char *out, size_t len, const char *str);
int test_nb_esp_caracs(arbre a, char* filename, int expected_nb_esp, int expected_nb_carac);
int test_list_carac(int nb_attendues, char** attendues, liste_t trouvees);
#endif
