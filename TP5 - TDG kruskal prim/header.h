#include <stdio.h>
#include <stdlib.h>


struct Arc                          // Structure d'un arc
{
    int sommet_depart;                    // numéro de sommet d'un arc adjacent au sommet initial
    int sommet_arrivee;
    int valeur;
    struct Arc* arc_suivant;
    int poids;
};
typedef struct Arc* pArc;           // Alias de pointeur sur un Arc


struct Sommet                       // Structure d'un sommet
{
    struct Arc* arc;
    int valeur;
    char couleur;
};
typedef struct Sommet* pSommet;     // Alias de pointeur sur un Sommet



typedef struct Graphe               // Alias d'un Graphe
{
    int taille;
    int orientation;
    int ordre;
    int n_arc;
    pSommet* pSommet;
    pArc* pArc;                     // On ajoute un pArc car il est demandé de travailler avec une représentation par liste d'aretes
} Graphe;
