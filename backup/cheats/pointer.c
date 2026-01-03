#include <stdio.h>

int main(void)
{
    // hodnota (adresa) ukazatele 
    // hodnota na kterou ukazatel ukazuje *
    int a = 10;
    int *p; 
    p = &a;

    printf("Hodnota a: %d\n", a);           
    printf("Adresa a: %p\n", &a);

    printf("Hodnota p (adresa a): %p\n", p);
    printf("Hodnota na kterou p ukazuje: %d\n", *p);

    puts("");
    *p = 20;

    printf("Hodnota a: %d\n", a);
    printf("Adresa a: %p\n", &a);

    printf("Hodnota p (adresa a): %p\n", p);
    printf("Hodnota na kterou p ukazuje: %d\n", *p);
    
    return 0;
}
