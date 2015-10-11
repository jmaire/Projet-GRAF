#ifndef INTERFACE_FUNCTION
#define INTERFACE_FUNCTION

#include "Graphe.h"

void menuDeSelection(void);

void afficherMenu(int isGraphInit);

graphe* executerAction(int num_action, graphe* g);

graphe* executerActionCreation(int num_action);

graphe* lectureFichier(void);

graphe* actionCreation(void);

/*void lecture(const char* file_name);

void insertionSommet(void);

void insertionArete(int sommet_depart, int sommet_arrive);

void suppressionSommet(int num_sommet);

void suppressionArete(int sommet_depart, int sommet_arrive);

void affichage(void);

void sauvegarde(const char* file_name);

void quitter(void);*/

#endif // INTERFACE_FUNCTION
