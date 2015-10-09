#include <stdlib.h>
#include <stdio.h>

#include "MaListe.h"

liste* creationListe(void)
{
	liste* l = (liste*)malloc(sizeof(liste));
	ajouteListe(l,-1,0);
	return l;
}

void ajouteListe(liste* l, int s, int p)
{
	// Empty list
	if(NULL == (*l))
	{
		elementListe* nouvelElement = (elementListe*) malloc(sizeof(elementListe));
		nouvelElement->sommet = s;
		nouvelElement->poids = p;
		nouvelElement->suiv = NULL;
		(*l) = nouvelElement;

		return;
	}

	// Element already in list
	if((*l)->sommet == s)
	{
		return;
	}

	// Element sorted in ascending order
	if((*l)->sommet > s)
	{
		elementListe* temp = (*l);

		elementListe* nouvelElement = (elementListe*) malloc(sizeof(elementListe));
		nouvelElement->sommet = s;
		nouvelElement->poids = p;
		nouvelElement->suiv = temp;

		(*l) = nouvelElement;

		return;
	}

	ajouteListe(&((*l)->suiv), s, p);
}

void supprimeListe(liste* l, int s)
{
	// Empty list
	if(NULL == (*l))
	{
		return;
	}

	// Element already in list
	if((*l)->sommet == s)
	{
		elementListe* temp = (*l);
		(*l) = (*l)->suiv;
		free(temp);

		return;
	}

	// Element sorted in ascending order
	if((*l)->sommet > s)
	{
		return;
	}

	supprimeListe(&((*l)->suiv), s);
}

void afficheListe(liste* l)
{
	if((*l)!=NULL)
	{
		printf("(%d/%d) ",(*l)->sommet, (*l)->poids);
		afficheListe(&((*l)->suiv));
	}
	else
	{
		printf("\n");
	}
}

void afficheListePos(liste* l)
{
	if((*l)!=NULL)
	{
		if((*l)->sommet>0)
		{
			printf("(%d/%d) ",(*l)->sommet, (*l)->poids);
		}
		afficheListe(&((*l)->suiv));
	}
	else
	{
		printf("\n");
	}
}
