#include <stdlib.h>
#include <stdio.h>

#include "Graphe.h"
#include <string.h>

graphe* creation(int max_sommet, int est_oriente)
{
	graphe* g = (graphe*)malloc(sizeof(graphe));

	g->nbSommets = 0;
	g->nbMaxSommets = max_sommet;
	g->estOriente = est_oriente;

	return g;
}

void insertionSommet(graphe* g)
{
	if(g->nbSommets == g->nbMaxSommets)
	{
		printf("Impossible\n");
		return;
	}
	g->nbSommets++;
	g->listesAdjacences = realloueMemoire(g->listesAdjacences,g->nbSommets*sizeof(TypVoisins));

	//liste* tmp = creationListe();
	initListe(&(g->listesAdjacences[g->nbSommets-1]));
}

void insertionArete(graphe* g, int s1, int s2, int poids)
{
	if(s1>=g->nbSommets || s1<0 || s2>=g->nbSommets || s2<0 || poids<0)
	{
		printf("Impossible\n");
		return;
	}
	
	ajouteListe(&(g->listesAdjacences[s1]),s2,poids);
}

void supprimerSommet(graphe* g, int s)
{
	if(s>=g->nbSommets || s<0)
	{
		printf("Impossible\n");
		return;
	}

	int i;
	for(i=0 ; i<g->nbSommets ; i++)
	{
		if(i==s)
		{
			continue;
		}
		supprimerArete(g,i,s);
		supprimerArete(g,s,i);
	}
	
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

	int taille = g->nbSommets-1;
	liste* tmp = &(g->listesAdjacences[s]);
	for(i=s ; i<taille ; i++)
	{
		g->listesAdjacences[i]=g->listesAdjacences[i+1];
	}

	//detruireListe(tmp);
	//free(tmp);

	g->nbSommets--;
	g->listesAdjacences = realloueMemoire(g->listesAdjacences,g->nbSommets*sizeof(TypVoisins));

}

void supprimerArete(graphe* g, int s1, int s2)
{
	if(s1>=g->nbSommets || s1<0 || s2>=g->nbSommets || s2<0)
	{
		printf("Impossible\n");
		return;
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
	for(i=0 ; i<g->nbSommets ; i++)
	{
		supprimerSommet(g,i);
		i--;
	}

	free(g);
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
		fprintf(f,"%d : ",i);
		fprintf(f,"%s",listeToString(&(g->listesAdjacences[i]),0));
	}
	if(f!=stdout)
	{
		fclose(f);
	}
}

void* realloueMemoire(void* ptr, int taille)
{
	void* temp = realloc(ptr, taille);

	if(NULL != temp)
	{
		return temp;
	}

	fprintf(stderr,"Erreur, plus de mémoire\n");
	return NULL;
	//exit(1);
}
