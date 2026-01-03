/*
 * ZADÁNÍ: Validace a zpracování XML (HTML) dokumentu
 * 1. Validace: Kontrola párování tagů <a>...</a> (stack). Nepárové tagy <b/> se neukládají.
 * 2. Statistiky: Seznam všech tagů a jejich četnost, nejčastější a nejméně častý tag.
 * 3. Rozšíření: Podpora vícepísmenných tagů (např. <able>).
 * 4. Sumace: Speciální tagy <sum> a <data>. Vypočtěte součet čísel uvnitř <data> v rámci <sum>.
 *
 * Příklad validace:
 * <a><b></a></b> -> NE (špatné pořadí)
 * <a><b/></a>    -> ANO (b je nepárový)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char jmeno[50];
    int cetnost;
} TagStat;

// --- POMOCNÉ FUNKCE PRO ZÁSOBNÍK (STACK) ---
void push(char ***stack, int *len, int *cap, char *tag)
{
    if (*len + 1 > *cap)
    {
        *cap = (*cap == 0) ? 10 : *cap * 2;
        *stack = realloc(*stack, *cap * sizeof(char *));
    }
    (*stack)[(*len)++] = strdup(tag);
}

char *pop(char **stack, int *len)
{
    if (*len == 0)
        return NULL;
    return stack[--(*len)];
}

// --- LOGIKA PRO STATISTIKY ---
void pridej_do_statistik(TagStat **stats, int *pocet, int *cap, char *tag)
{
    for (int i = 0; i < *pocet; i++)
    {
        if (strcmp((*stats)[i].jmeno, tag) == 0)
        {
            (*stats)[i].cetnost++;
            return;
        }
    }
    if (*pocet + 1 > *cap)
    {
        *cap = (*cap == 0) ? 10 : *cap * 2;
        *stats = realloc(*stats, *cap * sizeof(TagStat));
    }
    strcpy((*stats)[*pocet].jmeno, tag);
    (*stats)[*pocet].cetnost = 1;
    (*pocet)++;
}

int main()
{
    char **stack = NULL;
    int s_len = 0, s_cap = 0;

    TagStat *stats = NULL;
    int st_pocet = 0, st_cap = 0;

    int ch;
    int validni = 1;
    long celkova_suma = 0;
    int uvnitr_data = 0;

    while ((ch = getchar()) != EOF && validni)
    {
        if (ch == '<')
        {
            char tag_name[50];
            int idx = 0;
            int je_zaviraci = 0;
            int je_neparovy = 0;

            ch = getchar();
            if (ch == '/')
            {
                je_zaviraci = 1;
                ch = getchar();
            }

            while (ch != '>' && ch != '/' && ch != EOF)
            {
                tag_name[idx++] = (char)ch;
                ch = getchar();
            }
            tag_name[idx] = '\0';
            if (ch == '/')
            {
                je_neparovy = 1;
                getchar();
            } // přeskoč '>' u <b/>

            // --- VALIDACE A STACK ---
            if (!je_neparovy)
            {
                if (je_zaviraci)
                {
                    char *posledni = pop(stack, &s_len);
                    if (!posledni || strcmp(posledni, tag_name) != 0)
                    {
                        validni = 0;
                    }
                    free(posledni);
                }
                else
                {
                    push(&stack, &s_len, &s_cap, tag_name);
                }
            }

            // --- STATISTIKY ---
            pridej_do_statistik(&stats, &st_pocet, &st_cap, tag_name);

            // --- SUMACE ---
            if (strcmp(tag_name, "data") == 0)
            {
                uvnitr_data = !je_zaviraci;
            }
        }
        else if (uvnitr_data && isdigit(ch))
        {
            ungetc(ch, stdin);
            int hodnota;
            scanf("%d", &hodnota);
            celkova_suma += hodnota;
        }
    }

    if (s_len > 0)
        validni = 0;

    // --- VÝSTUP ---
    printf("Validni: %s\n", validni ? "Ano" : "Ne");
    if (validni)
    {
        printf("Suma: %ld\n", celkova_suma);
        printf("Statistiky tagu:\n");
        int max_idx = 0, min_idx = 0;
        for (int i = 0; i < st_pocet; i++)
        {
            printf(" - %s: %dx\n", stats[i].jmeno, stats[i].cetnost);
            if (stats[i].cetnost > stats[max_idx].cetnost)
                max_idx = i;
            if (stats[i].cetnost < stats[min_idx].cetnost)
                min_idx = i;
        }
        if (st_pocet > 0)
        {
            printf("Nejcastejsi: %s\n", stats[max_idx].jmeno);
            printf("Nejlene casty: %s\n", stats[min_idx].jmeno);
        }
    }

    // Úklid
    for (int i = 0; i < s_len; i++)
        free(stack[i]);
    free(stack);
    free(stats);

    return 0;
}