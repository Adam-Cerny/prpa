#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_NUMBER 100;
#define ERROR_MESSAGE "Error: Chyba histogramu!"

// pomocna funkce pro vypis chybove hlasky a ukonceni programu
int error(char *message, int code)
{
    fprintf(stderr, "%s", message);
    exit(code);
}

int nacteniPrvnihoCisla()
{
    int prvniCislo;
    scanf("%i", &prvniCislo); 
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

    // nacteni a ignorovani prvniho cisla 
    int prvniCislo;
    scanf("%i", &prvniCislo); 

    // cte cisla do EOF
    while (scanf("%i", &cislo) == 1) 
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

int main(void)
{
    int pocet = 0;
    
    // nacteni cisel    
    int *cisla = nacteniCisel(&pocet);
    
    // vypis medianu
    float median = vypocitejMedian(cisla, pocet);
    printf("Median %.2f\n", median);

    // vypis poctu cisel
    printf("Pocet cisel: %i\n", pocet);

    // vypis minimalniho cisla
    int min = najdiMin(cisla, pocet);
    printf("Min. hodnota: %i\n", min);

    // vypis maximalniho cisla
    int max = najdiMax(cisla, pocet);
    printf("Max. hodnota: %i\n", max);

    // vypis prvniho cisla
    int prvniCislo = nacteniPrvnihoCisla();
    printf("Prvni cislo: %i\n", prvniCislo);

    // uvolneni pameti
    free(cisla);
    
    return 0;
}
