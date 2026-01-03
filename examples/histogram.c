/*
 * ÚLOHA: Histogram hodnot 0-100
 * Načti celá čísla z stdin do EOF, povolený rozsah 0..100.
 * Spočítej četnost každé hodnoty a vypiš jen ty, které se vyskytly.
 */

#include <stdio.h>

int main(void)
{
    int freq[101] = {0};
    int x;

    while (scanf("%d", &x) == 1)
    {
        if (x >= 0 && x <= 100)
            freq[x]++;
    }

    for (int i = 0; i <= 100; i++)
    {
        if (freq[i] > 0)
            printf("%3d : %d\n", i, freq[i]);
    }
    return 0;
}
