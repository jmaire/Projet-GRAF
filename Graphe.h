#ifndef MON_GRAPHE_H
#define MON_GRAPHE_H

#include "MaListe.h"

typedef liste* TypVoisins;

typedef struct s_graphe
{
	int estOriente, nbMaxSommets, nbSommets;
	TypVoisins listesAdjacences;
} graphe;


/*
 * Fonction qui alloue sur le tas et initialise un graphe
 *
 * @param 	int				max_sommet		Nombre maximal de sommets du graphe
 * @param		int				est_oriente		1 si le graphe est orienté, 0 sinon
 *
 * Renvoie le graphe crée
 */
graphe* creation(int max_sommet, int est_oriente);


/*
 * Fonction qui permet d'insérer un sommet supplémentaire au graphe choisi
 *
 * @param		graphe*		g					Référence du graphe à qui l'on veut ajouter un sommet
 */
void insertionSommet(graphe* g);


/*
 * Fonction qui permet d'insérer une arête d'un certain poids entre deux sommets d'un graphe choisi
 *
 * @param		graphe*		g					Référence du graphe à qui l'on veut ajouter une arête
 * @param		int				s1				Numéro du sommet de départ
 * @param		int				s2				Numéro du sommet d'arrivée
 * @param		int				poids			Poids de l'arête
 * @param		int				oriente		1 si l'arête est orienté, 0 sinon
 */
void insertionArete(graphe* g, int s1, int s2, int poids, int oriente);


/*
 * Fonction qui permet de supprimer un sommet d'un graphe choisi
 *
 * @param		graphe*		g					Référence du graphe à qui l'on veut supprimer un sommet
 * @param		int				s					Numéro du sommet
 */
void supprimerSommet(graphe* g, int s);


/*
 * Fonction qui met à jour les arêtes après une suppression d'un sommet
 *
 * @param		graphe*		g					Référence du graphe à qui l'on veut supprimer un sommet
 * @param		int				s					Numéro du sommet à partir duquel il faut mettre à jour les sommets
 */
void remonterSommet(graphe* g, int s);


/*
 * Fonction qui permet de supprimer une arête entre deux sommets d'un graphe choisi
 *
 * @param		graphe*		g					Référence du graphe à qui l'on veut supprimer une arête
 * @param		int				s1				Numéro du sommet de départ
 * @param		int				s2				Numéro du sommet d'arrivée
 */
void supprimerArete(graphe* g, int s1, int s2);


/*
 * Fonction qui permet de supprimer un graphe
 *
 * @param		graphe*		g					Référence du graphe que l'on veut supprimer
 */
void supprimerGraphe(graphe* g);


/*
 * Fonction qui vérifié si l'arête entre deux sommets d'un graphe existe
 *
 * @param		graphe*		g					Référence du graphe
 * @param		int				s1				Numéro du sommet de départ
 * @param		int				s2				Numéro du sommet d'arrivée
 * @param		int				oriente		1 si l'arête est orienté, 0 sinon
 *
 * Retourne :
 * 		- 1 s'il existe une arête de s1 à s2
 * 		- 2 s'il existe une arête de s2 à s1 dans le cas :
 *				- d'une arête non orientée d'un graphe orienté
 *				- d'un graphe non orienté
 *		- 0 sinon
 */
int areteAppartientGraphe(graphe* g, int s1, int s2, int oriente);


/*
 * Fonction qui permet de lire un graphe à partir du fichier texte
 *
 * @param		char*			path			Chemin du fichier
 *
 * Retourne le graphe lu grâce au fichier
 */
graphe* lectureGraphe(char* path);


/*
 * Fonction qui sauvegarder un graphe dans un fichier entré en paramètre
 *
 * @param		graphe*		g					Référence du graphe que l'on veut sauvegarder
 * @param		char*			path			Chemin du fichier
 */
void sauvegardeGraphe(graphe* g, char* path);


/*
 * Fonction qui affiche un graphe dans la console
 *
 * @param		graphe*		g					Référence du graphe que l'on veut afficher
 */
void affichageGraphe(graphe* g);


/*
 * Fonction qui réalloue un pointeur avec un nouvelle taille
 *
 * @param		void*		ptr					Référence
 * @param		int			taille			Nouvelle taille à allouer
 */
void* realloueMemoire(void* ptr, int taille);

#endif
