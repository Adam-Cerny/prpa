/*
 * ÚLOHA: Násobení dvou matic A (R x K) a B (K x C)
 * Načti R, K, C. Načti A, pak B. Zkontroluj rozměry, spočítej C = A*B, vypiš.
 * Korektně uvolni paměť i při chybě alokace.
 */

#include <stdio.h>
#include <stdlib.h>

static void free_matrix(int **m, int rows)
{
    if (!m) return;
    for (int i = 0; i < rows; i++)
        free(m[i]);
    free(m);
}

int main(void)
{
    int R, K, C;
    if (scanf("%d %d %d", &R, &K, &C) != 3)
        return 100;

    // A: R x K
    int **A = (int **)malloc(R * sizeof(int *));
    if (!A) return 100;
    for (int i = 0; i < R; i++)
    {
        A[i] = (int *)malloc(K * sizeof(int));
        if (!A[i]) { free_matrix(A, i); return 100; }
    }

    // B: K x C
    int **B = (int **)malloc(K * sizeof(int *));
    if (!B) { free_matrix(A, R); return 100; }
    for (int i = 0; i < K; i++)
    {
        B[i] = (int *)malloc(C * sizeof(int));
        if (!B[i]) { free_matrix(B, i); free_matrix(A, R); return 100; }
    }

    // Načtení A
    for (int i = 0; i < R; i++)
        for (int j = 0; j < K; j++)
            scanf("%d", &A[i][j]);

    // Načtení B
    for (int i = 0; i < K; i++)
        for (int j = 0; j < C; j++)
            scanf("%d", &B[i][j]);

    // Výpočet C = A*B (R x C)
    int **Cmat = (int **)malloc(R * sizeof(int *));
    if (!Cmat) { free_matrix(A, R); free_matrix(B, K); return 100; }
    for (int i = 0; i < R; i++)
    {
        Cmat[i] = (int *)calloc(C, sizeof(int));
        if (!Cmat[i]) { free_matrix(Cmat, i); free_matrix(A, R); free_matrix(B, K); return 100; }
    }

    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            int sum = 0;
            for (int k = 0; k < K; k++)
                sum += A[i][k] * B[k][j];
            Cmat[i][j] = sum;
        }
    }

    // Výpis
    printf("\nSoucin A*B:\n");
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
            printf("%d ", Cmat[i][j]);
        printf("\n");
    }

    free_matrix(Cmat, R);
    free_matrix(A, R);
    free_matrix(B, K);
    return 0;
}
