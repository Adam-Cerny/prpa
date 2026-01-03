/*
 * ÚLOHA: Řazení datumů (YYYY-MM-DD)
 * - Načti řádky s daty ve formátu YYYY-MM-DD až do EOF.
 * - Zkontroluj validitu (rok>0, 1<=mesic<=12, 1<=den<=dni_v_mesici; počítáno prostě, neřeší přestupný rok přesně - jen únor 29 pro rok delitelný 4).
 * - Nevalidní datum přeskoč s warningem na stderr, pokračuj.
 * - Validní data ulož do dynamického pole, setřiď vzestupně (rok, měsíc, den) a vypiš.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int y, m, d;
} Date;

static int days_in_month(int y, int m)
{
    static const int mdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2) {
        int leap = (y % 4 == 0); // zjednodušeně
        return leap ? 29 : 28;
    }
    return mdays[m-1];
}

static int valid_date(int y, int m, int d)
{
    if (y <= 0 || m < 1 || m > 12) return 0;
    int md = days_in_month(y, m);
    return d >= 1 && d <= md;
}

static int cmp_date(const void *a, const void *b)
{
    const Date *x = a, *y = b;
    if (x->y != y->y) return (x->y < y->y) ? -1 : 1;
    if (x->m != y->m) return (x->m < y->m) ? -1 : 1;
    if (x->d != y->d) return (x->d < y->d) ? -1 : 1;
    return 0;
}

int main(void)
{
    Date *arr = NULL; int cap = 0, n = 0;
    int y, m, d;
    while (scanf("%d-%d-%d", &y, &m, &d) == 3)
    {
        if (!valid_date(y, m, d)) {
            fprintf(stderr, "Warning: Nevalidni datum %04d-%02d-%02d\n", y, m, d);
            continue;
        }
        if (n >= cap) {
            cap = cap ? cap*2 : 16;
            Date *tmp = realloc(arr, cap * sizeof(Date));
            if (!tmp) { free(arr); return 100; }
            arr = tmp;
        }
        arr[n++] = (Date){y,m,d};
    }
    if (n == 0) { free(arr); return 0; }
    qsort(arr, n, sizeof(Date), cmp_date);
    for (int i = 0; i < n; i++)
        printf("%04d-%02d-%02d\n", arr[i].y, arr[i].m, arr[i].d);
    free(arr);
    return 0;
}
