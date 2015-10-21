#ifndef MA_LISTE_H
#define MA_LISTE_H

typedef struct s_liste
{
	int sommet, poids;
	struct s_liste* suiv;
} elementListe, *liste;

liste* creationListe(void);

void initListe(liste* l);

void ajouteListe(liste* l, int s, int p);

void supprimeListe(liste* l, int s);

void afficheListe(liste* l, int opt);

void remonterListe(liste* l, int s);

liste* detruireListe(liste* l);

char* listeToString(liste* l, int opt);

#endif
