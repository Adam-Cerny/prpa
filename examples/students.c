// Input:
// 2
// Petr 3 5 4 5
// Anna 2 1 2

// Output:
// Počet studentů: 2
// Průměrná známka: 3.75
// Nejlepší student: Petr (4.67)
// Nejhorší student: Anna (1.50)

// Studenti (seřazeno):
// Petr: 4.67
// Anna: 1.50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define ERROR 100
#define ERROR_MESSAGE "Error: Chybny vstup!\n"

typedef struct
{
    char jmeno[20];
    int *znamky;     // UKAZATEL na pole známek
    int pocetZnamek; // počet známek
    float prumer;    // průměr (pro třídění)
} Student;

int error(char *message, int code)
{
    fprintf(stderr, "%s", message);
    exit(code);
}

// priklad pouziti pomocne funkce error
// error(ERROR_MESSAGE, ERROR);

int main(int argc, char *argv[])
{
    int pocetStudentu;
    int ret = scanf("%i", &pocetStudentu);

    if (ret != 1)
    {
        error(ERROR_MESSAGE, ERROR);
    }

    if (pocetStudentu < 0)
    {
        error(ERROR_MESSAGE, ERROR);
    }

    Student *trida = (Student *)malloc(pocetStudentu * sizeof(Student));
    if (trida == NULL)
    {
        error(ERROR_MESSAGE, ERROR);
    }

    for (int i = 0; i < pocetStudentu; i++)
    {
        int ret2 = scanf("%s %d", trida[i].jmeno, &trida[i].pocetZnamek);

        if (ret2 < 2)
        {
            free(trida);
            error(ERROR_MESSAGE, ERROR);
        }

        // Alokace pole známek pro studenta
        trida[i].znamky = (int *)malloc(trida[i].pocetZnamek * sizeof(int));
        if (trida[i].znamky == NULL)
        {
            free(trida);
            error(ERROR_MESSAGE, ERROR);
        }

        // Čtení jednotlivých známek
        int soucetZnamek = 0;
        for (int j = 0; j < trida[i].pocetZnamek; j++)
        {
            if (scanf("%d", &trida[i].znamky[j]) != 1)
            {
                free(trida[i].znamky);
                free(trida);
                error(ERROR_MESSAGE, ERROR);
            }
            soucetZnamek += trida[i].znamky[j];
        }

        // Výpočet průměru pro studenta
        trida[i].prumer = (float)soucetZnamek / trida[i].pocetZnamek;
    }

    // Výpočet průměru všech studentů
    float soucetVsechZnamek = 0;
    int celkemZnamek = 0;
    for (int i = 0; i < pocetStudentu; i++)
    {
        for (int j = 0; j < trida[i].pocetZnamek; j++)
        {
            soucetVsechZnamek += trida[i].znamky[j];
            celkemZnamek++;
        }
    }
    float prumerVseho = soucetVsechZnamek / celkemZnamek;

    // Hledání nejlepšího a nejhoršího studenta
    int nejlepsi = 0;
    int nejhorsi = 0;
    for (int i = 0; i < pocetStudentu; i++)
    {
        if (trida[i].prumer > trida[nejlepsi].prumer)
        {
            nejlepsi = i;
        }
        if (trida[i].prumer < trida[nejhorsi].prumer)
        {
            nejhorsi = i;
        }
    }

    printf("Počet studentů: %i\n", pocetStudentu);
    printf("Průměrná známka: %.2f\n", prumerVseho);
    printf("Nejlepší: %s (%.2f)\n", trida[nejlepsi].jmeno, trida[nejlepsi].prumer);
    printf("Nejhorší: %s (%.2f)\n", trida[nejhorsi].jmeno, trida[nejhorsi].prumer);

    // Uvolnění paměti pro známky každého studenta
    for (int i = 0; i < pocetStudentu; i++)
    {
        free(trida[i].znamky);
    }

    free(trida);

    return 0;
}
