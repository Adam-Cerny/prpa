// ============================================
// QSORT - Templaty na řazení
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. QSORT NA INT - VZESTUPNĚ
// ============================================

/*
qsort(pole, pocet, sizeof(prvku), komparator);

Komparátor vrací:
  < 0  pokud a < b
  = 0  pokud a == b
  > 0  pokud a > b
*/

// Komparátor - int vzestupně
int compare_int_asc(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    
    // Bezpečný způsob (bez overflow):
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
    
    // Nebo krátce (ale pozor na overflow!):
    // return *(int *)a - *(int *)b;
}

void priklad_1_int_asc()
{
    int pole[] = {5, 2, 8, 1, 9, 3};
    int pocet = 6;
    
    printf("Před: ");
    for (int i = 0; i < pocet; i++) printf("%d ", pole[i]);
    printf("\n");
    
    qsort(pole, pocet, sizeof(int), compare_int_asc);
    
    printf("Po:   ");
    for (int i = 0; i < pocet; i++) printf("%d ", pole[i]);
    printf("\n");
}

// ============================================
// 2. QSORT NA INT - SESTUPNĚ
// ============================================

int compare_int_desc(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    
    if (x > y) return -1;  // Obrácené!
    if (x < y) return 1;
    return 0;
}

void priklad_2_int_desc()
{
    int pole[] = {5, 2, 8, 1, 9, 3};
    int pocet = 6;
    
    qsort(pole, pocet, sizeof(int), compare_int_desc);
    
    printf("Sestupně: ");
    for (int i = 0; i < pocet; i++) printf("%d ", pole[i]);
    printf("\n");
}

// ============================================
// 3. QSORT NA FLOAT
// ============================================

int compare_float(const void *a, const void *b)
{
    float x = *(float *)a;
    float y = *(float *)b;
    
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

void priklad_3_float()
{
    float pole[] = {3.5f, 1.2f, 4.8f, 2.1f};
    int pocet = 4;
    
    qsort(pole, pocet, sizeof(float), compare_float);
    
    printf("Float: ");
    for (int i = 0; i < pocet; i++) printf("%.1f ", pole[i]);
    printf("\n");
}

// ============================================
// 4. QSORT NA ŘETĚZCE
// ============================================

/*
Řetězce jsou char*
Pole je char** (pole ukazatelů)
*/

int compare_string(const void *a, const void *b)
{
    // a a b jsou ukazatele na (char*)
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    
    return strcmp(str1, str2);
}

void priklad_4_string()
{
    // Pole UKAZATELŮ na řetězce!
    const char *slova[] = {"zebra", "apple", "mango", "banana"};
    int pocet = 4;
    
    printf("Před: ");
    for (int i = 0; i < pocet; i++) printf("%s ", slova[i]);
    printf("\n");
    
    // MUSÍŠ CASTAT na (char**)!
    qsort(slova, pocet, sizeof(const char *), compare_string);
    
    printf("Po:   ");
    for (int i = 0; i < pocet; i++) printf("%s ", slova[i]);
    printf("\n");
}

// ============================================
// 5. QSORT NA STRUKTURU
// ============================================

typedef struct {
    char jmeno[50];
    int vek;
    float vyska;
} Osoba;

// Komparátor - podle věku
int compare_osoba_vek(const void *a, const void *b)
{
    Osoba *o1 = (Osoba *)a;
    Osoba *o2 = (Osoba *)b;
    
    if (o1->vek < o2->vek) return -1;
    if (o1->vek > o2->vek) return 1;
    return 0;
}

// Komparátor - podle jména
int compare_osoba_jmeno(const void *a, const void *b)
{
    Osoba *o1 = (Osoba *)a;
    Osoba *o2 = (Osoba *)b;
    
    return strcmp(o1->jmeno, o2->jmeno);
}

// Komparátor - podle výšky (sestupně)
int compare_osoba_vyska(const void *a, const void *b)
{
    Osoba *o1 = (Osoba *)a;
    Osoba *o2 = (Osoba *)b;
    
    if (o1->vyska > o2->vyska) return -1;
    if (o1->vyska < o2->vyska) return 1;
    return 0;
}

void priklad_5_struktura()
{
    Osoba skupinka[] = {
        {"Petr", 25, 180.0},
        {"Anna", 30, 165.0},
        {"Jiří", 35, 175.0},
        {"Jana", 28, 170.0}
    };
    int pocet = 4;
    
    // Řaď podle věku
    qsort(skupinka, pocet, sizeof(Osoba), compare_osoba_vek);
    
    printf("Podle věku:\n");
    for (int i = 0; i < pocet; i++)
    {
        printf("  %s - %d let\n", skupinka[i].jmeno, skupinka[i].vek);
    }
    
    printf("\n");
    
    // Řaď podle jména
    qsort(skupinka, pocet, sizeof(Osoba), compare_osoba_jmeno);
    
    printf("Podle jména:\n");
    for (int i = 0; i < pocet; i++)
    {
        printf("  %s - %d let\n", skupinka[i].jmeno, skupinka[i].vek);
    }
}

// ============================================
// 6. QSORT - JEDNODUCHÉ ŠABLONY
// ============================================

/*
ŠABLONA 1: INT
--------
int compare(const void *a, const void *b) {
    int x = *(int *)a;
    int y = *(int *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

qsort(pole, pocet, sizeof(int), compare);


ŠABLONA 2: FLOAT
--------
int compare(const void *a, const void *b) {
    float x = *(float *)a;
    float y = *(float *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

qsort(pole, pocet, sizeof(float), compare);


ŠABLONA 3: STRING (pole ukazatelů!)
--------
int compare(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

const char *slova[] = {"b", "a", "c"};
qsort(slova, 3, sizeof(const char *), compare);


ŠABLONA 4: STRUKTURA
--------
typedef struct {
    int x;
    char jmeno[50];
} Data;

int compare(const void *a, const void *b) {
    Data *d1 = (Data *)a;
    Data *d2 = (Data *)b;
    if (d1->x < d2->x) return -1;
    if (d1->x > d2->x) return 1;
    return 0;
}

Data pole[] = {...};
qsort(pole, pocet, sizeof(Data), compare);
*/

// ============================================
// 7. PRAKTICKÉ PŘÍKLADY - ČTENÍ Z VSTUPU
// ============================================

void priklad_7_dynamicke()
{
    int pocet;
    printf("Kolik čísel? ");
    scanf("%d", &pocet);
    
    int *pole = (int *)malloc(pocet * sizeof(int));
    
    if (pole == NULL)
    {
        fprintf(stderr, "Chyba!\n");
        return;
    }
    
    // Čti čísla
    printf("Zadej čísla: ");
    for (int i = 0; i < pocet; i++)
    {
        scanf("%d", &pole[i]);
    }
    
    // Řaď
    qsort(pole, pocet, sizeof(int), compare_int_asc);
    
    // Tiskni
    printf("Seřazená: ");
    for (int i = 0; i < pocet; i++)
    {
        printf("%d ", pole[i]);
    }
    printf("\n");
    
    free(pole);
}

// ============================================
// 8. DUPLIKÁTY - ODSTRANĚNÍ
// ============================================

void priklad_8_bez_duplikatu()
{
    int pole[] = {5, 2, 5, 8, 2, 1, 9, 3, 5};
    int pocet = 9;
    
    // Nejdřív řaď
    qsort(pole, pocet, sizeof(int), compare_int_asc);
    
    printf("Seřazená: ");
    for (int i = 0; i < pocet; i++) printf("%d ", pole[i]);
    printf("\n");
    
    // Teď odstran duplikáty
    int j = 0;
    for (int i = 1; i < pocet; i++)
    {
        if (pole[i] != pole[j])
        {
            pole[++j] = pole[i];
        }
    }
    pocet = j + 1;
    
    printf("Bez duplikátů (%d prvků): ", pocet);
    for (int i = 0; i < pocet; i++) printf("%d ", pole[i]);
    printf("\n");
}

// ============================================
// 9. HLEDÁNÍ PRVKU - BSEARCH PO QSORT
// ============================================

int priklad_9_bsearch()
{
    int pole[] = {5, 2, 8, 1, 9, 3};
    int pocet = 6;
    
    // Nejdřív řaď!
    qsort(pole, pocet, sizeof(int), compare_int_asc);
    
    printf("Seřazené: ");
    for (int i = 0; i < pocet; i++) printf("%d ", pole[i]);
    printf("\n");
    
    // Hledej 8
    int hledany = 8;
    int *vysledek = (int *)bsearch(&hledany, pole, pocet, sizeof(int), compare_int_asc);
    
    if (vysledek != NULL)
    {
        printf("Číslo %d nalezeno! Hodnota: %d\n", hledany, *vysledek);
        return 1;
    }
    else
    {
        printf("Číslo %d nenalezeno\n", hledany);
        return 0;
    }
}

// ============================================
// 10. CUSTOM FUNKCE SE STAVEM
// ============================================

/*
Problém: qsort nedovoluje předat další parametr
Řešení: Použij globální proměnnou nebo bsearch s vlastní implementací
*/

static int trzeba_desc = 0;  // Globální - hack

int compare_int_flexible(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;
    
    int vysledek;
    if (x < y) vysledek = -1;
    else if (x > y) vysledek = 1;
    else vysledek = 0;
    
    return trzeba_desc ? -vysledek : vysledek;
}

void priklad_10_flexible()
{
    int pole[] = {5, 2, 8, 1, 9};
    int pocet = 5;
    
    // Vzestupně
    trzeba_desc = 0;
    qsort(pole, pocet, sizeof(int), compare_int_flexible);
    printf("Asc: ");
    for (int i = 0; i < pocet; i++) printf("%d ", pole[i]);
    printf("\n");
    
    // Sestupně
    trzeba_desc = 1;
    qsort(pole, pocet, sizeof(int), compare_int_flexible);
    printf("Desc: ");
    for (int i = 0; i < pocet; i++) printf("%d ", pole[i]);
    printf("\n");
}

// ============================================
// SHRNUTÍ - ZÁKLADNÍ TEMPLATE
// ============================================

/*
ZÁKLADNÍ POSTUP:

1. Napiš komparátor:
   int compare(const void *a, const void *b) {
       int x = *(int *)a;
       int y = *(int *)b;
       if (x < y) return -1;
       if (x > y) return 1;
       return 0;
   }

2. Zavolej qsort:
   qsort(pole, pocet, sizeof(int), compare);

3. Tiskni výsledek:
   for (int i = 0; i < pocet; i++)
       printf("%d\n", pole[i]);


PAMATUJ:
  ✓ qsort mění ORIGINÁLNÍ pole
  ✓ Vrať -1, 0, +1 (ne libovolné číslo)
  ✓ U stringů se castuje na char**
  ✓ U struktur se castuje na struct*
  ✓ Před bsearch MUSÍŠ qsort!
  ✓ Dej pozor na INTEGER OVERFLOW (a - b)

CHYBY NA ZKOUŠCE:
  ❌ Zapomenout na sizeof (qsort(pole, n, 4, ...))
  ❌ Vracel "return a - b" a přeteklo (int overflow)
  ❌ U stringů zapoměl ** v castu
  ❌ Qsort s divokou velikostí pole (0 prvků)
  ❌ Nebylo seřazeno před bsearch
*/
