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
	c->suiv = NULL;

	if (B->T[hach] == NULL) {
		B->T[hach] = c;
	}
	else {
		CellMorceau *curr = B->T[hach];
		while (curr->suiv != NULL) {
			curr = curr->suiv;
		}
		curr->suiv = c;
	}

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

// Fonctions servant à la fonction "uniques"

int nb_occurences(CellMorceau *list, char *titre, char *artiste) {
	int occ = 0;
	while (list) {
		if ((strcmp(artiste, list->artiste) == 0) && (strcmp(titre, list->titre) == 0)) occ++;
		list = list->suiv;
	}
	return occ;
}

Biblio *uniques (Biblio *B)
{
	Biblio *nB = nouvelle_biblio();

    int i;
	for (i = 0; i < B->m; i++) {
		CellMorceau *curr = B->T[i];
		while (curr) {
			if (nb_occurences(B->T[i], curr->titre, curr->artiste) == 1) insere(nB, curr->num, curr->titre, curr->artiste);
			curr = curr->suiv;
		}
	}

	return nB;
}

// Fin des fonctions servant à "uniques"

CellMorceau *rechercheParNum(Biblio *B, int num)
{
	int i;
	for (i = 0; i < B->m; i++) {
		CellMorceau *curr = B->T[i];
		while (curr) {
			if (curr->num == num) {
				CellMorceau *c = (CellMorceau *)malloc(sizeof(CellMorceau));
				c->num = curr->num;
				c->cle = curr->cle;
				c->titre = curr->titre;
				c->artiste = curr->artiste;
				c->suiv = NULL;

				return c;
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
				c->cle = curr->cle;
				c->titre = curr->titre;
				c->artiste = curr->artiste;
				c->suiv = NULL;

				return c;
			}
			curr = curr->suiv;
		}
	}

	return NULL;
}


Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	Biblio *nB = nouvelle_biblio();

	int keyF = fonction_cle(artiste);
	CellMorceau *curr = B->T[keyF];
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
		if (curr->num == num) {
			CellMorceau *tmp = curr;
			B->T[i] = tmp->suiv;
			free(tmp);
			return 1;
		}
		else {
			CellMorceau *tmp;
			while (curr && curr->num != num) {
				tmp = curr;
				curr = curr->suiv;
			}
			if (curr->num == num) {
				tmp->suiv = curr->suiv->suiv;
				free(curr);
				return 1;
			}
		}
		
	}

	return 0;
}





































