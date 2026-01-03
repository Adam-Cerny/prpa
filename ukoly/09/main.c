#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct {
    char *text;
    int pocet;
    int poradi;
} Slovo;

char *nactiSlovo(int case_sensitive) 
{
    int c;
    char *buffer = malloc(21 * sizeof(char));
    int i = 0;

    while ((c = getchar()) != EOF) 
    {
        if (isalpha(c) == FALSE) 
        {
            if (i > 0) 
            {
                buffer[i] = '\0';
                return buffer;
            }
        } 
        else 
        {
            if (i < 20) 
            {
                if (case_sensitive == FALSE)
                {
                    c = tolower(c);
                }
                buffer[i++] = c;
            }
        }
    }

    if (i > 0) 
    {
        buffer[i] = '\0';
        return buffer;
    }

    free(buffer);
    return NULL;
}

void zpracujSlovo(Slovo *seznam, int *unikatni_pocet, char *s) 
{
    for (int i = 0; i < *unikatni_pocet; i++) 
    {
        if (strcmp(seznam[i].text, s) == 0) 
        {
            seznam[i].pocet++;
            free(s);
            return;
        }
    }

    seznam[*unikatni_pocet].text = s;
    seznam[*unikatni_pocet].pocet = 1;
    seznam[*unikatni_pocet].poradi = *unikatni_pocet + 1;
    (*unikatni_pocet)++;

}

int najdiMaxPocet(Slovo *seznam, int unikatni_pocet)
{
    int max_pocet = 0;
    for (int i = 0; i < unikatni_pocet; i++) 
    {
        if (seznam[i].pocet > max_pocet) 
        {
            max_pocet = seznam[i].pocet;
        }
    }
    return max_pocet;
}

int najdiMinPocet(Slovo *seznam, int unikatni_pocet)
{
    int min_pocet = seznam[0].pocet;
    for (int i = 0; i < unikatni_pocet; i++) 
    {
        if (seznam[i].pocet < min_pocet) 
        {
            min_pocet = seznam[i].pocet;
        }
    }
    return min_pocet;
}

void vypisSlovoSPoctem(Slovo *seznam, int unikatni_pocet, int hledany_pocet)
{
    int prvni = TRUE;
    for (int i = 0; i < unikatni_pocet; i++) 
    {
        if (seznam[i].pocet == hledany_pocet) 
        {
            if (prvni == FALSE)
            {
                printf(" ");
            }
            printf("%s", seznam[i].text);
            prvni = FALSE;
        }
    }
}

void vypis(Slovo *seznam, int unikatni_pocet, int limit) 
{
    if (limit != 0)
    {
        puts("Seznam slov:");
        for (int i = 0; i < unikatni_pocet; i++) 
        {
            if (strlen(seznam[i].text) == limit || limit == -1)
            {
                printf("%-20s %d\n", seznam[i].text, seznam[i].pocet);
            }
        }
    }

    printf("Pocet slov: %8s %d\n", "", unikatni_pocet);

    int max_pocet = najdiMaxPocet(seznam, unikatni_pocet);
    int min_pocet = najdiMinPocet(seznam, unikatni_pocet);

    printf("Nejcastejsi: %7s ", "");
    vypisSlovoSPoctem(seznam, unikatni_pocet, max_pocet);
    printf("\n");

    printf("Nejmene caste: %5s ", "");
    vypisSlovoSPoctem(seznam, unikatni_pocet, min_pocet);
    printf("\n");
}

int porovnejCetnost(const void *a, const void *b) 
{
    Slovo *slovoA = (Slovo *)a;
    Slovo *slovoB = (Slovo *)b;

    if (slovoA->pocet != slovoB->pocet) 
    {
        return slovoA->pocet - slovoB->pocet;
    }

    return slovoA->poradi - slovoB->poradi;
}

int porovnejAbecedne(const void *a, const void *b) 
{
    Slovo *slovoA = (Slovo *)a;
    Slovo *slovoB = (Slovo *)b;

    return strcmp(slovoA->text, slovoB->text);
}

int main(int argc, char *argv[]) 
{
    char *slovo;
    int unikatni_pocet = 0;
    int kapacita = 10;

    int case_sensitive = FALSE;
    int styl_razeni = 0;
    int limit = -1;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0)
        {
            case_sensitive = TRUE;
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            if (++i < argc)
            {
                char *text_parametru = argv[i];

                int cislo = atoi(text_parametru);

                if (cislo == 1)
                {
                    styl_razeni = 1;
                }
                else if (cislo == 2)
                {
                    styl_razeni = 2;
                }
                else
                {
                    fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
                }
            }
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            if (++i < argc)
            {
                int cislo = atoi(argv[i]);
                if (cislo >= 0)
                    limit = cislo;
                else
                    fprintf(stderr, "Warning: Chybna hodnota parametru -l!\n");
            }
        }
    }

    Slovo *seznam = malloc(kapacita * sizeof(Slovo));
    while ((slovo = nactiSlovo(case_sensitive)) != NULL)
    {
        if (unikatni_pocet >= kapacita) 
        {
            kapacita *= 2;
            Slovo *tmp = realloc(seznam, kapacita * sizeof(Slovo));
            seznam = tmp;
        }
        zpracujSlovo(seznam, &unikatni_pocet, slovo); 
    }

    if (styl_razeni == 1)
    {
        qsort(seznam, unikatni_pocet, sizeof(Slovo), porovnejCetnost);
    }
    else if (styl_razeni == 2)
    {
        qsort(seznam, unikatni_pocet, sizeof(Slovo), porovnejAbecedne);
    }

    vypis(seznam, unikatni_pocet, limit);

    for (int i = 0; i < unikatni_pocet; i++) 
    {
        free(seznam[i].text);
    }
    free(seznam);

    return 0;
}
