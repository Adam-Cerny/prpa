//Napište program, který načte jeden znak (datový typ char) a tento znak klasifikuje do některé z následujících množin:

#include <stdio.h>
#include <stdbool.h>

#define ZNAK_MALE_PISMENO 1
#define ZNAK_VELKE_PISMENO 2

int klasifikaceZnaku(char c)
{
    if((c >= 'a') && (c <= 'z'))
    {
        return ZNAK_MALE_PISMENO;
    }
    else if((c >= 'A') && (c <= 'Z'))
    {
        return 2;
    }
    else if((c >= '0') && (c <= '9'))
    {
        return 3;
    }
    return 4;
}

int klasifikaceZnaku2(char c)
{
    int ret = 0;
    switch(c)
    {
        case 'a'...'z':
            ret = 1;
            break;
        case 'A'...'Z':
            ret = 2;
            break;
        case '0'...'9':
            ret = 3;
            break;
        default:
            ret = 4;
            break;
    }
}

int main(void)
{
    char znak;

    if(scanf("%c", &znak) != 1)
    {
        printf("Nebyl nacten znak.\n");
        return 100;
    }

    int typ = klasifikaceZnaku(znak);
    printf("Typ znaku: %i\n", typ);

    switch (typ)
    {
    case 1:
        printf("Male pismeno.\n");
        break;

    case 2:
        printf("Velke pismeno.\n");
        break;

    case 3:
        printf("Cislo.\n");
        break;

    default:
        printf("Jiny znak.\n");
        break;
    }

    return 0;
}