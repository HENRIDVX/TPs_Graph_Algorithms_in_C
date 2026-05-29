#ifndef GRAPHE_H
#define GRAPHE_H
#include "sommet.h"

typedef struct Graphe {
    int** matriceAdjacence; /// matrice d'adjacence
    int ordre; /// nb de sommets
    Sommet* sommets; /// tab dynamique des sommets
} Graphe;

void initialiser_graphe(int ordre, Graphe* graphe);
void afficher_influences(const Graphe* graphe);

#endif // GRAPHE_H
