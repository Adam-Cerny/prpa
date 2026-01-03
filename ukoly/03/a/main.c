#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define MIN -10000
#define MAX 10000

int main(void) {
    // deklarace promenne pro jednotlive cislo, ktere bude nacitano  
    int cislo;

    // boolean pro urceni prvniho cisla, coz nasledovne slouzi k optimalizaci vypisu cisel oddelenych carkami
    int prvni = FALSE;

    // iniciliaze pocetnich promennych na 0, aby se k nim nasledovne dalo pricitat ve smycce
    int pocet_cisel = 0;
    int pocet_kladnych = 0;
    int pocet_zapornych = 0;
    int pocet_sudych = 0;
    int pocet_lichych = 0;
    long sum = 0;

    // deklarace procentualnich promennych typu float, jelikoz potrebujeme 2 desetinna mista
    float procento_kladnych;
    float procento_zapornych;
    float procento_sudych;
    float procento_lichych;
    float prumer;

    // promenne pro maximum a minimum ze vsech cisel a prirazeni hodnot aby se daly porovnavat
    int maximum = -10000;
    int minimum = 10000;

    // hlavni cyklus - nacitani cisel z rady dokavad nejake existuje (scanf vraci hodnoty podle toho, kolik promennych nacte)
    while (scanf("%i", &cislo) == 1)
    {
        // kontrola zdali je cislo v intervalu, kdyz ne tak vytiskne chybovou hlasku a vrati 100
        if ((cislo > MAX) || (cislo < MIN))
        {
            printf("\nError: Vstup je mimo interval!\n");
            return 100;
        }

        // kdyz jeste prvni cislo nebylo tak se vytiskne bez carky
        if (prvni == FALSE)
        {
            printf("%i", cislo);
        }
        // od druheho cisla dale se tiskne cislo s carkou pred
        else 
        {
            printf(", %i", cislo);
        }

        // prvni cislo bylo vypsano, tak zmenime hodnotu bool
        prvni = TRUE; 

        // pricteni k poctu cisel
        pocet_cisel++;
        
        // pridani hodnoty cisla do souctu
        sum = sum + cislo;

        // kontrola zdali je cislo kladne ci zaporne a nasledne pricteni poctu 
        if (cislo > 0)
        {
            pocet_kladnych++;
        }
        else if (cislo < 0)
        {
            pocet_zapornych++;
        }

        // kontrola zdali je cislo delitelne dvema beze zbytku (sude) ci ne (liche) a nesledne pricteni poctu
        if ((cislo % 2) == 0)
        {
            pocet_sudych++;
        }
        else 
        {
            pocet_lichych++;
        }

        // porovnani cisla s maximem a minimem a pripadna aktualizace nove hodnoty
        if (cislo > maximum)
        {
            maximum = cislo;
        }

        if (cislo < minimum)
        {
            minimum = cislo;
        }
    }

    // dopocteni pomeru a vyjadreni v procentech
    procento_kladnych = ((float) pocet_kladnych/(float) pocet_cisel) * 100;
    procento_zapornych = ((float) pocet_zapornych/(float) pocet_cisel) * 100;
    procento_sudych = ((float) pocet_sudych/(float) pocet_cisel) * 100;
    procento_lichych = ((float) pocet_lichych/(float) pocet_cisel) * 100;

    // vypocet prumeru
    prumer = (float) sum / (float) pocet_cisel;

    // pripad ze vlozime nula cisel
    if (pocet_cisel == 0)
    {
        pocet_kladnych = 0;
        pocet_zapornych = 0;
        procento_kladnych = 0;
        procento_zapornych = 0;
        pocet_sudych = 0;
        pocet_lichych = 0;
        procento_sudych = 0;
        procento_lichych = 0;
        prumer = 0;
        maximum = 0;
        minimum = 0;
    }

    // vypisy do konsole 
    printf("\nPocet cisel: %i\n", pocet_cisel);
    printf("Pocet kladnych: %i\n", pocet_kladnych);
    printf("Pocet zapornych: %i\n", pocet_zapornych);
    printf("Procento kladnych: %.2f\n", procento_kladnych);
    printf("Procento zapornych: %.2f\n", procento_zapornych);
    printf("Pocet sudych: %i\n", pocet_sudych);
    printf("Pocet lichych: %i\n", pocet_lichych);
    printf("Procento sudych: %.2f\n", procento_sudych);
    printf("Procento lichych: %.2f\n", procento_lichych);
    printf("Prumer: %.2f\n", prumer);
    printf("Maximum: %i\n", maximum);
    printf("Minimum: %i\n", minimum);

    return 0;
}
