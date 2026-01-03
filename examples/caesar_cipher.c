/*
 * ÚLOHA: Caesarova šifra (HW06 styl)
 * - Parametr: shift (int) z argv[1]; záporný posouvá doleva.
 * - Čte stdin do EOF, posouvá pouze [A-Z] a [a-z], ostatní kopíruje.
 * - Ukládá do dyn. bufferu a vypíše až na konci (není nutné, ale ukázka práce s realloc).
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static char shift_char(char c, int k)
{
    if ('A' <= c && c <= 'Z')
        return (char)('A' + ( (c - 'A' + k) % 26 + 26 ) % 26);
    if ('a' <= c && c <= 'z')
        return (char)('a' + ( (c - 'a' + k) % 26 + 26 ) % 26);
    return c;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 100;
    int shift = atoi(argv[1]);

    char *buf = NULL;
    int cap = 0, len = 0;
    int ch;
    while ((ch = getchar()) != EOF)
    {
        if (len + 1 >= cap)
        {
            cap = (cap == 0) ? 256 : cap * 2;
            char *tmp = realloc(buf, cap);
            if (!tmp) { free(buf); return 100; }
            buf = tmp;
        }
        buf[len++] = shift_char((char)ch, shift);
    }
    if (buf)
    {
        fwrite(buf, 1, len, stdout);
        free(buf);
    }
    return 0;
}
