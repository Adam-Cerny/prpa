#include <stdio.h>

#define MAX 10000
#define MIN -10000

int main(void) 
{
    // deklarace promennych pro cisla na vstupu
    int n1, n2;

    // prirazeni hodnot od uzivatele (dve cela cisla oddelena mezerou)
    int ret = scanf("%d %d", &n1, &n2);

    // kontrola, zda byly zadany dve cisla
    if (ret != 2)
    {
        return 1;
    }

    // podminka pro validaci vstupu, zdali jsou cisla v intervalu
    if ((n1 < MIN || n1 > MAX) || (n2 < MIN || n2 > MAX))
    {
        printf("Vstup je mimo interval!\n");
    }
    else 
    {
        // vypis v dekadickem tvaru
        printf("Desitkova soustava: %d %d\n", n1, n2);

        // vypis v hexadecimalnim tvaru
        printf("Sestnactkova soustava: %x %x\n", n1, n2);

        // soucet
        int soucet = n1 + n2; 
        printf("Soucet: %d + %d = %d\n", n1, n2, soucet);

        // rozdil 
        int rozdil = n1 - n2;
        printf("Rozdil: %d - %d = %d\n", n1, n2, rozdil);

        // soucin
        int soucin = n1 * n2;
        printf("Soucin: %d * %d = %d\n", n1, n2, soucin);

        // podil s podminkou delitelnosti (jmenovatel nesmi byt 0)
        if (n2 == 0) 
        {
            printf("Nedefinovany vysledek!\n");
        }
        else 
        {
            int podil = n1 / n2;
            printf("Podil: %d / %d = %d\n", n1, n2, podil);
        }

        // prumer, je potreba pretypovat soucet na float
        float prumer = (float)soucet / 2;
        printf("Prumer: %.1f\n", prumer);
    }

    return 0;
}
