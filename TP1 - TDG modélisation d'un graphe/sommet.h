#ifndef SOMMET_H
#define SOMMET_H

typedef struct Sommet {
    char* nom; /// nom du sommet (chaine dynamique)
    int numero; /// numero du sommet
} Sommet;

Sommet* creerSommet(const char* nom, int numero); /// prototype du sous-programme décrit dans l'enonce, implemente dans sommet.c

#endif // SOMMET_H
