// Napište program, který načte ze standardního vstupu tři nenulová celá čisla reprezentující strany trojúhelníku a vyhodnotí, zda lze trojúhelník sestrojit.

#include <stdio.h>
#include <stdbool.h>

bool lzeSestrojitTroj(int a, int b, int c)
{
    if((a + b > c) && (b + c > a) && (a + c > b))
    {
        return true;
    }
    return false;
}

int main(void)
{
    int a, b, c;
    printf("Zadej tri nenulove strany trojuhelniku: ");

    // while((a == 0) || (b == 0) || (c == 0))
    // {
    //     printf("Zadej tri nenulove strany trojuhelniku: ");
    //     ret = scanf("%i %i %i", &a, &b, &c);
    // }

    int ret = scanf("%i %i %i", &a, &b, &c);

    if(ret == 3)
    {
        printf("Strany jsou %i, %i, %i\n", a, b, c);
    }
    else 
    {
        printf("Nebyly nacteny 3 hodnoty.\n");
        return 100;
    }

    if(lzeSestrojitTroj(a, b, c))
    {
        printf("Trojuhelnik lze sestrojit.\n");
    }
    else 
    {
        printf("Trojuhelnik nelze sestrojit.\n");
    }

    return 0;
}
