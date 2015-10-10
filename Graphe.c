#include <stdlib.h>
#include <stdio.h>

#include "Graphe.h"

graphe* creation(int max_sommet, int est_oriente)
{
	graphe* g = (graphe*)malloc(sizeof(graphe));

	g->nbSommets = 0;
	g->nbMaxSommets = max_sommet;
	g->estOriente = est_oriente;

	return g;
}

void lecture(graphe* g)
{
	printf("# Nombre maximum de sommets\n%d\n",g->nbMaxSommets);
	printf("# Est orienté\n");
	if(g->estOriente)
	{
		printf("oui");
	}
	else
	{
		printf("non");
	}
	printf("\n# sommets : voisins\n");

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
}





void* realloueMemoire(void* ptr, int taille)
{
	void* temp = realloc(ptr, taille);

	if(NULL != temp)
	{
		return temp;
	}

	fprintf(stderr,"Erreur, plus de mémoire\n");
	exit(1);
}
