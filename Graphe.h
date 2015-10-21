#ifndef MON_GRAPHE_H
#define MON_GRAPHE_H

#include "MaListe.h"

typedef liste* TypVoisins;

typedef struct s_graphe
{
	int estOriente, nbMaxSommets, nbSommets;
	TypVoisins listesAdjacences;
} graphe;

graphe* creation(int max_sommet, int est_oriente);

void insertionSommet(graphe* g);

void insertionArete(graphe* g, int s1, int s2, int poids);

void supprimerSommet(graphe* g, int s);

void remonterSommet(graphe* g, int s);

void supprimerArete(graphe* g, int s1, int s2);

void supprimerGraphe(graphe* g);

void sauvegardeGraphe(graphe* g, char* path);

void affichageGraphe(graphe* g);

void* realloueMemoire(void* ptr, int taille);

#endif
