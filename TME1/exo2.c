#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define LONG 10

int* alloue_tableau(int n) {
    int* tab = malloc(n * sizeof(int));
    return tab;
}

void remplir_tableau(int* tab, int n, int V) {
    srand(time(NULL));
    int i;
    for (i = 0; i < n; i++) {
        tab[i] = (int)(rand()%V);
    }
}

void afficher_tab(int* tab, int n) {
    printf("[\t");
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\t",tab[i]);
    }
    printf("]\n\n");
}

int somme_diff_carres_v1(int *tab, int n) {
    int i, j;
    int valeur = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            valeur = valeur + pow(tab[i] - tab[j], 2);
        }
    }

    return valeur;
}

int somme_diff_carres_v2(int *tab, int n) {
    int i, j;
    int val1 = 0; // Permet de calculer la somme des termes deux a deux au carré
    int val2 = 0; // Permet de calculer le carré de la somme des termes

    for (i = 0; i < n; i++) {
        val2 = val2 + tab[i];
        for (j = 0; j < n; j++) {
            val1 = val1 + (pow(tab[i], 2) + pow(tab[j], 2));
        }
    }

    return val1 - 2 * pow(val2, 2);

}

// Partie Matrices

int **alloue_matrice(int size) {
    int **mat = (int**)malloc(sizeof(int*) * size);
    int i;
    for (i = 0; i < size; i++) {
        mat[i] = (int*)malloc(sizeof(int) * size);
    }
    return mat;
}

void remplir_matrice(int** mat, int size, int n) {
    srand(time(NULL));
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            mat[i][j] = (int)(rand()%n);
        }
    }
}

void afficher_matrice(int** mat, int size) {
    int i;
    printf("\n");
    for (i = 0; i < size; i++) {
        afficher_tab(mat[i], size);
    }
}

// Fonctions allant permettre la recherche dans les matrices

int is_in_list(int *tab, int length, int value) {
    int i = 0;

    while (tab[i] != (-1)) {
        if (tab[i] == value) return 1;
        i++;
    }

    return 0;
}

int val_diff_v1(int** mat, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            int val = mat[i][j];
            int x, y;
            for (x = 0; x < size; x++){
                for (y = 0; y < size; y++) {
                    if ((i != x) && (j != y)) {
                        if (mat[x][j] == val) {
                            printf("Deux éléments du tableau sont égaux.\nValeur répétée: %d\n", val);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    printf("Toutes les valeurs de la matrice sont différentes l'un de l'autre.\n");
    return 1;
}

int val_diff_v2(int** mat, int size) {
    int* tab = malloc(size * size * sizeof(int));
    int m;
    for (m = 0; m < size * size; m++) tab[m] = -1;
    int c = 0;
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (is_in_list(tab, size * size, mat[i][j]) == 1) {
                printf("Deux éléments du tableau sont égaux.\nValeur répétée: %d\n", mat[i][j]);
                return 0;
            }
            else {
                tab[c] = mat[i][j];
                c++;
            }
        }
    }
    printf("Toutes les valeurs de la matrice sont différentes l'un de l'autre.\n");
    //afficher_tab(tab, size * size);
    return 1;
}

// Variables

#define N 10
#define V 10

int main(void) {
    /*
    
    // Création du tableau d'entiers (uniquement modifier les valeurs au-dessus)

    int* tab = alloue_tableau(N);
    remplir_tableau(tab, N, V);
    //afficher_tab(tab, N);

    //Création des outils de calcul du temps mis par le CPU*/

    clock_t temps_initial ; // Temps initial en micro-secondes
    clock_t temps_final ; // Temps final en micro-secondes
    double temps_cpu ; // Temps total en secondes

    // Utilisation des fonctions et affichages des temps mis par le CPU
    
    /*int val;

    temps_initial = clock ();
    val = somme_diff_carres_v1(tab, N);
    // printf("Valeur de retour = %d\n\n",val);
    temps_final = clock ();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC ;
    printf("METHODE V1\nTaille du tableau = %d\nTemps mis par le CPU = %f secondes\n\n",N, temps_cpu );

    temps_initial = clock ();
    val = somme_diff_carres_v2(tab, N);
    //printf("Valeur de retour = %d\n\n",val);
    temps_final = clock ();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC ;
    printf("METHODE V2\nTaille du tableau = %d\nTemps mis par le CPU = %f secondes\n\n",N, temps_cpu );

    // On automatise l'écriture sur un fichier des temps d'exécution pour une taille de tableau précise

    int taille = 500;
    int* tableau = alloue_tableau(taille);
    remplir_tableau(tableau, taille, 100);
    int i;
    FILE* doc = fopen("01_sortie_vitesse.txt", "w+");
    for (i = 1; i <= taille; i++) {
        temps_initial = clock ();
        int value = somme_diff_carres_v1(tableau, i);
        temps_final = clock ();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC ;
        fprintf(doc, "%d %f -\n", i, temps_cpu);
    }
    fclose(doc);

    doc = fopen("02_sortie_vitesse.txt", "w+");
    for (i = 1; i <= taille; i++) {
        temps_initial = clock ();
        int value = somme_diff_carres_v2(tableau, i);
        temps_final = clock ();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC ;
        fprintf(doc, "%d - %f\n", i, temps_cpu);
    }
    fclose(doc);

    free(tableau);

    // Fin du main

    */

    // Tests sur les matrices

    #define SIZE 5
    #define MAX_V 50

    // Ecriture sur fichiers des temps de recherche pour matrices

    int i;
    FILE* doc1 = fopen("01_matrice_vitesse.txt", "w+");
    FILE* doc2 = fopen("02_matrice_vitesse.txt", "w+");
    for (i = 1; i <= 100; i++) {
        int** mat = alloue_matrice(i);
        remplir_matrice(mat, i, 10000000);
        temps_initial = clock ();
        int v = val_diff_v1(mat, i);
        temps_final = clock ();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC ;
        fprintf(doc1, "%d %f -\n", i, temps_cpu);

        temps_initial = clock ();
        v = val_diff_v1(mat, i);
        temps_final = clock ();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC ;
        fprintf(doc2, "%d - %f\n", i, temps_cpu);

        free(mat);
    }
    fclose(doc1);
    fclose(doc2);

    return 0;
}