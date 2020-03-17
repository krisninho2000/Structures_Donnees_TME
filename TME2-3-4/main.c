#include "biblio.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


void menu()
{
	printf("Menu :\n");
	printf("0-Sortie\n");
	printf("1-Affichage\n");
	printf("2-Recherche morceaux uniques\n");
	printf("3-Recherche morceau par titre\n");
	printf("Votre choix : ");
}

/*
int main(int argc, const char *argv[]) {

	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return 1;
	}

	Biblio *B = nouvelle_biblio();
	B = charge_n_entrees(argv[1], 10000);

	clock_t temps_initial ; // Temps initial en micro-secondes
    clock_t temps_final ; // Temps final en micro-secondes
    double temps_cpu = 0.0; // Temps total en secondes

	int liste_num[5] = {3942, 6138, 236, 5844, 2771};
	char *liste_artiste[5] = {"DJ Quik", "Toby Keith Duet With Willie Nelson", "Lil Jon & The East Side Boyz Featuring Usher & Ludacris", "Manfred Mann", "The Danleers"};
	char *liste_titre[5] = {"Jus Lyke Compton", "Beer For My Horses", "Lovers And Friends", "Do Wah Diddy Diddy", "One Summer Night"};

	int i;
	for (i = 0; i < 5; i++) {
		int num = liste_num[i];
		temps_initial = clock();
		CellMorceau *c = rechercheParNum(B, num);
		temps_final = clock();
		temps_cpu = (double)(temps_final - temps_initial) + temps_cpu;
	}

	printf("Temps total (Recherche par Numero) - %lf\n", temps_cpu / CLOCKS_PER_SEC);
	temps_cpu = 0.0;

	for (i = 0; i < 5; i++) {
		char *titre = liste_titre[i];
		temps_initial = clock();
		CellMorceau *c = rechercheParTitre(B, titre);
		temps_final = clock();
		temps_cpu = (double)(temps_final - temps_initial) + temps_cpu;
	}

	printf("Temps total (Recherche par Titre) - %lf\n", temps_cpu / CLOCKS_PER_SEC);
	temps_cpu = 0.0;

	for (i = 0; i < 5; i++) {
		char *artiste = liste_artiste[i];
		temps_initial = clock();
		Biblio *nb = extraireMorceauxDe(B, artiste);
		temps_final = clock();
		temps_cpu = (double)(temps_final - temps_initial) + temps_cpu;
	}

	printf("Temps total (Recherche par Artiste) - %f\n", temps_cpu / CLOCKS_PER_SEC);
	free(B);

	return 0;
}
*/

/*
int main(int argc, const char *argv[]) {

	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return 1;
	}

	printf("# taille, temps\n");

	clock_t temps_initial ; // Temps initial en micro-secondes
    clock_t temps_final ; // Temps final en micro-secondes
    double temps_cpu = 0.0; // Temps total en secondes
	
	Biblio *b1 = charge_n_entrees(argv[1], 10000);
	temps_initial = clock();
	Biblio *r1 = uniques(b1);
	temps_final = clock();
	temps_cpu = (double)(temps_final - temps_initial);
	affiche(r1);
	free(b1);
	free(r1);

	printf("10000 %f\n", temps_cpu / CLOCKS_PER_SEC);

	Biblio *b2 = charge_n_entrees(argv[1], 30000);
	temps_initial = clock();
	Biblio *r2 = uniques(b2);
	temps_final = clock();
	temps_cpu = (double)(temps_final - temps_initial);
	free(b2);
	free(r2);

	printf("30000 %f\n", temps_cpu / CLOCKS_PER_SEC);

	Biblio *b3 = charge_n_entrees(argv[1], 50000);
	temps_initial = clock();
	Biblio *r3 = uniques(b3);
	temps_final = clock();
	temps_cpu = (double)(temps_final - temps_initial);
	free(b3);
	free(r3);

	printf("50000 %f\n", temps_cpu / CLOCKS_PER_SEC);

	Biblio *b4 = charge_n_entrees(argv[1], 100000);
	temps_initial = clock();
	Biblio *r4 = uniques(b4);
	temps_final = clock();
	temps_cpu = (double)(temps_final - temps_initial);
	free(b4);
	free(r4);

	printf("100000 %f\n", temps_cpu / CLOCKS_PER_SEC);

	Biblio *b5 = charge_n_entrees(argv[1], 150000);
	temps_initial = clock();
	Biblio *r5 = uniques(b5);
	temps_final = clock();
	temps_cpu = (double)(temps_final - temps_initial);
	free(b5);
	free(r5);

	printf("150000 %f\n", temps_cpu / CLOCKS_PER_SEC);

	Biblio *b6 = charge_n_entrees(argv[1], 200000);
	temps_initial = clock();
	Biblio *r6 = uniques(b6);
	temps_final = clock();
	temps_cpu = (double)(temps_final - temps_initial);
	free(b6);
	free(r6);

	printf("200000 %f\n", temps_cpu / CLOCKS_PER_SEC);

	Biblio *b7 = charge_n_entrees(argv[1], 250000);
	temps_initial = clock();
	Biblio *r7 = uniques(b7);
	temps_final = clock();
	temps_cpu = (double)(temps_final - temps_initial);
	free(b7);
	free(r7);

	printf("250000 %f\n", temps_cpu / CLOCKS_PER_SEC);

	Biblio *b8 = charge_n_entrees(argv[1], 300000);
	temps_initial = clock();
	Biblio *r8 = uniques(b8);
	temps_final = clock();
	temps_cpu = (double)(temps_final - temps_initial);
	free(b8);
	free(r8);

	printf("300000 %f\n", temps_cpu / CLOCKS_PER_SEC);

	return 0;
}
*/

int main(int argc, const char *argv[])
{

	if (argc != 3) {
		printf("Erreur format: %s <NomFichierBiblio.txt> <NbLigneALire>", argv[0]);
		return 1;
	}
	
	const char *nomfic = argv[1];
	int nlignes = atoi(argv[2]);
	char titre[249];
	printf("Lecture :\n");
	Biblio *biblio = charge_n_entrees(nomfic, nlignes);
	
	int ch;
	do {
		menu();
		int lus = scanf("%d", &ch);
		if (lus == 0)
			ch = 0;
		
		switch(ch) {
			case 1 :
				printf("Affichage\n");
				affiche(biblio);
				break;
			case 2:
				{
					Biblio *Bunique = uniques(biblio);
					affiche(Bunique);
					libere_biblio(Bunique);
					break;
				}
			case 3 :
				{
					printf("Saisir le titre du morceau :\n");
					scanf(" %248[^\n]", titre);
					CellMorceau * r = rechercheParTitre(biblio, titre);
					if (r == NULL) printf("Aucun morceau de titre : %s!!!\n", titre);
					else afficheMorceau(r);
					break;
				}
			default :
				ch = 0;
				break;
		
		}
		
	} while (ch != 0);
	
	libere_biblio(biblio);
	printf("Au revoir\n");
	
	return 0;
}