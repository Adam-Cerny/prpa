#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define ERROR_INPUT 100
#define ERROR_LENGHT 101

int error(char *message, int code)
{
    fprintf(stderr, "%s", message);
    exit(code);
}

char zasifrovani(char *vstup, int n, char *zasifrovany_vystup)
{   
    int delka = strlen(vstup);
    int index;

    for (int i = 0; i < delka; i++)
    {
        char zasifrovany_znak;
        char aktualni_znak = vstup[i];

        if (islower(aktualni_znak))
        {
            index = aktualni_znak - 'a';
        }
        else if (isupper(aktualni_znak))
        {
            index = aktualni_znak - 'A' + 26;
        }
        else
        {
            zasifrovany_znak = aktualni_znak;
        }

        int index_novy = (index - n + 52) % 52;

        if (index_novy < 26)
        {
            zasifrovany_znak = 'a' + index_novy;
        }
        else
        {
            zasifrovany_znak = (index_novy - 26) + 'A';
        }

        zasifrovany_vystup[i] = zasifrovany_znak;

    }

    zasifrovany_vystup[strlen(vstup)] = '\0';

    return *zasifrovany_vystup;
}

int porovnani(char *zasifrovany_vystup, char *vystup)
{
    int score = 0;
    int score_curr = 0;

    for (int i = 0; zasifrovany_vystup[i] != '\0'; i++)
    {
        if (zasifrovany_vystup[i] == vystup[i])
        {
            score_curr ++;
        }
    }

    if (score_curr > score)
    {
        score = score_curr;
    }
    return score;
}

int main(void)
{
    int n;
    int c;

    if ((scanf("%i", &n) != 1) || (n <= 0))
    {
        error("Error: Chybny vstup!", ERROR_INPUT);
    }

    char *vstup = (char *)malloc(n + 1);
    char *vystup = (char *)malloc(n + 1);
    char *zasifrovany_vystup = (char *)malloc(n + 1);

    if (scanf(" ") != 0)
    {

    }

    int delka = 0;

    while (delka < n)
    {
        int c = getchar();
        if (c == EOF || c == '\n')
        {
            break;
        }
        if (!isalpha(c))
        {
            free(vstup);
            free(vystup);
            free(zasifrovany_vystup);
            error("Error: Chybny vstup!", ERROR_INPUT);
        }

        vstup[delka++] = (char)c;
    }
    vstup[delka] = '\0';

    if (delka != n)
    {
        free(vstup);
        free(vystup);
        free(zasifrovany_vystup);
        error("Error: Chybna delka vstupu!", ERROR_LENGHT);
    }

    if (scanf(" ") != 0)
    {

    }

    delka = 0;

    while (delka < n)
    {
        c = getchar();
        if (c == EOF || isspace(c))
        {
            break;
        }
        if (!isalpha(c))
        {
            free(vstup);
            free(vystup);
            free(zasifrovany_vystup);
            error("Error: Chybny vstup!", ERROR_INPUT);
        }
        vystup[delka++] = (char)c;
    }
    vystup[delka] = '\0';

    if (delka != n)
    {
        free(vstup);
        free(vystup);
        free(zasifrovany_vystup);
        error("Error: Chybna delka vstupu!", ERROR_LENGHT);
    }

    int score_biggest = -1;
    int best_shift = 0;
    for (int i = 0; i < 52 ; i++)
    {
        zasifrovani(vstup, i, zasifrovany_vystup);

        int score = porovnani(zasifrovany_vystup, vystup);

        if (score > score_biggest)
        {
            score_biggest = score;
            best_shift = i;
        }
    }
    zasifrovani(vstup, best_shift, zasifrovany_vystup);

    printf("%s\n", zasifrovany_vystup);

    free(vstup);
    free(vystup);
    free(zasifrovany_vystup);

    return 0;
}
