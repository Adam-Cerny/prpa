#include <stdio.h>

#define MIN 10
#define MAX 15

void vypisRady(void)
{
    int cislo;
    //while ret
    for (int i = 0; i < 20; i++)
    {
        scanf("%i", &cislo);

        if (cislo >= MIN && cislo <= MAX)
        {
            printf("%i\n", cislo);
        }
    }    
}

void vypisFor(void)
{
    int cislo = 1;
    for (int i = 0; i < 10; i++)
    {
        printf("%i ", cislo);
        cislo++;
    }
    printf("\n");
}

void vypisWhile(void)
{
    int cislo = 1;
    while (cislo <= 10)
    {
        printf("%i ", cislo);
        cislo++;
    }
    printf("\n");
}

void vypisDoWhile(void)
{
    int cislo = 1;
    do
    {
        printf("%i ", cislo);
        cislo++;        
    } while (cislo <= 10);
    printf("\n");
}

void vypisBreak(void)
{
    for (int i = 1; ; i++)
    {
        if (i > 10)
        {
            break;
        }
        printf("%i ", i);
    }
    printf("\n");
}

void vypisSuda(int n)
{
    int cislo = 1;

    for (int i = 0; i < n; i++)
    {
        if ((cislo % 2) == 0)
        {
            printf("%i ", cislo);
        }
        cislo++;
    }
    printf("\n");
}

int main(void) 
{
    //vypisRady();

    //vypisFor();

    //vypisWhile();

    //vypisDoWhile();

    //vypisBreak();

    // int n;
    // scanf("%i", &n);
    // vypisSuda(n);

    return 0;
}
