#include "Graphe.h"
#include "fifo.h"
#include "cellule.h"
#include "fifo.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// CODE DONNE NON MODIFIE COMMENTE /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void afficher_successeurs(pSommet * sommet, int num)
/*
La fonction afficher_successeurs affichage des successeurs du sommet num
    IN : ENTIER  num
         STRUCTURE pSommet
    OUT :
*/
{
    printf(" sommet %d :\n",num);   /// affiche le sommet sur lequel on se trouve
    pArc arc = sommet[num]->arc;    /// la structure arc prend tous les arcs connecté au sommet num
    while(arc != NULL)              /// tant qu'il reste des arcs sur le sommet
    {
        printf("%d ",arc->sommet);  /// affiche le sommet connecté au sommet num
        arc = arc->arc_suivant;     /// passe à l'arc suivant
    }
}


pSommet* CreerArete(pSommet* sommet,int s1,int s2)
/*
La fonction pSommet* CreerArete ajoute l'arête entre les sommets s1 et s2 du graphe
    IN : ENTIER s1
         ENTIER s2
         STRUCTURE pSommet
    OUT :
*/
{
    if(sommet[s1]->arc == NULL)
    {
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->arc_suivant = NULL;
        sommet[s1]->arc = Newarc;
        return sommet;
    }
    else
    {
        pArc temp = sommet[s1]->arc;
        while( !(temp->arc_suivant == NULL))
        {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->arc_suivant = NULL;
        if(temp->sommet > s2)
        {
            Newarc->arc_suivant = temp->arc_suivant;
            Newarc->sommet = temp->sommet;
            temp->sommet = s2;
            temp->arc_suivant = Newarc;
            return sommet;
        }
        temp->arc_suivant = Newarc;
        return sommet;
    }
}


Graphe* CreerGraphe(int ordre)
/*
    La fonction CreerGraphe cree le graphe
    IN : ENTIER ordre
*/
{
    Graphe * Newgraphe = (Graphe*)malloc(sizeof(Graphe));           /// creation d'un tableau de structure de la taille de Graphe
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));
    for(int i = 0 ; i < ordre ; i++)        /// repete autant de fois que l'ordre du sommet
    {
        Newgraphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));     /// remplissage de la structure Sommet pour chaque liaison
        Newgraphe->pSommet[i]->valeur = i;  /// attribution de la valeur a chaque sommet
        Newgraphe->pSommet[i]->arc = NULL;  /// mise a NULL de l'arc du sommet
    }
    return Newgraphe;   /// renvoi le tableau de structure Newgraphe
}


///La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
///Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs

Graphe * lire_graphe(char * nomFichier)
/*
La fonction Graphe * lire_graphe rempli la structure Graphe a l'aide du fichier txt
    IN : POINTEUR CARACTERE nomFichier
    OUT :
*/
{
    Graphe* graphe;                         /// "appel" de la structure graphe
    FILE * ifs = fopen(nomFichier,"r");     /// ouverture du fichier texte
    int taille, orientation, ordre, s1, s2; /// initialisation de toutes les varibles
    if (!ifs)                               /// si le fichier texte ne s'ouvre  pas
    {
        printf("Erreur de lecture fichier\n");  /// affichage de l'erreur d'ouverture
        exit(-1);                           /// on sort du programme
    }

    fscanf(ifs,"%d",&ordre);                /// stocke la valeur de l'ordre du graphe
    graphe = CreerGraphe(ordre);            /// créer le graphe d'ordre sommets
    fscanf(ifs,"%d",&taille);               /// stocke la valeur de la taille du graphe
    fscanf(ifs,"%d",&orientation);          /// stocke la valeur de l'orientation du graphe

    graphe->orientation = orientation;      /// remplissage de la structure graphe (orientation)
    graphe->ordre = ordre;                  /// remplissage de la structure graphe (ordre)

    for (int i = 0; i < taille ; ++i)       /// boucle qui permet la création des aretes du graphe
    {
        fscanf(ifs,"%d%d",&s1,&s2);         /// recuperation des 2 sommets entre une liason
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2);  /// remplissage de la structure graphe a l'aide de la fonction CreerArete
    if(!orientation)
        graphe->pSommet = CreerArete(graphe->pSommet, s2, s1);  /// remplissage de la structure graphe a l'aide de la fonction CreerArete
    }
    return graphe;  /// renvoie la structure graphe
}

void graphe_afficher(Graphe* graphe)
/*
La fonction graphe_afficher affiche le graphe avec les successeurs de chaque sommet dans la console
    IN : STRUCTURE graphe
    OUT :
*/
{
    printf("graphe\n");                     /// affiche graphe
    if(graphe->orientation)                 /// si l'orientation est 1
        printf("oriente\n");                /// afficher oriente
    else                                    /// sinon
        printf("non oriente\n");            /// afficher non orienté
    printf("ordre = %d\n",graphe->ordre);   /// afficher l'ordre du graphe
    printf("listes d'adjacence :\n");       /// afficher la liste d'adjacence
    for (int i = 0 ; i < graphe->ordre ; i++)       /// repete autant de fois qu'il y a de sommets
    {
        afficher_successeurs(graphe->pSommet, i);  /// appel de la fonction afficher_successeurs
        printf("\n");                       /// retour à la ligne
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// CODE PRIS SUR LE LIEN DU TP //////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// fifo.c//

File fileVide()
/*
La  fonction File fileVide cree une file vide
    IN :
    OUT :
*/
{
    File F;                                             /// initialisation d'une file
    F = (File)malloc(sizeof(struct _file));             /// creation d'une file
    if (F == NULL) printf("erreur allocation fileVide");/// si la pile est vide on affiche pile vide
    F->longueur = 0;                                    /// la longueur de la file est mise a 0
    F->tete = F->queue = NULL;                          /// les valeurs de la tete et de la queue de la file sont mise a NULL
    return(F);                                          /// renvoie la file
}

int longueur(File F)
/*
La fonction longueur renvoie la longueur de la file
    IN : STRUCTURE File
    OUT : ENTIER longueur
*/
{
    if (F == NULL)printf("file existe pas - longueur");     /// si la pile est vide on affiche pile vide
    return(F->longueur);    /// renvoie la longueur de la file
}

void enfiler(File F, typage element)
/*
La fonction enfiler permet de remplir une file
    IN : STRUCTURE File
        typage element
    OUT :
*/
{
    Cellule cellule;        /// initialisation d'une cellule
    if (F == NULL) printf ("file existe pas - enfiler");    /// Si la File est vide afficher que la file n'existe pas

    cellule = (Cellule)malloc(sizeof(struct _cellule));
    if (cellule == NULL) printf("erreur allocation memoire - enfiler");     /// Si la Cellule est vide afficher qu'il y a une erreur d'allocation memoire
    cellule->element = element;     /// Remplissage de la structure cellule (element)
    cellule->suivant = NULL;        /// Remplissage de la structure cellule (cellule suivante)
    if (longueur(F) == 0)           /// Si la longueur est egale a 0
    {
        F->tete = F->queue = cellule;   /// La tete et la queue sont egale à la cellule
    }
    else                                /// Sinon
    {
        F->queue->suivant = cellule;    /// La  queue suivante est egale a la cellule
        F->queue = cellule;             /// La queue est egale a cellule
    }
    ++(F->longueur);                    /// On augmente de 1 la longueur de la file
}

typage tete(File F)
/*
La fonction typage tete verifie si la tete est nulle
    IN : STRUCTURE File
    OUT : INT element
*/
{
    if (F == NULL || longueur(F) == 0) printf(" File existe pas - tete");   /// Si la File est NULL ou que la longueur est egale a 0 on affiche que la file n'existe pas
    return(F->tete->element);   /// Renvoie la structure
}

void defiler(File F)
/*
La fonction defiler permet de defiler une file préalablement cree
    IN : STRUCTURE File
    OUT :
*/
{
    Cellule cellule;                /// Initialisation d'une cellule
    if (F == NULL || longueur(F) == 0)printf("File existe pas - defiler");      /// Si la file est nulle ou que sa longueur est de 0 ecrire qu'on ne peut pas la defiler
    cellule = F->tete;              /// La cellule prend comme valeur celle de la tete de la file
    if (longueur(F) == 1)           /// Si la longueur(verifié a l'aide de la fonction longueur) de la file est 1
    {
        F->tete = F->queue = NULL;  /// La valeur de la tete et celle de la queue sont NULL
    }
    else                            /// Sinon
    {
        F->tete = F->tete->suivant; /// La valeur de la tete est egale a la valeur de la tete de la file suivante
    }
    --(F->longueur);                /// On reduit la longueur de 1
    free(cellule);                  /// On vide la cellule
}

typage defilement(File F)
/*
La fonction typage defilement permet de verifier si le defilement est possible
    IN : STRUCTURE File
    OUT : ENTIER element
*/
{
    Cellule cellule;                /// Initialisation d'une cellule
    typage element;
    if (F == NULL || longueur(F) == 0) printf("File existe pas - defilement");  /// Si la file est nulle ou que sa longueur est de 0 ecrire que la File n'existe pas
    cellule = F->tete;              /// La cellule prend comme valeur celle de la tete de la File
    element = cellule->element;     /// L'element prend  comme valeur celle de de l'element de la cellule
    if (longueur(F) == 1)           /// Si la longueur de la file est de 1
    {
        F->tete = F->queue = NULL;  /// La valeur de la tete et celle de la queue sont NULL
    }
    else                            /// Sinon
    {
        F->tete = F->tete->suivant; /// La valeur de la tete est egale a la valeur de la tete de la file suivante
    }
    free(cellule);                  /// On vide la cellule
     --(F->longueur);               /// On reduit la longueur de 1
    return(element);                /// Renvoie element
}


File copie(File F)
/*
La foncton File copie permet de copier une File dans une autre File
    IN : STRUCUTRE File
    OUT :
*/
{
    File G, H;                              /// Initialisation de deux files
    Cellule cellule;                        /// Initialisation d'une cellule
    if (F == NULL) printf("erreur copie");  /// Si la File F est vide on marque erreur copie
    H = fileVide();                         /// On creer une file vide
    cellule = F->tete;                      /// La cellule prend la valeur de la tete de la File
    while (cellule != NULL)                 /// Tant que la cellule n'est pas vide
    {
        enfiler(H, cellule->element);       /// On enfile un element de cellule dans H
        cellule = cellule->suivant;         /// On passe a la cellule suivante
    }
    G = fileVide();                         /// On creer une file vide
    cellule = H->tete;                      /// La cellule prend la valeur de la tete de la File
    while (cellule != NULL)                 /// Tant que la cellule n'est pas vide
    {
        enfiler(G, cellule->element);       /// On enfile un element de cellule dans H
        cellule = cellule->suivant;         /// On passe a la cellule suivante
    }
    return(G);                              /// Renvoie la File copier
}


void ecrireFile(File F)
/*
La fonction ecrireFile permet de remplir une file
    IN : STRUCUTRE File
    OUT :
*/
{
    Cellule cellule;                            /// Initialisation d'une cellule
    if (F == NULL) printf("erreur ecrireFile"); /// Si la File F est vide on marque erreur ecrireFile
        cellule = F->tete;                      /// La cellule prend la valeur de la tete de la File
    while (cellule != NULL)                     /// Tant que la cellule n'est pas null
    {
        printf("%d ", cellule->element);        /// Ecrire l'element de la cellule
        cellule = cellule->suivant;             /// On passe a la cellule suivante
    }
    printf("\n");                               /// On retourne a la ligne
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// METHODE COMMUNE AU BFS ET AU DFS ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

///cette methode permet de creer l'affichage demande

int print_antecedent(int* antecedent)
/*
La fonction print_antecedent permet d'afficher l'antecedent
    IN  : ENTIER antecendent
    OUT : ENTIER 0
*/
{
    for (int i = 0 ; i < 15 ; i++)          /// Repete 15 fois
    {
        int j = i;                          /// La variable j prend comme valeur i
        printf("%d", j);                    /// Affiche j
        while(antecedent[j] != -1)          /// Tant que l'antecedent j est different de -1
        {
            printf(" <-- %d", antecedent[j]);   /// On affiche  l'antecedent
            j = antecedent[j];              /// j prend comme valeur l'antecedent de j
        }
        printf("\n");                       /// Retourne a la ligne
    }
    return 0;                               /// Renvoie 0
}




//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////BFS///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////




/// programme BFS inspiré de l'algo donné via le lien
/// les lignes en français de l'algo sont en commentaires à cote de chaque ligne

int BFS(Graphe *G, Sommet *s)
/*
La fonction BFS cherche le BFS d'un graphe
    IN : STRUCTURE Graphe
         STRUCTURE Sommet
    OUT : ENTIER 0
*/
{
    File maFile = fileVide();   /// Initialisation d'une file vide
    enfiler(maFile,s->valeur);  /// Enfiler la file

    int marque[G->ordre];       /// Initialisation de la variable marque
    int antecedent[G->ordre];   /// Initialisation de la variable antecedent
    for(int i = 0 ; i < G->ordre ; i++)     /// Repete n fois en fonction de l'ordre du sommet
    {
        marque[i] = 0;          /// Met l'element i du tableau marque a 0
        antecedent[i] = -1;     /// Met l'element i du tableau antecedent a -1
    }
    marque[s->valeur] = 1;      /// Met l'element valeur de s de marque a 1

    while( maFile->longueur != 0)       /// Tant que la fiel n'est pas vide
    {
        int x = maFile->tete->element;  /// Met l'element de la tete de la file dans x
        defiler(maFile);                /// Defile la file
        marque[x] = 1;                  /// Met l'element x du tableau marque a 1
        pArc arc_suivant = G->pSommet[x]->arc;
        while (arc_suivant!=NULL)       /// Tant que l'arc suivant n'est pas null
        {
            int z = arc_suivant->sommet;    /// Met le sommet de l'arc suivant dans z
            if(marque[z] == 0)              /// Si l'element z de marque est egale a 0
            {
                enfiler(maFile,z);          /// Enfile la file
                marque[z] = 1;              /// Met l'element z de marque a 1
                antecedent[z] = x;          /// Met l'element z de antecedent a x
            }
            arc_suivant = arc_suivant->arc_suivant;
        }
    }
    int success = print_antecedent(antecedent);     /// Affichage du BFS
    return 0;       /// Retourne 0
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////DFS////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void recursive_DFS(Graphe *g, Sommet *s, int* marque, int* antecedent)
/*
La fonction recursive_DFS permet de calculer recursivement le DFS
    IN : STRUCTURE Graphe
         STRUCTURE Sommet
         ENTIER marque
         ENTIER antecendent
    OUT :
*/
{
    pArc arc = s->arc;
    int old_sommet = s->valeur;                 /// Initialisation de l'encien sommet a sa nouvelle valeur
    while (arc != NULL)                         /// Tant que l'arc n'est pas null
    {
        int new_sommet =  arc->sommet;          /// Initialisation d'un nouveau sommet qui prend comme valeur le sommet de l'arc
        if (marque[new_sommet] == 0)            /// Si la marque d'indice du nouveau sommet est egale à 0
        {
            marque[new_sommet] = 1;             /// Cette marque passe à 1
            antecedent[new_sommet] = old_sommet;/// Le nouveau sommet devient l'ancien
            recursive_DFS(g, g->pSommet[new_sommet], marque, antecedent);   /// Appel de la fonction recursive_DFS
        }
    arc = arc->arc_suivant;                     /// L'arc prend la valeur de l'arc suivant
    }
}

int DFS(Graphe *G, Sommet *s)
/*
La fonction DFS permet d'effectuer le DFS
    IN : STRUCTURE Graphe
         STRUCUTRE Sommet
    OUT
*/
{
    int marque[G->ordre];                       /// Initialisation du tableau marque
    int antecedent[G->ordre];                   /// Initialisation du tableau antecendent
    for(int i = 0 ; i < G->ordre ; i++)         /// Boucle repetant autant de fois que l'ordre de G
    {
        marque[i] = 0;                          /// Met marque de i à 0
        antecedent[i] = -1;                     /// Met l'antecedent de i à -1
    }
    marque[s->valeur] = 1;                      /// Met marque de la valeur a 1
    recursive_DFS(G, s, marque, antecedent);    /// Appel de la fonction recursive_DFS
    int success = print_antecedent(antecedent); /// Initialise success avec l'affichage
    return 0;                                   /// Renvoie 0
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////RECHERCHE DES COMPOSANTES CONNEXES/////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///EXPLICATION DE LA METHODE
/// on cree un tab de 15 (rpz les sommets)
/// chaque element de ce tableau est initialisé à 0
/// on cree un int nbcompo
/// son role est de compter le nb de compo connexes
/// puis boucle de 0 à 15
/// si tab[i] est different de zero alors l element a deja ete decouvert
/// si tab[i]=0 alors le sommet n'a pas ete decouvert
/// on lance donc un DFS sur ce sommet
/// on marque à nbcompo ce sommet et tous les sommets découverts
/// on va modifier le programme du BFS pour récupérer les éléments reliés au sommet initial
/// on ajoute 1 au int nbcompo et continue
///AU FINAL
/// on a le nb de composantes_connexes : int -1
/// et un tab avec pour chaque entier le numéro de la composante connexe à laquelle il appartient


int BFS_modifie(Graphe *G, int sommet_init, int marque[])
{
    Sommet *s = G->pSommet[sommet_init];
    File maFile = fileVide();
    enfiler(maFile,s->valeur);
    int antecedent[G->ordre];
    for(int i=0;i<G->ordre;i++) {
        marque[i]=0;
        antecedent[i]=-1;
    };
    marque[s->valeur] = 1;
    while( maFile->longueur!=0)
    {
        int x = maFile->tete->element;
        defiler(maFile);
        marque[x] = 1;
        pArc arc_suivant = G->pSommet[x]->arc;
        while (arc_suivant!=NULL)
        {
            int z = arc_suivant->sommet;
            if(marque[z]==0) {enfiler(maFile,z); marque[z]=1;antecedent[z] = x;}
            arc_suivant = arc_suivant->arc_suivant;
        }
    }
    //int success = print_antecedent(antecedent);
    return 0;
}

void recherche_compo_connexes(Graphe *g, Sommet *s, int * tab)
{
    int nbcompo = 1;
    int marque[g->ordre]; /// marque est un tableau deja utilise pour le BFS et le DFS
    /// ici on le déclare avant d'appeler le BFS pour récupérer post BFS les infos modifiées à l intérieur

    for(int i=0;i<15;i++)
    {
        if(tab[i]==0) /// on verifie que le sommet sur lequel on est n'a pas été exploré
        {
            BFS_modifie(g,i,marque); /// on lance un BFS
            /*printf("exploration sommet %d \n", i);
            for (int ii = 0; ii<15; ii++) printf("%d,", marque[ii]);
            printf("\n");
            for (int ii = 0; ii<15; ii++) printf("%d,", tab[ii]);
            printf("\n");*/
            for(int j=0;j<=g->ordre;j++)
            {
                if (marque[j]!=0) /// quel sommet a été marqué pendant ce tour
                {
                    tab[j]=nbcompo;
                }
            }
            nbcompo=nbcompo+1; /// ATTENTION : voir ligne 528
            //for (int ii = 0; ii<15; ii++) printf("%d,", tab[ii]);
            //printf("\n");
        } else {
            ///printf("ignore le sommet %d car deja attribue a une composante connexe \n", i);
        }
    }
    //printf("NOMBRE COMPO VAUT %d \n",nbcompo-1); /// car comme on ajoute 1 a la fin de chaque boucle, il prend un +
    for(int k=1;k<=nbcompo-1;k++)
    {
        printf("composante connexe %d :",k);
        for(int i=0;i<=g->ordre;i++)
        {
            //printf("composante connexe %d :",&k);
            if (tab[i]==k)
            {
                printf(" %d",i);
            }
        }
        printf("\n");
    }
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// CYCLES EULERIENS ////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// copie de recherche_compo_connexes mais sans les print pour soigner l affichage
/// avec nbcompo_total le nb de compo connexe qu on veut recuperer pour la recherche des chaines cycles euleriens
void recherche_compo_connexes_sans_print(Graphe *g, Sommet *s, int * tab, int * nbcompo_total)
{
    int nbcompo = 1;
    int marque[g->ordre];

    for(int i=0;i<g->ordre+1;i++)
    {
        if(tab[i]==0)
        {
            BFS_modifie(g,i,marque);
            for(int j=0;j<=g->ordre;j++)
            {
                if (marque[j]!=0)
                {
                    tab[j]=nbcompo;
                }
            }
            nbcompo=nbcompo+1;
        }
    }
    *nbcompo_total= nbcompo-1;
}

/// inspire de afficher_successeurs
/// sert a trouver cb de sommets sont adjacents au sommet étudié
void trouver_successeurs(pSommet * sommet, int * marque, int num)
{
    for(int i=0; i<15; i++) marque[i] = 0;
    pArc arc = sommet[num]->arc;    /// La structure arc prend tous les arcs connecté au sommet num
    while(arc != NULL)              /// Tant qu'il reste des arcs sur le sommet
    {
        marque[arc->sommet] = 1;
        arc = arc->arc_suivant;     /// Passe à l'arc suivant
    }
}


void recherche_eulerien(Graphe * g, Sommet *s, int * tab, int nb_compoconnexe)
{
    //printf("Nb de compo connexe = %d \n", nb_compoconnexe); /// on verifie que le nb de composantes connexes correspond
    int marque[15] = {0};
    for (int i=1; i<nb_compoconnexe+1; i++){ /// on prend les composantes connexes une par une pour traiter
        int nb_sommets_impairs = 0; /// sert a compter le nb de sommets impairs
        int tous_les_sommets_sont_pairs = 0; /// utilise comme un booleen == n'est plus egal a 0 si on trouve un sommet avec un nb impair d'arretes
        for (int j=0; j<15; j++){ /// on recup les successeurs
            if (tab[j] == i){
                trouver_successeurs(g->pSommet, marque, j);
                int s=0;
                for(int k=0; k<15; k++) s=s+marque[k]; /// on compte le nb d arretes
                if (s%2!=0) { /// on test si ce nb est pair ou impair "SI IL EST IMPAIR ALORS ...
                    tous_les_sommets_sont_pairs=1; /// la condition du cycle eulerien n est plus vraie
                    nb_sommets_impairs =nb_sommets_impairs + 1; /// on ajoute 1 au compteur de sommets ayant un nb impair d arretes
                }
            //printf("le sommet %d a %d voisins \n", j, s);
            }
        }
        if (tous_les_sommets_sont_pairs==0) {printf("la composant connexe %d est un cycle eulerien \n", i);}
        else if ((nb_sommets_impairs == 0) || (nb_sommets_impairs==2)){printf("la composant connexe %d est une chaine eulerienne \n", i);}
        else {printf("la composant connexe %d n est ni un cycle eulerien ni une chaine eulerienne \n", i);}
    }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////MAIN//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(int argc, char *argv[])
{
    Graphe * g=NULL;
    int choixfichier;
    choixfichier=0;
    printf("Quel graphe souhaitez-vous traiter ?\n "
           "1. le graphe oriente donne dans l enonce\n"
           "2. le graphe non oriente donne dans l enonce\n"
           "3. un graphe issu de nous\n");
    scanf("%d",&choixfichier);
    if(choixfichier==1)
        g=lire_graphe("oriente.txt");

    else if (choixfichier==2)
        g= lire_graphe("pas_oriente.txt");

    else if (choixfichier==3)
        g=lire_graphe("graphe_perso_TP2.txt");


    /// lecture du fichier txt contenant toutes les informations du graphes
    /// afficher le graphe
    graphe_afficher(g);     /// on appelle de la fonction graphe_afficher pour afficher le graphe dans la console
    char choix;             /// init de la variable choix
    char selection[30];     /// init de la variable selection
    int asksommet=0;          /// init de la variable asksommet
    int nb_compoconnexe;    /// entier utile pour la recherche de chaines et cycles euleriens à partir de la recherche de compo connexes
    Sommet *s = g->pSommet[asksommet];
    int tab[15]={0}; /// on cree un tableau de 15 entiers tous à zéro = aucun sommet n'a été parcouru
    do                      // Faire tant que
    {
        choix = 0 ;         /// Variable choix mise à 0
        do                  // Faire tant que
        {
            printf("\nMenu  \n"
                   "Entrer 1 pour selectionner BFS \n"
                   "2 pour selectionner DFS \n"
                   "3 pour rechercher les compo connexes \n"
                   "4 pour rechercher les chaines / cycles eulerien\n"
                   "5 pour fermer le programme \n");    /// Affichage du menu
            scanf("%s", &selection);                    /// Recupération de la saisie de l'utilisateur
            /// La fonction atoi() convertit une chaîne de caractères en un entier
            if ( (atoi(selection) >= 1) && (atoi(selection) <= 5))      /// Si la valeur saisie est convertissable en entier entre 1 et 5
            {
                choix = atoi(selection);                /// La variable choix prend cette valeur
            }
        }
        while((choix < 1) && (choix > 5));              /// Premiere boucle qui repete tant que le choix du menu n'est pas correct

        if(choix == 1)      /// Si le choix est 1 (l'utilisateur choisit d'afficher le BFS)
        {
            printf("Veuillez entrer un numero pour le sommet de depart \n");       /// Demande à l'utilisateur de choisir le sommet de depart
            scanf("%d",&asksommet);                                     /// Stocke le sommet de depart dans asksommet
            if((asksommet < 0) || (asksommet > g->ordre))                     /// Si la condition n'est pas respecter
            {
            while((asksommet < 0) || (asksommet > g->ordre))                  /// On repete tant que la saisie n'est pas bonne
                {
                    printf("Veuillez respecter les conditions de saisie et prendre un numéro de sommet existant\n");  /// Demande à l'utilisateur de choisir le sommet de depart
                    scanf("%d",&asksommet);                             /// Stocke le sommet de depart dans asksommet
                }
            }
            Sommet *s = g->pSommet[asksommet];
            printf("parcours BFS a partir du sommet %d\n",asksommet);   /// Affichage de la methode en cours d'utilisation
            BFS(g, s);      /// Appel de la fonction BFS

        }
        if(choix == 2)      /// Si le choix est 2 (l'utilisateur choisit d'afficher le DFS)
        {
            printf("Veuillez entrer le numero de sommet de depart souhaite \n");       /// Demande à l'utilisateur de choisir le sommet de depart
            scanf("%d",&asksommet);                                     /// Stocke le sommet de depart dans asksommet
            if((asksommet < 0) || (asksommet > g->ordre))                     /// Si la condition n'est pas respecter
            {
            while((asksommet < 0) || (asksommet > g->ordre))                  /// On repete tant que la saisie n est pas bonne
                {
                    printf("Veuillez respecter les conditions de saisie et prendre un sommet existant\n");  /// Demande à l'utilisateur de choisir le sommet de depart
                    scanf("%d",&asksommet);                             /// Stocke le sommet de depart dans asksommet
                }
            }
            Sommet *s = g->pSommet[asksommet];
            printf("\n\n parcours DFS a partir du sommet %d\n",asksommet);  /// Affichage de la methode en cours d'utilisation
            DFS(g,s);   /// Appel de la fonction DFS

        }
        if (choix == 3)
        {
            recherche_compo_connexes(g, s, tab);
        }
        if (choix == 4)
        {
            recherche_compo_connexes_sans_print(g, s, tab, &nb_compoconnexe);
            recherche_eulerien(g, s, tab, nb_compoconnexe);
            /// Truc eulerien
        }

    }while (choix != 5);
    printf("SOURCES  :\n http://morissardjerome.free.fr/langageC/graphe2.html \n ");

    return 0;
}

