// ============================================
// STRUKTURY V C - Úplný průvodce
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. ZÁKLADNÍ STRUKTURA - Definice
// ============================================

/*
STRUKTURA = seskupení více proměnných různých typů
Syntax:
  struct Jmeno {
      typ1 member1;
      typ2 member2;
      ...
  };
*/

// Příklad 1: Jednoduchá struktura
struct Osoba {
    char jmeno[50];
    int vek;
    float vyska;
};

void priklad_1_zakladni()
{
    // Vytvoř proměnnou typu struct Osoba
    struct Osoba osoba;
    
    // Přístup k członům přes tečku
    strcpy(osoba.jmeno, "Petr");
    osoba.vek = 25;
    osoba.vyska = 180.5;
    
    printf("Jméno: %s\n", osoba.jmeno);
    printf("Věk: %d\n", osoba.vek);
    printf("Výška: %.1f\n", osoba.vyska);
}

// Příklad 2: Inicializace struktury
void priklad_2_inicializace()
{
    // Inicializace při deklaraci
    struct Osoba osoba = {"Anna", 30, 165.0};
    
    printf("Osoba: %s, věk: %d\n", osoba.jmeno, osoba.vek);
}

// Příklad 3: Pole struktur
void priklad_3_pole_struktur()
{
    struct Osoba skupinka[3] = {
        {"Petr", 25, 180.0},
        {"Anna", 30, 165.0},
        {"Jiří", 35, 175.0}
    };
    
    for (int i = 0; i < 3; i++)
    {
        printf("%s - %d let\n", skupinka[i].jmeno, skupinka[i].vek);
    }
}

// ============================================
// 2. TYPEDEF - Zkrácení zápisu
// ============================================

/*
TYPEDEF = vytvoření aliasu pro typ
Umožňuje psát: Osoba osoba;  místo: struct Osoba osoba;
*/

// Příklad 4: Typedef struktura
typedef struct {
    char jmeno[50];
    int vek;
    float vyska;
} Osoba;

void priklad_4_typedef()
{
    Osoba osoba = {"Petr", 25, 180.5};
    
    printf("Osoba: %s, věk: %d\n", osoba.jmeno, osoba.vek);
    // Kratší a čitelnější!
}

// Příklad 5: Typedef s jménem struktury
typedef struct Osoba_tag {
    char jmeno[50];
    int vek;
} Osoba_t;

void priklad_5_typedef_pojmenovana()
{
    Osoba_t o;
    // Lze také: struct Osoba_tag o;
}

// ============================================
// 3. UKAZATELE NA STRUKTURU
// ============================================

/*
Přístup přes ukazatel:
  osoba->member  (ekvivalentní: (*osoba).member)
*/

// Příklad 6: Ukazatel na strukturu
void priklad_6_ukazatel()
{
    typedef struct {
        char jmeno[50];
        int vek;
    } Osoba;
    
    Osoba osoba = {"Petr", 25};
    Osoba *p = &osoba;  // Ukazatel na strukturu
    
    // Přístup přes šipku (->)
    printf("Jméno: %s\n", p->jmeno);
    printf("Věk: %d\n", p->vek);
    
    // Ekvivalentně:
    printf("Věk: %d\n", (*p).vek);
}

// Příklad 7: Alokace struktury na heapu
void priklad_7_dinamicka_struktura()
{
    typedef struct {
        char jmeno[50];
        int vek;
    } Osoba;
    
    // Alokuj na heapu
    Osoba *osoba = (Osoba *)malloc(sizeof(Osoba));
    
    if (osoba == NULL)
    {
        fprintf(stderr, "Chyba: malloc!\n");
        return;
    }
    
    // Přístup přes šipku
    strcpy(osoba->jmeno, "Petr");
    osoba->vek = 25;
    
    printf("Osoba: %s, věk: %d\n", osoba->jmeno, osoba->vek);
    
    free(osoba);
    osoba = NULL;
}

// ============================================
// 4. FUNKCE SE STRUKTURAMI
// ============================================

// Příklad 8: Předání struktury hodnotou (KOPÍROVÁNÍ)
void tiskniOsobu(Osoba osoba)  // KOPÍRUJE strukturu!
{
    printf("Osoba: %s, věk: %d\n", osoba.jmeno, osoba.vek);
}

void priklad_8_predani_hodnotou()
{
    Osoba osoba = {"Petr", 25};
    tiskniOsobu(osoba);  // Předá kopii
    // Původní osoba se nezmění
}

// Příklad 9: Předání struktury přes ukazatel (BEZ KOPÍROVÁNÍ)
void menitOsobu(Osoba *osoba)  // BEZ kopírování!
{
    osoba->vek = 30;
    strcpy(osoba->jmeno, "Anna");
}

void priklad_9_predani_ukazatelem()
{
    Osoba osoba = {"Petr", 25};
    
    menitOsobu(&osoba);  // Předá ukazatel
    
    printf("Změněná osoba: %s, věk: %d\n", osoba.jmeno, osoba.vek);
    // Výstup: Anna, věk: 30
}

// Příklad 10: Vrácení struktury z funkce
Osoba vytvorOsobu(const char *jmeno, int vek)
{
    Osoba osoba;
    strcpy(osoba.jmeno, jmeno);
    osoba.vek = vek;
    return osoba;
}

void priklad_10_vratum_strukturu()
{
    Osoba osoba = vytvorOsobu("Petr", 25);
    printf("Osoba: %s, věk: %d\n", osoba.jmeno, osoba.vek);
}

// Příklad 11: Vrácení ukazatele na strukturu
Osoba* vytvorOsobuDynamicky(const char *jmeno, int vek)
{
    Osoba *osoba = (Osoba *)malloc(sizeof(Osoba));
    
    if (osoba == NULL)
        return NULL;
    
    strcpy(osoba->jmeno, jmeno);
    osoba->vek = vek;
    
    return osoba;
}

void priklad_11_vratum_ukazatel()
{
    Osoba *osoba = vytvorOsobuDynamicky("Petr", 25);
    
    if (osoba != NULL)
    {
        printf("Osoba: %s, věk: %d\n", osoba->jmeno, osoba->vek);
        free(osoba);
    }
}

// ============================================
// 5. VNOŘENÉ STRUKTURY (NESTED STRUCTURES)
// ============================================

// Příklad 12: Struktura v struktuře
typedef struct {
    int den, mesic, rok;
} Datum;

typedef struct {
    char jmeno[50];
    Datum datumNarozeni;  // Vnořená struktura
    int plat;
} Zamestnanec;

void priklad_12_vnorivane()
{
    Zamestnanec z = {
        "Petr",
        {5, 3, 1990},  // Datum
        30000
    };
    
    printf("Jméno: %s\n", z.jmeno);
    printf("Datum: %d.%d.%d\n", z.datumNarozeni.den,
                                z.datumNarozeni.mesic,
                                z.datumNarozeni.rok);
    printf("Plat: %d\n", z.plat);
}

// ============================================
// 6. POLE DYNAMICKÉ DÉLKY V STRUKTUŘE
// ============================================

// Příklad 13: Struktura s dynamickým polem
typedef struct {
    char jmeno[50];
    int *skore;      // Dynamické pole
    int pocet;       // Počet prvků
} Hrac;

void priklad_13_dynamicke_pole()
{
    Hrac hrac;
    strcpy(hrac.jmeno, "Petr");
    hrac.pocet = 5;
    
    // Alokuj pole skóre
    hrac.skore = (int *)malloc(hrac.pocet * sizeof(int));
    
    if (hrac.skore == NULL)
    {
        fprintf(stderr, "Chyba!\n");
        return;
    }
    
    // Naplň
    for (int i = 0; i < hrac.pocet; i++)
    {
        hrac.skore[i] = (i + 1) * 100;
    }
    
    // Tiskni
    printf("Hráč: %s, skóre: ", hrac.jmeno);
    for (int i = 0; i < hrac.pocet; i++)
    {
        printf("%d ", hrac.skore[i]);
    }
    printf("\n");
    
    // Uvolni pole
    free(hrac.skore);
    hrac.skore = NULL;
}

// ============================================
// 7. PŘÍKLADY Z VAŠICH ÚKOLŮ
// ============================================

// Z ukolu 09 - Struktura Slovo
typedef struct {
    char *text;
    int pocet;
    int poradi;
} Slovo;

void priklad_14_ukol_09()
{
    Slovo slovo;
    slovo.text = (char *)malloc(50 * sizeof(char));
    
    if (slovo.text == NULL)
        return;
    
    strcpy(slovo.text, "hello");
    slovo.pocet = 5;
    slovo.poradi = 1;
    
    printf("Slovo: %s\n", slovo.text);
    printf("Počet výskytů: %d\n", slovo.pocet);
    printf("Pořadí: %d\n", slovo.poradi);
    
    free(slovo.text);
}

// Z ukolu 10 - Struktura Queue
typedef struct {
    int capacity;
    int item_number;
    int rear;
    int tail;
    void **data;
} queue_t;

void priklad_15_ukol_10()
{
    // Alokuj strukturu
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));
    
    if (q == NULL)
        return;
    
    // Inicializuj
    q->capacity = 10;
    q->item_number = 0;
    q->rear = 0;
    q->tail = -1;
    
    // Alokuj data
    q->data = (void **)malloc(q->capacity * sizeof(void *));
    
    if (q->data == NULL)
    {
        free(q);
        return;
    }
    
    printf("Fronta vytvořena: kapacita %d\n", q->capacity);
    
    // Uvolnění
    free(q->data);
    free(q);
}

// ============================================
// 8. POROVNÁVÁNÍ STRUKTUR
// ============================================

// Příklad 16: Porovnání struktur - memcmp
void priklad_16_porovnani()
{
    typedef struct {
        int x, y;
    } Point;
    
    Point p1 = {10, 20};
    Point p2 = {10, 20};
    Point p3 = {10, 30};
    
    // Porovnání přes memcmp
    if (memcmp(&p1, &p2, sizeof(Point)) == 0)
    {
        printf("p1 == p2\n");
    }
    
    if (memcmp(&p1, &p3, sizeof(Point)) != 0)
    {
        printf("p1 != p3\n");
    }
}

// Příklad 17: Vlastní porovnání
int porovnajOsoby(Osoba *o1, Osoba *o2)
{
    // Porovnej věk
    if (o1->vek < o2->vek) return -1;
    if (o1->vek > o2->vek) return 1;
    return 0;
}

void priklad_17_vlastni_porovnani()
{
    Osoba o1 = {"Petr", 25};
    Osoba o2 = {"Anna", 30};
    
    int vysledek = porovnajOsoby(&o1, &o2);
    
    if (vysledek < 0)
        printf("Petr je mladší\n");
    else if (vysledek > 0)
        printf("Anna je mladší\n");
}

// ============================================
// 9. SIZEOF STRUKTURA - Alignment
// ============================================

// Příklad 18: Velikost struktury - padding
void priklad_18_sizeof()
{
    typedef struct {
        char a;       // 1 byte
        int b;        // 4 byty (ale zarovnáno!)
        char c;       // 1 byte (ale zarovnáno!)
    } BadAlignment;
    
    typedef struct {
        int b;        // 4 byty
        char a;       // 1 byte
        char c;       // 1 byte
    } GoodAlignment;
    
    printf("sizeof(BadAlignment) = %lu\n", sizeof(BadAlignment));   // 12
    printf("sizeof(GoodAlignment) = %lu\n", sizeof(GoodAlignment)); // 8
    
    // Pořadí členů ovlivňuje velikost!
}

// ============================================
// 10. UNION vs STRUCT - Sdílená paměť
// ============================================

// Příklad 19: Union - sdílená paměť
void priklad_19_union()
{
    typedef union {
        int cislo;
        float desetinna;
        char znaky[4];
    } Data;
    
    Data d;
    
    printf("sizeof(struct) = %lu\n", sizeof(struct Osoba));    // Součet + padding
    printf("sizeof(union) = %lu\n", sizeof(Data));             // Max člen (4)
    
    d.cislo = 0x12345678;
    printf("cislo: 0x%X\n", d.cislo);
    printf("znaky[0]: 0x%X\n", d.znaky[0]);
    // Změna cisla ovlivní znaky!
}

// ============================================
// 11. FUNKCE JAKO ČLENY STRUKTURY - Callback
// ============================================

// Příklad 20: Ukazatel na funkci v struktuře
typedef struct {
    char jmeno[50];
    int (*porovnej)(const char *, const char *);
} Osoba_cmp;

void priklad_20_callback()
{
    Osoba_cmp osoba;
    strcpy(osoba.jmeno, "Petr");
    
    // Přiřaď funkci strcmp
    osoba.porovnej = strcmp;
    
    // Zavolej přes strukturu
    int vysledek = osoba.porovnej("hello", "hello");
    printf("strcmp výsledek: %d\n", vysledek);  // 0
}

// ============================================
// 12. SERIALIZACE STRUKTURY
// ============================================

// Příklad 21: Zápis struktury do souboru
void priklad_21_serializace()
{
    Osoba osoba = {"Petr", 25};
    
    FILE *file = fopen("osoba.bin", "wb");
    
    if (file == NULL)
    {
        fprintf(stderr, "Chyba!\n");
        return;
    }
    
    // Zapiš strukturu jako byty
    fwrite(&osoba, sizeof(osoba), 1, file);
    
    fclose(file);
}

// Příklad 22: Čtení struktury ze souboru
void priklad_22_deserializace()
{
    Osoba osoba;
    
    FILE *file = fopen("osoba.bin", "rb");
    
    if (file == NULL)
    {
        fprintf(stderr, "Chyba!\n");
        return;
    }
    
    // Čti strukturu
    fread(&osoba, sizeof(osoba), 1, file);
    
    printf("Přečtená osoba: %s, věk: %d\n", osoba.jmeno, osoba.vek);
    
    fclose(file);
}

// ============================================
// 13. INICIALIZACE - Různé způsoby
// ============================================

// Příklad 23: Způsoby inicializace
void priklad_23_inicializace()
{
    // Zápis 1: Podle pozice
    Osoba o1 = {"Petr", 25};
    
    // Zápis 2: Částečná
    Osoba o2 = {"Anna"};  // vek = 0
    
    // Zápis 3: Designované inicializátory (C99+)
    Osoba o3 = {
        .jmeno = "Jiří",
        .vek = 35
    };
    
    // Zápis 4: Postupně
    Osoba o4;
    strcpy(o4.jmeno, "Jana");
    o4.vek = 28;
    
    printf("o1: %s (%d)\n", o1.jmeno, o1.vek);
    printf("o2: %s (%d)\n", o2.jmeno, o2.vek);
    printf("o3: %s (%d)\n", o3.jmeno, o3.vek);
    printf("o4: %s (%d)\n", o4.jmeno, o4.vek);
}

// ============================================
// 14. ŘAZENÍ POLE STRUKTUR
// ============================================

// Příklad 24: Řazení struktury podle věku
int porovnajVek(const void *a, const void *b)
{
    Osoba *o1 = (Osoba *)a;
    Osoba *o2 = (Osoba *)b;
    
    return o1->vek - o2->vek;
}

void priklad_24_razeni()
{
    Osoba skupinka[] = {
        {"Petr", 25},
        {"Anna", 30},
        {"Jiří", 20}
    };
    
    int pocet = 3;
    
    printf("Před řazením:\n");
    for (int i = 0; i < pocet; i++)
        printf("  %s (%d)\n", skupinka[i].jmeno, skupinka[i].vek);
    
    // Řaď podle věku
    qsort(skupinka, pocet, sizeof(Osoba), porovnajVek);
    
    printf("Po řazení:\n");
    for (int i = 0; i < pocet; i++)
        printf("  %s (%d)\n", skupinka[i].jmeno, skupinka[i].vek);
}

// ============================================
// 15. FORWARD DECLARATION
// ============================================

/*
Forward declaration = deklarace struktury bez definice členů
Používá se když struktury odkazují na sebe
*/

// Příklad 25: Forward declaration
typedef struct Uzel_tag Uzel;

struct Uzel_tag {
    int hodnota;
    Uzel *dalsi;  // Ukazatel na další uzel
};

void priklad_25_linked_list()
{
    Uzel n1 = {1, NULL};
    Uzel n2 = {2, NULL};
    Uzel n3 = {3, NULL};
    
    // Připoj dohromady
    n1.dalsi = &n2;
    n2.dalsi = &n3;
    
    // Procházej seznam
    Uzel *p = &n1;
    while (p != NULL)
    {
        printf("Hodnota: %d\n", p->hodnota);
        p = p->dalsi;
    }
}

// ============================================
// SHRNUTÍ - Nejdůležitější
// ============================================

/*
DEFINICE:
  struct Jmeno {
      typ1 a;
      typ2 b;
  };

TYPEDEF:
  typedef struct { int x; int y; } Point;

PŘÍSTUP:
  struktura.member    - k hodnotě
  ukazatel->member    - přes ukazatel

ALOKACE:
  Point *p = malloc(sizeof(Point));

FUNKCE:
  void fn(Point p)        - kopíruje
  void fn(Point *p)       - bez kopírování (lepší)
  Point fn()              - vrácení
  Point* fn()             - vrácení ukazatele

INICIALIZACE:
  Point p = {10, 20};
  Point p = {.x=10, .y=20};  (C99+)

VNOŘENÉ:
  struct Osoba { Datum datum; };

UNION (sdílená paměť):
  union Data { int x; float f; };

SIZEOF:
  sizeof(Point) - včetně paddingu
*/
