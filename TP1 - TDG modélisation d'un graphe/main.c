#include <stdio.h>
#include <stdlib.h>


#include "sommet.h"

typedef struct Graphe {
    int** matriceAdjacence; /// matrice d'adjacence
    int ordre; /// nb de sommets
    Sommet* sommets; /// tab dynamique des sommets
} Graphe;
/*
void initialiser_graphe(int ordre, Graphe* graphe);
void afficher_influences(const Graphe* graphe);
*/
void initialiser_graphe(int ordre, Graphe* graphe) {
    graphe->ordre = ordre;

    /// on alloue la matrice d'adjacence
    graphe->matriceAdjacence = (int**)malloc(ordre * sizeof(int*));
    ///on init une matrice d'adjacence pour ce cas précis, il n'était pas nécessaire de faire un malloc
    int matriceAdjacence[7][7] = {{0,1,0,0,0,0,1},
                                    {0,0,0,0,0,0,1},
                                    {0,0,0,0,0,0,1},
                                    {0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0},
                                    {0,0,0,0,0,0,0},
                                    {0,0,1,1,1,1,0}};
    printf("test\n"); ///on print un test pour verifier que toute l allocation s est bien passee
    for (int i = 0; i < ordre; i++) {
        graphe->matriceAdjacence[i] = (int*)malloc(ordre * sizeof(int));
    }
    char liste_nom[7][50] = { /// on cree une liste de chaine de caracteres pour pouvoir afficher les noms
        "Francois Stephan",
        "FabienneCoudray",
        "JuliennePalasi",
        "LouisM",
        "BoubakerD",
        "IlhemF",
        "JPS"
    };

/*
    for (int i = 0; i < 7; i++) {
        printf("%s\n", liste_nom[i]); /// on verifie qu ils s affichent tous
    }
*/

    /// initialiser la matrice d'adjacence du graphe
    for (int i = 0; i < ordre; i++) {
        for (int j = 0; j < ordre; j++) {
            graphe->matriceAdjacence[i][j] = matriceAdjacence[i][j];
        }
    }

    // Allouer le tableau dynamique de sommets
    graphe->sommets = (Sommet*)malloc(ordre * sizeof(Sommet));
}

void afficher_influences(const Graphe* graphe) {
    printf("Jeux d'influences :\n");
    char liste_nom[7][50] = {
        "Francois Stephan",
        "Fabienne Coudray",
        "Julienne Palasi",
        "LouisM",
        "BoubakerD",
        "IlhemF",
        "JPS"
    };

    for (int i = 0; i < graphe->ordre; i++) { /// on parcourt chaque ligne
        for (int j = 0; j < graphe->ordre; j++) { /// pour chaque ligne, on parcourt chaque colonne
            if (graphe->matriceAdjacence[i][j] == 1) {
                printf("\n%s influence %s\n", liste_nom[i], liste_nom[j]); /// on print qui influence qui
            }
        }
    }
}



int main() {
    Graphe* graphe = NULL; /// creation du graphe

    /// on alloue le graphe
    graphe = (Graphe*)malloc(sizeof(Graphe));

    if (graphe == NULL) {
        printf("Erreur : l'allocation de la mémoire pour le Graphe a échoué.\n");
        return 1; /// en cas d echec, on quitte le programme avec un code d'erreur
    }

    initialiser_graphe(7, graphe);
    printf("initialisation done\n");
    /// on appelle le sous-programme qui affiche les jeux d'influence des personnes
    afficher_influences(graphe);


    return 0;
}
