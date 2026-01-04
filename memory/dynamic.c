// ============================================
// DYNAMICKÁ PAMĚŤ - Úplný průvodce
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. MALLOC - Alokace paměti
// ============================================

/*
MALLOC - Memory Allocation
Přidělí N bajtů paměti a vrátí ukazatel na ni
Paměť je NEINICIALIZOVANÁ (obsahuje libovolné hodnoty)
Syntax: void *malloc(size_t size);

Návratová hodnota:
  - Ukazatel na alokovanou paměť (typedef - obvykle void *)
  - NULL, pokud se alokace nezdařila
*/

// Příklad 1: Alokace jednoho čísla
void priklad_1_jednoho_cisla()
{
    // Alokace paměti pro jedno int číslo
    int *p = (int *)malloc(sizeof(int));
    
    // VŽDY kontroluj, zda se alokace podařila!
    if (p == NULL)
    {
        fprintf(stderr, "Error: Nedostatek pameti!\n");
        return;  // nebo exit(100);
    }
    
    // Nyní můžeš používat paměť
    *p = 42;
    printf("Alokoval jsem cislo: %d\n", *p);
    
    // VŽDY uvolni paměť!
    free(p);
    p = NULL;  // Dobrá praxe - nastav na NULL po free
}

// Příklad 2: Alokace pole (array)
void priklad_2_pole()
{
    int n = 10;
    
    // Alokace pole o velikosti 10 intů
    int *pole = (int *)malloc(n * sizeof(int));
    
    if (pole == NULL)
    {
        fprintf(stderr, "Error: Nedostatek pameti!\n");
        return;
    }
    
    // Zapísání hodnot
    for (int i = 0; i < n; i++)
    {
        pole[i] = i * 10;
    }
    
    // Výpis
    for (int i = 0; i < n; i++)
    {
        printf("pole[%d] = %d\n", i, pole[i]);
    }
    
    free(pole);
    pole = NULL;
}

// Příklad 3: Alokace řetězce (string)
void priklad_3_retezec()
{
    int delka = 50;
    
    // Alokace místa pro řetězec dlouhý max 49 znaků + null terminator
    char *str = (char *)malloc((delka + 1) * sizeof(char));
    
    if (str == NULL)
    {
        fprintf(stderr, "Error: Nedostatek pameti!\n");
        return;
    }
    
    // Bezpečné čtení
    scanf("%50s", str);
    
    printf("Nacetl jsem: %s (delka %lu)\n", str, strlen(str));
    
    free(str);
    str = NULL;
}

// Příklad 4: Alokace struktury
void priklad_4_struktura()
{
    typedef struct
    {
        char jmeno[50];
        int vek;
        float vyska;
    } Osoba;
    
    // Alokace jedné osoby
    Osoba *osoba = (Osoba *)malloc(sizeof(Osoba));
    
    if (osoba == NULL)
    {
        fprintf(stderr, "Error: Nedostatek pameti!\n");
        return;
    }
    
    // Přístup k членům struktury přes ukazatel
    strcpy(osoba->jmeno, "Petr");
    osoba->vek = 25;
    osoba->vyska = 180.5;
    
    printf("Osoba: %s, vek: %d, vyska: %.1f\n", 
           osoba->jmeno, osoba->vek, osoba->vyska);
    
    free(osoba);
    osoba = NULL;
}

// ============================================
// 2. REALLOC - Změna velikosti paměti
// ============================================

/*
REALLOC - Re-Allocation
Změní velikost již alokované paměti
Syntax: void *realloc(void *ptr, size_t new_size);

Vrací:
  - Ukazatel na novou paměť (může být jiná adresa!)
  - NULL, pokud se operace nezdařila (původní paměť zůstane)
*/

// Příklad 5: Dynamické pole s reallocem - z ukolu 08
void priklad_5_realloc_dynamicke()
{
    int *cisla = NULL;
    int kapacita = 0;
    int pocet = 0;
    int cislo;
    
    // Čtení čísel do EOF
    while (scanf("%d", &cislo) == 1)
    {
        // Je-li pole plné, zvětši ho
        if (pocet >= kapacita)
        {
            // Nastavení počáteční kapacity
            if (kapacita == 0)
            {
                kapacita = 5;
            }
            // Zdvojnásobení kapacity
            else
            {
                kapacita *= 2;
            }
            
            // DŮLEŽITÉ: Ulož nový ukazatel do dočasné proměnné!
            int *new = realloc(cisla, kapacita * sizeof(int));
            
            // VŽDY kontroluj, zda se realloc zdařil!
            if (new == NULL)
            {
                fprintf(stderr, "Error: Nedostatek pameti!\n");
                free(cisla);  // Uvolni starou paměť!
                return;
            }
            
            // Teprve nyní použij new ukazatel
            cisla = new;
        }
        
        // Přidej číslo do pole
        cisla[pocet++] = cislo;
    }
    
    // Výpis
    printf("Nacteno %d cisel: ", pocet);
    for (int i = 0; i < pocet; i++)
    {
        printf("%d ", cisla[i]);
    }
    printf("\n");
    
    free(cisla);
    cisla = NULL;
}

// Příklad 6: Verze s kontrolou - BEZPEČNĚ
void priklad_6_realloc_bezpecne()
{
    int *pole = NULL;
    int kapacita = 0;
    int pocet = 0;
    
    // Simulace čtení 3 čísel
    int data[] = {10, 20, 30};
    
    for (int i = 0; i < 3; i++)
    {
        // Kontrola, zda je třeba zvětšit
        if (pocet >= kapacita)
        {
            int nova_kapacita = (kapacita == 0) ? 2 : kapacita * 2;
            
            // Ulož do tmp!
            int *tmp = realloc(pole, nova_kapacita * sizeof(int));
            
            if (tmp == NULL)
            {
                fprintf(stderr, "Chyba: realloc!\n");
                free(pole);
                return;
            }
            
            pole = tmp;
            kapacita = nova_kapacita;
        }
        
        pole[pocet++] = data[i];
    }
    
    printf("Pole má %d prvků: ", pocet);
    for (int i = 0; i < pocet; i++)
        printf("%d ", pole[i]);
    printf("\n");
    
    free(pole);
}

// ============================================
// 3. CALLOC - Alokace + Inicializace
// ============================================

/*
CALLOC - Cleared Allocation
Alokuje paměť a inicializuje ji na 0
Syntax: void *calloc(size_t num, size_t size);

Přiděluje: num * size bajtů paměti
Všechny byty jsou nastaveny na 0
*/

// Příklad 7: Calloc vs Malloc
void priklad_7_calloc_vs_malloc()
{
    int n = 5;
    
    // MALLOC - neinicializovaná paměť (libovolné hodnoty)
    int *m = (int *)malloc(n * sizeof(int));
    printf("Malloc (nemáš jistotu obsahu): %d, %d, ...\n", m[0], m[1]);
    
    // CALLOC - všechno je 0
    int *c = (int *)calloc(n, sizeof(int));
    printf("Calloc (všechno je 0): %d, %d, %d\n", c[0], c[1], c[2]);
    
    // Calloc je pomalejší, protože musí všechno nulovat!
    // Používej malloc pokud víš, že to ihned naplníš daty
    
    free(m);
    free(c);
}

// ============================================
// 4. FREE - Uvolnění paměti
// ============================================

/*
FREE - Dealokace
Uvolňuje alokovanou paměť
Syntax: void free(void *ptr);

DŮLEŽITÉ:
  - Uvolni pouze paměť, kterou jsi alokoval!
  - Neuvolni přesně tolikrát, kolikrát jsi alokoval = memory leak
  - Neuvolni paměť dvakrát = double free (crash)
  - Po free nikdy nepoužívej ukazatel!
*/

// Příklad 8: Správné uvolňování
void priklad_8_uvolnovani()
{
    int *p = (int *)malloc(sizeof(int));
    
    if (p == NULL)
        return;
    
    *p = 100;
    printf("Alokoval: %d\n", *p);
    
    free(p);      // Uvolní paměť
    p = NULL;     // Dobrá praxe - nastav na NULL
    
    // Teď je bezpečné opakovat:
    // if (p == NULL) { ... } // OK
    // *p = 50;  // CRASH! Tohle by se stalo bez NULL
}

// Příklad 9: Memory leak - co se stane
void priklad_9_memory_leak()
{
    // ŠPATNĚ - MEMORY LEAK!
    int *p = (int *)malloc(sizeof(int));
    *p = 42;
    // Zapomenuté free - paměť se uvolní až při konci programu
    // return;  // Ukazatel p se ztratí!
    
    // SPRÁVNĚ:
    // free(p);
    // p = NULL;
}

// Příklad 10: Double free - crash
void priklad_10_double_free()
{
    int *p = (int *)malloc(sizeof(int));
    
    free(p);
    // free(p);  // CRASH! Nesmíš uvolnit dvakrát!
    
    // Správně:
    free(p);
    p = NULL;
    // Teď je bezpečné volat free(p) znovu - nic se nestane
}

// ============================================
// 5. UKAZATELE NA UKAZATELE - Pro funkce
// ============================================

/*
Když chceš, aby funkce alokovala paměť a vrátila ji:

Špatně:
    int *fn() { return malloc(...); }  // OK, ale hůř se volá

Lépe:
    void fn(int **ptr) { *ptr = malloc(...); }  // Předej ukazatel na ukazatel
*/

// Příklad 11: Alokace v podřízené funkci - verze 1
void alokuj_v_funkci_v1(int **p, int velikost)
{
    *p = (int *)malloc(velikost * sizeof(int));
    
    if (*p == NULL)
    {
        fprintf(stderr, "Chyba: malloc!\n");
        return;
    }
    
    // Naplň daty
    for (int i = 0; i < velikost; i++)
    {
        (*p)[i] = i * 100;
    }
}

void priklad_11_ukazatel_na_ukazatel()
{
    int *pole = NULL;
    
    // Předej ukazatel na ukazatel
    alokuj_v_funkci_v1(&pole, 5);
    
    if (pole != NULL)
    {
        printf("Alokované pole: ");
        for (int i = 0; i < 5; i++)
            printf("%d ", pole[i]);
        printf("\n");
        
        free(pole);
        pole = NULL;
    }
}

// Příklad 12: Alokace v podřízené funkci - verze 2 (vrací ukazatel)
int* alokuj_v_funkci_v2(int velikost)
{
    int *p = (int *)malloc(velikost * sizeof(int));
    
    if (p == NULL)
        return NULL;
    
    for (int i = 0; i < velikost; i++)
        p[i] = i * 100;
    
    return p;
}

void priklad_12_return_pointer()
{
    int *pole = alokuj_v_funkci_v2(5);
    
    if (pole != NULL)
    {
        printf("Vrácené pole: ");
        for (int i = 0; i < 5; i++)
            printf("%d ", pole[i]);
        printf("\n");
        
        free(pole);
        pole = NULL;
    }
}

// ============================================
// 6. 2D POLE - Matice
// ============================================

/*
Alokace 2D pole (matice) má několik způsobů:

1. Alokace pole ukazatelů + každý řádek zvlášť
2. Jedna alokace - lineární pole s indexováním
*/

// Příklad 13: 2D pole - způsob 1 (nejčastější)
void priklad_13_2d_pole_v1()
{
    int m = 3, n = 4;  // 3 řádky, 4 sloupce
    
    // Alokuj pole ukazatelů na řádky
    int **matice = (int **)malloc(m * sizeof(int *));
    
    if (matice == NULL)
        return;
    
    // Alokuj každý řádek
    for (int i = 0; i < m; i++)
    {
        matice[i] = (int *)malloc(n * sizeof(int));
        
        if (matice[i] == NULL)
        {
            fprintf(stderr, "Chyba: malloc!\n");
            // Uvolni už alokované řádky
            for (int j = 0; j < i; j++)
                free(matice[j]);
            free(matice);
            return;
        }
    }
    
    // Naplň matici
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matice[i][j] = i * n + j;
        }
    }
    
    // Výpis matice
    printf("Matice:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matice[i][j]);
        }
        printf("\n");
    }
    
    // Uvolnění - v opačném pořadí!
    for (int i = 0; i < m; i++)
    {
        free(matice[i]);
    }
    free(matice);
    matice = NULL;
}

// Příklad 14: 2D pole - způsob 2 (rychlejší, jedna alokace)
void priklad_14_2d_pole_v2()
{
    int m = 3, n = 4;
    
    // Alokuj všechno v jednom kuse
    int *data = (int *)malloc(m * n * sizeof(int));
    int **matice = (int **)malloc(m * sizeof(int *));
    
    if (data == NULL || matice == NULL)
    {
        fprintf(stderr, "Chyba: malloc!\n");
        return;
    }
    
    // Nastav ukazatele na začátek každého řádku
    for (int i = 0; i < m; i++)
    {
        matice[i] = data + i * n;
    }
    
    // Naplň
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matice[i][j] = i * n + j;
        }
    }
    
    // Výpis
    printf("Matice:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matice[i][j]);
        }
        printf("\n");
    }
    
    // Uvolnění - jednoduše
    free(data);
    free(matice);
}

// ============================================
// 7. PŘÍKLADY Z VAŠICH ÚKOLŮ
// ============================================

// Příklad 15: Z ukolu 06 - Caesarova šifra s alokací
void priklad_15_ukol_06()
{
    int delka = 100;
    
    // Alokuj místo pro vstupní řetězec
    char *vstup = (char *)malloc((delka + 1) * sizeof(char));
    
    if (vstup == NULL)
    {
        fprintf(stderr, "Error: Nedostatek pameti!\n");
        return;
    }
    
    // Alokuj místo pro výstup
    char *vysifrovany = (char *)malloc((delka + 1) * sizeof(char));
    
    if (vysifrovany == NULL)
    {
        fprintf(stderr, "Error: Nedostatek pameti!\n");
        free(vstup);
        return;
    }
    
    // Simulace vstupu
    strcpy(vstup, "Ahoj");
    
    // ... zpracování ...
    strcpy(vysifrovany, vstup);
    
    printf("Vstup: %s\n", vstup);
    printf("Výstup: %s\n", vysifrovany);
    
    // Uvolnění
    free(vstup);
    free(vysifrovany);
    vstup = NULL;
    vysifrovany = NULL;
}

// Příklad 16: Z ukolu 10 - Fronta
void priklad_16_ukol_10()
{
    // Strukturu queue alokuješ takto:
    typedef struct
    {
        void **data;
        int capacity;
        int item_number;
    } queue_t;
    
    int kapacita = 10;
    
    // Alokuj samotnou strukturu
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    
    if (q == NULL)
    {
        fprintf(stderr, "Error: Nedostatek pameti!\n");
        return;
    }
    
    // Alokuj data ve frontě
    q->data = (void **)malloc(kapacita * sizeof(void *));
    
    if (q->data == NULL)
    {
        fprintf(stderr, "Error: Nedostatek pameti!\n");
        free(q);  // Uvolni strukturu!
        return;
    }
    
    q->capacity = kapacita;
    q->item_number = 0;
    
    // ... použití fronty ...
    
    // Uvolnění - nejdřív data, pak struktura
    free(q->data);
    free(q);
    q = NULL;
}

// ============================================
// 8. Memory DEBUGGER - Detekce problémů
// ============================================

/*
VALGRIND - Tool na detekci memory leaků

Spuštění:
    valgrind ./program

Výstup ukazuje:
    - Memory leaky
    - Double free
    - Use after free
    - Buffer overflow
*/

// Příklad 17: Program s memory leakem (k vyzkoušení s valgrind)
void priklad_17_memory_leak_example()
{
    int *p = (int *)malloc(100 * sizeof(int));
    
    if (p == NULL)
        return;
    
    p[0] = 42;
    
    // ZAPOMENUTÉ free - memory leak!
    // Správně by mělo být: free(p);
    
    return;  // p se zde ztratí!
}

// ============================================
// 9. CHECKLIST - Co vždy kontrolovat
// ============================================

/*
KONTROLNÍ SEZNAM pro dynamickou paměť:

☑ Je malloc/calloc vždy kontrolován na NULL?
    if (p == NULL) { error... }

☑ Je dost místa?
    malloc(n * sizeof(type))  // Nikdy ne: malloc(n) !!!

☑ Je free volána?
    free(p);
    
☑ Není free volán vícekrát?
    free(p);
    p = NULL;  // Bezpečně volat znovu

☑ Není paměť použita po free?
    free(p);
    // *p = 5;  // CRASH!

☑ Nejsou tam memory leaky?
    while (1) {
        int *p = malloc(...);
        // ... bez free ...
    }  // LEAK - paměť se plní

☑ Jsou ukazatele předávány správně?
    void fn(int **p)  { *p = malloc(...); }  // OK
    int* fn() { return malloc(...); }        // OK
    void fn(int *p)   { p = malloc(...); }   // ŠPATNĚ!

☑ Jsou alokační chyby kontrolovány?
    int *p = malloc(...);
    int *q = malloc(...);  // Když selže, p není free!

☑ Je realloc používán bezpečně?
    int *new = realloc(old, size);  // Do tmp!
    if (new == NULL) free(old);      // Old zůstane!
*/

// ============================================
// 10. BEST PRACTICES
// ============================================

/*
DOPORUČOVANÉ POSTUPY:

1. VŽDY inicializuj ukazatele
   int *p = NULL;  // Lepší než int *p;

2. VŽDY kontroluj malloc/calloc
   if (ptr == NULL) { error... }

3. VŽDY uvolni paměť
   free(ptr);
   ptr = NULL;

4. POUŽÍVEJ sizeof správně
   int *p = malloc(n * sizeof(int));      // OK
   int *p = malloc(n * sizeof(*p));       // LEPŠÍ (flexibilnější)

5. POUŽÍVEJ realloc správně
   int *new = realloc(old, size);
   if (new == NULL) { free(old); ... }

6. ALOKUJ blízko použití
   // OK:
   int *p = malloc(...);
   if (p) use(p);
   free(p);
   
   // ŠPATNĚ:
   int *p = malloc(...);
   ... 1000 řádků kódu ...
   free(p);

7. STRUKTUR S DYNAMICKOU PAMĚTÍ
   typedef struct {
       int *data;
       int size;
   } MyArray;
   
   MyArray* create() {
       MyArray *a = malloc(sizeof(MyArray));
       a->data = malloc(10 * sizeof(int));
       return a;
   }
   
   void destroy(MyArray *a) {
       free(a->data);
       free(a);
   }

8. TESTUJ S VALGRIND
   valgrind --leak-check=full ./program
*/

// ============================================
// SHRNUTÍ - Nejdůležitější
// ============================================

/*
MALLOC:
  int *p = (int *)malloc(n * sizeof(int));
  if (p == NULL) { error... }

REALLOC:
  int *new = realloc(p, new_size * sizeof(int));
  if (new == NULL) { free(p); ... }
  p = new;

CALLOC (alternativa k malloc):
  int *p = (int *)calloc(n, sizeof(int));  // Init na 0

FREE:
  free(p);
  p = NULL;

STRUKTURA:
  typedef struct {
      int *data;
      int size;
  } MyArray;
  
  MyArray *a = malloc(sizeof(MyArray));
  a->data = malloc(10 * sizeof(int));
  free(a->data);
  free(a);

2D POLE:
  int **m = malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++)
      m[i] = malloc(cols * sizeof(int));
  
  // Použití: m[i][j]
  
  for (int i = 0; i < rows; i++)
      free(m[i]);
  free(m);
*/
