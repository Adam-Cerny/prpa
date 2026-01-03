#include <stdio.h>

void vypisCtverecek(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void vypisTrojuhelnik1(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void vypisTrojuhelnik2(int n)
{
    for (int i = 0; i < n; i++)
    {
        // mezery na začátku
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        // hvězdičky
        for (int j = 0; j <= i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void vypisTrojuhelnik3(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

void vypisTrojuhelnik4(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < n - i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
}

int main(void)
{
    int n = 5;

    printf("(a) Čtverec:\n");
    vypisCtverecek(n);
    printf("\n");

    printf("(b) Levý rostoucí trojúhelník:\n");
    vypisTrojuhelnik1(n);
    printf("\n");

    printf("(c) Pravý rostoucí trojúhelník:\n");
    vypisTrojuhelnik2(n);
    printf("\n");

    printf("(d) Pravý klesající trojúhelník:\n");
    vypisTrojuhelnik3(n);
    printf("\n");

    printf("(e) Levý klesající trojúhelník:\n");
    vypisTrojuhelnik4(n);
    printf("\n");

    return 0;
}
