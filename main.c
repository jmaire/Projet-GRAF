#include <stdlib.h>
#include <stdio.h>

#include "Graphe.h"

int main()
{
	//liste* l = creationListe();
	//ajouteListe(l, 5, 1);
	//afficheListePos(l);

	graphe* g = creation(11, 1);
	//lecture(g);
	insertionSommet(g);
	return 0;
}
