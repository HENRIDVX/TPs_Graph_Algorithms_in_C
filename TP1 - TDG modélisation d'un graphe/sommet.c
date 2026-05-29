#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sommet.h"

Sommet* creerSommet(const char* nom, int numero) {
    Sommet* nouveauSommet = (Sommet*)malloc(sizeof(Sommet));

    if (nouveauSommet != NULL) {
        /// allocution pour le nom et copier le contenu
        nouveauSommet->nom = (char*)malloc(strlen(nom) + 1);

        if (nouveauSommet->nom != NULL) {
            strcpy(nouveauSommet->nom, nom);
            nouveauSommet->numero = numero;
            return nouveauSommet;
        } else {
            /// si fail de l'allocation pour le nom
            free(nouveauSommet);
            return NULL;
        }
    } else {
        /// si fail de l'allocation pour le sommet
        return NULL;
    }
}
