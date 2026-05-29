#include <stdio.h>
#include <stdlib.h>
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
        printf("%d ",arc->sommet);  // Affiche le sommet connecté au sommet num
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
        Newarc->sommet = s2;
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
        Newarc->sommet = s2;
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
}






/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////DIJKSTRA//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////



int trouver_element_avec_distance_minimale(int* tab, int nbsommet)
{
    int minimum=100000;
    int i_min=-1;
    for(int i=0; i<nbsommet; i++)
    {
        if((tab[i] != -1)&&(tab[i]<minimum))
        {
            minimum=tab[i];
            i_min=i;
        }
    }
    return i_min;
}

void ajouter_elem_file(int tab[], int nbsommet, pSommet s, int w)
{
    tab[s->valeur]=w;
}

void retirer_elem_file(int *tab, int nbsommet, pSommet s)
{
    tab[s->valeur]=-1;
}

int file_vide(int *tab, int nbsommet)
{
    for(int i=0; i<nbsommet; i++)
    {
        if(tab[i]!=-1)
            return 1;
    }
    return 0;
}

int est_dans_la_file(int *tab, int nbsommet, int w)
{
    if(tab[w]==-1)
        return 0;
    return 1;
}



void dijkstra(Graphe *g, pSommet s, int nbsommet)
{
    int *dv;
    dv = malloc(sizeof(int)*nbsommet);
    for (int i=0; i<nbsommet; i++)
        dv[i]=10000; // distance de s à v => on met toutes les distances à l'infini (ici un nombre trop grand car infini en C n existe pas
    int *pv;
    pv = malloc(sizeof(int)*nbsommet);
    for (int i=0; i<nbsommet; i++)
        pv[i]=-1; // prédécesseur de v dans le chemin minimal depuis s
    int *tab;
    tab = malloc(sizeof(int)*nbsommet);
    for (int i=0; i<nbsommet; i++)
        tab[i]=-1; // tab qui va permettre de faire les opé sur la file

    dv[s->valeur]=0; // distance de s à s
    pv[s->valeur]=-1; // prédecesseur de s dans le chemin depuis s

    /// Ajouter s dans la File avec la priorité 0
    ajouter_elem_file(tab, nbsommet, s, 0);
    /// Tant que File pas vide faire :
    while(file_vide(tab, nbsommet)!=0)
    {
        //for(int j=0; j<nbsommet; j++)
        //printf("%d , ", tab[j]); printf("\n\n");
        int v = trouver_element_avec_distance_minimale(tab, nbsommet); // element de la file ayant une distance depuis s minimale
        retirer_elem_file(tab, nbsommet, g->pSommet[v]); // retirer v de la File
        pArc arc_suivant = g->pSommet[v]->arc;

        while (arc_suivant!=NULL)       // Tant que l'arc suivant n'est pas null
        {
            int w = arc_suivant->sommet;    // Met le sommet de l'arc suivant dans z
            int dvw = arc_suivant->poids; // poids de l arrete
            //printf("dijkstra voisin w=%d poids arc vw w=%d dist(v)=%d, distvw=%d\n", w, dv[w], dv[v], dvw);
            if(dv[w]>dv[v]+dvw)
            {
                dv[w]=dv[v]+dvw; // mise à jour de la distance de s à w
                pv[w]=v; // mise a jour du prédecesseur de w dans le chemin minimal depuis s

                /// ATTENTION : peu importe si la condition du if est respectee,
                /// ajouter ou mettre à jour w dans la file revient au meme
                /// par soucis de coller a l'algorithme fourni, nous avons gardé le if else meme si ça n'est pas important
                if(est_dans_la_file(tab, nbsommet, w)==0)
                    ajouter_elem_file(tab,nbsommet, g->pSommet[w], dv[w]);
                else
                    ajouter_elem_file(tab,nbsommet, g->pSommet[w], dv[w]);
            }
            arc_suivant = arc_suivant->arc_suivant;
        }
    }
    /// AFFICHAGE AVEC LES FLECHES

    char modeAffichage[30];
    int choixAffichage;
// CREER UN CHOIX : SOIT IL CHOISIT UN SOMMET D ARRIVEE SOIT IL AFFICHE TOUS LES CHEMINS MINIMUM POUR CHAQUE SOMMET
// *1 = choix du sommet d arrivee
// *2 = affiche les chemins minimum de chaque sommet
    do
    {
        do
        {
            choixAffichage = -1;
            printf("\nSelectionner le mode d'affichage \n"
                   "0 Pour quitter le programme \n"
                   "1 Pour le choix du sommet d'arrivee\n"
                   "2 Pour afficher les chemins minimum de chaque sommet\n"
                   "3 Pour changer de sommet de depart\n");
            scanf("%s",&modeAffichage);
            if ( (atoi(modeAffichage) >=0 ) && (atoi(modeAffichage) <= 3))  // La fonction atoi() convertit une chaîne de caractères en un entier
            {
                choixAffichage = atoi(modeAffichage);
            }
        }
        while(!((choixAffichage >= 0) && (choixAffichage <= 3)));

        if(choixAffichage == 1)
        {
            ///*1
            int j;
            printf("VEUILLEZ CHOISIR LE SOMMET D ARRIVEE \n");
            scanf("%d",&j);                          // La variable j prend comme valeur i
            printf("%d", j);                    // Affiche j
            while(pv[j] != -1)          // Tant que l'antecedent j est different de -1
            {
                printf(" <-- %d", pv[j]);   // On affiche  l'antecedent
                j = pv[j];              // j prend comme valeur l'antecedent de j
            }
            printf("\n\n");
        }
        if(choixAffichage == 2)
        {
            for (int i = 0 ; i < nbsommet ; i++)          // Repete nbsommet fois
            {
                int j = i;                          // La variable j prend comme valeur i
                printf("%d", j);                    // Affiche j
                while(pv[j] != -1)          // Tant que l'antecedent j est different de -1
                {
                    printf(" <-- %d", pv[j]);   // On affiche  l'antecedent
                    j = pv[j];              // j prend comme valeur l'antecedent de j
                }
                printf("\n DISTANCE TOTALE LA PLUS OPTIMALE D APRES DIJKSTRA DEPUIS LE SOMMET DE DEPART CHOISI : %d",dv[i]);
                printf("\n\n");                       // Retourne a la ligne
            }
        }
        if(choixAffichage == 3)
        {
            int choix;
            printf("A PARTIR DE QUEL SOMMET VOULEZ VOUS PARTIR ?? \n Veuillez entrer votre choix : ");
            scanf("%d", &choix);
            pSommet sommet_depart = g->pSommet[choix];
            //printf("%d \n", sommet_depart->valeur);
            int nbsommet = g->ordre;
            dijkstra(g, sommet_depart, nbsommet);
        }
    }
    while(choixAffichage != 0);
}



///*1
/*    int j;
    printf("Veuillez choisir le sommet d arrivee \n");
    scanf("%d",&j);                          // La variable j prend comme valeur i
    printf("%d", j);                    // Affiche j
    while(pv[j] != -1)          // Tant que l'antecedent j est different de -1
    {
        printf(" <-- %d", pv[j]);   // On affiche  l'antecedent
        j = pv[j];              // j prend comme valeur l'antecedent de j
    }
    if(dv[j]!=0)
        printf("\n DISTANCE TOTALE LA PLUS OPTIMALE D APRES DIJKSTRA DEPUIS LE SOMMET DE DEPART CHOISI : %d",dv[j]);
    else
        printf("\n SOMMET DE DEPART");
    printf("\n\n");
*/
/// *2
/*   for (int i = 0 ; i < nbsommet ; i++)          // Repete nbsommet fois
   {
       int j = i;                          // La variable j prend comme valeur i
       printf("%d", j);                    // Affiche j
       while(pv[j] != -1)          // Tant que l'antecedent j est different de -1
       {
           printf(" <-- %d", pv[j]);   // On affiche  l'antecedent
           j = pv[j];              // j prend comme valeur l'antecedent de j
       }
       if(dv[i]!=0)
           printf("\n DISTANCE TOTALE LA PLUS OPTIMALE D APRES DIJKSTRA DEPUIS LE SOMMET DE DEPART CHOISI : %d",dv[i]);
       else
           printf("\n SOMMET DE DEPART");
       printf("\n\n");                       // Retourne a la ligne
   }
   */
/// FIN CHOIX

/// ANCIENNE PRESENTATION
/*
    printf("VOICI LE DETAIL DE LA PRESENTATION \n"
           " \n PREMIERE LIGNE : liste des sommets \n\n"
           "DEUXIEME LIGNE : precedent du sommet dans le trajet minimum a partir du sommet de depart"
           "\n ATTENTION : le sommet de depart est a -1 car il n a pas de precedent \n\n"
           "TROISIEME LIGNE : distance au sommet de depart \n\n");
    for(int j=0; j<nbsommet;j++)
        printf("%d , ", j);
    printf("\n\n");
    for(int j=0; j<nbsommet; j++)
        printf("%d , ", dv[j]);
    printf("\n\n");
    for(int j=0; j<nbsommet; j++)
        printf("%d , ", pv[j]);
    printf("\n\n");
*/



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////MAIN//////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //Graphe * g = lire_graphe("graphe1_TP2.txt");
    Graphe * g = lire_graphe("grapheTP3ex1.txt");
    int choix;
    printf("A PARTIR DE QUEL SOMMET VOULEZ VOUS PARTIR ?? \n Veuillez entrer votre choix : ");
    scanf("%d", &choix);

    pSommet sommet_depart =g->pSommet[choix];
    //printf("%d \n", sommet_depart->valeur);
    int nbsommet = g->ordre;
    dijkstra(g, sommet_depart, nbsommet);




    return 0;
}

