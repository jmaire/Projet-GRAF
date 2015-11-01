#include <stdio.h>

#include "../INCLUDE/interface.h"

void menuDeSelection(void)
{
	int selection;
	graphe* grapheCourant = NULL;
	int res;

	do  // lors du lancement aucun graphe n'est initialisé, seule les actions de creation et quitter sont disponibles
    {
		afficherMenu(0);
		res = scanf("%d", &selection);
		scanf("%*[^\n]s");
		getchar();
		printf("\n");

		if(res < 1)
        {
            fprintf(stderr, "Action inconnue\n");
            continue;
        }

		grapheCourant = executerActionCreation(selection);

    } while ((!grapheCourant) && (selection != 3)); // tant que le graphe est NULL et qu'il n'y a pas eu de demande pour quitter on continue

    if(!grapheCourant)
    {
        return;
    }

	while (selection != 9)
	{
		afficherMenu(1);
		res = scanf("%d", &selection);
		scanf("%*[^\n]s");
		getchar();
		printf("\n");

		if(res < 1)
        {
            fprintf(stderr, "Action inconnue\n");
            continue;
        }

		grapheCourant = executerAction(selection, grapheCourant);
	}

	supprimerGraphe(grapheCourant);
}

void afficherMenu(int isGraphInit)
{
    if(isGraphInit)
    {
        printf("\n\t1. Création d'un graphe\n\t2. Lecture d'un graphe depuis un fichier\n\t3. Insertion d'un sommet\n\t4. Insertion d'une arête\n\t5. Suppression d'un sommet\n\t6. Suppression d'une arête\n\t7. Afficher le graghe\n\t8. Sauvegarder le graphe\n\t9. Quitter\n");
    }
    else
    {
        printf("\n\t1. Création d'un graphe\n\t2. Lecture d'un graphe depuis un fichier\n\t3. Quitter\n");
    }
}

graphe* executerAction(int num_action, graphe* g)
{
	if((num_action == 1) || (num_action == 2))
	{
		graphe* res = executerActionCreation(num_action);

		if(NULL == res)
		{
			return g;
		}
		else
		{
			return res;
		}
	}

    switch (num_action)
    {
    case 3: // insertion d'un sommet
		insertionSommet(g);
        break;
    case 4: // insertion d'une arête
    	actionInsertionArete(g);
        break;
    case 5: // suppression d'un sommet
    	actionSuppressionSommet(g);
        break;
    case 6: // suppression d'une arête
        actionSuppressionArete(g);
        break;
    case 7: // afficher le graghe
    	affichageGraphe(g);
        break;
    case 8: // sauvegarder le graphe
    	actionSauvegarde(g);
        break;
    case 9: // quitter
        break;
    default:
        fprintf(stderr, "Action inconnue\n");
        return NULL;
        break;
    }
	return g;
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
        fprintf(stderr, "Action inconnue.\n");
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

    return lectureGraphe(file_path);
}

graphe* actionCreation(void)
{
	int nb_sommet, res = 0;

	while(!res)
	{
		printf("Entrez le nombre de sommets du graphe.\n");

		res = scanf("%d", &nb_sommet);
		scanf("%*[^\n]s");
		getchar();
	}

	char isOrient;

	res = 0;
	while(!res)
	{
		printf("Le graphe est il orienté ? (o/n)\n");

    	res = scanf("%c", &isOrient);
		scanf("%*[^\n]s");
		getchar();

		if((isOrient != 'o') && (isOrient != 'n'))
			res = 0;
	}

    return creation(nb_sommet, isOrient == 'o');
}

void actionSauvegarde(graphe* g)
{
    char file_path[50];

    printf("Entrez le nom du fichier où enregistrer le graphe.\n");
    scanf("%s", file_path);
	scanf("%*[^\n]s");
	getchar();

    sauvegardeGraphe(g, file_path);
}

void actionInsertionArete(graphe* g)
{
	int s1, s2, poids, res = 0;

	while(!res)
	{
		printf("Entrez le numero du premier sommet.\n");

		res = scanf("%d", &s1);
		scanf("%*[^\n]s");
		getchar();
	}

	res = 0;

	while(!res)
	{
		printf("Entrez le numero du deuxième sommet.\n");

		res = scanf("%d", &s2);
		scanf("%*[^\n]s");
		getchar();
	}

	res = 0;

	while(!res)
	{
		printf("Entrez le poids de l'arête.\n");

		res = scanf("%d", &poids);
		scanf("%*[^\n]s");
		getchar();
	}

	char oriente;

	if(g->estOriente)
    {
        res = 0;

        while(!res)
        {
            printf("L'arête est elle orientée ? (o/n)\n");

            res = scanf("%c", &oriente);
            scanf("%*[^\n]s");
            getchar();

            if((oriente != 'o')&&(oriente != 'n'))
            {
                continue;
            }
        }
    }

	insertionArete(g, s1, s2, poids, oriente == 'o');
}

void actionSuppressionSommet(graphe* g)
{
	int num_sommet, res = 0;

	while(!res)
	{
		printf("Entrez le numero du sommet à supprimer.\n");

		res = scanf("%d", &num_sommet);
		scanf("%*[^\n]s");
		getchar();
	}

	supprimerSommet(g, num_sommet);
}

void actionSuppressionArete(graphe* g)
{
	int s1, s2, res = 0;

	while(!res)
	{
		printf("Entrez le numero du sommet de départ.\n");

		res = scanf("%d", &s1);
		scanf("%*[^\n]s");
		getchar();
	}

	res = 0;

    while(!res)
	{
		printf("Entrez le numero du sommet d'arrivé.\n");

		res = scanf("%d", &s2);
		scanf("%*[^\n]s");
		getchar();
	}

	supprimerArete(g, s1, s2);
}
