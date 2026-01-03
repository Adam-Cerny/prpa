/*
 * ZADÁNÍ:
 * Načtěte ze stdin seznam studentů (jméno, počet bodů) až do EOF.
 * Použijte dynamické pole struktur.
 * Seřaďte studenty:
 * 1. Sestupně podle bodů.
 * 2. Při rovnosti bodů abecedně podle jména.
 * Na konci vypište seřazený seznam a průměr bodů.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char jmeno[50];
    int body;
} Student;

// Porovnávací funkce pro qsort (2 kritéria)
int porovnej_studenty(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;

    // 1) body sestupně
    if (s1->body != s2->body)
        return s2->body - s1->body;
    // 2) jméno vzestupně
    return strcmp(s1->jmeno, s2->jmeno);
}

int main(void)
{
    Student *seznam = NULL;
    int pocet = 0;
    int kapacita = 0;
    char tmp_jmeno[50];
    int tmp_body;

    // Načítání dvojic (Jméno Body) až do EOF
    while (scanf("%49s %d", tmp_jmeno, &tmp_body) == 2)
    {
        if (pocet >= kapacita)
        {
            kapacita = (kapacita == 0) ? 4 : kapacita * 2;
            Student *tmp_ptr = realloc(seznam, kapacita * sizeof(Student));
            if (!tmp_ptr)
            {
                free(seznam);
                return 100;
            }
            seznam = tmp_ptr;
        }
        strcpy(seznam[pocet].jmeno, tmp_jmeno);
        seznam[pocet].body = tmp_body;
        pocet++;
    }

    if (pocet > 0)
    {
        qsort(seznam, pocet, sizeof(Student), porovnej_studenty);

        double soucet = 0.0;
        printf("\n--- Serazeny seznam ---\n");
        for (int i = 0; i < pocet; i++)
        {
            printf("%-15s: %d b\n", seznam[i].jmeno, seznam[i].body);
            soucet += seznam[i].body;
        }
        printf("-----------------------\n");
        printf("Prumer: %.2f\n", soucet / pocet);
    }

    free(seznam);
    return 0;
}
