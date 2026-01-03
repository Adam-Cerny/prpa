/*
 * ÚLOHA: Analýza textu s parametry (-c, -s, -l) z HW09
 * - Čte ze stdin do EOF, slova bez diakritiky, čísla nejsou.
 * - Parametry:
 *   -c : case-sensitive (default case-insensitive)
 *   -s N : N=1 řazení vzestupně dle četnosti, N=2 dle abecedy (jinak warning)
 *   -l K : omez délku vypisovaných slov na K (>0). 0 = nevypisuj seznam. (jinak warning)
 * - Vypíše seznam (pokud l != 0), počet slov, nejčastější a nejméně častá slova.
 * - Návratový kód vždy 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD 256

typedef struct {
    char *word;
    int freq;
    int first_pos; // pro stabilitu při rovnosti
} Item;

static int cmp_alpha(const void *a, const void *b)
{
    const Item *x = a, *y = b;
    return strcmp(x->word, y->word);
}

// setrid dle freq (vzestupne), pri shode podle first_pos
static int cmp_freq(const void *a, const void *b)
{
    const Item *x = a, *y = b;
    if (x->freq != y->freq) return x->freq - y->freq;
    return x->first_pos - y->first_pos;
}

// pomocné
static void to_lower_str(char *s)
{
    for (; *s; ++s) *s = (char)tolower((unsigned char)*s);
}

int main(int argc, char *argv[])
{
    int case_sensitive = 0;
    int sort_mode = 0; // 0 = podle výskytu, 1=freq, 2=alpha
    int len_limit = -1; // -1 = bez limitu, 0 = nevypisuj seznam

    // parametry
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0) case_sensitive = 1;
        else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc)
        {
            sort_mode = atoi(argv[++i]);
            if (sort_mode != 1 && sort_mode != 2)
            {
                fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
                sort_mode = 0;
            }
        }
        else if (strcmp(argv[i], "-l") == 0 && i + 1 < argc)
        {
            len_limit = atoi(argv[++i]);
            if (len_limit < 0)
            {
                fprintf(stderr, "Warning: Chybna hodnota parametru -l!\n");
                len_limit = -1;
            }
        }
    }

    Item *items = NULL;
    int count = 0, cap = 0;
    int total_words = 0;

    char buf[MAX_WORD];
    int pos = 0; // pořadí prvního výskytu

    // čtení slov přes scanf("%255s")
    while (scanf("%255s", buf) == 1)
    {
        pos++;
        if (!case_sensitive)
            to_lower_str(buf);

        // najdi existující
        int found = -1;
        for (int i = 0; i < count; i++)
        {
            if (strcmp(items[i].word, buf) == 0)
            {
                found = i; break;
            }
        }
        if (found >= 0)
        {
            items[found].freq++;
        }
        else
        {
            if (count >= cap)
            {
                cap = (cap == 0) ? 16 : cap * 2;
                Item *tmp = realloc(items, cap * sizeof(Item));
                if (!tmp) { free(items); return 100; }
                items = tmp;
            }
            items[count].word = strdup(buf);
            if (!items[count].word) { /* memory fail */ return 100; }
            items[count].freq = 1;
            items[count].first_pos = pos;
            count++;
        }
        total_words++;
    }

    // řazení pro výpis seznamu
    if (sort_mode == 1) qsort(items, count, sizeof(Item), cmp_freq);
    else if (sort_mode == 2) qsort(items, count, sizeof(Item), cmp_alpha);

    // najdi nejčastější/nejméně častá v pořadí výskytu
    int minf = count ? items[0].freq : 0;
    int maxf = count ? items[0].freq : 0;
    for (int i = 1; i < count; i++)
    {
        if (items[i].freq < minf) minf = items[i].freq;
        if (items[i].freq > maxf) maxf = items[i].freq;
    }

    if (len_limit != 0) // 0 = nevypisuj seznam
    {
        printf("Seznam slov:\n");
        for (int i = 0; i < count; i++)
        {
            int ok = (len_limit < 0) || ((int)strlen(items[i].word) <= len_limit);
            if (ok)
                printf("%-20s %d\n", items[i].word, items[i].freq);
        }
    }

    printf("Pocet slov:          %d\n", total_words);

    // nejčastější / nejméně časté v pořadí výskytu
    printf("Nejcastejsi:         ");
    for (int i = 0, first = 1; i < count; i++)
    {
        if (items[i].freq == maxf)
        {
            if (!first) printf(" ");
            printf("%s", items[i].word);
            first = 0;
        }
    }
    printf("\n");

    printf("Nejmene caste:       ");
    for (int i = 0, first = 1; i < count; i++)
    {
        if (items[i].freq == minf)
        {
            if (!first) printf(" ");
            printf("%s", items[i].word);
            first = 0;
        }
    }
    printf("\n");

    for (int i = 0; i < count; i++)
        free(items[i].word);
    free(items);
    return 0;
}
