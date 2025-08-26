#include <stdio.h>   // standardna biblioteka za ulaz i izlaz
#include <string.h>  // biblioteka za stringove
#include <stdlib.h>  // korisne alatke
#include <stdbool.h> // biblioteka za booleane

struct bashKomande
{
    char tipKomande[5];
    char komanda[255];
} bash;

void ucitavanjeIzboraTipova()
{
    printf("\n\nIzaberite tip komande:\n");
    printf("1. SuperUser (sudo)\n2. RegularUser\n\n");
}

void ucitavanjeMenija() // funkcija za ucitavanje menija
{
    printf("\n\nDobrodosli\n---------------------\n");
    printf("Izaberite sta zelite da uradite:\n");
    printf("1. Dodavanje nove komande\n2. Ispisivanje celokupne skripte\n\n");
}

char *crvenaStampa(const char *tekst) // funkcija za stampu u crvenoj boji
{
    char crvenaPocetak[] = "\033[0;31m";                                         // crveni tekst pocetni deo
    char crvenaKraj[] = "\033[0m";                                               // crveni tekst zavrsni deo
    int duzina = strlen(crvenaPocetak) + strlen(tekst) + strlen(crvenaKraj) + 1; // izracunavanje duzine kompletnog stringa
    char *crveniTekst = (char *)malloc(duzina * sizeof(char));                   // alociranje memorije varijable crveniTekst na osnovu duzine stringa i velicine karaktera

    if (crveniTekst == NULL)
    {
        printf("Greska pri alokaciji memorije!");
    }
    snprintf(crveniTekst, duzina, "%s%s%s", crvenaPocetak, tekst, crvenaKraj);

    return crveniTekst;
}

void unosUserKomandi(FILE *imeFajla)
{
    printf("Unesite vasu komandu bez prefixa (sudo):\n");
    fgets(bash.komanda, sizeof(bash.komanda), stdin);
    printf("Vasa komanda: %s", bash.komanda);
    fprintf(imeFajla, "%s", bash.komanda);
}

void unosSuperUserKomandi(FILE *imeFajla)
{
    strcpy(bash.tipKomande, "sudo");
    printf("%s", bash.tipKomande);
    printf("Unesite vasu komandu bez prefixa (sudo):\n");
    fgets(bash.komanda, sizeof(bash.komanda), stdin);
    printf("Vasa komanda: %s %s", bash.tipKomande, bash.komanda);
    fprintf(imeFajla, "%s %s", bash.tipKomande, bash.komanda);
}

int main()
{
    int izborTipa, generalniIzbor;
    bool stanjeMenija = true;
    bool stanjeMenijaTip = false;

    while (stanjeMenija)
    {
        stanjeMenija = true;
        ucitavanjeMenija();
        printf("\nVas izbor: ");
        scanf(" %d", &generalniIzbor);
        switch (generalniIzbor)
        {
        case 1:
        {
            FILE *fajlKomandi;
            fajlKomandi = fopen("komande.txt", "a+");
            if (fajlKomandi == NULL)
            {
                system("cls");
                char *greska = crvenaStampa("\nGreska pri otvaranju datoteke.\nPritisnite taster da bi se vratili na pocetak\n");
                if (greska != NULL)
                {
                    printf("%s", greska);
                    free(greska);
                }
            }
            else
            {
                stanjeMenijaTip = true;
                while (stanjeMenijaTip)
                {
                    ucitavanjeIzboraTipova();
                    printf("\nVas izbor: ");
                    scanf(" %d", &izborTipa);

                    switch (izborTipa)
                    {
                    case 1:
                    {
                        unosSuperUserKomandi(fajlKomandi);
                        fclose(fajlKomandi);
                        stanjeMenijaTip = false;
                        izborTipa = 0;
                        break;
                    }
                    case 2:
                    {
                        unosUserKomandi(fajlKomandi);
                        fclose(fajlKomandi);
                        stanjeMenijaTip = false;
                        izborTipa = 0;
                        break;
                    }
                    default:
                    {
                        break;
                    }
                    }
                }
            }
            break;
        }
        default:
        {
            printf("Uneli ste pogresan broj");
            getchar();

            break;
        }
        }
    }
}