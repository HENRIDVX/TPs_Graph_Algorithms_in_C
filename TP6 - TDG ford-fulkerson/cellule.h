#ifndef CELLULE_H_INCLUDED
#define CELLULE_H_INCLUDED


/*cellule.h*/
typedef int typage;

struct _cellule
{
    typage element;
    struct _cellule *suivant;
};

typedef struct _cellule* Cellule;


#endif // CELLULE_H_INCLUDED
