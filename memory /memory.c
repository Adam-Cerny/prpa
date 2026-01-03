// ============================================
// PRÁCE S PAMĚTÍ - Pokročilé operace
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// ============================================
// 1. UKAZATELE - Aritmetika s ukazateli
// ============================================

/*
Ukazatele jsou proměnné, které obsahují ADRESU v paměti
Syntax: type *p;   - p je ukazatel na typ "type"

Operace:
  *p     - dereference (přístup k hodnotě)
  &x     - adresa proměnné x
  p++    - posun o sizeof(type) bajtů
  p + n  - posun o n * sizeof(type) bajtů
*/

// Příklad 1: Základní ukazatele
void priklad_1_zakladni_ukazatele()
{
    int x = 42;
    
    // Vytvoř ukazatel na x
    int *p = &x;  // & = "adresa x"
    
    printf("Hodnota x: %d\n", x);           // 42
    printf("Adresa x: %p\n", (void *)&x);   // 0x7fff...
    printf("Ukazatel p: %p\n", (void *)p);  // 0x7fff... (stejná adresa)
    printf("Hodnota přes p: %d\n", *p);     // 42 (* = dereference)
    
    // Změna hodnoty přes ukazatel
    *p = 100;
    printf("Nová hodnota x: %d\n", x);      // 100
}

// Příklad 2: Ukazatele na pole - aritmetika
void priklad_2_ukazatele_pole()
{
    int pole[] = {10, 20, 30, 40, 50};
    int *p = pole;  // p ukazuje na první prvek
    
    printf("Prvek 0 (p[0]): %d\n", p[0]);   // 10
    printf("Prvek 1 (p[1]): %d\n", p[1]);   // 20
    printf("Prvek 2 (*(p+2)): %d\n", *(p + 2)); // 30
    
    // Posun ukazatele
    p++;  // p nyní ukazuje na druhý prvek
    printf("Po p++, hodnota: %d\n", *p);    // 20
    
    p += 2;  // Posun o 2 prvky
    printf("Po p+=2, hodnota: %d\n", *p);   // 40
}

// Příklad 3: Rozdíl ukazatelů
void priklad_3_rozdil_ukazatelu()
{
    int pole[] = {1, 2, 3, 4, 5};
    int *p1 = &pole[1];
    int *p2 = &pole[4];
    
    // Kolik prvků je mezi nimi?
    int vzdalenost = p2 - p1;
    printf("Vzdálenost: %d prvků\n", vzdalenost);  // 3
}

// ============================================
// 2. MEMCPY - Kopírování paměti
// ============================================

/*
memcpy - Memory Copy
Kopíruje N bajtů z jedné oblasti na druhou
Syntax: void *memcpy(void *dest, const void *src, size_t n);

POZOR: Může se překrývat -> buffer overflow!
*/

// Příklad 4: Kopírování paměti - memcpy
void priklad_4_memcpy()
{
    int zdroj[5] = {10, 20, 30, 40, 50};
    int cil[5];
    
    // Zkopíruj všech 5 intů
    memcpy(cil, zdroj, 5 * sizeof(int));
    
    printf("Zdroj: ");
    for (int i = 0; i < 5; i++) printf("%d ", zdroj[i]);
    printf("\n");
    
    printf("Cil: ");
    for (int i = 0; i < 5; i++) printf("%d ", cil[i]);
    printf("\n");
}

// Příklad 5: Kopírování struktur - memcpy
void priklad_5_memcpy_struktura()
{
    typedef struct
    {
        char jmeno[30];
        int vek;
        float vyska;
    } Osoba;
    
    Osoba o1 = {"Petr", 25, 180.5};
    Osoba o2;
    
    // Zkopíruj celou strukturu
    memcpy(&o2, &o1, sizeof(Osoba));
    
    printf("Osoba 1: %s, %d, %.1f\n", o1.jmeno, o1.vek, o1.vyska);
    printf("Osoba 2: %s, %d, %.1f\n", o2.jmeno, o2.vek, o2.vyska);
}

// Příklad 6: Kopírování řetězců - lepší než strcpy
void priklad_6_memcpy_retezec()
{
    char src[] = "Ahoj svet!";
    char dst[50];
    
    // memcpy je bezpečnější a explicitní
    memcpy(dst, src, strlen(src) + 1);  // +1 pro null terminator
    
    printf("Kopírované: %s\n", dst);
}

// ============================================
// 3. MEMMOVE - Bezpečné kopírování (překrývání)
// ============================================

/*
memmove - Memory Move
Stejné jako memcpy, ale bezpečné když se oblasti překrývají!
Syntax: void *memmove(void *dest, const void *src, size_t n);
*/

// Příklad 7: Překrývající se oblasti - memmove
void priklad_7_memmove()
{
    char buffer[] = "ABCDEFGHIJ";
    
    printf("Původní: %s\n", buffer);
    
    // Posuň obsah o 3 místa doprava
    // memcpy by selhal!
    // memmove bezpečně zvládne překrytí
    memmove(buffer + 3, buffer, 7);
    
    printf("Po memmove: %s\n", buffer);
}

// ============================================
// 4. MEMSET - Vyplnění paměti
// ============================================

/*
memset - Memory Set
Vyplní N bajtů určitou hodnotou (0-255)
Syntax: void *memset(void *ptr, int value, size_t n);

Nejčastěji: memset(ptr, 0, size)  - nulování
*/

// Příklad 8: Nulování paměti
void priklad_8_memset_nulovani()
{
    int pole[10];
    
    // Vyplň všechny byty nulou
    memset(pole, 0, sizeof(pole));
    
    printf("Nulované pole: ");
    for (int i = 0; i < 10; i++) printf("%d ", pole[i]);
    printf("\n");  // 0 0 0 0 0 0 0 0 0 0
}

// Příklad 9: Vyplnění různými hodnotami
void priklad_9_memset_hodnota()
{
    unsigned char pole[10];
    
    // Vyplň všechny byty hodnotou 255 (0xFF)
    memset(pole, 255, sizeof(pole));
    
    printf("Pole vyplněné 255: ");
    for (int i = 0; i < 10; i++) printf("%d ", pole[i]);
    printf("\n");  // 255 255 255 255...
}

// Příklad 10: Inicializace struktury
void priklad_10_memset_struktura()
{
    typedef struct
    {
        int a, b, c;
        char text[50];
    } MyStruct;
    
    MyStruct s;
    
    // Vynuluj celou strukturu
    memset(&s, 0, sizeof(MyStruct));
    
    printf("Inicializovaná struktura: a=%d, text='%s'\n", s.a, s.text);
}

// ============================================
// 5. STRINGOVÉ FUNKCE - Práce s řetězci v paměti
// ============================================

// Příklad 11: strlen - délka řetězce
void priklad_11_strlen()
{
    char str[] = "Ahoj";
    
    // strlen - počet znaků BEZ null terminatoru
    size_t delka = strlen(str);
    printf("Délka '%s': %lu\n", str, delka);  // 4
    
    // Potřebuješ místo pro null terminator
    char buffer[strlen(str) + 1];
}

// Příklad 12: strcpy - kopírování řetězce (NEBEZPEČNÉ!)
void priklad_12_strcpy_nebezpecne()
{
    char src[] = "Ahoj";
    char dst[50];
    
    // strcpy - NEBEZPEČNÉ! Co když src je delší?
    strcpy(dst, src);  // OK, src je malý
    printf("Kopírováno: %s\n", dst);
    
    // LEPŠÍ: strncpy
    strncpy(dst, src, sizeof(dst) - 1);
    dst[sizeof(dst) - 1] = '\0';  // Jistota null terminatoru
}

// Příklad 13: strcat - zřetězení (NEBEZPEČNÉ!)
void priklad_13_strcat()
{
    char text[100] = "Ahoj ";
    char jmeno[] = "Petra";
    
    // Přidej řetězec
    strcat(text, jmeno);  // text = "Ahoj Petra"
    printf("Výsledek: %s\n", text);
    
    // BEZPEČNĚJI:
    strncat(text, " !", sizeof(text) - strlen(text) - 1);
}

// Příklad 14: strcmp - porovnání řetězců
void priklad_14_strcmp()
{
    char a[] = "Ahoj";
    char b[] = "Ahoj";
    char c[] = "Cau";
    
    // strcmp vrací:
    // 0 = stejné
    // < 0 = a < b
    // > 0 = a > b
    
    printf("strcmp(a, b) = %d\n", strcmp(a, b));    // 0 (stejné)
    printf("strcmp(a, c) = %d\n", strcmp(a, c));    // < 0 (A < C)
    printf("strcmp(c, a) = %d\n", strcmp(c, a));    // > 0 (C > A)
}

// Příklad 15: strstr - hledání podřetězce
void priklad_15_strstr()
{
    char text[] = "Hledám slovo v textu";
    char hledam[] = "slovo";
    
    char *vysledek = strstr(text, hledam);
    
    if (vysledek != NULL)
    {
        printf("Nalezen na pozici: %ld\n", vysledek - text);  // 7
    }
    else
    {
        printf("Nenalezen\n");
    }
}

// ============================================
// 6. STACK vs HEAP - Rozdíl v paměti
// ============================================

/*
STACK - automatická paměť
  - Deklarace: int x = 5;
  - Automaticky se uvolňuje
  - Rychlejší
  - Omezená velikost
  - Lokální proměnné, parametry

HEAP - dynamická paměť
  - Přidělení: malloc, calloc
  - Musíš ručně uvolnit free
  - Pomalejší
  - Větší kapacita
  - Alokace za běhu
*/

// Příklad 16: Stack
void priklad_16_stack()
{
    // Všechny jsou na STACKU - automaticky se uvolňují
    int x = 5;
    int pole[100];
    char str[] = "Ahoj";
    
    printf("Stack: x=%d\n", x);
    // Při návratu z funkce se všechno uvolní
}

// Příklad 17: Heap
void priklad_17_heap()
{
    // Všechny jsou na HEAPU - musíš uvolnit!
    int *x = malloc(sizeof(int));
    int *pole = malloc(100 * sizeof(int));
    char *str = malloc(50);
    
    *x = 5;
    
    printf("Heap: *x=%d\n", *x);
    
    // VŽDY uvolni!
    free(x);
    free(pole);
    free(str);
}

// ============================================
// 7. VOID POINTERY - Generické ukazatele
// ============================================

/*
void* = ukazatel na cokoli
Zvyklostně se používá v malloc, memcpy apod
Musíš pretypovat (cast) když chceš používat
*/

// Příklad 18: Void pointery
void priklad_18_void_pointer()
{
    int cislo = 42;
    char znaky[] = "Ahoj";
    
    // void* může ukazovat na cokoliv
    void *p = &cislo;
    printf("cislo: %d\n", *(int *)p);  // Cast na int*
    
    p = znaky;
    printf("znaky: %s\n", (char *)p);  // Cast na char*
}

// Příklad 19: malloc vrací void*
void priklad_19_malloc_void()
{
    // malloc vrací (void *)
    void *p = malloc(100);
    
    // Musíš pretypovat
    int *cisla = (int *)p;
    char *text = (char *)p;
    
    cisla[0] = 42;
    printf("cisla[0] = %d\n", cisla[0]);
    
    free(p);
}

// ============================================
// 8. ALIGNMENT - Zarovnání v paměti
// ============================================

/*
Alignment = jak jsou data zarovnána v paměti
- int obvykle na 4bajtové hranici
- char není třeba
- struct má alignment svého největšího členu
*/

// Příklad 20: Velikost struktur - alignment
void priklad_20_alignment_struktur()
{
    struct Zla {
        char a;       // 1 byte
        int b;        // 4 byty (ale zarovnáno - padding!)
        char c;       // 1 byte (ale zarovnáno - padding!)
    };
    
    struct Dobra {
        int b;        // 4 byty
        char a;       // 1 byte
        char c;       // 1 byte
    };
    
    printf("sizeof(struct Zla) = %lu\n", sizeof(struct Zla));     // 12 (padding!)
    printf("sizeof(struct Dobra) = %lu\n", sizeof(struct Dobra));  // 8 (méně padding)
}

// Příklad 21: offsetof - pozice členu v struktuře
void priklad_21_offsetof()
{
    typedef struct
    {
        char a;
        int b;
        char c;
    } MyStruct;
    
    // offsetof = pozice členu v bytech
    printf("offsetof(a) = %lu\n", offsetof(MyStruct, a));  // 0
    printf("offsetof(b) = %lu\n", offsetof(MyStruct, b));  // 4 (zarovnáno)
    printf("offsetof(c) = %lu\n", offsetof(MyStruct, c));  // 8
}

// ============================================
// 9. CAST - Přetypování ukazatelů
// ============================================

/*
Přetypování mezi různými ukazateli
Syntax: (type *)pointer
*/

// Příklad 22: Cast mezi typy
void priklad_22_cast()
{
    int cislo = 0x12345678;
    
    // Pohledej na int jako na bytes
    unsigned char *p = (unsigned char *)&cislo;
    
    printf("Byty int: ");
    for (int i = 0; i < 4; i++)
    {
        printf("%02X ", p[i]);
    }
    printf("\n");  // Závislé na endianness
}

// Příklad 23: Void* cast
void priklad_23_void_cast()
{
    int x = 42;
    
    // Cokoliv -> void* -> cokoli
    void *generic = (void *)&x;
    int *znova = (int *)generic;
    
    printf("Originál: %d\n", x);
    printf("Přes void*: %d\n", *znova);
}

// ============================================
// 10. ENDIANNESS - Pořadí bajtů
// ============================================

/*
BIG ENDIAN: nejdůležitější byte první
LITTLE ENDIAN: nejméně důležitý byte první (Intel)
*/

// Příklad 24: Kontrola endianness
void priklad_24_endianness()
{
    int cislo = 0x12345678;
    unsigned char *p = (unsigned char *)&cislo;
    
    if (p[0] == 0x12)
    {
        printf("Big Endian\n");
    }
    else if (p[0] == 0x78)
    {
        printf("Little Endian\n");
    }
}

// ============================================
// 11. BITWISE OPERACE - Práce s bity
// ============================================

/*
&  - AND
|  - OR
^  - XOR
~  - NOT
<< - LEFT SHIFT
>> - RIGHT SHIFT
*/

// Příklad 25: Bitové operace
void priklad_25_bitwise()
{
    unsigned char x = 0b10110101;  // 181
    
    printf("x = %d (0b%d)\n", x, x);
    printf("x & 0b00001111 = %d\n", x & 0b00001111);  // 5
    printf("x | 0b00001111 = %d\n", x | 0b00001111);  // 191
    printf("x ^ 0b00001111 = %d\n", x ^ 0b00001111);  // 170
    printf("~x = %d\n", ~x);                          // 74 (inverzní)
    printf("x << 2 = %d\n", x << 2);                  // 212
    printf("x >> 2 = %d\n", x >> 2);                  // 45
}

// Příklad 26: Práce s jednotlivými bity
void priklad_26_jednotlive_bity()
{
    unsigned char x = 0;
    
    // Nastav bit 3
    x |= (1 << 3);
    printf("Po nastavení bitu 3: %d\n", x);  // 8
    
    // Smaž bit 3
    x &= ~(1 << 3);
    printf("Po smazání bitu 3: %d\n", x);    // 0
    
    // Ověř bit 3
    if (x & (1 << 3))
    {
        printf("Bit 3 je nastaven\n");
    }
    else
    {
        printf("Bit 3 není nastaven\n");
    }
}

// ============================================
// 12. UNION - Sdílená paměť
// ============================================

/*
union = všechny členy sdílejí stejný prostor paměti
- Velikost = největší člen
- Když změníš jeden člen, ovlivní to ostatní
*/

// Příklad 27: Union - sdílená paměť
void priklad_27_union()
{
    union Data {
        int cislo;
        char znaky[4];
    };
    
    union Data d;
    d.cislo = 0x12345678;
    
    printf("sizeof(union Data) = %lu\n", sizeof(d));  // 4
    printf("d.cislo = 0x%X\n", d.cislo);
    printf("d.znaky[0] = 0x%X\n", d.znaky[0]);        // Závisí na endianness
    
    // Když změníš znaky, změní se i cislo!
    d.znaky[0] = 0xFF;
    printf("Po změně: d.cislo = 0x%X\n", d.cislo);
}

// ============================================
// 13. BITFIELD - Bity v struktuře
// ============================================

/*
Umožňuje definovat čísla s menší bitovou šířkou
Šetří místo v paměti
*/

// Příklad 28: Bitfield
void priklad_28_bitfield()
{
    struct Flags {
        unsigned int flag1 : 1;   // 1 bit
        unsigned int flag2 : 1;   // 1 bit
        unsigned int cislo : 6;   // 6 bitů (0-63)
    };
    
    struct Flags f;
    f.flag1 = 1;
    f.flag2 = 0;
    f.cislo = 42;
    
    printf("sizeof(struct Flags) = %lu\n", sizeof(f));  // Obvykle 4 (alignment)
}

// ============================================
// 14. TYPEDEF - Definování typů
// ============================================

/*
typedef = vytvoření aliasu pro typ
*/

// Příklad 29: Typedef
void priklad_29_typedef()
{
    typedef int Integer;
    typedef int *IntPtr;
    typedef struct {
        int x, y;
    } Point;
    
    Integer a = 42;
    IntPtr p = &a;
    Point pt = {10, 20};
    
    printf("a = %d\n", a);
    printf("*p = %d\n", *p);
    printf("pt = (%d, %d)\n", pt.x, pt.y);
}

// ============================================
// 15. POINTERY NA FUNKCE - Callback
// ============================================

/*
Ukazatele na funkce umožňují callback
*/

// Příklad 30: Pointer na funkci
void priklad_30_pointer_na_funkci()
{
    // Definuj funkci
    int scitej(int a, int b) { return a + b; }
    
    // Ukazatel na funkci
    int (*op)(int, int) = scitej;
    
    // Zavolej přes ukazatel
    int vysledek = op(5, 3);
    printf("5 + 3 = %d\n", vysledek);  // 8
}

// ============================================
// SHRNUTÍ - Nejdůležitější funkce
// ============================================

/*
UKAZATELE:
  int *p = &x;      - ukazatel na x
  *p = 100;         - dereference
  p++;              - posun o sizeof(int)
  *(p+n);           - n-tý prvek

PAMĚŤ:
  memcpy(dst, src, n)   - kopíruj n bajtů
  memmove(dst, src, n)  - kopíruj s překrytím
  memset(ptr, val, n)   - vyplň n bajtů
  memcmp(a, b, n)       - porovnej n bajtů

ŘETĚZCE:
  strlen(s)         - délka
  strcpy(d, s)      - NEBEZPEČNÉ!
  strncpy(d, s, n)  - bezpečněji
  strcmp(a, b)      - porovnání
  strstr(hay, ned)  - hledání

STACK vs HEAP:
  int x;            - STACK
  int *p = malloc() - HEAP

TYPEDEF:
  typedef int MyInt;
  typedef struct {...} MyStruct;

UNION:
  union Data { int a; char b[4]; };  - sdílená paměť

BITFIELD:
  struct Flags { unsigned int x:3; };  - 3 bity
*/
