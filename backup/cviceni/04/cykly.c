#include <stdio.h>

int main(void)
{

    // for (int i = 2; i <= n; i+=2)
    // {
    //     printf("%i ", i);
    // }
    // printf("\n");

    // do
    // {
    //     printf("%i ", k);
    //     k += 2;
    // }
    // while (k <= n);

    // printf("\n");    


    // for (int i = 1; ; i++)
    // {
    //     if (i > 10)
    //     {
    //         break;
    //     }
    //     printf("%i ", i);
    // }
    // printf("\n");

    // while (1)
    // {

    //     if (k > n)
    //     {
    //         break;
    //     }

    //     printf("%i ", k);
    //     k += 2;
    // }
    // printf("\n");

    // int n;
    // scanf("%i", &n);
    // // int k = 2;

    // long soucin = 1;

    // for (int i = 2; i <= n; i += 2)
    // {
    //     soucin *= i;
    // }

    // printf("soucin finalni: %li\n", soucin);

    int n = 20;
    int i = 2;
    long int soucin = 1;
    do
    {
        soucin = soucin * i;
        i = i + 2;
    } while (i <= n);
    
    printf("Soucin: %li\n", soucin);

    // do
    // {
    //     int cislo;
    //     int ret = scanf("%i", &cislo);
    //     if (ret == 1)
    //     {
    //         printf("%i", cislo);
    //     }
    //     // else if (ret == 0)
    //     // {

    //     // }
    // } 
    // while (1);
    

    return 0;
}   
