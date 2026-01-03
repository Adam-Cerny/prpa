#include <stdio.h>
#include <string.h>
#include <inttypes.h>

struct Clovek 
{
    char jmeno[50];
    int vek;
};

typedef struct Clovek StrukturaClovek; 

typedef struct
{
    char jmeno[50];
    int vek;
} ClovekTypedef;

int main(void)
{   
    StrukturaClovek ctvrty_clovek = {"Karel", 40};
    printf("Ctvrty clovek - Jmeno: %s, Vek: %d\n", ctvrty_clovek.jmeno, ctvrty_clovek.vek);
    
    struct Clovek clovek;
    printf("Zadejte jmeno: ");
    scanf("%49s", clovek.jmeno); 
    printf("Zadejte vek: ");
    scanf("%d", &clovek.vek);
    printf("Jmeno: %s, Vek: %d\n", clovek.jmeno, clovek.vek);

    clovek.vek = clovek.vek + 1;
    printf("Po zvyseni veku: Jmeno: %s, Vek: %d\n", clovek.jmeno, clovek.vek);

    strcpy(clovek.jmeno, "Honza");
    printf("Po zmene jmena: Jmeno: %s, Vek: %d\n", clovek.jmeno, clovek.vek);

    struct Clovek druhy_clovek = {"Eva", 30};
    printf("Druhy clovek - Jmeno: %s, Vek: %d\n", druhy_clovek.jmeno, druhy_clovek.vek);

    struct Clovek pole_cloveku[2] = {
        {"Petr", 25},
        {"Anna", 28}
    };
    for (int i = 0; i < 2; i++) {
        printf("Pole cloveku [%d] - Jmeno: %s, Vek: %d\n", i, pole_cloveku[i].jmeno, pole_cloveku[i].vek);
    }

    struct Clovek *ptr_clovek = &clovek;
    ptr_clovek->vek += 5;
    printf("Po zvyseni veku pres ukazatel: Jmeno: %s, Vek: %d\n", ptr_clovek->jmeno, ptr_clovek->vek);

    // sizeof Clovek != sizeof jmeno + sizeof vek (padding 2 bajty)
    int size = sizeof(struct Clovek);
    printf("Velikost struktury Clovek: %d bajtu\n", size);    
    int size_jmeno = sizeof(clovek.jmeno);
    printf("Velikost pole jmeno ve strukture Clovek: %d bajtu\n", size_jmeno);
    int size_vek = sizeof(clovek.vek);
    printf("Velikost pole vek ve strukture Clovek: %d bajtu\n", size_vek);


    // ClovekTypedef clovek2;
    // printf("Zadejte jmeno: ");
    // scanf("%49s", clovek2.jmeno);
    // printf("Zadejte vek: ");
    // scanf("%d", &clovek2.vek);
    // printf("Jmeno: %s, Vek: %d\n", clovek2.jmeno, clovek2.vek);

    return 0;
}
