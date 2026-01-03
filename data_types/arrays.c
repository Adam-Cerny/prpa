// ============================================
// POLE (ARRAYS) - Úplný průvodce
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. ZÁKLADNÍ POLE - Deklarace a inicializace
// ============================================

/*
POLE = sekvence prvků stejného typu vedle sebe v paměti
Syntax: type nazev[velikost];

Vlastnosti:
- Indexování od 0
- Kontinuální paměť
- Pevná velikost (při kompilaci)
- Přístup v O(1)
*/

// Příklad 1: Základní pole
void priklad_1_zakladni()
{
    int pole[5];  // Pole 5 intů
    
    // Inicializace hodnotami
    pole[0] = 10;
    pole[1] = 20;
    pole[2] = 30;
    pole[3] = 40;
    pole[4] = 50;
    
    // Přístup k prvku
    printf("pole[0] = %d\n", pole[0]);  // 10
    printf("pole[2] = %d\n", pole[2]);  // 30
}

// Příklad 2: Inicializace při deklaraci
void priklad_2_inicializace()
{
    // Úplná inicializace
    int pole1[] = {1, 2, 3, 4, 5};  // Velikost se detekuje automaticky
    
    // Částečná inicializace
    int pole2[10] = {1, 2, 3};  // Zbytek = 0
    
    // Všechny nuly
    int pole3[5] = {0};
    
    // Všechny stejné (C99+)
    int pole4[5] = {[0 ... 4] = 7};  // Všechny = 7
    
    for (int i = 0; i < 10; i++)
    {
        printf("pole2[%d] = %d\n", i, pole2[i]);
    }
}

// ============================================
// 2. DÉLKA POLE A ITERACE
// ============================================

// Příklad 3: Zjištění délky pole
void priklad_3_delka()
{
    int pole[] = {1, 2, 3, 4, 5};
    
    // POZOR: sizeof vrací velikost v bytech!
    int velikost_bajtu = sizeof(pole);  // 5 * 4 = 20 bajtů
    int pocet_prvku = sizeof(pole) / sizeof(pole[0]);  // 20 / 4 = 5
    
    printf("Velikost v bytech: %d\n", velikost_bajtu);
    printf("Počet prvků: %d\n", pocet_prvku);
}

// Příklad 4: Iterace přes pole
void priklad_4_iterace()
{
    int pole[] = {10, 20, 30, 40, 50};
    int n = sizeof(pole) / sizeof(pole[0]);
    
    // For cyklus
    printf("For cyklus: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", pole[i]);
    }
    printf("\n");
    
    // While cyklus
    printf("While cyklus: ");
    int i = 0;
    while (i < n)
    {
        printf("%d ", pole[i]);
        i++;
    }
    printf("\n");
}

// ============================================
// 3. POLE RŮZNÝCH TYPŮ
// ============================================

// Příklad 5: Pole znaků (řetězec)
void priklad_5_znaky()
{
    char text[] = "Ahoj";  // Automaticky + null terminator
    
    printf("Text: %s\n", text);  // "Ahoj"
    printf("Délka: %lu\n", strlen(text));  // 4
    
    // Jednotlivé znaky
    for (int i = 0; i < strlen(text); i++)
    {
        printf("text[%d] = '%c'\n", i, text[i]);
    }
}

// Příklad 6: Pole floatů
void priklad_6_floaty()
{
    float teploty[] = {20.5f, 21.0f, 19.8f, 22.3f};
    int n = sizeof(teploty) / sizeof(teploty[0]);
    
    float soucet = 0;
    for (int i = 0; i < n; i++)
    {
        soucet += teploty[i];
    }
    
    float prumer = soucet / n;
    printf("Průměrná teplota: %.1f°C\n", prumer);
}

// ============================================
// 4. UKAZATELE A POLE
// ============================================

/*
Pole se v C převádí na ukazatel!
int pole[10];
int *p = pole;  // Ekvivalentní s &pole[0]

p[0] == pole[0]
p[1] == pole[1]
*(p+0) == pole[0]
*(p+1) == pole[1]
*/

// Příklad 7: Ukazatel na pole
void priklad_7_ukazatel()
{
    int pole[] = {10, 20, 30, 40, 50};
    
    // Ukazatel
    int *p = pole;  // Ukazuje na prvek [0]
    
    // Přístup přes ukazatel
    printf("*p = %d\n", *p);      // 10
    printf("*(p+1) = %d\n", *(p+1));  // 20
    printf("p[2] = %d\n", p[2]);   // 30
    
    // Posun ukazatele
    p++;  // Nyní ukazuje na prvek [1]
    printf("Po p++: *p = %d\n", *p);  // 20
}

// Příklad 8: Procházení přes ukazatel
void priklad_8_procházeni_ukazatel()
{
    int pole[] = {1, 2, 3, 4, 5};
    int n = 5;
    
    int *p = pole;
    int *konec = pole + n;  // Ukazatel na konec
    
    printf("Prvky: ");
    while (p < konec)
    {
        printf("%d ", *p);
        p++;  // Posun na další prvek
    }
    printf("\n");
}

// ============================================
// 5. DYNAMICKÉ POLE
// ============================================

/*
DYNAMICKÉ POLE:
- Velikost není známa při kompilaci
- Alokace za běhu s malloc/calloc
- Musíš pamatovat si délku
- Uvolni s free()
*/

// Příklad 9: Dynamické pole
void priklad_9_dynamicke()
{
    int n;
    printf("Kolik prvků? ");
    scanf("%d", &n);
    
    if (n <= 0)
    {
        fprintf(stderr, "Chyba: počet musí být > 0\n");
        return;
    }
    
    // Alokuj pole
    int *pole = (int *)malloc(n * sizeof(int));
    
    if (pole == NULL)
    {
        fprintf(stderr, "Chyba: malloc!\n");
        return;
    }
    
    // Naplnění
    for (int i = 0; i < n; i++)
    {
        pole[i] = (i + 1) * 10;
    }
    
    // Výpis
    printf("Pole: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", pole[i]);
    }
    printf("\n");
    
    // Uvolnění
    free(pole);
    pole = NULL;
}

// Příklad 10: Calloc - inicializace na 0
void priklad_10_calloc()
{
    int n = 10;
    
    // calloc inicializuje všechno na 0
    int *pole = (int *)calloc(n, sizeof(int));
    
    if (pole == NULL)
    {
        fprintf(stderr, "Chyba: calloc!\n");
        return;
    }
    
    printf("Calloc inicializované pole: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", pole[i]);  // Všechno 0
    }
    printf("\n");
    
    free(pole);
}

// Příklad 11: Realloc - změna velikosti
void priklad_11_realloc()
{
    int n = 5;
    int *pole = (int *)malloc(n * sizeof(int));
    
    if (pole == NULL)
        return;
    
    // Naplnění
    for (int i = 0; i < n; i++)
        pole[i] = i + 1;
    
    printf("Původní pole (5 prvků): ");
    for (int i = 0; i < n; i++)
        printf("%d ", pole[i]);
    printf("\n");
    
    // Zvětšení na 10 prvků
    int nova_velikost = 10;
    int *nova = (int *)realloc(pole, nova_velikost * sizeof(int));
    
    if (nova == NULL)
    {
        fprintf(stderr, "Chyba: realloc!\n");
        free(pole);
        return;
    }
    
    pole = nova;
    n = nova_velikost;
    
    // Naplnění nových prvků
    for (int i = 5; i < n; i++)
        pole[i] = i + 1;
    
    printf("Po realloc (10 prvků): ");
    for (int i = 0; i < n; i++)
        printf("%d ", pole[i]);
    printf("\n");
    
    free(pole);
}

// ============================================
// 6. VYHLEDÁVÁNÍ V POLI
// ============================================

// Příklad 12: Lineární vyhledávání
int linearniVyhledavani(int *pole, int n, int hledana)
{
    for (int i = 0; i < n; i++)
    {
        if (pole[i] == hledana)
            return i;  // Nalezeno na pozici i
    }
    return -1;  // Nenalezeno
}

void priklad_12_vyhledavani()
{
    int pole[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    
    int hledana = 8;
    int pozice = linearniVyhledavani(pole, n, hledana);
    
    if (pozice != -1)
    {
        printf("Číslo %d nalezeno na pozici %d\n", hledana, pozice);
    }
    else
    {
        printf("Číslo %d nenalezeno\n", hledana);
    }
}

// Příklad 13: Binární vyhledávání (pole musí být seřazené!)
int binarniVyhledavani(int *pole, int n, int hledana)
{
    int leva = 0, prava = n - 1;
    
    while (leva <= prava)
    {
        int stred = (leva + prava) / 2;
        
        if (pole[stred] == hledana)
            return stred;
        else if (pole[stred] < hledana)
            leva = stred + 1;
        else
            prava = stred - 1;
    }
    
    return -1;
}

void priklad_13_binarni_vyhledavani()
{
    int pole[] = {1, 3, 5, 7, 9, 11, 13};  // Musí být seřazené!
    int n = 7;
    
    int hledana = 7;
    int pozice = binarniVyhledavani(pole, n, hledana);
    
    if (pozice != -1)
    {
        printf("Číslo %d nalezeno na pozici %d\n", hledana, pozice);
    }
    else
    {
        printf("Číslo %d nenalezeno\n", hledana);
    }
}

// ============================================
// 7. ŘAZENÍ POLE
// ============================================

// Příklad 14: Bubble sort
void bubbleSort(int *pole, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (pole[j] > pole[j + 1])
            {
                // Vyměň
                int temp = pole[j];
                pole[j] = pole[j + 1];
                pole[j + 1] = temp;
            }
        }
    }
}

void priklad_14_bubble_sort()
{
    int pole[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    
    printf("Před řazením: ");
    for (int i = 0; i < n; i++)
        printf("%d ", pole[i]);
    printf("\n");
    
    bubbleSort(pole, n);
    
    printf("Po řazení: ");
    for (int i = 0; i < n; i++)
        printf("%d ", pole[i]);
    printf("\n");
}

// Příklad 15: Quick sort pomocí qsort
int porovnej(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

void priklad_15_qsort()
{
    int pole[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    
    printf("Před qsort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", pole[i]);
    printf("\n");
    
    // Standardní qsort
    qsort(pole, n, sizeof(int), porovnej);
    
    printf("Po qsort: ");
    for (int i = 0; i < n; i++)
        printf("%d ", pole[i]);
    printf("\n");
}

// ============================================
// 8. MIN, MAX, SOUČET
// ============================================

// Příklad 16: Minimum a maximum
void priklad_16_min_max()
{
    int pole[] = {5, 2, 8, 1, 9, 3};
    int n = 6;
    
    int min = pole[0], max = pole[0];
    
    for (int i = 1; i < n; i++)
    {
        if (pole[i] < min) min = pole[i];
        if (pole[i] > max) max = pole[i];
    }
    
    printf("Minimum: %d\n", min);  // 1
    printf("Maximum: %d\n", max);  // 9
}

// Příklad 17: Součet a průměr
void priklad_17_suma_prumer()
{
    int pole[] = {10, 20, 30, 40, 50};
    int n = 5;
    
    int suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += pole[i];
    }
    
    float prumer = (float)suma / n;
    
    printf("Součet: %d\n", suma);     // 150
    printf("Průměr: %.1f\n", prumer);  // 30.0
}

// ============================================
// 9. POLE STRUKTUR
// ============================================

// Příklad 18: Pole struktur
typedef struct {
    char jmeno[50];
    int vek;
} Osoba;

void priklad_18_pole_struktur()
{
    Osoba skupinka[] = {
        {"Petr", 25},
        {"Anna", 30},
        {"Jiří", 35}
    };
    
    int n = 3;
    
    for (int i = 0; i < n; i++)
    {
        printf("Osoba %d: %s (%d let)\n", i+1, 
               skupinka[i].jmeno, skupinka[i].vek);
    }
}

// ============================================
// 10. POLE ŘETĚZCŮ
// ============================================

// Příklad 19: Pole řetězců
void priklad_19_pole_retezcu()
{
    char *slova[] = {
        "ahoj",
        "svet",
        "program",
        "C"
    };
    
    int n = 4;
    
    printf("Slova:\n");
    for (int i = 0; i < n; i++)
    {
        printf("  %d: %s (délka %lu)\n", i+1, slova[i], strlen(slova[i]));
    }
}

// Příklad 20: 2D pole znaků (pole řetězců)
void priklad_20_2d_znaky()
{
    char text[3][10] = {
        "Ahoj",
        "Svet",
        "Program"
    };
    
    for (int i = 0; i < 3; i++)
    {
        printf("Řetězec %d: %s\n", i+1, text[i]);
    }
}

// ============================================
// 11. PROCHÁZENÍ POLE - Různé metody
// ============================================

// Příklad 21: For cyklus
void priklad_21_for()
{
    int pole[] = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", pole[i]);
    }
    printf("\n");
}

// Příklad 22: Ukazatel
void priklad_22_ukazatel_procházení()
{
    int pole[] = {1, 2, 3, 4, 5};
    int n = 5;
    
    for (int *p = pole; p < pole + n; p++)
    {
        printf("%d ", *p);
    }
    printf("\n");
}

// Příklad 23: Reverse (pozpátku)
void priklad_23_reverse()
{
    int pole[] = {1, 2, 3, 4, 5};
    int n = 5;
    
    printf("Pozpátku: ");
    for (int i = n - 1; i >= 0; i--)
    {
        printf("%d ", pole[i]);
    }
    printf("\n");
}

// ============================================
// 12. PROBLÉMY A BEZPEČNOST
// ============================================

// Příklad 24: Buffer overflow - NEBEZPEČNÉ!
void priklad_24_buffer_overflow()
{
    int pole[5] = {0};
    
    // NEBEZPEČNÉ - přístup mimo pole!
    // pole[10] = 100;  // Buffer overflow!
    // printf("%d\n", pole[10]);  // Čte libovolné místo v paměti
    
    // Bezpečně - kontrola hranic
    int index = 10;
    if (index >= 0 && index < 5)
    {
        pole[index] = 100;
    }
    else
    {
        fprintf(stderr, "Chyba: index mimo rozsah!\n");
    }
}

// Příklad 25: Ztráta paměti
void priklad_25_memory_leak()
{
    int *pole = (int *)malloc(100 * sizeof(int));
    
    // ... práce s polem ...
    
    // VŽDY uvolni!
    free(pole);
    pole = NULL;
    
    // Bez free() dochází k memory leak
}

// ============================================
// SHRNUTÍ - Nejdůležitější
// ============================================

/*
ZÁKLADNÍ POLE:
  int pole[10];                    // Deklarace
  int pole[] = {1,2,3};            // Inicializace
  pole[0] = 5;                     // Přístup

DÉLKA:
  sizeof(pole) / sizeof(pole[0])   // Počet prvků

UKAZATELE:
  int *p = pole;                   // Ukazatel
  p[0] == pole[0]
  *(p+i) == pole[i]

DYNAMICKÉ POLE:
  int *p = malloc(n * sizeof(int));
  int *p = calloc(n, sizeof(int));
  free(p);

REALLOC:
  int *new = realloc(old, new_size * sizeof(int));
  if (new == NULL) { free(old); ... }
  old = new;

VYHLEDÁVÁNÍ:
  lineárni: O(n)
  binární: O(log n) - pole musí být seřazené!

ŘAZENÍ:
  bubble sort: O(n²)
  quick sort (qsort): O(n log n)

POLE STRUKTUR:
  Osoba pole[10];
  pole[0].jmeno = ...

BEZPEČNOST:
  Vždy kontroluj hranic: i >= 0 && i < n
  Vždy uvolni malloc: free(p);
  Vždy kontroluj NULL: if (p == NULL) { ... }
*/
