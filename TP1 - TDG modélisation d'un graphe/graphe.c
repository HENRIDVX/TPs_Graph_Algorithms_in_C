#include <stdio.h>
#include <stdlib.h>
//#include "graphe.h"
/*
void initialiser_graphe(int ordre, Graphe* graphe) {
    graphe->ordre = ordre;

    /// on alloue la matrice d'adjacence
    graphe->matriceAdjacence = (int**)malloc(ordre * sizeof(int*));
    ///on init une matrice d'adjacence pour ce cas précis, il n'était pas nécessaire de faire un malloc
    graphe->matriceAdjacence= [[0,1,0,0,0,0,1],
                                [0,0,0,0,0,0,1],
                                [0,0,0,0,0,0,1],
                                [0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0],
                                [0,0,0,0,0,0,0],
                                [0,0,1,1,1,1,0]];

    for (int i = 0; i < ordre; i++) {
        graphe->matriceAdjacence[i] = (int*)malloc(ordre * sizeof(int));
    }

    // Initialiser la matrice d'adjacence (par exemple, tous les éléments à zéro)
    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            graphe->matriceAdjacence[i][j] = 0;
        }
    }

    // Allouer le tableau dynamique de sommets
    graphe->sommets = (Sommet*)malloc(ordre * sizeof(Sommet));
}

void afficher_influences(const Graphe* graphe) {
    printf("Jeux d'influences :\n");

    for (int i = 0; i < graphe->ordre; i++) {
        for (int j = 0; j < graphe->ordre; j++) {
            if (graphe->matriceAdjacence[i][j] == 1) {
                printf("%s influence %s\n", graphe->sommets[i].nom, graphe->sommets[j].nom);
            }
        }
    }
}
