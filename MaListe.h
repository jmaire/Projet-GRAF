#ifndef MA_LISTE_H
#define MA_LISTE_H

typedef struct s_liste
{
	int sommet, poids;
	struct s_liste* suiv;
} elementListe, *liste;


/*
 * Fonction qui initialise une liste en lui ajoutant l'élément (-1,0)
 *
 * @param 	liste*		l							Référence de la liste que l'on veut initialiser
 */
void initListe(liste* l);


/*
 * Fonction qui ajoute un élément à la liste choisie
 *
 * @param 	liste*		l							Référence de la liste à qui l'on veut ajouter un élément
 * @param 	int				s							Sommet de l'élément à ajouter
 * @param 	int				p							Poids de l'élément à ajouter
 */
void ajouteListe(liste* l, int s, int p);

/*
 * Fonction qui vérifie s'il existe un élément dans la liste choisie avec un sommet entré en paramètre
 *
 * @param 	liste*		l							Référence de la liste
 * @param 	int				s							Sommet de l'élément
 */
int appartientListe(liste* l, int s);

/*
 * Fonction qui supprime un élément de la liste choisie
 *
 * @param 	liste*		l							Référence de la liste à qui l'on veut supprimer un élément
 * @param 	int				s							Sommet de l'élément à supprimer
 */
void supprimeListe(liste* l, int s);

/*
 * Fonction qui affiche la liste choisie
 *
 * @param 	liste*		l							Référence de la liste que l'on veut afficher
 * @param 	int				opt						1 si l'on veut afficher les éléments qui ont un sommet négatif, 0 sinon
 */
void afficheListe(liste* l, int opt);

/*
 * Fonction qui met à jour les sommets après avoir supprimer un sommet d'un graphe
 *
 * @param 	liste*		l							Référence de la liste que l'on veut mettre à jour
 * @param 	int				s							Numéro à partir duquel il faut mettre à jour les sommets
 */
void remonterListe(liste* l, int s);

/*
 * Fonction qui vide une liste
 *
 * @param 	liste*		l							Référence de la liste que l'on veut vider
 */
void viderListe(liste* l);

/* 
 * Fonction qui transforme une liste en une chaîne de caratère utilisé pour l'affichage
 *
 * @param 	liste*		l							Référence de la liste que l'on veut vider
 * @param 	int				opt						1 si l'on veut afficher les éléments qui ont un sommet négatif, 0 sinon
 */
char* listeToString(liste* l, int opt);

#endif
