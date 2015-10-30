#include <stdlib.h>
#include <stdio.h>

#include "Graphe.h"
#include <string.h>

#define AFFICHER_SOMMET_FICTIF 0

graphe* creation(int max_sommet, int est_oriente)
{
	graphe* g = (graphe*)malloc(sizeof(graphe));

	g->nbSommets = 0;
	g->nbMaxSommets = max_sommet;
	g->estOriente = est_oriente;
	g->listesAdjacences = NULL;

	return g;
}

void insertionSommet(graphe* g)
{
	if(g->nbSommets == g->nbMaxSommets)
	{
		fprintf(stderr,"Impossible d'ajouter un sommet supplémentaire\n");
		return;
	}
	g->nbSommets++;
	g->listesAdjacences = realloueMemoire(g->listesAdjacences,g->nbSommets*sizeof(TypVoisins));

	initListe(&(g->listesAdjacences[g->nbSommets-1]));
}

void insertionArete(graphe* g, int s1, int s2, int poids)
{
	if(s1==s2 || s1>=g->nbSommets || s1<0 || s2>=g->nbSommets || s2<0 || poids<0)
	{
		fprintf(stderr,"Impossible d'ajouter cette arête : (%d) --%d-> (%d)\n",s1,s2,poids);
		return;
	}

	ajouteListe(&(g->listesAdjacences[s1]),s2,poids);
}

void supprimerSommet(graphe* g, int s)
{
	if(s>=g->nbSommets || s<0)
	{
		fprintf(stderr,"Impossible de supprimer le sommet %d\n",s);
		return;
	}

	int i;
	for(i=0 ; i<g->nbSommets ; i++)
	{
		supprimerArete(g,i,s);
	}

	viderListe(&(g->listesAdjacences[s]));
	remonterSommet(g,s);
}

void remonterSommet(graphe* g, int s)
{
	int i;
	for(i=0 ; i<g->nbSommets ; i++)
	{
		if(i==s)
		{
			continue;
		}
		remonterListe(&(g->listesAdjacences[i]),s);
	}

	g->nbSommets--;
	for(i=s ; i<g->nbSommets ; i++)
	{
		g->listesAdjacences[i]=g->listesAdjacences[i+1];
	}

	//free(&(g->listesAdjacences[g->nbSommets]));

	g->listesAdjacences = realloueMemoire(g->listesAdjacences,g->nbSommets*sizeof(TypVoisins));
}

void supprimerArete(graphe* g, int s1, int s2)
{
	if(s1>=g->nbSommets || s1<0 || s2>=g->nbSommets || s2<0)
	{
		fprintf(stderr,"Impossible de supprimer cette arête : (%d) ---> (%d)\n",s1,s2);
		return;
	}
	supprimeListe(&(g->listesAdjacences[s1]),s2);
}

void affichageGraphe(graphe* g)
{
	sauvegardeGraphe(g, "");
}

void supprimerGraphe(graphe* g)
{
	int i;
	for(i=g->nbSommets-1 ; i>=0 ; i--)
	{
		supprimerSommet(g,i);
	}

	free(g);
}

graphe* lectureGraphe(char* path)
{
    graphe* resultat_parcing;

    FILE* f = fopen(path, "r");

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

void sauvegardeGraphe(graphe* g, char* path)
{
	FILE* f;
	if(strlen(path)==0)
	{
		f = stdout;
	}
	else
	{
		f = fopen(path,"w+");
	}

	fprintf(f,"# nombre maximum de sommets\n%d\n",g->nbMaxSommets);
	fprintf(f,"# oriente\n");
	if(g->estOriente)
	{
		fprintf(f,"o");
	}
	else
	{
		fprintf(f,"n");
	}
	fprintf(f,"\n# sommets : voisins\n");
	int i;
	for(i=0 ; i<g->nbSommets ; i++)
	{
		fprintf(f,"%d : ",i);
		char * s = listeToString(&(g->listesAdjacences[i]),AFFICHER_SOMMET_FICTIF);
		fprintf(f,"%s",s);
		free(s);
	}
	if(f!=stdout)
	{
		fclose(f);
	}
}

void* realloueMemoire(void* ptr, int taille)
{
	void* temp = realloc(ptr, taille);

	if(NULL==temp && taille<0)
	{
		fprintf(stderr,"Erreur, plus de mémoire\n");
		return NULL;
	}

	return temp;
}
