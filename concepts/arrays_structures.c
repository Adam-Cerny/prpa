// ============================================
// NAPLNĚNÍ POLE STRUKTUR - Všechny způsoby
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char jmeno[50];
    int vek;
    float vyska;
} Osoba;

// ============================================
// 1. INICIALIZACE PŘI DEKLARACI
// ============================================

/*
Nejjednoduššší - vše najednou při deklaraci
Vhodné když znáš data předem
*/

void priklad_1_inicializace()
{
    // Způsob 1: Bez velikosti pole - odvodí se
    Osoba skupinka[] = {
        {"Petr", 25, 180.0},
        {"Anna", 30, 165.0},
        {"Jiří", 35, 175.0}
    };
    
    // sizeof(skupinka) / sizeof(Osoba) = 3
    int pocet = sizeof(skupinka) / sizeof(Osoba);
    
    printf("Počet osob: %d\n", pocet);
    for (int i = 0; i < pocet; i++)
    {
        printf("%s - %d let, %.1f cm\n", 
               skupinka[i].jmeno, 
               skupinka[i].vek,
               skupinka[i].vyska);
    }
}

// ============================================
// 2. ALOKACE A RUČNÍ NAPLNĚNÍ
// ============================================

void priklad_2_staticka_alokace()
{
    // Vytvoř pole 5 osob
    Osoba skupinka[5];
    
    // Naplň prvky ruční
    strcpy(skupinka[0].jmeno, "Petr");
    skupinka[0].vek = 25;
    skupinka[0].vyska = 180.0;
    
    strcpy(skupinka[1].jmeno, "Anna");
    skupinka[1].vek = 30;
    skupinka[1].vyska = 165.0;
    
    strcpy(skupinka[2].jmeno, "Jiří");
    skupinka[2].vek = 35;
    skupinka[2].vyska = 175.0;
    
    // Zbývající (3 a 4) zůstanou neinicializované
    
    printf("Prvních 3 osob:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%s - %d\n", skupinka[i].jmeno, skupinka[i].vek);
    }
}

// ============================================
// 3. DYNAMICKÉ POLE - PŘEČTI POČET
// ============================================

void priklad_3_dynamicke()
{
    int pocet;
    printf("Kolik osob? ");
    scanf("%d", &pocet);
    
    // Alokuj pole
    Osoba *skupinka = (Osoba *)malloc(pocet * sizeof(Osoba));
    
    if (skupinka == NULL)
    {
        fprintf(stderr, "Chyba: malloc!\n");
        return;
    }
    
    // Naplň z klávesnice
    for (int i = 0; i < pocet; i++)
    {
        printf("\nOsoba %d:\n", i + 1);
        
        printf("  Jméno: ");
        scanf("%49s", skupinka[i].jmeno);
        
        printf("  Věk: ");
        scanf("%d", &skupinka[i].vek);
        
        printf("  Výška: ");
        scanf("%f", &skupinka[i].vyska);
    }
    
    // Tiskni
    printf("\n=== SEZNAM OSOB ===\n");
    for (int i = 0; i < pocet; i++)
    {
        printf("%s - %d let, %.1f cm\n",
               skupinka[i].jmeno,
               skupinka[i].vek,
               skupinka[i].vyska);
    }
    
    free(skupinka);
}

// ============================================
// 4. NAPLNĚNÍ POMOCÍ CYKLU
// ============================================

void priklad_4_cyklus()
{
    int pocet = 3;
    Osoba skupinka[3];
    
    // Vygeneruj data
    char jmena[][20] = {"Petr", "Anna", "Jiří"};
    int vek[] = {25, 30, 35};
    float vyska[] = {180.0, 165.0, 175.0};
    
    for (int i = 0; i < pocet; i++)
    {
        strcpy(skupinka[i].jmeno, jmena[i]);
        skupinka[i].vek = vek[i];
        skupinka[i].vyska = vyska[i];
    }
    
    // Tiskni
    for (int i = 0; i < pocet; i++)
    {
        printf("%s - %d\n", skupinka[i].jmeno, skupinka[i].vek);
    }
}

// ============================================
// 5. NAPLNĚNÍ Z FUNKCE
// ============================================

void vytvorOsobu(Osoba *o, const char *jmeno, int vek, float vyska)
{
    strcpy(o->jmeno, jmeno);
    o->vek = vek;
    o->vyska = vyska;
}

void priklad_5_funkcni()
{
    Osoba skupinka[3];
    
    vytvorOsobu(&skupinka[0], "Petr", 25, 180.0);
    vytvorOsobu(&skupinka[1], "Anna", 30, 165.0);
    vytvorOsobu(&skupinka[2], "Jiří", 35, 175.0);
    
    for (int i = 0; i < 3; i++)
    {
        printf("%s - %d\n", skupinka[i].jmeno, skupinka[i].vek);
    }
}

// ============================================
// 6. NAPLNĚNÍ ZE SOUBORU
// ============================================

void priklad_6_ze_souboru()
{
    // Vytvoř test soubor:
    // Petr 25 180.0
    // Anna 30 165.0
    // Jiří 35 175.0
    
    FILE *file = fopen("osoby.txt", "r");
    
    if (file == NULL)
    {
        printf("Soubor neexistuje, přeskočeno\n");
        return;
    }
    
    Osoba skupinka[10];
    int pocet = 0;
    
    // Čti ze souboru
    while (fscanf(file, "%49s %d %f",
                  skupinka[pocet].jmeno,
                  &skupinka[pocet].vek,
                  &skupinka[pocet].vyska) == 3)
    {
        pocet++;
        if (pocet >= 10) break;  // Max 10 osob
    }
    
    fclose(file);
    
    // Tiskni
    printf("Přečteno %d osob:\n", pocet);
    for (int i = 0; i < pocet; i++)
    {
        printf("%s - %d\n", skupinka[i].jmeno, skupinka[i].vek);
    }
}

// ============================================
// 7. MEMSET - VYČISTIT PAMĚŤ
// ============================================

void priklad_7_memset()
{
    Osoba skupinka[3];
    
    // Vyčisti paměť (nastaví všechny byty na 0)
    memset(skupinka, 0, sizeof(skupinka));
    
    // Teď jsou všechny hodnoty 0/NULL
    for (int i = 0; i < 3; i++)
    {
        printf("jmeno='%s', vek=%d\n",
               skupinka[i].jmeno,
               skupinka[i].vek);
    }
}

// ============================================
// 8. REALLOC - ZVĚTŠENÍ POLE
// ============================================

void priklad_8_realloc()
{
    int kapacita = 2;
    int pocet = 0;
    
    // Alokuj na začátek
    Osoba *skupinka = (Osoba *)malloc(kapacita * sizeof(Osoba));
    
    if (skupinka == NULL)
    {
        fprintf(stderr, "Chyba!\n");
        return;
    }
    
    // Přidej osobu
    strcpy(skupinka[pocet].jmeno, "Petr");
    skupinka[pocet].vek = 25;
    pocet++;
    
    strcpy(skupinka[pocet].jmeno, "Anna");
    skupinka[pocet].vek = 30;
    pocet++;
    
    // Pole je plné! Zvětši
    printf("Kapacita byla %d, zvětšuji...\n", kapacita);
    
    kapacita *= 2;  // Zdvoj kapacitu
    Osoba *nove = (Osoba *)realloc(skupinka, kapacita * sizeof(Osoba));
    
    if (nove == NULL)
    {
        fprintf(stderr, "Chyba: realloc!\n");
        free(skupinka);
        return;
    }
    
    skupinka = nove;
    
    // Přidej třetí
    strcpy(skupinka[pocet].jmeno, "Jiří");
    skupinka[pocet].vek = 35;
    pocet++;
    
    printf("Nová kapacita: %d\n", kapacita);
    
    // Tiskni
    for (int i = 0; i < pocet; i++)
    {
        printf("%s - %d\n", skupinka[i].jmeno, skupinka[i].vek);
    }
    
    free(skupinka);
}

// ============================================
// 9. KOPÍROVÁNÍ POLE
// ============================================

void priklad_9_kopie()
{
    // Originál
    Osoba original[2] = {
        {"Petr", 25, 180.0},
        {"Anna", 30, 165.0}
    };
    
    // Kopie
    Osoba kopie[2];
    
    // Způsob 1: Cyklus
    for (int i = 0; i < 2; i++)
    {
        kopie[i] = original[i];  // Přiřazení struktury
    }
    
    // Způsob 2: memcpy (rychlejší)
    // memcpy(kopie, original, sizeof(original));
    
    printf("Originál[0]: %s\n", original[0].jmeno);
    printf("Kopie[0]: %s\n", kopie[0].jmeno);
}

// ============================================
// 10. SWAP - PROHOZENÍ PRVKŮ
// ============================================

void priklad_10_swap()
{
    Osoba skupinka[2] = {
        {"Petr", 25, 180.0},
        {"Anna", 30, 165.0}
    };
    
    printf("Před:\n");
    printf("  [0]: %s\n", skupinka[0].jmeno);
    printf("  [1]: %s\n", skupinka[1].jmeno);
    
    // Prohod
    Osoba temp = skupinka[0];
    skupinka[0] = skupinka[1];
    skupinka[1] = temp;
    
    printf("Po:\n");
    printf("  [0]: %s\n", skupinka[0].jmeno);
    printf("  [1]: %s\n", skupinka[1].jmeno);
}

// ============================================
// SHRNUTÍ - VŠECHNY ZPŮSOBY
// ============================================

/*
1. INICIALIZACE PŘI DEKLARACI:
   Osoba skupinka[] = {
       {"Petr", 25, 180.0},
       {"Anna", 30, 165.0}
   };

2. RUČNÍ NAPLNĚNÍ:
   Osoba skupinka[2];
   strcpy(skupinka[0].jmeno, "Petr");
   skupinka[0].vek = 25;
   ...

3. CYKLUS:
   for (int i = 0; i < pocet; i++) {
       strcpy(skupinka[i].jmeno, ...);
   }

4. DYNAMICKÉ POLE:
   Osoba *skupinka = malloc(pocet * sizeof(Osoba));
   ...
   free(skupinka);

5. REALLOC - ZVĚTŠENÍ:
   skupinka = realloc(skupinka, nova_velikost);

6. ZE SOUBORU:
   fscanf(file, "%49s %d", skupinka[i].jmeno, &skupinka[i].vek);

7. MEMSET - VYČISTIT:
   memset(skupinka, 0, sizeof(skupinka));

8. MEMCPY - KOPÍROVAT:
   memcpy(kopie, original, sizeof(original));

NEJČASTĚJŠÍ CHYBY:
  ❌ strcpy bez kontroly délky - použij strncpy nebo scanf s limitem
  ❌ Přístup za konec pole - vždy si hlídej index!
  ❌ malloc bez free - memory leak!
  ❌ realloc bez temp proměnné - může se ztratit ukazatel
  ❌ Zapomenutí '\0' u řetězců - nemusí skončit s null terminator
*/
