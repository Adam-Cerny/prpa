#include <stdio.h>
#include <string.h>

#define MIN -1000
#define MAX 1000

int main(void)
{
    // deklarace promennych
    int a, b, c;
    char zprava[25];

    // inicializace promennych
    int ret = scanf("%d %d %d", &a, &b, &c);

    // kontrola poctu vstupu
    if (ret != 3)
    {
        return 1;
    }

    // vypocet pro diskriminant
    int diskriminant = b*b - 4*a*c;

    // kontrola, zdali je diskriminant v intervalu pozadovanem
    if (diskriminant > MAX || diskriminant < MIN)
    {
        printf("Diskriminant mimo povoleny interval!\n");
    }

    else 
    {
    // uprava zpravy podle poctu korenu
    if (diskriminant > 0) 
    {
        strcpy(zprava, "Dva realne koreny");
    }
    else if (diskriminant < 0) 
    {
        strcpy(zprava, "Dva imaginarni koreny");
    }
    else 
    {
        strcpy(zprava, "Jeden koren");
    }

    // vypis formatovane tabulky
    printf("+-----+-----+-----+-----+\n");
    printf("|%4d |%4d |%4d |%4d |\n", a, b, c, diskriminant);
    printf("+-----+-----+-----+-----+\n");
    printf("| %21s |\n", zprava);
    printf("+-----------------------+\n");
    }

    return 0;
}
