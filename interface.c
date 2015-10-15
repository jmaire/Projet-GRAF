#include "interface.h"

#include <stdio.h>

void menuDeSelection(void)
{
	int selection;
	graphe* grapheCourant = NULL;

	do  // lors du lancement aucun graphe n'est initialisé, seule les actions de creation et quitter sont disponibles
    {
		afficherMenu(0);
		scanf("%d", &selection);
		scanf("%*[^\n]s");
		getchar();

		grapheCourant = executerActionCreation(selection);

    } while ((!grapheCourant) && (selection != 3)); // tant que le graphe est NULL et qu'il n'y a pas eu de demande pour quitter on continue

    if(!grapheCourant)
    {
        return;
    }

	while (selection != 9)
	{
		afficherMenu(1);
		scanf("%d", &selection);
		scanf("%*[^\n]s");
		getchar();

		graphe* graphres = executerAction(selection, grapheCourant);
		if(NULL != graphres)
        {
            grapheCourant = graphres;
        }

	}
}

void afficherMenu(int isGraphInit)
{
    if(isGraphInit)
    {
        printf("\t1. Creation d'un graphe\n\t2. Lecture d'un graphe depuis un fichier\n\t3. Insertion d'un sommet\n\t4. Insertion d'une arête\n\t5. Suppression d'un sommet\n\t6. Suppression d'une arête\n\t7. Afficher le graghe\n\t8. Sauvegarder le graphe\n\t9. Quitter\n");
    }
    else
    {
        printf("\t1. Creation d'un graphe\n\t2. Lecture d'un graphe depuis un fichier\n\t3. Quitter\n");
    }
}

graphe* executerAction(int num_action, graphe* g)
{
    switch (num_action)
    {
    case 1: // creation d'un graphe
        return actionCreation();
        break;
    case 2: // creation d'un graphe depuis un fichier
        return lectureFichier();
        break;
    case 3: // insertion d'un sommet
        return NULL;
        break;
    case 4: // quitter
        return NULL;
        break;
    case 5: // quitter
        return NULL;
        break;
    case 6: // quitter
        return NULL;
        break;
    case 7: // quitter
        return NULL;
        break;
    case 8: // quitter
        return NULL;
        break;
    case 9: // quitter
        return NULL;
        break;
    default:
        fprintf(stderr, "Action inconnue\n");
        return NULL;
        break;
    }
}

graphe* executerActionCreation(int num_action)
{
    switch (num_action)
    {
    case 1: // creation d'un graphe
        return actionCreation();
        break;
    case 2: // creation d'un graphe depuis un fichier
        return lectureFichier();
        break;
    case 3: // quitter
        return NULL;
        break;
    default:
        fprintf(stderr, "Action inconnue\n");
        return NULL;
        break;
    }
}

graphe* lectureFichier(void)
{
    char file_path[50];

    printf("Entrez le chemin du fichier à charger.\n");
    scanf("%s", file_path);
	scanf("%*[^\n]s");
	getchar();

    FILE* f = fopen(file_path, "r");

    int maxNumSommet;
    char isOrient;

    fscanf(f, "# nombre maximum de sommets\n%d\n# oriente\n%c\n# sommets : voisins\n", &maxNumSommet, &isOrient);

    if(maxNumSommet <= 0 || ((isOrient != 'n') && (isOrient != 'o')))
    {
        fprintf(stderr, "le format du fichier est incorrect.\n");
        return NULL;
    }

    char buffer[50];
    fgets(buffer, 50, f);
    printf("\n%s\n",buffer);

    // TODO : faire le parsing du fichier

    return NULL;
}

graphe* actionCreation(void)
{
    return creation(15, 0);
}

/*void lecture(const char* file_name)
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
