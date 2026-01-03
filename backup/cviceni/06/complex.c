#include <stdio.h>
#include "complex.h"

complex_t secti(complex_t c1, complex_t c2)
{
    c1.re += c2.re;
    c1.im += c2.im;
    return c1;
}

void vystiskni(complex_t c)
{
    if (c.im < 0.0)
    {
        printf("%f - j%f", c.re, -c.im);
    }
    else 
    {
        printf("%f + j%f", c.re, -c.im);
    }
}


int main(void)
{
    complex_t cislo1 = {1.5, 2.5};
    complex_t cislo2 =
    {
        .re = 7.2,
        .im = -5.5,
    };

    // printf("%i", secti(cislo1, cislo2));

    printf("Cislo 1: ");
    vystiskni(cislo1);
    printf("\n");

    printf("Cislo 2: ");
    vystiskni(cislo2);
    printf("\n");

    complex_t cislo3 = secti(cislo1, cislo2);
    printf("Cislo 3: ");
    vystiskni(cislo3);
    printf("\n");

    return 0;
}