/*
 * ÚLOHA: Medián čísel
 * Načti celá čísla do EOF, ulož do dynamického pole, setřiď a vypiš medián.
 * Při sudém počtu vypiš průměr prostředních dvou jako double.
 */

#include <stdio.h>
#include <stdlib.h>

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main(void)
{
    int *arr = NULL;
    int cap = 0, n = 0, x;

    while (scanf("%d", &x) == 1)
    {
        if (n >= cap)
        {
            cap = (cap == 0) ? 8 : cap * 2;
            int *tmp = realloc(arr, cap * sizeof(int));
            if (!tmp) { free(arr); return 100; }
            arr = tmp;
        }
        arr[n++] = x;
    }

    if (n == 0)
    {
        free(arr);
        return 0;
    }

    qsort(arr, n, sizeof(int), cmp_int);

    if (n % 2 == 1)
    {
        printf("Median: %d\n", arr[n / 2]);
    }
    else
    {
        double m = (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
        printf("Median: %.2f\n", m);
    }

    free(arr);
    return 0;
}
