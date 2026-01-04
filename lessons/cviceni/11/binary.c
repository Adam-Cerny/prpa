#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    FILE *outputFile = fopen("data.bin", "wb");
    if (outputFile == NULL) 
    {
        fprintf(stderr, "Chyba při otevírání souboru");
        return 100;
    }

    for (int i = 0; i < 10; i++) 
    { 
        int number = i + 1;
        fwrite(&number, sizeof(int), 1, outputFile);
    }
    fclose(outputFile);


    FILE *inputFile = fopen("data.bin", "rb");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Chyba při otevírání souboru");
        return 101;
    }

    int number;
    while (fread(&number, sizeof(int), 1, inputFile) == 1) 
    {
        printf("%d\n", number);
    }

    fseek(inputFile, 4 * sizeof(int), SEEK_SET);

    while (fread(&number, sizeof(int), 1, inputFile) == 1)
    {
        printf("%d\n", number);
    }

    fclose(inputFile);

    return 0;
}
