#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

void upperCase(char* c)
{
    if (*c >= 'a' && *c <= 'z')
    {
        *c &= ~0x20; //bitova maska ... nastaveni 6. bitu na 0
    }
}

void lowerCase(char* c)
{
    if (*c >= 'A' && *c <= 'Z')
    {
        *c |= 0x20; //bitova maska ... nastaveni 6. bitu na 1
    }
}

void toggleCase(char* c)
{
    if ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z'))
    {
        *c ^= 0x20; //bitova maska ... prepnuti 6. bitu
    }
}

int main(int argc, char* argv[])
{
    int type = 0; // 0 - none, 1 - upper, 2 - lower, 3 - toggle

    for (int i = 0; i < argc; i++)
    {
        printf("arg %d: %s\n", i, argv[i]);
        if (strcmp(argv[i], "-u") == 0)
        {
            type = 1;
        }
        else if (strcmp(argv[i], "-l") == 0)
        {
            type = 2;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            type = 3;
        }
    }

    char** slovnik = malloc(30 * sizeof(char*));
    int noWords = 0;

    while (TRUE)
    {
        char c;
        char word[10];

        if (scanf("%s", word) != 1)
        {
            break; 
        }
        // switch (type)
        // {
        // case 1:
        //     upperCase(&c);
        //     break;
        // case 2:
        //     lowerCase(&c);
        //     break;
        // case 3:
        //     toggleCase(&c);
        //     break;
        // default:
        //     break;
        // }
        slovnik[noWords] = malloc((strlen(word) + 1));
        strcpy(&slovnik[noWords], word);
        noWords++;
        printf("%s\n", word);
    }

    for (int i = 0; i < noWords; i++)
    {
        printf("word %d: %s\n", i, &slovnik[i]);
    }



    return 0;
}
