#include "biblio_arbrelex.h"

Biblio *nouvelle_biblio(void) 
{
   Biblio *B = (Biblio *)malloc(sizeof(Biblio));
   B->nE = 0;
   B->A = NULL;
   return B;
}

void libere_biblio(Biblio *B)
{
    free(B);
}

// Recherche si un artiste est présent
void recherche_artiste(Biblio *B, char *artiste) {
	int i = 0; // Indice lisant nom
	Noeud *cour = B->A; // Pointeur courant
	Noeud *prec = cour; // Pointeur sur la valeur precedant cour

	while ((cour != NULL) && (artiste[i] != '\0')) {
		prec = cour;

		if (cour->car == artiste[i]) { // On a lu le bon caractere
			cour = cour->car_suiv;
			i++;
		}
		else { // On tente un caractere alternatif
			cour = cour->liste_car;
		}
	}

	if (artiste[i] == '\0'){
		printf("La chaine %s est présente.\n", artiste);
	}
	else {
		printf("La chaine %s est présente jusqu'au caractère numero %d.\n", artiste, i - 1);
		if (artiste[i-1] == prec->car) {
			printf("La suite de la chaine peut etre inseree a la suite de la lettre %c.\n", prec->car);
		}
		else {
			printf("La suite de la chaine peut etre en alternative a la lettre %c.\n", prec->car);
		}
	}
}

void insere(Biblio *B, int num, char *titre, char *artiste)
{
    int i = 0; // Indice lisant nom

	if (B->A == NULL) {
		Noeud *n = (Noeud *)malloc(sizeof(Noeud));
		n->car = artiste[0];
		n->car_suiv = NULL;
		n->liste_car = NULL;
		n->liste_morceaux = NULL;
		B->A = n;
	}

	Noeud *cour = B->A; // Pointeur courant
	Noeud *prec = cour; // Pointeur sur la valeur precedant cour

	while ((cour != NULL) && (artiste[i] != '\0')) {
		prec = cour;

		if (cour->car == artiste[i]) { // On a lu le bon caractere
			cour = cour->car_suiv;
			i++;
		}
		else { // On tente un caractere alternatif
			cour = cour->liste_car;
		}
	}

	if (artiste[i] == '\0') {
		CellMorceau *morc = (CellMorceau *)malloc(sizeof(CellMorceau));
		morc->num = num;
		morc->titre = strdup(titre);
		morc->artiste = strdup(artiste);
		morc->suiv = NULL;
		
		CellMorceau *tete = prec->liste_morceaux;
		if (tete != NULL) {
			while (tete->suiv != NULL) {
				tete = tete->suiv;
			}
			tete->suiv = morc;
		}
		else {
			prec->liste_morceaux = morc;
		}

		B->nE++;
	}

	else {
		Noeud *n = (Noeud *)malloc(sizeof(Noeud));
		n->car = artiste[i];
		n->car_suiv = NULL;
		n->liste_car = NULL;
		n->liste_morceaux = NULL;

		if (artiste[i-1] == prec->car) {
			prec->car_suiv = n;
			insere(B, num, titre, artiste);
		}
		else {
			prec->liste_car = n;
			insere(B, num, titre, artiste);
		}
	}

	return;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("|A| %8d | %-32.32s | %-32.32s |A|\n", cell->num, cell->titre, cell->artiste);
}

void afficheNoeud(Noeud *N) {
	if (N == NULL) return;

	CellMorceau *c = N->liste_morceaux;
	while (c) {
		afficheMorceau(c);
		c = c->suiv;
	}

	afficheNoeud(N->liste_car);
	afficheNoeud(N->car_suiv);
}

void affiche(Biblio *B)
{
    afficheNoeud(B->A);
}



// Fonction servants à la fonction 'uniques'

int compte_nombre_morceaux(CellMorceau *C) {
	char *titre = strdup(C->titre);
	char *artiste = strdup(C->artiste);
	int it = 0;

	CellMorceau *curr = C;
	while (curr) {
		if (strcmp(titre, curr->titre) == 0) it++;
		curr = curr->suiv;
	}

	return it;
}

void cherche_uniques(Noeud *N, Biblio *B) {
	if (N == NULL) return;

	CellMorceau *c = N->liste_morceaux;
	while (c) {
		if (compte_nombre_morceaux(c) == 1) insere(B, c->num, strdup(c->titre), strdup(c->artiste));
		c = c->suiv;
	}

	cherche_uniques(N->liste_car, B);
	cherche_uniques(N->car_suiv, B);
}

Biblio *uniques (Biblio *B)
{
	Biblio *RB = nouvelle_biblio();
	cherche_uniques(B->A, RB);
	return RB;
}

// Fin des fonctions servant à la fonction 'uniques'



// Fonctions servant à la fonction 'rechercheParNum'

void cherche_num(Noeud *N, CellMorceau *C, int num) {
	if ((N == NULL) || (C->titre != NULL)) return;

	CellMorceau *curr = N->liste_morceaux;
	while (curr) {
		if (curr->num == num) {
			C->num = num;
			C->titre = strdup(curr->titre);
			C->artiste = strdup(curr->artiste);
			C->suiv = NULL;
			return;
		}
		curr = curr->suiv;
	}

	cherche_num(N->liste_car, C, num);
	cherche_num(N->car_suiv, C, num);
}

CellMorceau *rechercheParNum(Biblio *B, int num)
{
	CellMorceau *C = (CellMorceau *)malloc(sizeof(CellMorceau));
	cherche_num(B->A, C, num);
	if (C->titre != NULL) return C;
	else return NULL;
}

// Fin des fonctions servant à la fonction 'rechercheParNum'




// Fonctions servant à la fonction rechercheParTitre

void cherche_titre(Noeud *N, CellMorceau *C, char *titre) {
	if ((N == NULL) || (C->titre != NULL)) return;

	CellMorceau *curr = N->liste_morceaux;
	while (curr) {
		if (strcmp(curr->titre, titre) == 0) {
			C->num = curr->num;
			C->titre = strdup(curr->titre);
			C->artiste = strdup(curr->artiste);
			C->suiv = NULL;
			return;
		}
		curr = curr->suiv;
	}

	cherche_titre(N->liste_car, C, titre);
	cherche_titre(N->car_suiv, C, titre);
}

CellMorceau *rechercheParTitre(Biblio *B, char * titre)
{
	CellMorceau *C = (CellMorceau *)malloc(sizeof(CellMorceau));
	cherche_titre(B->A, C, titre);
	if (C->titre != NULL) return C;
	else return NULL;
}

// Fin des fonctions servant à la fonction rechercheParTitre




Biblio *extraireMorceauxDe(Biblio *B, char * artiste)
{
	int i = 0; // Indice lisant nom
	Noeud *cour = B->A; // Pointeur courant
	Noeud *prec = cour; // Pointeur sur la valeur precedant cour

	while ((cour != NULL) && (artiste[i] != '\0')) {
		prec = cour;

		if (cour->car == artiste[i]) { // On a lu le bon caractere
			cour = cour->car_suiv;
			i++;
		}
		else { // On tente un caractere alternatif
			cour = cour->liste_car;
		}
	}

	Biblio *rB = nouvelle_biblio();

	if (artiste[i] == '\0'){
		CellMorceau *c = prec->liste_morceaux;
		while (c) {
			insere(rB, c->num, strdup(c->titre), strdup(c->artiste));
			c = c->suiv;
		}
	}
	else {
		printf("L'artiste n'a pas pu etre trouvé dans la base de données.\n");
	}

	return B;
}


void insereSansNum(Biblio *B, char *titre, char *artiste)
{
	insere(B, B->nE, strdup(titre), strdup(artiste));
}


// Fonctions servant à la fonction 'supprimeMorceau'

void supprime_num(Noeud *N, int num, int *r) {
	if (N == NULL) return;

	CellMorceau *curr = N->liste_morceaux;
	if (curr->num == num) {
		N->liste_morceaux = curr->suiv;
		free(curr);
		*r = 1;
	}
	else {
		while (curr->suiv->num != num) {
			curr = curr->suiv;
		}

		CellMorceau *tmp = curr->suiv; 
		if (tmp != NULL && tmp->num == num) {
			curr->suiv = tmp->suiv;
			free(tmp);
			*r = 1;
		}
	}

	supprime_num(N->liste_car, num, r);
	supprime_num(N->car_suiv, num, r);
}

int supprimeMorceau(Biblio *B, int num)
{
	int r = 0;
	supprime_num(B->A, num, &r);
	if (r == 1) B->nE++;

	return r; // Si r est égal à 1, alors la suppression a eu lieu. Sinon, il n y a pas eu de suppression
}

// Fin des fonctions servant à la fonction 'supprimeMorceau'
