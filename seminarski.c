#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct bashKomande
{
    char tipKomande[5];
    char pomocniTekst[255];
} bash;

void ucitavanjeMenija()
{
    printf("\n\nDobrodosli\n---------------------\n");
    printf("Izaberite sta zelite da uradite:\n");
    printf("1. Dodavanje nove komande\n2. Ispisivanje celokupne skripte\n\n");
}

int main()
{
    struct bashKomande bash;
    int izborTipa, generalniIzbor;
    system("color 2");
    ucitavanjeMenija();
}
