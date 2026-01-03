/*
 * ÚLOHA: Otočení čtvercové matice o 90° doprava
 * - Načti N, pak N×N int hodnot.
 * - Ulož do 2D (dynamická alokace), vytvoř výstupní matici rotovanou o 90° CW.
 * - Vypiš rotovanou matici.
 */

#include <stdio.h>
#include <stdlib.h>

static void free_m(int **m, int n){ if(!m)return; for(int i=0;i<n;i++) free(m[i]); free(m); }

int main(void)
{
    int N; if (scanf("%d", &N) != 1 || N <= 0) return 100;

    int **a = malloc(N * sizeof(int*));
    if(!a) return 100;
    for(int i=0;i<N;i++){
        a[i]=malloc(N*sizeof(int));
        if(!a[i]){ free_m(a,i); return 100; }
    }
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) scanf("%d", &a[i][j]);

    int **b = malloc(N * sizeof(int*));
    if(!b){ free_m(a,N); return 100; }
    for(int i=0;i<N;i++){
        b[i]=malloc(N*sizeof(int));
        if(!b[i]){ free_m(b,i); free_m(a,N); return 100; }
    }

    // rotace: b[i][j] = a[N-1-j][i]
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) b[i][j] = a[N-1-j][i];

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++) printf("%d ", b[i][j]);
        printf("\n");
    }

    free_m(b,N); free_m(a,N);
    return 0;
}
