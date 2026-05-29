#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "fifo.h"
//#include "cellule.h"
#include "file.h"

void initialiser_graphe(Graphe *g, int ordre)
{
    g->ordre = ordre;
    g->matrice = malloc(sizeof(int*)*g->ordre); /// on cree un tableau a deux dimensions = matrice telle que demandee sur le sujet
    g->nom_sommets = malloc(sizeof(char)*g->ordre);
    for(int i = 0; i < g->ordre; i++)
    {
        g->matrice[i]= malloc(sizeof(int)*g->ordre);
    }
    for (int i=0; i<g->ordre; i++)
        g->nom_sommets[i] = 'z';
    for (int i=0; i<g->ordre; i++)
    {
        for (int j=0; j<g->ordre; j++)
            g->matrice[i][j]=0;
    }
}

int initialiser_graphe_flot(Graphe *g, int ordre, Graphe *g_init)
{
    g->ordre = ordre;
    g->matrice = malloc(sizeof(int*)*g->ordre); /// on cree un tableau a deux dimensions = matrice telle que demandee sur le sujet
    g->nom_sommets = malloc(sizeof(char)*g->ordre);
    for(int i = 0; i < g->ordre; i++)
    {
        g->matrice[i]= malloc(sizeof(int)*g->ordre);
    }
    for (int i=0; i<g->ordre; i++)
        g->nom_sommets[i] = g_init->nom_sommets[i];
    for (int i=0; i<g->ordre; i++)
    {
        for (int j=0; j<g->ordre; j++)
            g->matrice[i][j]=0;
    }
    g->source=g_init->source;
    g->puit=g_init->puit;
}


int recherche_source_puit(Graphe *g)
/// sert a rechercher quel sommet est la source et quel sommet est le puit
/// pour la source on recherche quelle colonne ne contient que des zéros
/// pour le puit on recherche quelle ligne ne contient que des zéros
{
    /// recherche du puit
    for(int i=0; i<g->ordre; i++) /// on parcourt chaque ligne
    {
        int j=0;
        while((j<g->ordre)&&(g->matrice[i][j]==0))
            j=j+1;
        if(j==g->ordre)
            g->puit=i; /// si le nb de zeros comptes est égal au nb d element dans la ligne alors c'est le puit
    }
    /// recherche de la source
    /// meme fonctionnement que pour le puit mais on remplace ligne par colonne
    for (int k=0; k<g->ordre; k++)
    {
        int m=0;
        while((m<g->ordre)&&(g->matrice[m][k]==0))
            m=m+1;
        if (m==g->ordre)
            g->source=k;
    }

    return 0;
}


int lire_graphe(char * nomFichier, Graphe *g) /// ce sous programme prend en argument le fichier texte et cree un tableau a deux dimensions
{
    FILE * ifs = fopen(nomFichier,"r");     // Ouverture du fichier texte
    if (!ifs)                               // Si le fichier texte ne s'ouvre  pas
    {
        printf("Erreur de lecture fichier\n");  // Affichage de l'erreur d'ouverture
        exit(-1);                           // On sort du programme
    }
    char tmp; /// on cree un char pour prendre le \n après l'ordre et les espaces entre les noms de sommets
    fscanf(ifs,"%d",&g->ordre); ///on recup l'ordre
    fscanf(ifs,"%c",&tmp);  /// on prend le \n
    initialiser_graphe(g, g->ordre); /// on parametrise le graphe avec l ordre recupere dans le fichier txt
    for(int nbchar=0; nbchar<g->ordre; nbchar++) /// on parcourt la 1 ere ligne
     {
        fscanf(ifs,"%c", &g->nom_sommets[nbchar]); /// on recup les lettres = noms de sommets
        fscanf(ifs,"%c", &tmp); /// on prend en compte l espace entre chaque lettre
        //printf("%c \n", tmp);
     }

    for (int ja = 0; ja < g->ordre ; ja++) /// on prend chaque ligne
    {
        //printf("Element numero %d \n", ja);
        for(int jb = 0; jb < g->ordre; jb++) /// on prend chaque colonne de chaque ligne
        {
            //printf("Attribution numero %d \n", jb);
            fscanf(ifs,"%d",&g->matrice[ja][jb]); /// on recup le nb présent en coordonnees saisies et on le met dans la matrice
            //printf("%d \n", g->matrice[ja][jb]);
        }
    }
    return 0;
}

int dupliquer_graphe(Graphe* graphe_a_dupliquer, Graphe* nouveau_graphe)
/// sert à copier le graphe cree
/// on utilise ce sous programme pour creer le graphe residuel
{
    initialiser_graphe(nouveau_graphe, graphe_a_dupliquer->ordre); /// on initialise le graphe a dupliquer de mm ordre que le graphe de base
    nouveau_graphe->source = graphe_a_dupliquer->source; /// il prend la meme source
    nouveau_graphe->puit = graphe_a_dupliquer->puit; /// et le meme puit
    for (int i=0; i<nouveau_graphe->ordre; i++)
    {
        nouveau_graphe->nom_sommets[i] = graphe_a_dupliquer->nom_sommets[i]; /// recup le nom des sommets
    }
    for (int i=0; i<nouveau_graphe->ordre; i++)
        for (int j=0; j<nouveau_graphe->ordre; j++)
           nouveau_graphe->matrice[i][j] = graphe_a_dupliquer->matrice[i][j]; /// recup les valeurs des flots
    return 0;
}

int afficher_graphe(Graphe *g)
/// sert à afficher le graphe sous forme de ligne colonne comme dans le document txt et ses informations
{
    printf("ordre du graphe : %d \n", g->ordre); /// on print l ordre
    for(int nbchar=0; nbchar<g->ordre; nbchar++)
     {
        printf("%c, ", g->nom_sommets[nbchar]); /// on print la lettre nom de sommet
     }
     printf("\n");
    for(int pi=0; pi<g->ordre; pi++)
    {
        for(int pj=0; pj<g->ordre; pj++)
        {
            printf("%4d ", g->matrice[pi][pj]); /// on print la valeur de la matrice
        }
        printf("\n");
    }
    printf("Source : %d \nPuit : %d \n", g->source, g->puit); /// on indique qui est la source et qui est le puit
}




///Methode utile au BFS et au DFS pour afficher le resultat
/// inutile sauf pour tester le DFS et le BFS modifiés pour faire ce TP
/// modifié à partir du TP2
int print_antecedent(int ordre, int* antecedent)
/*
La fonction print_antecedent permet d'afficher l'antecedent
    IN  : ENTIER antecendent
    OUT : ENTIER 0
*/
{
    for (int i = 0 ; i < ordre ; i++)          /// Repete ordre fois
    {
        int j = i;                          /// La variable j prend comme valeur i
        //printf("%d", j);                    /// Affiche j
        while(antecedent[j] != -1)          /// Tant que l'antecedent j est different de -1
        {
            //printf(" <-- %d", antecedent[j]);   /// On affiche  l'antecedent
            j = antecedent[j];              /// j prend comme valeur l'antecedent de j
        }
        //printf("\n");                       /// Retourne a la ligne
    }
    return 0;
}


/// utile au DFS
/// d apres votre mail, on peut le faire en recursif ou avec une pile
/// comme nous avions fait en recursif, on a repris la base du code de notre TP2
void recursive_DFS(Graphe *g, int s, int* marque, int* antecedent)
/*
La fonction recursive_DFS permet de calculer recursivement le DFS
    IN : STRUCTURE Graphe
         STRUCTURE Sommet
         ENTIER marque
         ENTIER antecendent
    OUT :
*/
{
    /// Initialisation de l'ancien sommet a sa nouvelle valeur
    int new_sommet=0;
    while(g->matrice[s][new_sommet]==0) new_sommet=new_sommet+1;
    while (new_sommet<g->ordre)
    {
        /// Initialisation d'un nouveau sommet qui prend comme valeur le sommet
        if (marque[new_sommet] == 0)            /// Si la marque d'indice du nouveau sommet est egale à 0
        {
            marque[new_sommet] = 1;             /// Cette marque passe à 1
            antecedent[new_sommet] = s;/// Le nouveau sommet devient l'ancien
            recursive_DFS(g, new_sommet, marque, antecedent);   /// Appel recursif
        }
        new_sommet = new_sommet + 1;
        while(g->matrice[s][new_sommet]==0)
            new_sommet=new_sommet+1;
    }
}




/// DFS modifie à partir du tp2 pour realiser ce tp
int DFS(Graphe *G, int s, int *chemin, int puit)
/*
La fonction DFS permet d'effectuer le DFS
    IN : STRUCTURE Graphe
         STRUCUTRE Sommet
    OUT
*/
{
    //printf("DFS \n");
    int marque[G->ordre];                       /// Initialisation du tableau marque
    int antecedent[G->ordre];                   /// Initialisation du tableau antecendent
    for(int i = 0 ; i < G->ordre ; i++)         /// Boucle repetant autant de fois que l'ordre de G
    {
        marque[i] = 0;                          /// Met marque de i à 0
        antecedent[i] = -1;                     /// Met l'antecedent de i à -1
    }
    marque[s]=1;                      /// Met marque de la valeur a 1
    recursive_DFS(G, s, marque, antecedent);    /// Appel de la fonction recursive_DFS
    int success = print_antecedent(G->ordre, antecedent); /// Initialise success avec l'affichage

    /// ci dessous le code ajoute au DFS du tp2 pour trouver le chemin
    for (int i=0; i<G->ordre; i++)
        chemin[i]= -1;
    int i=0;
    chemin[0] = puit; /// on affiche le chemin sous la forme suivante : puit nbsommet nbsommet ... nbsommet source
    while(antecedent[chemin[i]] != -1){
        chemin[i+1]=antecedent[chemin[i]];
        //printf("%d, %d\n", chemin[i+1], i);
        i=i+1;
    };
    //printf("FIN DFS \n");
    return 0;
}



/// BFS modifie pour la resolution du tp6
/// ayant mal lu, nous avons fait un BFS modifie
/// mais apres avoir parle avec madame Palasi, nous avons fait le DFS recursif ci-dessus
/// voici tout de meme le BFS modifie qui marche tout aussi bien :)
int BFS(Graphe *G, int s, int *chemin, int puit)
/*
La fonction BFS cherche le BFS d'un graphe
    IN : STRUCTURE Graphe
         STRUCTURE Sommet
    OUT : ENTIER 0
*/
{
    //printf("BFS \n");
    File maFile = fileVide();   /// Initialisation d'une file vide
    enfiler(maFile,s);  /// Enfiler la file
    int antecedent[G->ordre];
    int marque[G->ordre];
    // Repete n fois en fonction de l'ordre du sommet
    for(int i=0;i<G->ordre; i++)
    {
        marque[i] = 0;          /// Met l'element i du tableau marque a 0
        antecedent[i] = -1;     /// Met l'element i du tableau antecedent a -1
    }
    marque[s] = 1;      /// Met l'element valeur de s de marque a 1
    while( maFile->longueur != 0)       /// Tant que la fiel n'est pas vide
    {
        int x = maFile->tete->element;  /// Met l'element de la tete de la file dans x
        defiler(maFile);                /// Defile la file
        marque[x] = 1; /// Met l'element x du tableau marque a 1
        for(int j=0; j<G->ordre; j++)
        {
            if((G->matrice[x][j]!=0)&&(marque[j]==0))
            {
                enfiler(maFile,j);          /// Enfile la file
                marque[j] = 1;              /// Met l'element j de marque a 1
                antecedent[j] = x;          /// Met l'element j de antecedent a x
            }
        }
    }
    //int success = print_antecedent(G->ordre, antecedent);     // Affichage du BFS
    for (int i=0; i<G->ordre; i++) chemin[i]= -1;
    int i=0;
    chemin[0] = puit; /// on affiche le chemin sous la forme suivante : puit nbsommet nbsommet ... nbsommet source
    while(antecedent[chemin[i]] != -1){
        chemin[i+1]=antecedent[chemin[i]];
        //printf("%d, %d\n", chemin[i+1], i);
        i=i+1;
    };
    //printf("FIN BFS \n");
    return 0;       // Retourne 0
}


/// programme qui calcule le flot min sur le chemin
int calcule_le_flot_min_sur_le_chemin(Graphe *g, int * chemin)
{
    //printf("CALCUL DU FLOT MIN SUR LE CHEMIN \n");
    int flot_min=100000; /// on init un flot min trop grand pour que ça puisse direct etre remplace par la 1 ere valeur de flot rencontrée
    int i=0;
    int flot_arete;
    while (chemin[i] != g->source) {
        //printf("%d \n", chemin[i+1]);
        flot_arete = g->matrice[chemin[i+1]][chemin[i]];
        //printf("depart %d, arrivee %d residu %d \n", chemin[i], chemin[i+1], flot_arete);
        if (flot_arete < flot_min)
            flot_min=flot_arete;
        i=i+1;
    }
    //printf("FIN CALCUL FLOT MIN SUR CHEMIN \n");
    return flot_min;
}

int mettre_a_jour_le_graphe_residuel(Graphe *g_residuel, Graphe *g, Graphe *g_flot)
{
    for (int i=0; i<g_residuel->ordre; i++ )
        for (int j=0; j<g_residuel->ordre; j++)
            g_residuel->matrice[i][j] = 0; /// on remet à 0
    for (int i=0; i<g_residuel->ordre; i++ )
        for (int j=0; j<g_residuel->ordre; j++)
            {
                if (g->matrice[i][j]!=0)
                    {
                        // mise a jour pour les aretes directes
                        if (g_flot->matrice[i][j]<g->matrice[i][j])
                        {
                            //printf("mise ajour directe de %d, %d, %d \n", i, j, g->matrice[i][j] - g_flot->matrice[i][j]);
                            g_residuel->matrice[i][j] = g->matrice[i][j] - g_flot->matrice[i][j];
                        }
                        // mise a jour pour les aretes inverses
                        if ((g->matrice[i][j]!=0)&&(g_flot->matrice[i][j]>0))

                        {
                            //printf("mise a jour inverse de %d, %d, %d \n", i, j, g_flot->matrice[j][i]);
                            g_residuel->matrice[j][i] = g_flot->matrice[i][j];
                        }
                    }
            }
    return 0;
}


int mettre_a_jour_le_graphe_des_flots(Graphe *g_flot, Graphe *g_residuel, int *chemin)
{
    int flot_max_chemin = calcule_le_flot_min_sur_le_chemin(g_residuel, chemin);
    //printf("flot max: %d \n", flot_max_chemin);
    int i =0;
    while (chemin[i] != g_residuel->source)
    {
        //printf("debut %d, fin %d \n", chemin[i+1], chemin[i]);
        // arc direct
        int ancienne_valeur=g_flot->matrice[chemin[i+1]][chemin[i]];
        g_flot->matrice[chemin[i+1]][chemin[i]] = g_flot->matrice[chemin[i+1]][chemin[i]] + flot_max_chemin;
        // arc indirect
        g_flot->matrice[chemin[i]][chemin[i+1]] = g_flot->matrice[chemin[i]][chemin[i+1]] - flot_max_chemin;
        i = i+1;
    }
    return 0;
}

int calcule_flot_max(Graphe *g)
{
    int s=0;
    for (int i=0; i<g->ordre; i++)
    if (g->matrice[0][i]>0)
        s=s+g->matrice[0][i];
    return s;
}


int main()
{
    // graphe de base
    Graphe *g = malloc(sizeof(Graphe)); /// on cree le graphe de base
    lire_graphe("fichier_tp6.txt", g); /// on lit le fichier txt et on recup les info
    recherche_source_puit(g); /// on determine le sommet source et le sommet puit
    printf("Graphe recupere dans le fichier texte \n");
    afficher_graphe(g); /// on affiche le graphe
    printf("\n");

    // Graphe residuel
    Graphe *g_residuel = malloc(sizeof(Graphe)); /// on cree le graphe residuel
    dupliquer_graphe(g, g_residuel); /// on lui donne les memes infos que le graphe de base

    // Graphe des flots
    Graphe *g_flot= malloc(sizeof(Graphe)); /// on cree le graphe des flots
    initialiser_graphe_flot(g_flot, g->ordre, g); /// on l initialise (toutes les valeurs à zero)

    // Chemin
    int * chemin = malloc(sizeof(int)*g->ordre); /// on cree un tableau dyn 1 dimension pour le chemin
    for (int i=0; i<g->ordre; i++)
        chemin[i]= 0; /// on met tout à zero

    printf("\n");

    do
    {
        DFS(g_residuel,g->source, chemin, g->puit);
        //for (int i=0; i<g->ordre; i++)
        //    printf("%d,", chemin[i]);
        if (chemin[1]!= -1)
        {
            mettre_a_jour_le_graphe_des_flots(g_flot, g_residuel, chemin);
            mettre_a_jour_le_graphe_residuel(g_residuel, g, g_flot);
            /// veuillez décommenter pour print les graphes des flots, résiduel et le flot max à chaque étape
            /*
            printf("graphe des flots \n");
            afficher_graphe(g_flot);
            printf("\nflot max %d \n", calcule_flot_max(g_flot));
            printf("graphe residuel \n");
            afficher_graphe(g_residuel);
            */
        }
    } while (chemin[1] != -1);
    printf("Graphe des flots \n");
    afficher_graphe(g_flot);
    printf("\n\n Graphe residuel \n");
    afficher_graphe(g_residuel);
    printf("\nflot max %d \n", calcule_flot_max(g_flot));


    return 0;
}
