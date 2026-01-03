/*
 * ZADÁNÍ:
 * Načtěte rozměry matice R a C.
 * Dynamicky alokujte 2D pole typu int.
 * Naplňte matici hodnotami ze stdin.
 * Vypište transponovanou matici (prohozené řádky a sloupce).
 * Všechnu paměť korektně uvolněte.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int R, C;
    if (scanf("%d %d", &R, &C) != 2)
        return 100;

    // 1. Alokace pole ukazatelů na řádky
    int **matice = (int **)malloc(R * sizeof(int *));
    if (!matice)
        return 100;

    // 2. Alokace jednotlivých řádků
    for (int i = 0; i < R; i++)
    {
        matice[i] = (int *)malloc(C * sizeof(int));
        if (!matice[i])
        {
            // korektní úklid už alokovaných řádků
            for (int k = 0; k < i; k++)
                free(matice[k]);
            free(matice);
            return 100;
        }
    }

    // Načtení dat
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            scanf("%d", &matice[i][j]);
        }
    }

    // Výpis transponované matice (C x R)
    printf("\nTransponovana matice:\n");
    for (int j = 0; j < C; j++)
    {
        for (int i = 0; i < R; i++)
        {
            printf("%d ", matice[i][j]);
        }
        printf("\n");
    }

    // 3. ÚKLID v obráceném pořadí než alokace
    for (int i = 0; i < R; i++)
        free(matice[i]);
    free(matice);

    return 0;
}
