/*
 * ÚLOHA: RLE kódér (HW04 styl)
 * - Čte ze stdin znaky A-Z až do EOF.
 * - Pokud najde jiný znak, vypíše chybu a návratový kód 100.
 * - Kóduje sekvence: délka 1-2 se vypisuje původně, 3+ jako Z<delka> (dekadicky).
 * - Newline na konci vstupu se do kódování ani statistiky nezapočítává.
 * - Po úspěchu vypíše kód a na stderr statistiku a poměr.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ch, last = -1;
    int count = 0;
    int in_symbols = 0; // bez '\n'
    int out_symbols = 0; // délka kódovaného výstupu (znaky)

    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
            break; // nezapočítávat do statistik ani kódu

        if (ch < 'A' || ch > 'Z')
        {
            fprintf(stderr, "Error: Neplatny symbol!\n");
            return 100;
        }

        if (count == 0) { last = ch; count = 1; }
        else if (ch == last) { count++; }
        else {
            // flush předchozí série
            if (count == 1) { putchar(last); out_symbols += 1; }
            else if (count == 2) { putchar(last); putchar(last); out_symbols += 2; }
            else { printf("%c%d", last, count); out_symbols += 1 + (count >= 100 ? 3 : count >= 10 ? 2 : 1); }
            in_symbols += count;
            last = ch; count = 1;
        }
    }

    // flush poslední série
    if (count > 0)
    {
        if (count == 1) { putchar(last); out_symbols += 1; }
        else if (count == 2) { putchar(last); putchar(last); out_symbols += 2; }
        else { printf("%c%d", last, count); out_symbols += 1 + (count >= 100 ? 3 : count >= 10 ? 2 : 1); }
        in_symbols += count;
    }

    if (in_symbols > 0)
        putchar('\n');

    if (in_symbols > 0)
    {
        fprintf(stderr, "Pocet vstupnich symbolu: %d\n", in_symbols);
        fprintf(stderr, "Pocet zakodovanych symbolu: %d\n", out_symbols);
        fprintf(stderr, "Kompresni pomer: %.2f\n", (double)out_symbols / in_symbols);
    }

    return 0;
}
