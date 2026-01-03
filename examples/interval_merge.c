/*
 * ÚLOHA: Slučování intervalů
 * - Načti dvojice L R (celá čísla) do EOF, kde L<=R.
 * - Ulož do dynamického pole, setřiď podle L a slouč překrývající se intervaly.
 * - Vypiš výsledné disjunktní intervaly, každý na řádek "L R".
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct { int l, r; } Interval;

static int cmp_interval(const void *a, const void *b)
{
    const Interval *x = a, *y = b;
    if (x->l != y->l) return (x->l < y->l) ? -1 : 1;
    return (x->r < y->r) ? -1 : (x->r > y->r);
}

int main(void)
{
    Interval *arr = NULL; int cap = 0, n = 0;
    int l, r;
    while (scanf("%d %d", &l, &r) == 2)
    {
        if (l > r) { int t = l; l = r; r = t; }
        if (n >= cap) {
            cap = cap ? cap*2 : 16;
            Interval *tmp = realloc(arr, cap * sizeof(Interval));
            if (!tmp) { free(arr); return 100; }
            arr = tmp;
        }
        arr[n++] = (Interval){l, r};
    }
    if (n == 0) { free(arr); return 0; }

    qsort(arr, n, sizeof(Interval), cmp_interval);

    int out_cap = n;
    Interval *out = malloc(out_cap * sizeof(Interval));
    if (!out) { free(arr); return 100; }

    int k = 0;
    out[k] = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i].l <= out[k].r) {
            if (arr[i].r > out[k].r) out[k].r = arr[i].r; // merge
        } else {
            out[++k] = arr[i];
        }
    }

    for (int i = 0; i <= k; i++)
        printf("%d %d\n", out[i].l, out[i].r);

    free(out); free(arr);
    return 0;
}
