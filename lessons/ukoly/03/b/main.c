#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define MIN 0
#define MAX 100

int main(void) {    
    // deklarace promenne, do ktere se nasledne bude ukladat hodnota cisla kazdou iteraci
    int cislo;
    // promenna pro predchozi cislo, aby se dalo porovnavat s momentalnim cislem
    int prev;
    // promenna pro skore, nastavena na 0, aby se k ni dalo pricitat 
    int score = 0;
    // promenna, ktera urcuje zdali probehl prvni pruchod cyklem
    int prvni = FALSE;

    // hlavni cyklus, postupne nacita cisla ze seznamu
    while (scanf("%i", &cislo) == 1)
    {  
        // kontrola zdali je cislo prvni
        if (!prvni)
        {
            // promenne prev priradime hodnotu cisla, jelikoz se muze jednat o radu
            prev = cislo;
            // zmenime pravdivost prvniho
            prvni = TRUE;
        }

        // kontrola zdali je cislo stejne jako predchozi cislo
        if (cislo == prev)
        {
            // pricteni skore
            score++;
        }

        // pokud cislo neni stejne jako predchozi
        else
        {
            // pokud je skore vetsi nez 1
            if (score > 1)
            {
                // vypis skore
                printf("%ix %i\n", score, prev);
            }
            // reset skore
            score = 1;
        } 

        // kontrola intervalu
        if ((cislo > MAX) || (cislo < MIN))
        {
            printf("Error: Vstup je mimo interval!\n");
            return 100;
        }

        // posun cisla
        prev = cislo;
    
    }

    // osetreni posledniho skore, jelikoz v cyklu by k vypisu nikdy nedoslo
    if (score > 1)
    {
        printf("%ix %i\n", score, prev);
    }

    return 0;
}
