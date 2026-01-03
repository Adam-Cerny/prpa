// ============================================
// ZÁKLADNÍ DATOVÉ TYPY V C
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

// ============================================
// 1. CELOČÍSELNÉ TYPY (INTEGERS)
// ============================================

/*
CELOČÍSELNÉ TYPY:
  char          1 byte       -128 až 127
  short         2 byty       -32768 až 32767
  int           4 byty       -2147483648 až 2147483647
  long          4 nebo 8 bytů
  long long     8 bajtů      -9223372036854775808 až ...

UNSIGNED (bez znaménka):
  unsigned char  0 až 255
  unsigned short 0 až 65535
  unsigned int   0 až 4294967295
*/

// Příklad 1: Celočíselné typy
void priklad_1_int_typy()
{
    char c = 65;              // 'A'
    short s = 1000;
    int i = 100000;
    long l = 1000000;
    long long ll = 9223372036854775807LL;
    
    printf("char: %d\n", c);
    printf("short: %d\n", s);
    printf("int: %d\n", i);
    printf("long: %ld\n", l);
    printf("long long: %lld\n", ll);
}

// Příklad 2: Velikost typů
void priklad_2_velikost()
{
    printf("Velikosti typů:\n");
    printf("char: %lu bajtů\n", sizeof(char));
    printf("short: %lu bajtů\n", sizeof(short));
    printf("int: %lu bajtů\n", sizeof(int));
    printf("long: %lu bajtů\n", sizeof(long));
    printf("long long: %lu bajtů\n", sizeof(long long));
}

// Příklad 3: Rozsahy celočíselných typů
void priklad_3_rozsahy()
{
    printf("Rozsahy celočíselných typů:\n");
    printf("char: %d až %d\n", CHAR_MIN, CHAR_MAX);
    printf("short: %d až %d\n", SHRT_MIN, SHRT_MAX);
    printf("int: %d až %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: 0 až %u\n", UINT_MAX);
    printf("long long: %lld až %lld\n", LLONG_MIN, LLONG_MAX);
}

// Příklad 4: Unsigned vs Signed
void priklad_4_signed_vs_unsigned()
{
    signed char sc = -128;      // -128 až 127
    unsigned char uc = 255;     // 0 až 255
    
    signed int si = -1;
    unsigned int ui = 4294967295U;
    
    printf("signed char: %d (min=-128, max=127)\n", sc);
    printf("unsigned char: %u (min=0, max=255)\n", uc);
    printf("signed int: %d\n", si);
    printf("unsigned int: %u\n", ui);
}

// ============================================
// 2. PLOVOUCÍ ČÁRKA (FLOATING POINT)
// ============================================

/*
PLOVOUCÍ ČÁRKA:
  float         4 byty       6-7 znaků přesnost
  double        8 bajtů      15-16 znaků přesnost
  long double   8-16 bajtů   15-33 znaků přesnost

PŘESNOST:
  float: ~1e-6
  double: ~1e-15
*/

// Příklad 5: Plovoucí čárka
void priklad_5_float()
{
    float f = 3.14f;                // Suffix 'f' pro float
    double d = 3.14159265358979;    // Default je double
    long double ld = 3.141592653589793238L;
    
    printf("float: %.6f\n", f);
    printf("double: %.15f\n", d);
    printf("long double: %.20Lf\n", ld);
}

// Příklad 6: Vědecký zápis
void priklad_6_vedecky_zapis()
{
    float f = 1.23e-4f;   // 0.000123
    double d = 1.5e10;    // 15000000000
    
    printf("1.23e-4 = %.6f\n", f);
    printf("1.5e10 = %.0f\n", d);
    printf("Ve vědeckém zápisu: %e, %E\n", 1234.5, 1234.5);
}

// Příklad 7: Přesnost float vs double
void priklad_7_presnost()
{
    float f = 1.0f / 3.0f;
    double d = 1.0 / 3.0;
    
    printf("float:  %.10f\n", f);    // 0.3333333433
    printf("double: %.15f\n", d);    // 0.333333333333333
    
    printf("float má asi 6-7 platných číslic\n");
    printf("double má asi 15-16 platných číslic\n");
}

// Příklad 8: Speciální hodnoty
void priklad_8_specialni_hodnoty()
{
    float f = 0.0f / 0.0f;         // NaN (Not a Number)
    float inf = 1.0f / 0.0f;       // Infinity
    float nf = -1.0f / 0.0f;       // -Infinity
    
    printf("0.0/0.0 = %f\n", f);
    printf("1.0/0.0 = %f\n", inf);
    printf("-1.0/0.0 = %f\n", nf);
    
    // Kontrola speciálních hodnot
    if (f != f)  // NaN není rovno samo sobě!
    {
        printf("f je NaN\n");
    }
}

// Příklad 9: Rozsahy float/double
void priklad_9_rozsahy_float()
{
    printf("float:\n");
    printf("  Minimum: %e\n", FLT_MIN);
    printf("  Maximum: %e\n", FLT_MAX);
    printf("  Epsilon (přesnost): %e\n", FLT_EPSILON);
    
    printf("\ndouble:\n");
    printf("  Minimum: %e\n", DBL_MIN);
    printf("  Maximum: %e\n", DBL_MAX);
    printf("  Epsilon (přesnost): %e\n", DBL_EPSILON);
}

// ============================================
// 3. ZNAKY A ŘETĚZCE
// ============================================

/*
CHAR - jeden znak (ASCII kód)
ŘETĚZEC - pole znaků zakončené '\0' (null terminator)
*/

// Příklad 10: Znaky
void priklad_10_znaky()
{
    char c1 = 'A';        // Znak
    char c2 = 65;         // ASCII kód znaku 'A'
    char c3 = '\n';       // Escape sekvence
    
    printf("Znak 'A': %c\n", c1);
    printf("ASCII 65: %c\n", c2);
    printf("ASCII hodnota 'A': %d\n", 'A');
    printf("ASCII hodnota 'a': %d\n", 'a');
    printf("ASCII hodnota '0': %d\n", '0');
}

// Příklad 11: Escape sekvence
void priklad_11_escape()
{
    printf("Escape sekvence:\n");
    printf("\\n = newline (nový řádek)\n");
    printf("\\t = tab (tabulátor)\n");
    printf("\\r = carriage return\n");
    printf("\\b = backspace\n");
    printf("\\\\ = backslash\n");
    printf("\\\" = dvojité uvozovky\n");
    printf("\\' = apostrof\n");
    printf("\\0 = null terminator\n");
}

// Příklad 12: Řetězce
void priklad_12_retezce()
{
    char text1[] = "Ahoj svet";      // Automaticky alokuje
    char text2[20] = "Nazdar";       // Pevná délka
    char text3[] = {'A', 'h', 'o', 'j', '\0'};  // Manuálně
    
    printf("text1: %s\n", text1);
    printf("text2: %s\n", text2);
    printf("text3: %s\n", text3);
    
    printf("Délka text1: %lu\n", strlen(text1));
    printf("Délka text2: %lu\n", strlen(text2));
}

// Příklad 13: Znaková funkce
void priklad_13_charfunkce()
{
    char c = 'A';
    
    printf("'%c' je:\n", c);
    printf("  Isalpha: %s\n", (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? "ano" : "ne");
    printf("  Isupper: %s\n", (c >= 'A' && c <= 'Z') ? "ano" : "ne");
    printf("  Isdigit: %s\n", (c >= '0' && c <= '9') ? "ano" : "ne");
    
    // Lépe: použij <ctype.h>
    // printf("  isalpha: %d\n", isalpha(c));
}

// ============================================
// 4. KONVERZE TYPŮ
// ============================================

/*
KONVERZE TYPŮ:
- Implicitní (automatická)
- Explicitní (casting)
*/

// Příklad 14: Implicitní konverze
void priklad_14_implicitni()
{
    int i = 10;
    float f = i;  // int -> float (automaticky)
    
    char c = 65;
    int ii = c;   // char -> int
    
    printf("int %d -> float %f\n", i, f);
    printf("char %d -> int %d\n", c, ii);
    
    // Pozor: ztráta informace
    float ff = 3.7f;
    int ii2 = ff;  // 3.7 -> 3 (ztracená část)
    printf("float %.1f -> int %d (ztraceno!)\n", ff, ii2);
}

// Příklad 15: Explicitní konverze (cast)
void priklad_15_casting()
{
    float f = 3.7f;
    
    int i = (int)f;     // Explicitní cast
    int i2 = f;         // Implicitní (stejný efekt)
    
    printf("(int)3.7 = %d\n", i);
    
    // Casting ukazatelů
    int x = 42;
    void *p = (void *)&x;      // int* -> void*
    int *p2 = (int *)p;        // void* -> int*
    printf("Casted pointer: %d\n", *p2);
}

// Příklad 16: Congruence a promotion
void priklad_16_promotion()
{
    // Integer promotion
    char c = 100;
    short s = 1000;
    int i = c + s;  // c a s jsou povýšeny na int
    
    printf("char %d + short %d = int %d\n", c, s, i);
    
    // Float promotion
    float f = 1.5f;
    double d = f + 1.0;  // f je povýšen na double
    
    printf("float %.1f + double 1.0 = double %.1f\n", f, d);
}

// ============================================
// 5. BOOLEAN (LOGICKÉ HODNOTY)
// ============================================

/*
V C99+ lze používat: #include <stdbool.h>
bool hodnota (true/false)

V C89: int (0 = false, nonzero = true)
*/

// Příklad 17: Boolean hodnoty
void priklad_17_boolean()
{
    // Bez stdbool.h (tradiční C)
    int pravda = 1;
    int nepravda = 0;
    
    if (pravda)
        printf("Pravda\n");
    
    if (!nepravda)
        printf("Ne nepravda\n");
    
    // Jakékoliv číslo != 0 je "pravda"
    int x = 5;
    if (x)
        printf("Nonzero je pravda\n");
}

// Příklad 18: Porovnávací operátory
void priklad_18_porovnani()
{
    int a = 5, b = 3;
    
    printf("Porovnávací operátory:\n");
    printf("a == b: %d\n", a == b);  // 0 (nepravda)
    printf("a != b: %d\n", a != b);  // 1 (pravda)
    printf("a > b: %d\n", a > b);    // 1 (pravda)
    printf("a < b: %d\n", a < b);    // 0 (nepravda)
    printf("a >= b: %d\n", a >= b);  // 1 (pravda)
    printf("a <= b: %d\n", a <= b);  // 0 (nepravda)
}

// ============================================
// 6. TYPEDEF - Vytváření aliasů
// ============================================

/*
TYPEDEF = vytvoření nového jména pro typ
*/

// Příklad 19: Typedef
void priklad_19_typedef()
{
    typedef int Integer;
    typedef float Cislo;
    typedef char Znak;
    
    Integer a = 10;
    Cislo f = 3.14f;
    Znak c = 'A';
    
    printf("Integer: %d\n", a);
    printf("Cislo: %.2f\n", f);
    printf("Znak: %c\n", c);
}

// Příklad 20: Typedef s unsigned
void priklad_20_typedef_unsigned()
{
    typedef unsigned int uint;
    typedef unsigned char byte;
    
    uint velik_cislo = 4294967295U;
    byte b = 255;
    
    printf("uint: %u\n", velik_cislo);
    printf("byte: %u\n", (unsigned char)b);
}

// ============================================
// 7. DĚLKA A KONVERZE V PRINTF
// ============================================

/*
PRINTF formáty:
  %d, %i      int
  %u          unsigned int
  %ld, %li    long
  %lld, %lli  long long
  %f, %F      float/double
  %e, %E      vědecký zápis
  %g, %G      kratší z %f nebo %e
  %x, %X      hexadecimální
  %o          osmičková
  %c          char
  %s          string
  %p          pointer
  %%          procento
*/

// Příklad 21: Printf formáty
void priklad_21_printf_formaty()
{
    int i = 42;
    unsigned int u = 4294967295U;
    float f = 3.14159f;
    double d = 3.14159265359;
    char c = 'Z';
    char *s = "ahoj";
    
    printf("int %%d: %d\n", i);
    printf("int %%i: %i\n", i);
    printf("unsigned %%u: %u\n", u);
    printf("float %%f: %f\n", f);
    printf("float %%e: %e\n", f);
    printf("float %%g: %g\n", f);
    printf("double %%f: %.10f\n", d);
    printf("char %%c: %c\n", c);
    printf("string %%s: %s\n", s);
    printf("int %%x: %x\n", i);      // Hexadecimální
    printf("int %%o: %o\n", i);      // Osmičková
}

// Příklad 22: Formáty s modifikátory
void priklad_22_modifikatory()
{
    int i = 42;
    float f = 3.14159f;
    
    printf("Šírka a zarovnání:\n");
    printf("%%5d: |%5d|\n", i);          // Zarovnání doprava
    printf("%%-5d: |%-5d|\n", i);        // Zarovnání doleva
    printf("%%05d: |%05d|\n", i);        // S nulami
    
    printf("\nDes. místa:\n");
    printf("%%.2f: %.2f\n", f);          // 2 des. místa
    printf("%%.5f: %.5f\n", f);          // 5 des. míst
    printf("%%10.2f: |%10.2f|\n", f);    // Šírka 10, 2 des. místa
}

// ============================================
// 8. KONSTANTA
// ============================================

/*
KONSTANTA = nemůžeš měnit po inicializaci
*/

// Příklad 23: Konstanty
void priklad_23_konstanty()
{
    const int MAX = 100;
    const float PI = 3.14159f;
    const char KONEC = '\0';
    
    printf("MAX: %d\n", MAX);
    printf("PI: %.5f\n", PI);
    printf("KONEC: %d\n", KONEC);
    
    // MAX = 200;  // CHYBA! Je to konstanta
}

// Příklad 24: Makra a #define
void priklad_24_makra()
{
    // Definuj v horní části souboru:
    // #define MAX_SIZE 100
    // #define PI 3.14159f
    
    printf("Makra se rozšiřují na místo voláním\n");
}

// ============================================
// 9. SROVNĚNÍ TYPŮ
// ============================================

// Příklad 25: Tabulka typů
void priklad_25_tabulka()
{
    printf("=== TABULKA TYPŮ ===\n");
    printf("Typ          | Velikost | Min              | Max\n");
    printf("-----        | -------- | ---              | ---\n");
    printf("char         | %lu      | %d               | %d\n", 
           sizeof(char), (int)CHAR_MIN, (int)CHAR_MAX);
    printf("short        | %lu      | %d               | %d\n", 
           sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("int          | %lu      | %d               | %d\n", 
           sizeof(int), INT_MIN, INT_MAX);
    printf("long         | %lu      | %ld              | %ld\n", 
           sizeof(long), LONG_MIN, LONG_MAX);
    printf("long long    | %lu      | %lld             | %lld\n", 
           sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("float        | %lu      | %e               | %e\n", 
           sizeof(float), FLT_MIN, FLT_MAX);
    printf("double       | %lu      | %e               | %e\n", 
           sizeof(double), DBL_MIN, DBL_MAX);
}

// ============================================
// SHRNUTÍ - Nejdůležitější
// ============================================

/*
CELOČÍSELNÉ:
  char:       1 byte,  -128 až 127
  short:      2 byty,  -32k až 32k
  int:        4 byty,  ±2 miliardy
  long:       4-8 bytů
  long long:  8 bajtů, ±9 trillion

PLOVOUCÍ ČÁRKA:
  float:      4 byty,  6-7 číslic
  double:     8 bajtů, 15-16 číslic

ZNAKY A ŘETĚZCE:
  char:       jeden znak (ASCII)
  string:     pole znaků + '\0'
  "text":     string literal

KONVERZE:
  int i = 3.14;           // int -> ztráta
  float f = 10;           // int -> float OK
  (int)3.14               // Explicitní casting

FORMÁTY PRINTF:
  %d          int
  %f          float/double
  %e          vědecký zápis
  %c          char
  %s          string
  %x          hex
  %.2f        2 des. místa

TYPEDEF:
  typedef int Integer;
  typedef unsigned char byte;
*/
