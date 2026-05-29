#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

typedef struct Graphe
{
    int ordre;
    char* nom_sommets;
    int** matrice;
    int source;
    int puit;
} Graphe;


#endif // HEADER_H_INCLUDED
