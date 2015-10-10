#include "interface.h"

#include <stdio.h>

void menuDeSelection(void)
{
	int selection;
	do
	{
		afficherMenu();
		scanf("%d", &selection);
		scanf("%*[^\n]s");
		getchar();
		executerAction(selection);
	} while (selection != 9);
}

void afficherMenu(void)
{
	printf("\t1. Creation d'un graphe\n\t2. Lecture d'un graphe depuis un fichier\n\t3. Insertion d'un sommet\n\t4. Insertion d'une arête\n\t5. Suppression d'un sommet\n\t6. Suppression d'une arête\n\t7. Afficher le graghe\n\t8. Sauvegarder le graphe\n\t9. Quitter\n");
}

void executerAction(int num_action)
{
    switch (num_action)
    {
    case 2: // creation d'un graphe depuis un fichier

        break;
    default:
        fprintf(stderr, "Action inconnue\n");
        break;
    }
}

/*graphe* creation(int nb_sommet)
{
}

void lecture(const char* file_name)
{
}

void insertionSommet(void)
{
}

void insertionArete(int sommet_depart, int sommet_arrive)
{
}

void suppressionSommet(int num_sommet)
{
}

void suppressionArete(int sommet_depart, int sommet_arrive)
{
}

void affichage(void)
{
}

void sauvegarde(const char* file_name)
{
}

void quitter(void)
{
	exit(0);
}*/
