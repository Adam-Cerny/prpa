/*
 * ZADÁNÍ:
 * Načtěte text do EOF.
 * Dynamicky ukládejte nejdelší slovo.
 * Ignorujte interpunkci při měření délky slova (volitelné, zde isalpha).
 * Vypište statistiku: znaky, slova, nejdelší slovo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int ch;
    int pocet_znaku = 0, pocet_slov = 0;

    char *nejdelsi_slovo = NULL;
    int max_len = 0;

    char *aktualni_slovo = NULL;
    int akt_len = 0;
    int akt_cap = 0;

    while ((ch = getchar()) != EOF)
    {
        pocet_znaku++;

        if (isspace(ch))
        {
            if (akt_len > 0)
            {
                if (akt_len > max_len)
                {
                    max_len = akt_len;
                    free(nejdelsi_slovo);
                    nejdelsi_slovo = strdup(aktualni_slovo);
                }
                akt_len = 0; // reset pro další slovo
            }
        }
        else
        {
            if (akt_len == 0)
                pocet_slov++;

            // realokace pro aktuální slovo
            if (akt_len + 2 > akt_cap)
            {
                akt_cap = (akt_cap == 0) ? 16 : akt_cap * 2;
                char *tmp = realloc(aktualni_slovo, akt_cap);
                if (!tmp)
                {
                    free(aktualni_slovo);
                    free(nejdelsi_slovo);
                    return 100;
                }
                aktualni_slovo = tmp;
            }
            aktualni_slovo[akt_len++] = (char)ch;
            aktualni_slovo[akt_len] = '\0';
        }
    }

    // poslední slovo, pokud text nekončil mezerou
    if (akt_len > max_len)
    {
        max_len = akt_len;
        free(nejdelsi_slovo);
        nejdelsi_slovo = strdup(aktualni_slovo);
    }

    printf("Znaky: %d\nSlova: %d\n", pocet_znaku, pocet_slov);
    if (nejdelsi_slovo)
        printf("Nejdelsi slovo: %s (%d)\n", nejdelsi_slovo, max_len);

    free(aktualni_slovo);
    free(nejdelsi_slovo);
    return 0;
}
