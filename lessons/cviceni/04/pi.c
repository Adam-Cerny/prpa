#include <stdio.h>
#include <math.h>

int main(void)
{
    double citatel, jmenovatel, zlomek;
    double suma = 0.0;
    double predchozi_suma;
    int i = 0;
    double presnost = 1e-6; 

    do {
        predchozi_suma = suma;

        if ((i % 2) == 0)
            citatel = 1;
        else
            citatel = -1;

        jmenovatel = 2 * i + 1;
        zlomek = citatel / jmenovatel;

        suma += zlomek;
        i++;
    } while (fabs(suma - predchozi_suma) > presnost);

    suma *= 4; 

    printf("Pi ≈ %.6f\n", suma);
    printf("Pocet clenu: %d\n", i);

    return 0;
}
