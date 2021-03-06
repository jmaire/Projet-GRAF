#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../INCLUDE/Graphe.h"

#define AFFICHER_SOMMET_FICTIF 0

graphe* creation(int max_sommet, int est_oriente)
{
	// Allocation de mémoire pour le graphe
	graphe* g = (graphe*)malloc(sizeof(graphe));

	// Initialisation des attributs de la structure du graphe
	g->nbSommets = 0;
	g->nbMaxSommets = max_sommet;
	g->estOriente = est_oriente;
	g->listesAdjacences = NULL;

	// Renvoie du graphe crée
	return g;
}

void insertionSommet(graphe* g)
{
	// Vérification en cas de paramètres erronés
	if(g->nbSommets == g->nbMaxSommets)
	{
		fprintf(stderr,"Impossible d'ajouter un sommet supplémentaire :\n");
		fprintf(stderr,"\t-Limite de sommet atteinte\n");
		return;
	}

	// Incrémentation du nombre de sommet
	g->nbSommets++;

	// Réajustement de la mémoire alloué des listes d'ajacences
	g->listesAdjacences = realloueMemoire(g->listesAdjacences,g->nbSommets*sizeof(TypVoisins));

	// Initialisation de la liste du sommet crée
	initListe(&(g->listesAdjacences[g->nbSommets-1]));
}

void insertionArete(graphe* g, int s1, int s2, int poids, int oriente)
{
	// Vérification en cas de paramètres erronés
	if(s1==s2 || s1>=g->nbSommets || s1<0 || s2>=g->nbSommets || s2<0 || poids<=0)
	{
		fprintf(stderr,"Impossible d'ajouter l'arête (%d) --%d-> (%d) :\n",s1+DECALAGE_SOMMET,poids,s2+DECALAGE_SOMMET);
		if(s1==s2)
		{
			fprintf(stderr,"\t-Un arête doit se faire entre deux sommets différents\n");
		}
		if(s1<0 || s2<0 || s1>=g->nbSommets || s2>=g->nbSommets)
		{
			fprintf(stderr,"\t-Les sommets choisis n'existent pas\n");
		}
		if(poids<0)
		{
			fprintf(stderr,"\t-Le poids doit être positif\n");
		}
		return;
	}

	// Vérifie si l'arête appartient au graphe
	int res = areteAppartientGraphe(g, s1, s2, oriente);

	if(res!=0)
	{
		switch(res)
		{
			case 1:
				fprintf(stderr,"Une arête entre le sommet %d et %d est déjà présente\n",s1+DECALAGE_SOMMET,s2+DECALAGE_SOMMET);
				break;

			case 2:
				fprintf(stderr,"Une arête entre le sommet %d et %d est déjà présente\n",s2+DECALAGE_SOMMET,s1+DECALAGE_SOMMET);
				break;

			default:
				break;
		}
		return;
	}

	// Ajout de l'arête de s2 à s1 dans le cas d'une arête non orientée dans un graphe orienté ou d'un graphe non orienté
	if(!g->estOriente || (!oriente && g->estOriente))
	{
		ajouteListe(&(g->listesAdjacences[s2]),s1,poids);
	}

	// Ajout de l'arête de s1 à s2
	ajouteListe(&(g->listesAdjacences[s1]),s2,poids);
}

void supprimerSommet(graphe* g, int s)
{
	if(s>=g->nbSommets || s<0)
	{
		fprintf(stderr,"Impossible de supprimer le sommet %d\n",s+DECALAGE_SOMMET);
		fprintf(stderr,"\t-Le sommet choisi n'existe pas\n");
		return;
	}

	int i;
	for(i=0 ; i<g->nbSommets ; i++)
	{
		supprimerArete(g,i,s);
	}

	viderListe(&(g->listesAdjacences[s]));
	remonterSommet(g,s);
}

void remonterSommet(graphe* g, int s)
{
	int i;
	for(i=0 ; i<g->nbSommets ; i++)
	{
		if(i==s)
		{
			continue;
		}
		remonterListe(&(g->listesAdjacences[i]),s);
	}

	g->nbSommets--;
	for(i=s ; i<g->nbSommets ; i++)
	{
		g->listesAdjacences[i]=g->listesAdjacences[i+1];
	}

	g->listesAdjacences = realloueMemoire(g->listesAdjacences,g->nbSommets*sizeof(TypVoisins));
}

void supprimerArete(graphe* g, int s1, int s2)
{
	// Vérification en cas de paramètres erronés
	if(s1>=g->nbSommets || s1<0 || s2>=g->nbSommets || s2<0)
	{
		fprintf(stderr,"Impossible de supprimer l'arête (%d) ---> (%d)\n",s1+DECALAGE_SOMMET,s2+DECALAGE_SOMMET);
		fprintf(stderr,"\t-Les sommets choisis n'existent pas\n");
		return;
	}

	// En cas de graphe non orienté, on supprime également une éventuelle arête de s2 à s1
	if(!g->estOriente)
	{
		supprimeListe(&(g->listesAdjacences[s2]),s1);
	}
	supprimeListe(&(g->listesAdjacences[s1]),s2);
}

void affichageGraphe(graphe* g)
{
	sauvegardeGraphe(g, "");
}

void supprimerGraphe(graphe* g)
{
	int i;
	for(i=g->nbSommets-1 ; i>=0 ; i--)
	{
		supprimerSommet(g,i);
	}

	free(g);
}

int areteAppartientGraphe(graphe* g, int s1, int s2, int oriente)
{
	int res = appartientListe(&(g->listesAdjacences[s1]),s2);
	if(res)
	{
		// Retourne 1 s'il existe une arête de s1 à s2
		return 1;
	}
	if(!g->estOriente || (g->estOriente && !oriente)) {
		res = appartientListe(&(g->listesAdjacences[s2]),s1);
		if(res)
		{
			// Retourne 2 s'il existe une arête de s2 à s1 dans le cas :
			//	- d'une arête non orientée d'un graphe orienté
			//	- d'un graphe non orienté
			return 2;
		}
	}
	// Retourne 0 sinon
	return 0;
}

int rechercheFlotMaximal(graphe* g, int s, int t)
{
  //TODO vérifier les sommets

  int i, j;

  // Initialiser le flot à 0
  int f[g->nbSommets][g->nbSommets];
  for(i=0; i<g->nbSommets; i++)
  {
    for(j=0; j<g->nbSommets; j++)
    {
      f[i][j] = 0;
    }
  }

  int cf[g->nbSommets];

  // Initialisation à zéro du flot maximal
  int flot_max = 0;

  // Copie du graphe g vers une matrice d'ajacences
  int** Gf = toMatriceAdjacences(g);

  //tant que il existe un chemin améliorant p de s à t dans le graphe résiduel Gf
  while(existeChemin(Gf,g->nbSommets,s,t,cf))
  {
    int flot_chemin = INT_MAX;

    int i;
    for(i=t; i!=s; i=cf[i])
    {
      j = cf[i];
      flot_chemin = MIN(flot_chemin, Gf[j][i]);
    }

    for(i=t; i!=s; i=cf[i])
    {
      j = cf[i];
      Gf[j][i] -= flot_chemin;
      Gf[i][j] += flot_chemin;
    }

    flot_max += flot_chemin;
  }

  return flot_max;
}

graphe* lectureGraphe(char* path)
{
	graphe* resultat_parcing;

	FILE* f = fopen(path, "r");

	if(NULL == f)
	{
		fprintf(stderr, "Le fichier choisi n'existe pas.\n");
		return NULL;
	}

    int maxNumSommet, res;
    char isOrient, verif;

    res = fscanf(f, "# nombre maximum de sommets\n%d\n# oriente\n%c\n# sommets : voisin%c\n", &maxNumSommet, &isOrient, &verif);

    if((maxNumSommet <= 0) || ((isOrient != 'n') && (isOrient != 'o')) || (res < 3) || (verif != 's'))
    {
        fprintf(stderr, "Le format du fichier est incorrect.\n");
        return NULL;
    }

    resultat_parcing = creation(maxNumSommet, isOrient == 'o');

    int sommet_actuel = 0, sommet_depart, sommet_arrive, poids;
    char curseur;
    int i, j, liste_adjacences[maxNumSommet][maxNumSommet];

    for(i=0;i<maxNumSommet;i++)
    {
        for(j=0;j<maxNumSommet;j++)
        {
            liste_adjacences[i][j] = -1;
        }
    }

    while(1)
    {
        res = fscanf(f, "%d :%c", &sommet_depart, &verif);  // lecture de l'entête du sommet

        if((res < 2) || ((verif != ' ')&&(verif != '\n')))  // si le formatage n'est pas correct
        {
            if(EOF == fgetc(f))
            {
                break;
            }

            fprintf(stderr, "Le format du fichier est incorrect.\n");
            return NULL;
        }

        sommet_depart -= DECALAGE_SOMMET;

        if(sommet_depart != sommet_actuel)  // verification si le sommet indiqué par le fichier correspond au successeur des précédents
        {
            fprintf(stderr, "Le sommet %d est manquant.\n", sommet_actuel);
            return NULL;
        }

        sommet_actuel++;
        insertionSommet(resultat_parcing);

        curseur = fgetc(f);
        fseek(f, -1, SEEK_CUR);

        if((verif == '\n') || (curseur == '\n'))
        {
            continue;
        }
        if(curseur != '(')
        {
            fprintf(stderr, "Le format du fichier est incorrect.\n");
            return NULL;
        }

        while(1)
        {
            res = fscanf(f, "(%d/%d)%c", &sommet_arrive, &poids, &verif);

            if((res < 2)||((verif != ' ')&&(verif != ',')&&(verif != '\n')))
            {
                fprintf(stderr, "Le format du fichier est incorrect.\n");
                return NULL;
            }

            sommet_arrive -= DECALAGE_SOMMET;

            liste_adjacences[sommet_depart][sommet_arrive] = poids;
            if('n' == isOrient)
            {
                liste_adjacences[sommet_arrive][sommet_depart] = -1;
            }

            if((verif == ' ')||(verif == '\n')||(res == 2))
            {
                break;
            }
            else // verif == ','
            {
                if(' ' != fgetc(f)) // si la virgule n'est pas suivie d'un espace
                {
                    fprintf(stderr, "Le format du fichier est incorrect.\n");
                    return NULL;
                }
            }
        }
    }

    for(i=0;i<sommet_actuel;i++)
    {
        for(j=0;j<sommet_actuel;j++)
        {
            if(liste_adjacences[i][j] != -1)
            {
                insertionArete(resultat_parcing, i, j, liste_adjacences[i][j], 1);
            }
        }
    }

    return resultat_parcing;
}

void sauvegardeGraphe(graphe* g, char* path)
{
	FILE* f;
	if(strlen(path)==0)
	{
		f = stdout;
	}
	else
	{
		f = fopen(path,"w+");
	}

	fprintf(f,"# nombre maximum de sommets\n%d\n",g->nbMaxSommets);
	fprintf(f,"# oriente\n");
	if(g->estOriente)
	{
		fprintf(f,"o");
	}
	else
	{
		fprintf(f,"n");
	}
	fprintf(f,"\n# sommets : voisins\n");
	int i;
	for(i=0 ; i<g->nbSommets ; i++)
	{
		fprintf(f,"%d : ",i+DECALAGE_SOMMET);
		char * s = listeToString(&(g->listesAdjacences[i]),AFFICHER_SOMMET_FICTIF,0);
		fprintf(f,"%s",s);
		free(s);
	}
	if(f!=stdout)
	{
		fclose(f);
	}
}

int parcoursProfondeurGraphe(graphe* g, int sommet, int* taille, int* listeSommet, int* sommetMarque, int sommetATrouve)
{
    listeSommet[*taille] = sommet;
    (*taille)++;
    sommetMarque[sommet] = 1;

    if(sommetATrouve == sommet)
    {
        return 1;
    }
    liste l = g->listesAdjacences[sommet];
    while(l != NULL)
    {
        if(sommetMarque[l->sommet] == 0)
        {
            if(parcoursProfondeurGraphe(g, l->sommet, taille, listeSommet, sommetMarque, sommetATrouve))
            {
                return 1;
            }
        }
        l = l->suiv;
    }
    return 0;
}

int cheminExisteGraphe(graphe* g, int sommetDepart, int sommetArrive)
{
    if(sommetDepart >= g->nbSommets)
    {
        fprintf(stderr, "Le sommet %d n'appartient pas au graphe.\n", sommetDepart);
        return 0;
    }
    if(sommetArrive >= g->nbSommets)
    {
        fprintf(stderr, "Le sommet %d n'appartient pas au graphe.\n", sommetArrive);
        return 0;
    }

    int taille = 0;
	int* listeSommet = malloc(sizeof(int)*g->nbSommets);
	int* sommetMarque = calloc(sizeof(int), g->nbSommets);
    return parcoursProfondeurGraphe(g, sommetDepart, &taille, listeSommet, sommetMarque, sommetArrive);
}

int* getParcoursDepuisSommet(graphe* g, int sommetDepart, int* tailleParcours)
{
    *tailleParcours = 0;
    if(sommetDepart >= g->nbSommets)
    {
        fprintf(stderr, "Le sommet %d n'appartient pas au graphe.\n", sommetDepart);
        return NULL;
    }
	int* listeSommet = malloc(sizeof(int)*g->nbSommets);
	int* sommetMarque = calloc(sizeof(int), g->nbSommets);
    parcoursProfondeurGraphe(g, sommetDepart, tailleParcours, listeSommet, sommetMarque, -1);
    return listeSommet;
}

int existeChemin(int** rGraph, int V, int s, int t, int* cf)
{
    int est_visite[V];
    memset(est_visite, 0, sizeof(est_visite));

    int taille = 512;
    int file[taille];
    taille = 0;
    file[taille++] = s;
    est_visite[s] = 1;
    cf[s] = -1;

    while (taille > 0)
    {
        int u = file[--taille];
		    int v;

        for (v=0; v<V; v++)
        {
            if (!est_visite[v] && rGraph[u][v] > 0)
            {
                file[taille++] = v;
                cf[v] = u;
                est_visite[v] = 1;
            }
        }
    }

    return (est_visite[t]);
}

int** toMatriceAdjacences(graphe* g)
{
  int** ma = (int**)calloc(g->nbSommets,sizeof(int*));
  int i;

  for(i=0; i<g->nbSommets; i++)
  {
    ma[i] = (int*)calloc(g->nbSommets,sizeof(int));
    remplirMatriceAdjacences(&(g->listesAdjacences[i]),ma[i]);
  }

  return ma;
}

void* realloueMemoire(void* ptr, int taille)
{
	void* temp = realloc(ptr, taille);

	if(NULL==temp && taille<0)
	{
		fprintf(stderr,"Erreur, plus de mémoire\n");
		return NULL;
	}

	return temp;
}
