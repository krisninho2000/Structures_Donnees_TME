#include "biblio.h"

// FONCTIONS

Biblio *charge_n_entrees(const char *nom_fichier, int n) 
{
    FILE *doc = fopen(nom_fichier, "r+");
    Biblio *b = nouvelle_biblio();
    int it = 0;

    while ((end_of_file(doc) == 0) && (it < n)) {
        int num, sizeTitle, sizeArtist;
        char *title = (char*)malloc(sizeof(char) * 100);
        char *artist = (char*)malloc(sizeof(char) * 100);

        parse_int(doc, &num);
        parse_char(doc, '\t');

        parse_string(doc, &title, &sizeTitle, '\t');
        parse_char(doc, '\t');

        parse_string(doc, &artist, &sizeArtist, '\n');
        parse_char(doc, '\n');

        insere(b, num, title, artist);

        it++;
    }

    fclose(doc);
    return b;
}
