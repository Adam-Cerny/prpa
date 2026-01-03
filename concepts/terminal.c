// ============================================
// ARGUMENTY Z TERMINÁLU (ARGC, ARGV)
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. ZÁKLADY - ARGC A ARGV
// ============================================

/*
int main(int argc, char *argv[])

argc = počet argumentů (včetně jména programu)
argv = pole ukazatelů na řetězce argumentů

Příklad: program hello world 123
  argc = 4
  argv[0] = "program"
  argv[1] = "hello"
  argv[2] = "world"
  argv[3] = "123"
*/

// Příklad 1: Vypsání všech argumentů
int priklad_1_vse(int argc, char *argv[])
{
    printf("Počet argumentů: %d\n", argc);
    
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }
    
    return 0;
}

// Příklad 2: Zpracování argumentů v cyklu
int priklad_2_cyklus(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Použití: %s <arg1> <arg2> ...\n", argv[0]);
        return 1;
    }
    
    // Preskočit argv[0] (jméno programu)
    for (int i = 1; i < argc; i++)
    {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    
    return 0;
}

// ============================================
// 2. PŘEVOD NA ČÍSLA
// ============================================

// Příklad 3: atoi - String na int (jednoduchý)
int priklad_3_atoi(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Použití: %s <číslo>\n", argv[0]);
        return 1;
    }
    
    int cislo = atoi(argv[1]);  // atoi = ASCII to Integer
    printf("Řetězec '%s' -> číslo %d\n", argv[1], cislo);
    
    return 0;
}

// Příklad 4: strtol - String na long (s kontrolou chyb)
int priklad_4_strtol(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Použití: %s <číslo>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    long cislo = strtol(argv[1], &endptr, 10);  // base 10
    
    // Kontrola chyby
    if (*endptr != '\0')
    {
        printf("Chyba: '%s' není validní číslo\n", argv[1]);
        return 1;
    }
    
    printf("Řetězec '%s' -> číslo %ld\n", argv[1], cislo);
    return 0;
}

// Příklad 5: atof - String na float
int priklad_5_atof(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Použití: %s <číslo s des. čárkou>\n", argv[0]);
        return 1;
    }
    
    double cislo = atof(argv[1]);  // atof = ASCII to Float
    printf("Řetězec '%s' -> číslo %.2f\n", argv[1], cislo);
    
    return 0;
}

// ============================================
// 3. JEDNODUCHÉ PARSOVÁNÍ
// ============================================

// Příklad 6: Suma čísel z argumentů
int priklad_6_suma(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Použití: %s <číslo> <číslo> ...\n", argv[0]);
        return 1;
    }
    
    int suma = 0;
    for (int i = 1; i < argc; i++)
    {
        int cislo = atoi(argv[i]);
        suma += cislo;
    }
    
    printf("Suma: %d\n", suma);
    return 0;
}

// Příklad 7: Součin všech argumentů
int priklad_7_soucin(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Použití: %s <číslo> <číslo> ...\n", argv[0]);
        return 1;
    }
    
    long soucin = 1;
    for (int i = 1; i < argc; i++)
    {
        soucin *= atol(argv[i]);
    }
    
    printf("Součin: %ld\n", soucin);
    return 0;
}

// ============================================
// 4. ZPRACOVÁNÍ VOLEB (FLAGS)
// ============================================

// Příklad 8: Volby začínající s "-"
int priklad_8_volby(int argc, char *argv[])
{
    int verbose = 0;
    int debug = 0;
    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
        {
            verbose = 1;
            printf("Verbose režim zapnut\n");
        }
        else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0)
        {
            debug = 1;
            printf("Debug režim zapnut\n");
        }
        else
        {
            printf("Neznámá volba: %s\n", argv[i]);
        }
    }
    
    printf("verbose=%d, debug=%d\n", verbose, debug);
    return 0;
}

// Příklad 9: Volby s parametry
int priklad_9_parametry(int argc, char *argv[])
{
    char *jmeno = NULL;
    int vek = 0;
    
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
        {
            jmeno = argv[++i];  // Příští argument
        }
        else if (strcmp(argv[i], "-a") == 0 && i + 1 < argc)
        {
            vek = atoi(argv[++i]);
        }
    }
    
    if (jmeno)
        printf("Jméno: %s\n", jmeno);
    if (vek > 0)
        printf("Věk: %d\n", vek);
    
    return 0;
}

// ============================================
// 5. PRAKTICKÝ PŘÍKLAD
// ============================================

// Příklad 10: Kalkulačka z argumentů
int priklad_10_kalkulator(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Použití: %s <číslo1> <operátor> <číslo2>\n", argv[0]);
        printf("Operátory: + - * /\n");
        return 1;
    }
    
    double a = atof(argv[1]);
    char op = argv[2][0];
    double b = atof(argv[3]);
    
    double vysledek = 0;
    int chyba = 0;
    
    switch (op)
    {
        case '+': vysledek = a + b; break;
        case '-': vysledek = a - b; break;
        case '*': vysledek = a * b; break;
        case '/':
            if (b == 0.0)
            {
                printf("Chyba: dělení nulou!\n");
                chyba = 1;
            }
            else
                vysledek = a / b;
            break;
        default:
            printf("Neznámý operátor: %c\n", op);
            chyba = 1;
    }
    
    if (!chyba)
        printf("%.2f %c %.2f = %.2f\n", a, op, b, vysledek);
    
    return chyba;
}

// ============================================
// SHRNUTÍ
// ============================================

/*
argc = počet argumentů
argv[] = pole řetězců s argumenty

ČTENÍ:
  for (int i = 1; i < argc; i++)  // od 1, ne od 0!
  {
      printf("%s\n", argv[i]);
  }

PŘEVOD NA ČÍSLA:
  atoi(str)       -> int
  atol(str)       -> long
  atof(str)       -> double
  strtol(str, &ep, 10) -> long s kontrolou chyby

KONTROLA CHYB S STRTOL:
  char *endptr;
  long n = strtol(argv[i], &endptr, 10);
  if (*endptr != '\0')
  {
      printf("Chyba: není číslo\n");
  }

VOLBY:
  if (strcmp(argv[i], "-v") == 0)  // Porovnání řetězců!
  {
      // Zpracování volby
  }

PŘÍKLAD:
  program -v -n Adam 10 20 30
  argc = 7
  argv[0] = "program"
  argv[1] = "-v"
  argv[2] = "-n"
  argv[3] = "Adam"
  atd.

KLÍČ:
  1. argc vždy >= 1 (alespoň jméno programu)
  2. Cyklus od 1, ne od 0
  3. strcmp() pro porovnání řetězců
  4. strtol/strtod pro bezpečnější konverzi
  5. Vždy zkontroluj počet argumentů!
*/
