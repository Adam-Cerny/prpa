#include <stdio.h>

void vypisVektor(int* vektor, int velikost)
{
    for (int i = 0; i < velikost; i++)
    {
        printf("%d ", vektor[i]);
    }    
    
    printf("\n");
}

int nactiVektor(int* vektor, int velikost)
{
    for(int i = 0; i < velikost; i++)
    {
        int cislo;
        if (scanf("%d", &cislo) != 1)
        {
            fprintf(stderr, "Nepovedlo se nacist cislo do vektoru.\n");
            return 101;
        }
        vektor[i] = cislo;
    }
    return 0;
}

int min(int* vektor, int velikost, int* minVal)
{
    int minHodnota = vektor[0];
    for (int i = 1; i < velikost; i++)
    {
        if (vektor[i] < minHodnota)
        {
            minHodnota = vektor[i];
        }
    }
    *minVal = minHodnota;
    return minHodnota;
}

int max(int* vektor, int velikost, int* maxVal)
{
    int maxHodnota = vektor[0];
    for (int i = 1; i < velikost; i++)
    {
        if (vektor[i] > maxHodnota)
        {
            maxHodnota = vektor[i];
        }
    }
    *maxVal = maxHodnota;
    return maxHodnota;
}

int prictiSkalar(int* vektor, int velikost, int skalar, int minHodnota)
{
    for (int i = 0; i < velikost; i++)
    {
        vektor[i] += skalar;
    }
    return 0;
}

int main(void)
{
    int velikost = 0;
    printf("Zadej pocet cisel pro nacteni: ");

    int ret = scanf("%d", &velikost);

    if (ret != 1)
    {
        fprintf(stderr, "Nebyla zadana velikost pole.\n");
        return 100;
    }

    int vektor[velikost];

    ret = nactiVektor(vektor, velikost);
    if (ret != 0)
    {
        return ret;
    }
    vypisVektor(vektor, velikost);

    int minHodnota = min(vektor, velikost, &minHodnota);
    int maxHodnota = max(vektor, velikost, &maxHodnota);
    printf("Minimum: %d\n", minHodnota);
    printf("Maximum: %d\n", maxHodnota);

    int skalar = 0;
    printf("Zadej skalar pro pricteni: ");
    ret = scanf("%d", &skalar);
    if (ret != 1)
    {
        fprintf(stderr, "Nebyl zadán skalar.\n");
        return 102;
    }
    prictiSkalar(vektor, velikost, skalar, minHodnota);
    printf("Vektor po pricteni skalaru %d:\n", skalar);
    vypisVektor(vektor, velikost);

    return 0;
}
