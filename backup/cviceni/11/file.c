#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// upravte program tak, aby bylo možné cestu k souboru zadat jako parametr příkazové řádky
int main(int argc, char *argv[])
{
    // w = write 
    // a = append
    // r = read
    // b = binary

    char *inputFileName = NULL;
    char *outputFileName = NULL;

    for(int i = 0; i < argc; i++) 
    {
        if (strncmp(argv[i], "-i", 2) == 0)
        {
            ++i;
            if (i < argc) 
            {
                inputFileName = argv[i];
            }
            else 
            {
                printf("Chyba: Nebyl zadán název vstupního souboru po přepínači -i.\n");
                return 101;
            }
        }
        if (strncmp(argv[i], "-o", 2) == 0)
        {
            ++i;
            if (i < argc)
            {
                outputFileName = argv[i];
            }
            else
            {
                printf("Chyba: Nebyl zadán název vystupního souboru po přepínači -i.\n");
                return 101;
            }
        }
        if (outputFileName == NULL) 
        {
            fprintf(stderr, "Chyba: Nebyl zadán název výstupního souboru.\n");
            return 102;
        }
    }


    FILE *fileWrite = fopen(outputFileName, "w");
    if (fileWrite == NULL) 
    {
        printf("Chyba při otevírání souboru");
        return 1;
    }
    fprintf(fileWrite, "Hello world\n");
    fprintf(fileWrite, "Hello world\n");
    fprintf(fileWrite, "Hello world\n");
    fclose(fileWrite);

    FILE *fileRead = fopen(inputFileName, "r");
    if (fileRead == NULL) 
    {
        printf("Soubor neexistuje.\n");
        return 100;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fileRead) != NULL) 
    {
        printf("%s", buffer);
    }
    fclose(fileRead);

    return 0;
}
