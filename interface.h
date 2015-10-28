#ifndef INTERFACE_FUNCTION
#define INTERFACE_FUNCTION

#include "Graphe.h"

void menuDeSelection(void);

void afficherMenu(int isGraphInit);

graphe* executerAction(int num_action, graphe* g);

graphe* executerActionCreation(int num_action);

graphe* lectureFichier(void);

graphe* actionCreation(void);

void actionSauvegarde(graphe* g);

void actionInsertionArete(graphe* g);

void actionSuppressionSommet(graphe* g);

void actionSuppressionArete(graphe* g);

#endif // INTERFACE_FUNCTION
