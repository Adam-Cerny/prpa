#include <stdio.h>

int main(void){
    int a = 5;  // vytvoreni promenne a a nastaveni na hodnotu 5
    int b;
    b = -4;
    double pi = 3.141592654;

    printf("Hello world.\n");
    printf("a = %d\n", a);  // predani celeho cisla na stdout (promenna a)
    printf("b = %d\n", b);
    printf("\t%d\n\t%d\n", a, b);
    printf("pi = %.20lf\n", pi);
    printf("pi = %10.6lf\n", pi);

    scanf("%d", &a);
    printf("a = %d\n", a);

    int ret = scanf("%d %d", &a, &b);
    if(ret == 2){
        printf("Nactene hodnoty jsou: %d, %d\n", a, b);
    }
    else {
        printf("Nastala chyba pri nacitani hodnot.\n");
    }

    return 100;
}
