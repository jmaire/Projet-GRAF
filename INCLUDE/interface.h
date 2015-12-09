#ifndef INTERFACE_FUNCTION
#define INTERFACE_FUNCTION

#include "Graphe.h"

#define MENU_QUITTER 0
#define MENU_CREATION_GRAPHE 1
#define MENU_LECTURE_GRAPHE 2
#define MENU_INSERTION_SOMMET 3
#define MENU_INSERTION_ARETE 4
#define MENU_SUPPRESSION_SOMMET 5
#define MENU_SUPPRESSION_ARETE 6
#define MENU_AFFICHER_GRAPHE 7
#define MENU_SAUVEGARDER_GRAPHE 8
#define MENU_RECHERCHER_FLOT_MAX 9

/*
 * Fonction de lancement du menu, affichage du menu et gestion des entrées utilisateur
 */
void menuDeSelection(void);

/*
 * Fonction d'affichage du menu, affiche uniquement les fonctions de création et quitter si le graphe courant est NULL
 * affiche toutes les options sinon
 *
 * @param 	int				isGraphInit						0 si le graphe courant est NULL, 1 sinon
 */
void afficherMenu(int isGraphInit);

/*
 * Fonction d'appel des fonctionnalités sur le graphe
 *
 * @param 	int				num_action						entier correspondant à l'action souhaitée
 * @param 	graphe*			g			        			graphe sur lequel effectuer l'action
 *
 * Retourne le graphe modifié par l'action demandée
 */
graphe* executerAction(int num_action, graphe* g);

/*
 * Fonction d'appel des fonctionnalités de création d'un graphe
 *
 * @param 	int				num_action						entier correspondant à l'action souhaitée
 *
 * Retourne le graphe créé ou NULL si une erreur se produit lors de la création
 */
graphe* executerActionCreation(int num_action);

/*
 * Fonction de création de graphe à partir d'un fichier
 *
 * Retourne le graphe créé par la lecture ou NULL si une erreur se produit
 */
graphe* lectureFichier(void);

/*
 * Fonction de création de graphe à partir de données utilisateur
 *
 * Retourne le graphe correspondant aux caractéristiques entrées par l'utilisateur
 */
graphe* actionCreation(void);

/*
 * Fonction d'écriture du graphe courant dans un fichier
 *
 * @param 	graphe*			g			        			graphe à sauvegarder
 */
void actionSauvegarde(graphe* g);

/*
 * Fonction d'ajout d'une arête au graphe courant
 *
 * @param 	graphe*			g			        			graphe auquel ajouter une arête
 */
void actionInsertionArete(graphe* g);

/*
 * Fonction de suppression d'un sommet au graphe courant
 *
 * @param 	graphe*			g			        			graphe auquel supprimer un sommet
 */
void actionSuppressionSommet(graphe* g);

/*
 * Fonction de suppression d'une arête au graphe courant
 *
 * @param 	graphe*			g			        			graphe auquel supprimer une arête
 */
void actionSuppressionArete(graphe* g);

#endif // INTERFACE_FUNCTION
