/*
 * ÚLOHA: Statistika číselné řady (HW08 styl)
 * - Načti int hodnoty do EOF (žádné další validace).
 * - Ulož dynamicky, spočítej min, max, součet, průměr, medián.
 */

#include <stdio.h>
#include <stdlib.h>

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int main(void)
{
    int *arr = NULL;
    int cap = 0, n = 0, x;
    long long sum = 0;

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
        sum += x;
    }

    if (n == 0)
    {
        free(arr);
        return 0;
    }

    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    qsort(arr, n, sizeof(int), cmp_int);
    double median = (n % 2) ? arr[n/2] : (arr[n/2 - 1] + arr[n/2]) / 2.0;

    printf("Pocet:   %d\n", n);
    printf("Min:     %d\n", min);
    printf("Max:     %d\n", max);
    printf("Prumer:  %.2f\n", (double)sum / n);
    printf("Median:  %.2f\n", median);

    free(arr);
    return 0;
}
