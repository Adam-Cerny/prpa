#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char title[100];
    char author[100];
    int year;
} KNIHA;

int main(void)
{
    char *file = "lab11_books.txt";
    
    FILE *fileRead = fopen(file, "r");
    if (fileRead == NULL) 
    {
        fprintf(stderr, "Chyba při otevírání souboru");
        return 100; 
    }

    KNIHA k;

    while (1)
    {
        int nacteno = fscanf(fileRead, " %99[^;];%d;%99[^\n]", k.author, &k.year, k.title);
        if (nacteno != 3) 
        {
            break;
        }
        printf("Název: %s, Autor: %s, Rok vydání: %d\n", k.title, k.author, k.year);
    }
    fclose(fileRead);
    return 0;
}
