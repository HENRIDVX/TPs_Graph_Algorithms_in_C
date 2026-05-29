#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED


// fifo.c//

File fileVide()
/*
La  fonction File fileVide cree une file vide
    IN :
    OUT :
*/
{
    File F;                                             // Initialisation d'une file
    F = (File)malloc(sizeof(struct _file));             // Creation d'une file
    if (F == NULL) printf("erreur allocation fileVide");// Si la pile est vide on affiche pile vide
    F->longueur = 0;                                    // La longueur de la file est mise a 0
    F->tete = F->queue = NULL;                          // Les valeurs de la tete et de la queue de la file sont mise a NULL
    return(F);                                          // Renvoie la file
}

int longueur(File F)
/*
La fonction longueur renvoie la longueur de la file
    IN : STRUCTURE File
    OUT : ENTIER longueur
*/
{
    if (F == NULL)printf("file existe pas - longueur");     // Si la pile est vide on affiche pile vide
    return(F->longueur);    // Renvoie la longueur de la file
}

void enfiler(File F, typage element)
/*
La fonction enfiler permet de remplir une file
    IN : STRUCTURE File
        typage element
    OUT :
*/
{
    Cellule cellule;        // Initialisation d'une cellule
    if (F == NULL) printf ("file existe pas - enfiler");    // Si la File est vide afficher que la file n'existe pas

    cellule = (Cellule)malloc(sizeof(struct _cellule));
    if (cellule == NULL) printf("erreur allocation memoire - enfiler");     // Si la Cellule est vide afficher qu'il y a une erreur d'allocation memoire
    cellule->element = element;     // Remplissage de la structure cellule (element)
    cellule->suivant = NULL;        // Remplissage de la structure cellule (cellule suivante)
    if (longueur(F) == 0)           // Si la longueur est egale a 0
    {
        F->tete = F->queue = cellule;   // La tete et la queue sont egale à la cellule
    }
    else                                // Sinon
    {
        F->queue->suivant = cellule;    // La  queue suivante est egale a la cellule
        F->queue = cellule;             // La queue est egale a cellule
    }
    ++(F->longueur);                    // On augmente de 1 la longueur de la file
}

typage tete(File F)
/*
La fonction typage tete verifie si la tete est nulle
    IN : STRUCTURE File
    OUT : INT element
*/
{
    if (F == NULL || longueur(F) == 0) printf(" File existe pas - tete");   // Si la File est NULL ou que la longueur est egale a 0 on affiche que la file n'existe pas
    return(F->tete->element);   // Renvoie la structure
}

void defiler(File F)
/*
La fonction defiler permet de defiler une file préalablement cree
    IN : STRUCTURE File
    OUT :
*/
{
    Cellule cellule;                // Initialisation d'une cellule
    if (F == NULL || longueur(F) == 0)printf("File existe pas - defiler");      // Si la file est nulle ou que sa longueur est de 0 ecrire qu'on ne peut pas la defiler
    cellule = F->tete;              // La cellule prend comme valeur celle de la tete de la file
    if (longueur(F) == 1)           // Si la longueur(verifié a l'aide de la fonction longueur) de la file est 1
    {
        F->tete = F->queue = NULL;  // La valeur de la tete et celle de la queue sont NULL
    }
    else                            // Sinon
    {
        F->tete = F->tete->suivant; // La valeur de la tete est egale a la valeur de la tete de la file suivante
    }
    --(F->longueur);                // On reduit la longueur de 1
    free(cellule);                  // On vide la cellule
}

typage defilement(File F)
/*
La fonction typage defilement permet de verifier si le defilement est possible
    IN : STRUCTURE File
    OUT : ENTIER element
*/
{
    Cellule cellule;                // Initialisation d'une cellule
    typage element;
    if (F == NULL || longueur(F) == 0) printf("File existe pas - defilement");  // Si la file est nulle ou que sa longueur est de 0 ecrire que la File n'existe pas
    cellule = F->tete;              // La cellule prend comme valeur celle de la tete de la File
    element = cellule->element;     // L'element prend  comme valeur celle de de l'element de la cellule
    if (longueur(F) == 1)           // Si la longueur de la file est de 1
    {
        F->tete = F->queue = NULL;  // La valeur de la tete et celle de la queue sont NULL
    }
    else                            // Sinon
    {
        F->tete = F->tete->suivant; // La valeur de la tete est egale a la valeur de la tete de la file suivante
    }
    free(cellule);                  // On vide la cellule
     --(F->longueur);               // On reduit la longueur de 1
    return(element);                // Renvoie element
}


File copie(File F)
/*
La foncton File copie permet de copier une File dans une autre File
    IN : STRUCUTRE File
    OUT :
*/
{
    File G, H;                              // Initialisation de deux files
    Cellule cellule;                        // Initialisation d'une cellule
    if (F == NULL) printf("erreur copie");  // Si la File F est vide on marque erreur copie
    H = fileVide();                         // On creer une file vide
    cellule = F->tete;                      // La cellule prend la valeur de la tete de la File
    while (cellule != NULL)                 // Tant que la cellule n'est pas vide
    {
        enfiler(H, cellule->element);       // On enfile un element de cellule dans H
        cellule = cellule->suivant;         // On passe a la cellule suivante
    }
    G = fileVide();                         // On creer une file vide
    cellule = H->tete;                      // La cellule prend la valeur de la tete de la File
    while (cellule != NULL)                 // Tant que la cellule n'est pas vide
    {
        enfiler(G, cellule->element);       // On enfile un element de cellule dans H
        cellule = cellule->suivant;         // On passe a la cellule suivante
    }
    return(G);                              // Renvoie la File copier
}


void ecrireFile(File F)
/*
La fonction ecrireFile permet de remplir une file
    IN : STRUCUTRE File
    OUT :
*/
{
    Cellule cellule;                            // Initialisation d'une cellule
    if (F == NULL) printf("erreur ecrireFile"); // Si la File F est vide on marque erreur ecrireFile
        cellule = F->tete;                      // La cellule prend la valeur de la tete de la File
    while (cellule != NULL)                     // Tant que la cellule n'est pas null
    {
        printf("%d ", cellule->element);        // Ecrire l'element de la cellule
        cellule = cellule->suivant;             // On passe a la cellule suivante
    }
    printf("\n");                               // On retourne a la ligne
}


#endif // FILE_H_INCLUDED
