#ifndef MON_GRAPHE_H
#define MON_GRAPHE_H

#include "MaListe.h"

typedef liste TypVoisins;

typedef struct s_graphe
{
	int estOriente, nbMaxSommets, nbSommets;
	TypVoisins* listesAdjacences;
} graphe;

graphe* creation(int max_sommet, int est_oriente);

void lecture(graphe* g);

void insertionSommet(graphe* g);








void* realloueMemoire(void* ptr, int taille);

#endif
