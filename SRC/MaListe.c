#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../INCLUDE/MaListe.h"

#define MY_SIZE 1024

void initListe(liste* l)
{
	(*l) = NULL;
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

	return ajouteListe(&((*l)->suiv), s, p);
}

int appartientListe(liste* l, int s)
{
	// Empty list
	if(NULL == (*l) || (*l)->sommet > s)
	{
		return 0;
	}

	// Element already in list
	if((*l)->sommet == s)
	{
		return 1;
	}

	return appartientListe(&((*l)->suiv), s);
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
		char* s = listeToString(l, opt, 0);
		printf("%s\n",s);
		free(s);
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

void viderListe(liste* l)
{
	if((*l)==NULL)
	{
		l = NULL;
		return;
	}

	liste* temp = &((*l)->suiv);
	free(*l);
	viderListe(temp);
}

char* listeToString(liste* l, int opt, int virgule)
{
	char* rep = malloc(MY_SIZE*sizeof(char));
	strcpy(rep,"");

	char tmp[256];

	if((*l)!=NULL)
	{
		if((*l)->sommet>=0 || opt)
		{
			if(virgule)
			{
				sprintf(tmp,", ");
				strcat(rep,tmp);
			}
			sprintf(tmp,"(%d/%d)",(*l)->sommet, (*l)->poids);
			strcat(rep,tmp);

			virgule=1;
		}
		char * s = listeToString(&((*l)->suiv),opt,virgule);
		strcat(rep,s);
		free(s);
	}
	else
	{
		strcat(rep,"\n");
	}

	return rep;
}
