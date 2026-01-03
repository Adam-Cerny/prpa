#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 25

#define ERROR_NUMBER 100
#define ERROR_MESSAGE "Error: Chyba histogramu!"

// pomocna funkce pro vypis chybove hlasky a ukonceni programu
int error(char *message, int code)
{
    fprintf(stderr, "%s", message);
    exit(code);
}

// funkce pro nacteni prvniho cisla (poctu sloupcu histogramu)
int nacteniPrvnihoCisla()
{
    int prvniCislo;
    if (scanf("%d", &prvniCislo) != 1)
    {
        error(ERROR_MESSAGE, ERROR_NUMBER);
    }
    return prvniCislo;
}

// funkce pro nacteni neomezeneho poctu cisel
int *nacteniCisel(int *pocet)
{
    // ukazatel na dynamicke pole, zatim prazdny
    int *cisla = NULL;
    // pomocna promenna pro kapacitu pole
    int kapacita = 0;
    // promenna pro nactene cislo
    int cislo;
    // ukazatel na promennou pocet, ktera je mimo funkci
    *pocet = 0;

    // varianta B: prvni cislo (pocet sloupcu) nacita main(), zde uz jen data

    // cte cisla do EOF
    while (scanf("%d", &cislo) == 1) 
    {
        // kontrola plnosti pole, je-li plne, tak ho zvetsime
        if (*pocet >= kapacita) 
        {
            // pokud jeste pole zvetseno nebylo, nastavime pocatecni kapacitu na 5
            if (kapacita == 0)
            {
                kapacita = 5;
            }
            // pokud pole jiz melo nejake prvky, zdvojime jeho kapacitu
            else 
            {
                kapacita *= 2;
            }
            // presuneme pole na novou adresu s vetsi kapacitou
            cisla = realloc(cisla, kapacita * sizeof(int));
        }

        // pricteme nactene cislo do pole
        cisla[(*pocet)++] = cislo;
    }
    
    return cisla;
}

// pomocna funkce pro porovnani dvou cisel, pouzita pro quicksort, jde o to pouze zjistit znamenko rozdilu
int porovnej(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

float vypocitejMedian(int *cisla, int pocet)
{
    float median = 0.0;

    // radime cisla pomoci quicksortu
    qsort(cisla, pocet, sizeof(int), porovnej);

    // vypocet medianu
    // pokud je pocet cisel lichy, vezmeme prostredni cislo
    if (pocet % 2 == 1) 
    {
        median = cisla[pocet / 2];
    } 
    // pokud je pocet cisel sudy, vezmeme prumer dvou prostrednich cisel
    else 
    {
        median = (cisla[(pocet / 2) - 1] + cisla[pocet / 2]) / 2.0;
    }
    
    return median;
}

int zjistiPocetCisel(int *cisla, int pocet)
{
    return pocet;
}

int najdiMin(int *cisla, int pocet)
{
    // inicializace minima prvnim prvkem pole
    int min = cisla[0];
    // prochazeni pole a hledani minima
    for (int i = 1; i < pocet; i++) 
    {
        if (cisla[i] < min) 
        {
            min = cisla[i];
        }
    }
    return min;
}

int najdiMax(int *cisla, int pocet)
{
    // inicializace maxima prvnim prvkem pole
    int max = cisla[0];
    // prochazeni pole a hledani maxima
    for (int i = 1; i < pocet; i++) 
    {
        if (cisla[i] > max) 
        {
            max = cisla[i];
        }
    }
    return max;
}

// funkce pro vypis histogramu 
void vypisHistogram(int *cisla, int pocet, int n, int min, int max)
{
    // vypocet velikosti binu 
    double rozsah = max - min;
    double velikostBinu = rozsah / n;

    // alokace pole pro frekvence
    int *biny = (int *)calloc(n, sizeof(int));
    if (biny == NULL)
    {
        error(ERROR_MESSAGE, ERROR_NUMBER);
    }

    int maxFrekvence = 0;

    // naplneni binu
    for (int j = 0; j < pocet; j++)
    {   
        // vypocet indexu binu pro cislo cisla[j]
        double indexFloat = (cisla[j] - min) / velikostBinu;
        // zaokrouhleni dolu na cele cislo
        int index = (int)indexFloat;

        // osetreni hranic
        if (index < 0) 
        {
            index = 0;
        }

        if (index >= n) 
        {
            index = n - 1;
        }

        // zvyseni frekvence daneho binu
        biny[index]++;
        if (biny[index] > maxFrekvence)
        {
            maxFrekvence = biny[index];
        }
    }

    // vykresleni histogramu 
    for (int i = 0; i < n; i++)
    {
        double dolni_hranice = min + i * velikostBinu;
        double horni_hranice = min + (i + 1) * velikostBinu;

        int delka = 0;
        if (maxFrekvence > 0)
        {
            delka = (int)((biny[i] * MAX_LENGTH) / maxFrekvence);
        }

        if (i < n - 1)
        {
            printf("%5.1f - %5.1f |", dolni_hranice, horni_hranice);
        }
        else
        {
            printf("%5.1f - %5.1f |", dolni_hranice, (double)max);
        }

        for (int s = 0; s < delka; s++)
        {
            printf("=");
        }
        printf("\n");
    }

    free(biny);
}

int main(void)
{
    int pocet = 0;
    
    // nacitani poctu sloupcu histogramu (varianta B)
    int n = nacteniPrvnihoCisla();
    if (n <= 0)
    {
        error(ERROR_MESSAGE, ERROR_NUMBER);
    }
    
    // nacteni zbylych cisel (datova rada)
    int *cisla = nacteniCisel(&pocet);
    
    // vypis medianu
    float median = vypocitejMedian(cisla, pocet);
    printf("Median %.2f\n", median);

    // vypis poctu cisel
    printf("Pocet cisel: %d\n", pocet);

    // vypis minimalniho cisla
    int min = najdiMin(cisla, pocet);
    printf("Min. hodnota: %d\n", min);

    // vypis maximalniho cisla
    int max = najdiMax(cisla, pocet);
    printf("Max. hodnota: %d\n", max);

    // vypis histogramu
    printf("Histogram:\n");
    vypisHistogram(cisla, pocet, n, min, max);

    // uvolneni pameti
    free(cisla);
    
    return 0;
}
