#include <stdlib.h>
#include <stdio.h>

#include "MaListe.h"
#include <string.h>

#define MY_SIZE 1024

liste* creationListe(void)
{
	liste* l = (liste*)malloc(sizeof(liste));
	ajouteListe(l,-1,0);
	return l;
}

void initListe(liste* l)
{
	ajouteListe(l,-1,0);
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

void afficheListe(liste* l, int opt)
{
	if(l!=NULL)
	{
		printf("%s\n",listeToString(l, opt));
	}
}

void remonterListe(liste* l, int s)
{
	// Empty list
	if(NULL == (*l))
	{
		return;
	}

	// Element already in list
	if((*l)->sommet > s)
	{
		(*l)->sommet--;
	}

	remonterListe(&((*l)->suiv), s);
}

liste* detruireListe(liste* l)
{
	if((*l)==NULL)
	{
		return NULL;
	}

	elementListe* temp = (*l)->suiv;
	free(*l);
	detruireListe(&temp);
}

char* listeToString(liste* l, int opt)
{
	char* rep = malloc(MY_SIZE*sizeof(char));
	strcpy(rep,"");

	char tmp[256];

	if((*l)!=NULL)
	{
		if((*l)->sommet>0 || opt)
		{
			sprintf(tmp,"(%d/%d) ",(*l)->sommet, (*l)->poids);
			strcat(rep,tmp);
		}
		strcat(rep,listeToString(&((*l)->suiv),opt));
	}
	else
	{
		strcat(rep,"\n");
	}
	return rep;
}
