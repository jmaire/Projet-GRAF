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
		printf("\n");

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
		printf("\n");

		grapheCourant = executerAction(selection, grapheCourant);
	}
}

void afficherMenu(int isGraphInit)
{
    if(isGraphInit)
    {
        printf("\n\t1. Creation d'un graphe\n\t2. Lecture d'un graphe depuis un fichier\n\t3. Insertion d'un sommet\n\t4. Insertion d'une arête\n\t5. Suppression d'un sommet\n\t6. Suppression d'une arête\n\t7. Afficher le graghe\n\t8. Sauvegarder le graphe\n\t9. Quitter\n");
    }
    else
    {
        printf("\n\t1. Creation d'un graphe\n\t2. Lecture d'un graphe depuis un fichier\n\t3. Quitter\n");
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
    graphe* resultat_parcing;
    char file_path[50];

    printf("Entrez le chemin du fichier à charger.\n");
    scanf("%s", file_path);
	scanf("%*[^\n]s");
	getchar();

    FILE* f = fopen(file_path, "r");

	if(NULL == f)
	{
		fprintf(stderr, "Le fichier choisi n'existe pas.\n");
		return NULL;
	}

    int maxNumSommet, res;
    char isOrient, verif;

    res = fscanf(f, "# nombre maximum de sommets\n%d\n# oriente\n%c\n# sommets : voisin%c\n", &maxNumSommet, &isOrient, &verif);

    if((maxNumSommet <= 0) || ((isOrient != 'n') && (isOrient != 'o')) || (res < 3) || (verif != 's'))
    {
        fprintf(stderr, "Le format du fichier est incorrect.\n");
        return NULL;
    }

    resultat_parcing = creation(maxNumSommet, isOrient == 'o');

    int sommet_actuel = 0, sommet_depart, sommet_arrive, poids;
    char curseur;
    int i, j, liste_adjacences[maxNumSommet][maxNumSommet];

    for(i=0;i<maxNumSommet;i++)
    {
        for(j=0;j<maxNumSommet;j++)
        {
            liste_adjacences[i][j] = -1;
        }
    }

    while(1)
    {
        res = fscanf(f, "%d :%c", &sommet_depart, &verif);  // lecture de l'entête du sommet

        if((res < 2) || ((verif != ' ')&&(verif != '\n')))  // si le formatage n'est pas correct
        {
            if(EOF == fgetc(f))
            {
                break;
            }

            fprintf(stderr, "Le format du fichier est incorrect.\n");
            return NULL;
        }

        if(sommet_depart != sommet_actuel)  // verification si le sommet indiqué par le fichier correspond au successeur des précédents
        {
            fprintf(stderr, "Le sommet %d est manquant.\n", sommet_actuel);
            return NULL;
        }

        sommet_actuel++;
        insertionSommet(resultat_parcing);

        curseur = fgetc(f);
        fseek(f, -1, SEEK_CUR);

        if((verif == '\n') || (curseur == '\n'))
        {
            continue;
        }
        if(curseur != '(')
        {
            fprintf(stderr, "Le format du fichier est incorrect.\n");
            return NULL;
        }

        while(1)
        {
            res = fscanf(f, "(%d/%d)%c", &sommet_arrive, &poids, &verif);

            if((res < 3)||((verif != ' ')&&(verif != ',')&&(verif != '\n')))
            {
                fprintf(stderr, "Le format du fichier est incorrect.\n");
                return NULL;
            }

            liste_adjacences[sommet_depart][sommet_arrive] = poids;

            if((verif == ' ')||(verif == '\n'))
            {
                break;
            }
            else // verif == ','
            {
                if(' ' != fgetc(f)) // si la virgule n'est pas suivie d'un espace
                {
                    fprintf(stderr, "Le format du fichier est incorrect.\n");
                    return NULL;
                }
            }
        }
    }

    for(i=0;i<sommet_actuel;i++)
    {
        for(j=0;j<sommet_actuel;j++)
        {
            if(liste_adjacences[i][j] != -1)
            {
                insertionArete(resultat_parcing, i, j, liste_adjacences[i][j]);
            }
        }
    }

    return resultat_parcing;
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

	insertionArete(g, s1, s2, poids);
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
