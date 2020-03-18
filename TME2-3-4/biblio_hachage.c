#include "biblio_hachage.h"

// Fonctions de hachage

int fonction_cle(char *artiste) {
	int i;
	int cpt = 0;
	for (i = 0; i < strlen(artiste); i++) {
		char c = artiste[i];
		cpt = cpt + (int) c;
	}
	return cpt;
}

unsigned int fonction_hachage(unsigned int cle, int m) {
	return floor(m * (cle * A - floor(cle * A)));
}

// Fonctions de structure

Biblio *nouvelle_biblio(void) 
{
   Biblio *B = (Biblio *)malloc(sizeof(Biblio));
   B->nE = 0;
   B->m = TAILLE_TABLE;
   B->T = (CellMorceau **)malloc(sizeof(CellMorceau *) * B->m);
   return B;
}

void libere_biblio(Biblio *B)
{
    int i;
	for (i = 0; i < B->m; i++) {
		CellMorceau *curr = B->T[i];
		while (curr) {
			CellMorceau *tmp = curr;
			curr = curr->suiv;
			free(tmp);
		}
	}
	free(B->T);
	free(B);
}


void insere(Biblio *B, int num, char *titre, char *artiste)
{
	int key = fonction_cle(artiste);
	int hach = fonction_hachage(key, B->m);

	CellMorceau *c = (CellMorceau *)malloc(sizeof(CellMorceau));
	c->num = num;
	c->cle = key;
	c->artiste = strdup(artiste);
	c->titre = strdup(titre);
	c->suiv = B->T[hach];
	B->T[hach] = c;

    B->nE++;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("§§ %8d § %-32.32s § %-32.32s §§\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B)
{
    int i;
	for (int i = 0; i < B->m; i++) {
		CellMorceau *curr = B->T[i];
		while (curr) {
			afficheMorceau(curr);
			curr = curr->suiv;
		}
	}
	printf("\nNombre de morceaux - %d\n", B->nE);
}

Biblio *uniques (Biblio *B)
{
	Biblio *nB = nouvelle_biblio();

    unsigned int i;
	for (i = 0; i < B->m; i++) {
		CellMorceau *curr = B->T[i];
		if (curr) {
			while (curr) {
				int occ = 0;
				CellMorceau *alt = B->T[i];
				while (alt) {
					if ((strcmp(alt->titre, curr->titre) == 0) && (strcmp(alt->artiste, curr->artiste) == 0)) occ++;
					alt = alt->suiv;
				}
				if (occ == 1) insere(nB, nB->nE, curr->titre, curr->artiste);
				curr = curr->suiv;
			}
		}
	}

	return nB;
}

CellMorceau *rechercheParNum(Biblio *B, int num)
{
	int i;
	for (i = 0; i < B->m; i++) {
		CellMorceau *curr = B->T[i];
		while (curr) {
			if (curr->num == num) {
				return curr;
			}
			curr = curr->suiv;
		}
	}

	return NULL;
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	int i;
	for (i = 0; i < B->m; i++) {
		CellMorceau *curr = B->T[i];
		while (curr) {
			if (strcmp(titre, curr->titre) == 0) {
				CellMorceau *c = (CellMorceau *)malloc(sizeof(CellMorceau));
				c->num = curr->num;
				return curr;
			}
			curr = curr->suiv;
		}
	}

	return NULL;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	Biblio *nB = nouvelle_biblio();

	unsigned int keyF = fonction_cle(artiste);
	unsigned int hash = fonction_hachage(keyF, B->m);

	CellMorceau *curr = B->T[hash];
	while (curr) {
		insere(nB, curr->num, curr->titre, curr->artiste);
		curr = curr->suiv;
	}

	return nB;
}

void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	insere(B, B->nE, titre, artiste);
}


int supprimeMorceau(Biblio *B, int num)
{
	int i;
	for (i = 0; i < B->m; i++) {
		CellMorceau *curr = B->T[i];
		
		if (curr) {
			if (curr->num == num) {
				B->T[i] = curr->suiv;
				free(curr->titre);
				free(curr->artiste);
				free(curr);
				B->nE--;
				return 1;
			}

			while (curr->suiv && curr->suiv->num != num) {
				curr = curr->suiv;
			}

			if (curr->suiv != NULL) {
				CellMorceau *tmp = curr->suiv;
				curr->suiv = tmp->suiv;
				free(tmp->titre);
				free(tmp->artiste);
				free(tmp);
				B->nE--;
				return 1;
			}
		}
	}

	return 0;
}


