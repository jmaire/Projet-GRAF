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
}

void insertionArete(graphe* g, int s1, int s2, int poids)
{
	if(s1>=g->nbSommets && s2>=g->nbSommets && poids<0)
	{
		printf("Impossible\n");
		return;
	}
	
	ajouteListe(&(g->listesAdjacences[s1]),s2,poids);
}

void affichageGraphe(graphe* g)
{
	sauvegardeGraphe(g, "");
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

	fprintf(f,"# Nombre maximum de sommets\n%d\n",g->nbMaxSommets);
	fprintf(f,"# Est orienté\n");
	if(g->estOriente)
	{
		fprintf(f,"oui");
	}
	else
	{
		fprintf(f,"non");
	}
	fprintf(f,"\n# sommets : voisins\n");
	int i;
	for(i=0 ; i<g->nbSommets ; i++)
	{
		fprintf(f,"%d : ",i);
		fprintf(f,"%s",listeToString(&(g->listesAdjacences[i]), 0));
	}
	fclose(f);
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
