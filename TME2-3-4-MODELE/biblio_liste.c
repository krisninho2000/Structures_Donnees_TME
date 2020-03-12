#include <stdlib.h>
#include <stdio.h>
#include "biblio.h"
#include "parser.h"
#include "string.h"

// DEFINTION DES STRUCTURES

typedef struct CellMorceau {
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
} CellMorceau;

struct Biblio {
    CellMorceau *L; // Liste des morceaux
    int nE; // Nombre de morceaux dans la liste
};

// FONCTIONS GENERALES (CREATION, MODIFICATION, AFFICHAGE)

CellMorceau *creation_Morceau(int numero, char *titre, char *artiste) 
{
    CellMorceau *morceau = (CellMorceau *)malloc(sizeof(CellMorceau));

    morceau->num = numero;
    morceau->titre = titre;
    morceau->artiste = artiste;
    morceau->suiv = NULL;

    return morceau;
}

Biblio * nouvelle_biblio(void) 
{
    Biblio *b = (Biblio*)malloc(sizeof(Biblio));
    b->L = NULL;
    b->nE = 0;
    return b;
}

void insere(Biblio *B, int num, char *titre, char *artiste)
{
    CellMorceau *c = creation_Morceau(num, titre, artiste);

    if (B->L == NULL) {
        B->L = c;
    }
    else {
        CellMorceau *morc = B->L;
        while (morc->suiv != NULL) {
            morc = morc->suiv;
        }
        morc->suiv = c;
    }

    B->nE++;
}

void libere_biblio(Biblio *B)
{
    free(B);
}

void afficheMorceau(CellMorceau *cell)
{
	printf("$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
   CellMorceau *morceau = B->L;
    
    while (morceau) {
        afficheMorceau(morceau);
        morceau = morceau->suiv;
    }

    printf("Nombre de morceaux dans la bibliotheque - %d\n\n", B->nE);
}

int compte_nombre_morceaux_bibli(CellMorceau *c, Biblio *B) 
{
    int occ = 0;
    char *titre = strdup(c->titre);
    char *artiste = strdup(c->artiste);
    CellMorceau *curr = B->L;

    while (curr) {
        if ((strcmp(strdup(curr->titre), strdup(titre)) == 0) && (strcmp(strdup(curr->artiste), strdup(artiste)) == 0)) {
            occ++;
        }
        curr = curr->suiv;
    }

    return occ;
}

Biblio *uniques (Biblio *B)
{
    Biblio *b = nouvelle_biblio();
    CellMorceau *curr = B->L;

    while (curr) {
        if (compte_nombre_morceaux_bibli(curr, B) == 1) insere(b, b->nE, strdup(curr->titre), strdup(curr->artiste));
        curr = curr->suiv;
    }

    return b;
}

CellMorceau * rechercheParNum(Biblio *B, int num)
{
	CellMorceau *curr = B->L;

    while (curr) {
        if (curr->num == num) {
            // On retourne le morceau
            printf("Un morceau correspondant a pu etre trouvé.\n");
            return creation_Morceau(curr->num, strdup(curr->titre), strdup(curr->artiste));
        }
        curr = curr->suiv;
    }
    
    // Aucun morceau n'a pu etre trouve
    printf("Aucun morceau n'a pu etre trouvé.\n");
    return NULL;
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	CellMorceau *curr = B->L;

    while (curr) {
        if (strcmp(strdup(curr->titre), titre) == 0) {
            // On retourne le morceau
            printf("Un morceau correspondant a pu etre trouvé.\n");
            return creation_Morceau(curr->num, strdup(curr->titre), strdup(curr->artiste));
        }
        curr = curr->suiv;
    }
    
    // Aucun morceau n'a pu etre trouve
    printf("Aucun morceau n'a pu etre trouvé.\n");
    return NULL;
}

Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	Biblio *b = nouvelle_biblio();
    CellMorceau *curr = B->L;

    while (curr) {
        if (strcmp(strdup(curr->artiste), artiste) == 0) insere(b, b->nE, strdup(curr->titre), strdup(curr->artiste));
        curr = curr->suiv;
    }

    return b;
}


void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	insere(B, B->nE, strdup(titre), strdup(artiste));
}

int supprimeMorceau(Biblio *B, int num)
{
	CellMorceau *curr = B->L;
	CellMorceau *temp;

	if (num == 0) {
		B->L = B->L->suiv;
		return 1;
	}

	while (curr) {
		if (curr->suiv->num == num) {
            CellMorceau *c = curr->suiv;
			curr->suiv = curr->suiv->suiv;
            free(c);
            B->nE--;

			return 1;
		}
		curr = curr->suiv;
	}

	return 0;
}