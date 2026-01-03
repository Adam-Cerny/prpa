/*
 * ÚLOHA: Reverz řetězce s filtrováním
 * - Parametr: F (0=bez filtru, 1=jen písmena, 2=jen cifry)
 * - Načti řetězec, podle filtru vyber znaky a vypiš obrácené.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc < 2) return 100;
    int filter = atoi(argv[1]);
    if (filter < 0 || filter > 2) return 100;

    char buf[512];
    if (scanf("%511s", buf) != 1) return 100;

    char out[512];
    int len = 0;

    for (int i = 0; buf[i]; i++)
    {
        char c = buf[i];
        int ok = 0;
        if (filter == 0) ok = 1;
        else if (filter == 1 && isalpha((unsigned char)c)) ok = 1;
        else if (filter == 2 && isdigit((unsigned char)c)) ok = 1;

        if (ok) out[len++] = c;
    }

    // reverse
    for (int i = 0; i < len / 2; i++)
    {
        char t = out[i];
        out[i] = out[len - 1 - i];
        out[len - 1 - i] = t;
    }
    out[len] = '\0';

    printf("%s\n", out);
    return 0;
}
