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
 * Fonction qui recherche du flot maximal entre deux sommets du graphe
 *
 * @param		graphe*		g         Référence du graphe
 * @param		int				s1        Numéro du sommet de départ
 * @param		int				s2        Numéro du sommet d'arrivée
 */
int rechercheFlotMaximal(graphe* g, int s, int t);


/*
 * Fonction qui permet de lire un graphe à partir du fichier texte
 *
 * @param		char*			path			Chemin du fichier
 *
 * Retourne le graphe lu grâce au fichier ou NULL en cas d'échec de lecture
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
 * Fonction qui trouve un chemin de s vers t
 *
 * @param		int**		rGraph				graphe résiduel
 * @param		int			V					taille de la matrice du graphe
 * @param		int			s					sommet de départ
 * @param		int			t					sommet d'arrivé
 * @param		int[]		parent				chemin trouvé
 *
 * Retourne 1 si un chemin existe de s vers t, 0 sinon
 */
int existeChemin(int** rGraph, int V, int s, int t, int* cf);


/*
 * Fonction qui affiche un graphe dans la console
 *
 * @param		graphe*		g					Référence du graphe que l'on veut afficher
 */
void affichageGraphe(graphe* g);


/*
 * Fonction qui éffectue un parcours en profondeur d'un graphe,
 * le parcours s'arrête soit lorsque tous les sommets on été parcouru
 * soit lorque le sommetATrouve est rencontré
 *
 * @param		graphe*			g   			graphe sur lequel éffectuer le parcours
 * @param		int 			sommet			sommet de départ du parcours
 * @param		int*			taille			taille de la liste des sommets rencontrés
 * @param		int*			listeSommet		liste des sommets rencontrés
 * @param		int*			sommetMarque	tableau référençant les sommets trouvés
 * @param		int 			sommetATrouve	sommet à trouver durant le parcours
 *
 * Retourne 1 si sommetATrouve a été trouvé durant le parcours, 0 sinon
 */
int parcoursProfondeurGraphe(graphe* g, int sommet, int* taille, int* listeSommet, int* sommetMarque, int sommetATrouve);


/*
 * Fonction 
 *
 * @param		graphe*			g   			graphe
 */
int** toMatriceAdjacences(graphe* g);


/*
 * Fonction qui permet de déterminer si un chemin existe depuis sommetDepart vers sommetArrive
 *
 * @param		graphe*			g   			graphe à tester
 * @param		int 			sommetDepart	sommet de départ
 * @param		int 			sommetArrive	sommet d'arrivée
 *
 * Retourne 1 s'il existe un chemin de sommetDepart à sommetArrive, 0 sinon
 */
int cheminExisteGraphe(graphe* g, int sommetDepart, int sommetArrive);


/*
 * Fonction qui permet retourner un parcours en profondeur d'un graphe depuis un sommet donné
 *
 * @param		graphe*			g   			graphe à parcourir
 * @param		int 			sommetDepart	sommet de départ du parcours
 * @param		int* 			tailleParcours	taille du tableau retourné
 *
 * Retourne la liste de sommets correspondant au parcours
 */
int* getParcoursDepuisSommet(graphe* g, int sommetDepart, int* tailleParcours);


/*
 * Fonction qui réalloue un pointeur avec un nouvelle taille
 *
 * @param		void*		ptr					Référence
 * @param		int			taille			Nouvelle taille à allouer
 */
void* realloueMemoire(void* ptr, int taille);

#endif
