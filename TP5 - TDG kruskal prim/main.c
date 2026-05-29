#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

void afficher_successeurs(pSommet * sommet, int num)
/*
La fonction afficher_successeurs affichage des successeurs du sommet num
    IN : ENTIER  num
         STRUCTURE pSommet
    OUT :
*/
{
    printf(" sommet %d :\n",num);   // Affiche le sommet sur lequel on se trouve
    pArc arc = sommet[num]->arc;    // La structure arc prend tous les arcs connecté au sommet num
    while(arc != NULL)              // Tant qu'il reste des arcs sur le sommet
    {
        printf("%d ",arc->sommet_arrivee);  // Affiche le sommet connecté au sommet num
        arc = arc->arc_suivant;     // Passe à l'arc suivant
    }
}


pSommet* CreerArete(pSommet* sommet,int s1,int s2, int poids)
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
        Newarc->sommet_depart = s1;
        Newarc->sommet_arrivee= s2;
        Newarc->arc_suivant = NULL;
        Newarc->poids=poids;
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
        Newarc->sommet_depart= s1;
        Newarc->sommet_arrivee = s2;
        Newarc->poids=poids;
        Newarc->arc_suivant = NULL;

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
    Graphe * Newgraphe = (Graphe*)malloc(sizeof(Graphe));           // Creation d'un tableau de structure de la taille de Graphe
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));
    for(int i = 0 ; i < ordre ; i++)        // Repete autant de fois que l'ordre du sommet
    {
        Newgraphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));     // Remplissage de la structure Sommet pour chaque liaison
        Newgraphe->pSommet[i]->valeur = i;  // Attribution de la valeur a chaque sommet
        Newgraphe->pSommet[i]->arc = NULL;  // Mise a NULL de l'arc du sommet
    }
    return Newgraphe;   // Renvoi le tableau de structure Newgraphe
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
    struct Arc* Arc;
    Graphe* graphe;                       // "Appel" de la structure graphe
    FILE * ifs = fopen(nomFichier,"r");     // Ouverture du fichier texte
    int taille, orientation, ordre, s1, s2, L; // Initialisation de toutes les varibles
    if (!ifs)                               // Si le fichier texte ne s'ouvre  pas
    {
        printf("Erreur de lecture fichier\n");  // Affichage de l'erreur d'ouverture
        exit(-1);                           // On sort du programme
    }

    fscanf(ifs,"%d",&ordre);                // Stocke la valeur de l'ordre du graphe
    graphe = CreerGraphe(ordre);            // créer le graphe d'ordre sommets
    fscanf(ifs,"%d",&taille);               // Stocke la valeur de la taille du graphe
    fscanf(ifs,"%d",&orientation);          // Stocke la valeur de l'orientation du graphe

    graphe->orientation = orientation;      // Remplissage de la structure graphe (orientation)
    graphe->ordre = ordre;                  // Remplissage de la structure graphe (ordre)
    for (int i = 0; i < taille ; ++i)       // Boucle qui permet la création des aretes du graphe
    {
        fscanf(ifs,"%d%d",&s1,&s2);         // Recuperation des 2 sommets entre une liason
        fscanf(ifs, "%d", &L);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, L);  // Remplissage de la structure graphe a l'aide de la fonction CreerArete

        if(!orientation)
            graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, L);  // Remplissage de la structure graphe a l'aide de la fonction CreerArete
    }
    //Adaptattion demandee
    // suit le meme schema que pour les sommets
    int i_arc=0;
    for(int j=0; j<graphe->ordre; j++)
    {
        pArc arc_suivant = graphe->pSommet[j]->arc;
        while (arc_suivant != NULL) {
                arc_suivant->valeur = i_arc;
                arc_suivant = arc_suivant->arc_suivant;
                i_arc=i_arc+1;
        }
    }
    graphe->n_arc = i_arc;
    graphe->pArc = (pArc*)malloc(graphe->n_arc*sizeof(pArc));
    for(int j=0; j<graphe->ordre; j++)
    {
        pArc arc_suivant = graphe->pSommet[j]->arc;
        while (arc_suivant != NULL) {
                graphe->pArc[arc_suivant->valeur] = arc_suivant;
                arc_suivant = arc_suivant->arc_suivant;
        }
    }
    return graphe;  // Renvoie la structure graphe
}

void graphe_afficher(Graphe* graphe)
/*
La fonction graphe_afficher affiche le graphe avec les successeurs de chaque sommet dans la console
    IN : STRUCTURE graphe
    OUT :
*/
{
    printf("graphe\n");                     // Affiche graphe
    if(graphe->orientation)                 // Si l'orientation est 1
        printf("oriente\n");                // Afficher oriente
    else                                    // Sinon
        printf("non oriente\n");            // Afficher non orienté
    printf("ordre = %d\n",graphe->ordre);   // Afficher l'ordre du graphe
    printf("listes d'adjacence :\n");       // Afficher la liste d'adjacence
    for (int i = 0 ; i < graphe->ordre ; i++)       // Repete autant de fois qu'il y a de sommets
    {
        afficher_successeurs(graphe->pSommet, i);  // Appel de la fonction afficher_successeurs
        printf("\n");                       // Retour à la ligne
    }
    int poids_total=0;
    for (int i=0; i <graphe->n_arc; i++)
    {
        printf("arete %d - %d, poids %d \n",graphe->pArc[i]->sommet_depart, graphe->pArc[i]->sommet_arrivee, graphe->pArc[i]->poids);
        poids_total=poids_total+graphe->pArc[i]->poids;
    }
    printf("le poids total est : %d \n",poids_total);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// KRUSKAL ////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



void kruskal(Graphe * g)
{

    /// INITIALISATION
    int nbsommet = g->ordre; /// on note nbsommet pour clarifier le code
    int *nbCC = malloc(sizeof(int)*nbsommet); /// on cree un tab d entiers pour contenir la compo connexe d un sommet i
    for(int i=0; i<nbsommet; i++)
        nbCC[i]=i; /// on donne a chaque sommet une valeur de compo connexe differente

    /// TRI DES ARETES
    int *poids_aretes = malloc(sizeof(int)*g->n_arc); /// on cree un tab dynamique qui va recup tous les poids

    for (int i_arc=0; i_arc<g->n_arc; i_arc++)
        poids_aretes[i_arc]=g->pArc[i_arc]->poids;
    /// BOUCLE FOR QUI AFFICHE LE NUMERO DES ARETES AVEC LEUR POIDS
    /*
    for (int i_arc=0; i_arc<g->n_arc; i_arc++)
        printf("poids arete %d; %d \n", i_arc, poids_aretes[i_arc]);
    */
    int *kruskal_selection = malloc(sizeof(int) *g->n_arc); /// tableau permettant de savoir quelles sont les aretrs retenues par Kruskal

    for (int i_arc=0; i_arc<g->n_arc; i_arc++)
        kruskal_selection[i_arc] = 0; /// on  les initialise tous à zéro

    int dernier_poids_min= -1;
    int nb_kruskal_selection = 0; /// compteur d aretes retenues (RAPPEL : Kruskal s execute jusqu à ordre-1, on doit donc compter les aretes retenues pour savoir quand s arreter

    while (nb_kruskal_selection != g->ordre-1)
    {
        // recherche du prochain poids minimum
        int poids_min=1000000; /// on définit un poids minimum trop grand pour que le premier poids prenne la valeur du min
        for (int i_arc=0; i_arc<g->n_arc; i_arc++)
        {
            if (g->pArc[i_arc]->poids > dernier_poids_min)
            {
                if (g->pArc[i_arc]->poids < poids_min) /// si le poids de l'arete numero i_arc est plus petit que le minimum
                    poids_min = g->pArc[i_arc]->poids; /// alors on modifie poids_min
            }
        }
        //printf("poids minimum courant %d %d nb kruskal=%d\n", poids_min, dernier_poids_min, nb_kruskal_selection);
        dernier_poids_min = poids_min;
        /// on commence à selectionner
        for (int i_arc=0; i_arc<g->n_arc; i_arc++) /// on parcourt
        {
            if (g->pArc[i_arc]->poids == poids_min) /// si l arrete a le meme poids que le poids minimum
            {
                /// on definit s1 et s2 les deux sommets relies par l arete
                int s1 = g->pArc[i_arc]->sommet_depart;
                int s2 = g->pArc[i_arc]->sommet_arrivee;
                //printf("exploring %d, %d, %d, nbCC %d, %d \n", i_arc, s1, s2, nbCC[s1], nbCC[s2]);
                if (nbCC[s1] != nbCC[s2]) /// si ils ne font pas partis de la meme compo connexe (si leur numero de CC est different)
                {
                    //printf("modification kruskal \n");
                    kruskal_selection[i_arc] = 1; /// on marque pour dire qu on a deja explore
                    nb_kruskal_selection += 1; /// on ajoute 1 au nb de selections
                    for (int jj=0; jj<nbsommet; jj++)
                    {
                        if (nbCC[jj] == nbCC[s1])
                            nbCC[jj] = nbCC[s2]; /// on modifie le numéro de compo connexe de tous les sommets de la compo annexe du sommet s1 pour donner celui de s2
                    }
                }
            }
        }

    }
    printf(" \nLISTE DES ARETES SELECTIONNEES PAR KRUSKAL\n\n");
    int poids_total=0;
    for (int i_arc=0; i_arc<g->n_arc; i_arc++)
    {
        if (kruskal_selection[i_arc]!=0) /// si le num de l arete a été marqué = si l arete a ete selectionné par kruskal
        {
            /// on print ses informations : numéro, les deux sommets relies et le poids de l arete
            printf("arete %d - %d, poids %d \n",g->pArc[i_arc]->sommet_depart, g->pArc[i_arc]->sommet_arrivee, g->pArc[i_arc]->poids);
            poids_total=poids_total+g->pArc[i_arc]->poids;
        }
    }
    printf("le poids total est : %d \n", poids_total);

}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////// PRIM ///////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



void prim(Graphe *g, int sommet_depart)
{
    /// on cree deux tableaux dynamique
    /// RAPPEL : Prim implique de creer un autre graphe, on doit donc recuperer les sommets d une part et les aretes d autre part
    int *selection_sommet= malloc(sizeof(int) *g->ordre); /// tab dyn d 'entiers pour select les sommets
    int *selection_arc= malloc(sizeof(int) *g->n_arc); /// mm chose pour les arcs

    for (int i_s=0; i_s<g->ordre; i_s++) /// on initialise tous les elements du tableau de selection des sommets
        selection_sommet[i_s] = 0;
    for (int i_arc=0; i_arc<g->n_arc; i_arc++) /// meme chose pour le tab des aretes
        selection_arc[i_arc] = 0;

    selection_sommet[sommet_depart] = 1; /// on marque le sommet de depart
    int nb_sommets_selectionnes = 1; /// comme le sommet de depart est marque, on a un sommet selectionne = on ajoute 1 au compteur
    while (nb_sommets_selectionnes != g->ordre)
    {
        int arc_a_ajouter = -1;
        int poids_min = 10000000; /// comme kruskal, on met un poids minimum trop grand pour qu il prenne la valeur du premier poids
        for (int i_s=0; i_s<g->ordre; i_s++)
        {
            if (selection_sommet[i_s] == 1)
            {
                pArc arc_suivant = g->pSommet[i_s]->arc;
                while (arc_suivant != NULL) {
                    //printf("sommet depart %d, sommet arrivee %d \n", arc_suivant->sommet_depart, arc_suivant->sommet_arrivee);
                    if (((selection_sommet[arc_suivant->sommet_depart] == 0) |(selection_sommet[arc_suivant->sommet_arrivee] == 0)) &(arc_suivant->poids < poids_min)) {
                        poids_min = arc_suivant->poids;
                        arc_a_ajouter = arc_suivant->valeur;
                    }
                    arc_suivant = arc_suivant->arc_suivant;
                }
            }
        }
        //printf("selection arc %d, %d, %d\n", arc_a_ajouter, g->pArc[arc_a_ajouter]->sommet_depart, g->pArc[arc_a_ajouter]->sommet_arrivee);
        selection_arc[arc_a_ajouter] = 1; /// on marque l arc a ajouter
        selection_sommet[g->pArc[arc_a_ajouter]->sommet_depart] = 1;
        selection_sommet[g->pArc[arc_a_ajouter]->sommet_arrivee] = 1;
        nb_sommets_selectionnes += 1;
        //printf("nb_sommets %d \n", nb_sommets_selectionnes);
    }
    /*
    printf("selection sommets \n");
    for (int i_s=0; i_s<g->ordre; i_s++)
        if (selection_sommet[i_s]!=0)
            printf("%d, ", i_s);
    printf("\n");
    */
    int poids_total=0;
    printf("le poids avant boucle est : %d \n", poids_total);
    for (int i_arc=0; i_arc<g->n_arc; i_arc++)
    {
        if (selection_arc[i_arc]!=0)
        {
            printf("arete %d - %d, poids %d \n", g->pArc[i_arc]->sommet_depart, g->pArc[i_arc]->sommet_arrivee, g->pArc[i_arc]->poids);
            poids_total=poids_total+g->pArc[i_arc]->poids;
        }
    }
    printf("le poids total est : %d \n", poids_total);
}


int main()
{
    Graphe * g = lire_graphe("grapheTP3ex1.txt"); /// on prend le meme graphe que pour le tp3

    char choix;             // Initialisation de la variable choix
    char selection[30];     // Initialisation de la variable selection
    do                      // Faire tant que
    {
        choix = 0 ;         // Variable choix mise à 0
        do                  // Faire tant que
        {
            printf("\nMenu  \n"
                   "Entrer 1 pour afficher le graphe \n"
                   "2 pour executer Kruskal\n"
                   "3 pour executer Prim \n"
                   "4 pour fermer le programme \n");    // Affichage du menu
            scanf("%s", &selection);                    // Recupération de la saisie de l'utilisateur
            // La fonction atoi() convertit une chaîne de caractères en un entier
            if ( (atoi(selection) >= 1) && (atoi(selection) <= 5))      // Si la valeur saisie est convertissable en entier entre 1 et 5
            {
                choix = atoi(selection);                // La variable choix prend cette valeur
            }
        }
        while((choix < 1) && (choix > 5));              // Premiere boucle qui repete tant que le choix du menu n'est pas correct

        if(choix == 1)      // Si le choix est 1 (l'utilisateur choisit d'afficher le graphe)
        {
            graphe_afficher(g); // affiche les donnees du graphe : liste des sommets et leurs adjacences, puis la liste des aretes avec leur numero, les deux sommets relies et leur poids
        }
        if(choix == 2)      // Si le choix est 2 (l'utilisateur choisit d'executer le programme Kruskal)
        {
            kruskal(g); // executer kruskal
        }
        if (choix == 3) // si le choix esr 3 (l'utilisateur choisit d'executer le programme Prim
        {
            /// RAPPEL : dans l algo de Prim, le sommet de depart ne change pas le resultat
            /// Ainsi, nous laissons le choix à l'utilisateur de choisir si il souhaite ou non le choisir
            int choix_prim;
            int sommet_depart_prim;
            printf("Voulez-vous choisir le sommet de depart de Prim ou preferez-vous partir d'un sommet aleatoire ? \n "
                   "Ne change rien au resultat \n"
                   "Entrez 1 pour choisir et 2 pour aleatoire \n");
            scanf("%d",&choix_prim);
            if(choix_prim == 1)
            {
                printf("Veuillez selectionner un sommet de depart pour executer Prim \n");
                scanf("%d", &sommet_depart_prim);
                prim(g, sommet_depart_prim); /// executer prim
            }
            if(choix_prim ==2)
            {
                const int MAX = g->ordre, MIN = 0;
                srand(time(NULL));
                sommet_depart_prim = (rand() % (MAX - MIN)) + MIN;
                printf("Le sommet aleatoire est le numero %d, on part donc de ce sommet \n",sommet_depart_prim);
                prim(g, sommet_depart_prim); /// executer prim
            }
        }

    }while (choix != 4);
    return 0;
}


