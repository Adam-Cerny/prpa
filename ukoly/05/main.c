#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
 
// navratove hodnoty
#define ERROR_NUMBER 100
#define ERROR_INTERVAL 101
#define ERROR_ODD 102
#define ERROR_FENCE 103
 
// krajni meze intervalu
#define MIN 3
#define MAX 69
 
// pomocna funkce pro vypis error message a navratu hodnoty
int error(char *message, int code)
{
    fprintf(stderr, "%s\n", message);
    exit(code);
}
 
// validace vstupu
int validateInput(int ret, int sirka, int vyska, int plot)
{
    if (ret == 0)
    {
        return error("Error: Chybny vstup!", ERROR_NUMBER);
    }
 
    if ((ret >= 1 && (sirka < MIN || sirka > MAX)) || (ret >= 2 && (vyska < MIN || vyska > MAX)) || (ret == 3 && (plot < MIN || plot > MAX)))
    {
        return error("Error: Vstup mimo interval!", ERROR_INTERVAL);
    }
 
    if ((sirka % 2) != 1 && (ret > 1))
    {
        return error("Error: Sirka neni liche cislo!", ERROR_ODD);
    }
 
    if ((ret == 3) && (plot > vyska))
    {
        return error("Error: Neplatna velikost plotu!", ERROR_FENCE);
    }
 
    return 0;
}
 
// funkce pro vykresleni tela a plotu
void telo(int sirka, int vyska, int vypln, int plot)
{
    // vertikalni pruchod
    for (int i = 0; i < vyska; i++)
    {
        // horizontalni pruchod
        for (int j = 0; j < sirka; j++)
        {
            // 'X' tiskneme kdyz jsme na zacatku nebo na konci horizontalne i diagonalne
            if ((i == 0) || (j == 0) || (i == (vyska - 1)) || (j == (sirka - 1)))
            {
                printf("X");
            }
            // kdyz jsme uprostred
            else
            {
                // kontrola zdali volame funkci s vyplni
                if (vypln)
                {
                    // diagonala pro 'o'
                    if (((i + j) % 2) == 0)
                    {
                        printf("o");
                    }
                    // diagonala pro '*'
                    else
                    {
                        printf("*");
                    }
                }
                // kdyz nepotrebujeme vypln tak vlozime pouze ' '
                else
                {
                    printf(" ");
                }
            }
        }
 
        // kontrola zdali se aktualni radek nachazi v oblasti kde ma byt plot
        if ((plot > 0) && (i >= (vyska - plot)))
        {
            // index radku plotu
            int radek_plotu = i - (vyska - plot);
 
            if ((plot % 2) == 0)
            {
                // tiskneme 2 znaky naraz
                for (int k = 0; k < (plot / 2); k++)
                {
                    // kdyz je ve vrchni nebo spodni pozici
                    if ((radek_plotu == 0) || (radek_plotu == (plot - 1)))
                    {
                        printf("-|");
                    }
                    // kdyz je uprostred
                    else
                    {
                        printf(" |");
                    }
                }
            }
            else
            {
                for (int k = 0; k < plot / 2; k++)
                {
                    printf("|");
                    // kdyz je ve vrchni nebo spodni pozici
                    if ((radek_plotu == 0) || (radek_plotu == (plot - 1)))
                    {
                        printf("-");
                    }
                    // kdyz je uprostred
                    else
                    {
                        printf(" ");
                    }
                }
                printf("|");
            }
        }
        // novy radek
        printf("\n");
    }
}
 
// funkce pro vykresleni strechy
void strecha(int sirka)
{
    // vypocet vysky strechy
    int vyska = (sirka + 1) / 2;
 
    // vertikalni pruchod
    for (int i = 1; i < vyska; i++)
    {
        // mezery nalevo od 'X'
        for (int j = 1; j <= (vyska - i); j++)
        {
            printf(" ");
        }
        printf("X");
 
        // prazdna plocha uprostred
        if (i > 1)
        {
            // rovnomerny rust s kazdym radkem dolu
            for (int k = 1; k <= 2 * i - 3; k++)
            {
                printf(" ");
            }
            printf("X");
        }
        // novy radek
        printf("\n");
    }
}
 
// funkce pro podukol A
void A(int sirka)
{
    telo(sirka, sirka, 0, 0);
}
 
// funkce pro podukol B
void B(int sirka, int vyska)
{
    strecha(sirka);
    telo(sirka, vyska, sirka == vyska, 0);
}
 
// funkce pro podukol C
void C(int sirka, int vyska, int plot)
{
    strecha(sirka);
    telo(sirka, vyska, sirka == vyska, plot);
}
 
int main(void)
{
    int sirka, vyska, plot, retHelper;
    int ret = 0;
     
    retHelper = scanf("%i", &sirka);
    if (retHelper == 1)
    {
        ret++;
        retHelper = 0;
    }
    else if (retHelper == 0)
    {
        error("Error: Chybny vstup!", ERROR_NUMBER);
    }
 
    retHelper = scanf("%i", &vyska);
    if (retHelper == 1)
    {
        ret++;
        retHelper = 0;
    }
    else if (retHelper == 0)
    {
        error("Error: Chybny vstup!", ERROR_NUMBER);
    }
 
    retHelper = scanf("%i", &plot);
    if (retHelper == 1)
    {
        ret++;
        retHelper = 0;
    }
    else if (retHelper == 0)
    {
        error("Error: Chybny vstup!", ERROR_NUMBER);
    }
 
    // validace vstupu, pokud nedostaneme hodnotu 0 tak vracime danou hodnotu (100-103)
    int code = validateInput(ret, sirka, vyska, plot);
    if (code != 0)
    {
        return code;
    }
 
    // switch ktery rozezna podle poctu nactenych promennych o ktery podukol se jedna
    switch (ret)
    {
    case 1:
        A(sirka);
        break;
    case 2:
        B(sirka, vyska);
        break;
    case 3:
        C(sirka, vyska, plot);
    default:
        break;
    }
}
