// ============================================
// OUTPUT - Všechny způsoby výstupu v C
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. PRINTF - Základní výstup na standardní výstup
// ============================================

// Jednoduchý text
void priklad_1_text()
{
    printf("Ahoj svet!\n");
    printf("Toto je program v C\n");
}

// Čísla - celočíselné typy
void priklad_2_cisla_int()
{
    int n = 42;
    printf("Cislo: %d\n", n);           // Desítková soustava
    printf("Hexadecimalne: %x\n", n);   // Šestnáctková (42 = 2A)
    printf("Hexadecimalne velke: %X\n", n); // Velká písmena (2A)
    printf("Osmickove: %o\n", n);       // Osmičková (52)
}

// Čísla - plovoucí čárka
void priklad_3_cisla_float()
{
    float f = 3.14159;
    double d = 2.71828;
    
    printf("Float: %f\n", f);           // Výchozí 6 desetinných míst
    printf("Float 2 desetinna: %.2f\n", f);  // Přesně 2 místa: 3.14
    printf("Float 4 desetinna: %.4f\n", f);  // Přesně 4 místa: 3.1416
    printf("Double: %lf\n", d);         // Double typ
    printf("Vědecký zápis: %e\n", f);   // 3.141590e+00
}

// Znaky a řetězce
void priklad_4_znaky_retezce()
{
    char c = 'A';
    char str[] = "Ahoj";
    
    printf("Znak: %c\n", c);            // Jeden znak
    printf("Retezec: %s\n", str);       // Řetězec
    printf("Retezec delka: %lu\n", strlen(str));  // Délka
}

// ============================================
// 2. FORMÁTOVÁNÍ - printf s modifikátory
// ============================================

// Zarovnání a šírka
void priklad_5_zarovnani_sirka()
{
    int n = 42;
    
    printf("|%5d|\n", n);       // Zarovnání doprava, šírka 5: |   42|
    printf("|%-5d|\n", n);      // Zarovnání doleva, šírka 5:  |42   |
    printf("|%05d|\n", n);      // Zarovnání doprava s nulami: |00042|
    printf("|%+d|\n", n);       // Znaménko: |+42|
    printf("|% d|\n", n);       // Mezera pro kladné: | 42|
}

// Šírka pro řetězce a floaty
void priklad_6_sirka_retezce_float()
{
    char str[] = "Ahoj";
    float f = 3.14;
    
    printf("|%10s|\n", str);    // Zarovnání doprava, šírka 10: |      Ahoj|
    printf("|%-10s|\n", str);   // Zarovnání doleva, šírka 10:  |Ahoj      |
    printf("|%10.2f|\n", f);    // Šírka 10, 2 desetinna: |      3.14|
}

// ============================================
// 3. VÝPIS VÍCE HODNOT NAJEDNOU
// ============================================

// Příklady z ukolu 02 - aritmetické operace
void priklad_7_aritmetika()
{
    int n1 = 10, n2 = 3;
    
    printf("Desitkova soustava: %d %d\n", n1, n2);
    printf("Sestnactkova soustava: %x %x\n", n1, n2);
    
    int soucet = n1 + n2;
    printf("Soucet: %d + %d = %d\n", n1, n2, soucet);
    
    int rozdil = n1 - n2;
    printf("Rozdil: %d - %d = %d\n", n1, n2, rozdil);
    
    int soucin = n1 * n2;
    printf("Soucin: %d * %d = %d\n", n1, n2, soucin);
    
    if (n2 == 0)
    {
        printf("Nedefinovany vysledek!\n");
    }
    else
    {
        int podil = n1 / n2;
        printf("Podil: %d / %d = %d\n", n1, n2, podil);
    }
    
    float prumer = (float)soucet / 2;
    printf("Prumer: %.1f\n", prumer);
}

// ============================================
// 4. FPRINTF - Výstup na standardní chybový výstup
// ============================================

// Chybové hlášky
void priklad_8_chyby()
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    fprintf(stderr, "Error: Nedostatek pameti!\n");
    fprintf(stderr, "Error: Nelze otevrit soubor!\n");
}

// Chyby s hodnotami
void priklad_9_chyby_s_hodnotami()
{
    int n = 42;
    int min = 0, max = 100;
    
    fprintf(stderr, "Error: Cislo %d je mimo interval!\n", n);
    fprintf(stderr, "Error: Ocekavano %d, bylo %d\n", 100, n);
    fprintf(stderr, "Error: Vstup mimo interval <%d, %d>!\n", min, max);
}

// ============================================
// 5. VÝPIS HODNOT V CYKLU
// ============================================

// Příklady z ukolu 03 - statistika
void priklad_10_cyklus_oddelene()
{
    int pole[] = {1, 2, 3, 4, 5};
    int pocet = 5;
    int prvni = 1;  // TRUE
    
    for (int i = 0; i < pocet; i++)
    {
        if (prvni)
        {
            printf("%d", pole[i]);
            prvni = 0;  // FALSE
        }
        else
        {
            printf(", %d", pole[i]);
        }
    }
    printf("\n");  // Newline na konci
}

// Výpis bez oddělování
void priklad_11_cyklus_jednoduchy()
{
    int pole[] = {10, 20, 30, 40, 50};
    
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", pole[i]);
    }
    printf("\n");
}

// Výpis do obdélníku / tabulky
void priklad_12_tabulka()
{
    printf("| %3s | %5s |\n", "Jmeno", "Vek");
    printf("|-----|-------|\n");
    printf("| %3s | %5d |\n", "Petr", 25);
    printf("| %3s | %5d |\n", "Anna", 30);
}

// ============================================
// 6. PRINTF S PROCENTY (%)
// ============================================

void priklad_13_procenta()
{
    int pocet_kladnych = 3;
    int pocet_cisel = 10;
    
    float procento = ((float)pocet_kladnych / (float)pocet_cisel) * 100;
    
    printf("Kladnych: %d / %d = %.2f%%\n", pocet_kladnych, pocet_cisel, procento);
    // Výstup: Kladnych: 3 / 10 = 30.00%
    // Poznámka: %% se tiskne jako %
}

// ============================================
// 7. VÝPIS NA STANDARDNÍ CHYBU
// ============================================

void priklad_14_chybovy_vystup()
{
    fprintf(stderr, "Warning: Neco se nepovedlo!\n");
    fprintf(stderr, "Error: Kod chyby: %d\n", 100);
    fprintf(stderr, "Info: Program se konci.\n");
}

// ============================================
// 8. VÝPIS DO SOUBORU
// ============================================

void priklad_15_zapis_do_souboru()
{
    FILE *file = fopen("output.txt", "w");
    
    if (file == NULL)
    {
        fprintf(stderr, "Error: Nelze otevrit soubor!\n");
        return;
    }
    
    fprintf(file, "Toto je text v souboru\n");
    fprintf(file, "Cislo: %d\n", 42);
    fprintf(file, "Float: %.2f\n", 3.14);
    
    fclose(file);
}

// Přidání do souboru (append)
void priklad_16_append_do_souboru()
{
    FILE *file = fopen("output.txt", "a");  // "a" = append
    
    if (file == NULL)
    {
        fprintf(stderr, "Error: Nelze otevrit soubor!\n");
        return;
    }
    
    fprintf(file, "Dalsi radek pridam\n");
    fprintf(file, "A jeste jeden: %s\n", "tady");
    
    fclose(file);
}

// ============================================
// 9. SPRINTF - Zápis do řetězce
// ============================================

void priklad_17_sprintf()
{
    char buffer[100];
    int n = 42;
    float f = 3.14;
    
    // Zapsání do řetězce místo na stdout
    sprintf(buffer, "Cislo: %d, Float: %.2f", n, f);
    
    printf("Obsah bufferu: %s\n", buffer);
    // Výstup: Obsah bufferu: Cislo: 42, Float: 3.14
}

// Bezpečnější varianta - snprintf
void priklad_18_snprintf()
{
    char buffer[50];
    int n = 42;
    
    // snprintf (%d znaky max, včetně null terminatoru)
    snprintf(buffer, sizeof(buffer), "Cislo je %d", n);
    
    printf("Obsah: %s\n", buffer);
}

// ============================================
// 10. VÝPIS RŮZNÝCH DATOVÝCH TYPŮ
// ============================================

void priklad_19_typy()
{
    char c = 'Z';
    short s = 1000;
    int i = 42;
    long l = 123456789L;
    float f = 3.14f;
    double d = 2.71828;
    
    printf("char: %c\n", c);
    printf("short: %hd\n", s);
    printf("int: %d\n", i);
    printf("long: %ld\n", l);
    printf("float: %f\n", f);
    printf("double: %lf\n", d);
    printf("unsigned int: %u\n", (unsigned int)100);
}

// ============================================
// 11. PUTCHAR A PUTS - Jednoduché výstupy
// ============================================

void priklad_20_putchar_puts()
{
    putchar('A');           // Vypíše: A
    putchar('\n');          // Vypíše newline
    
    puts("Ahoj svete!");     // Vypíše: Ahoj svete! (s newline)
}

// ============================================
// 12. VÝPIS S BARVAMI A SPECIÁLNÍMI ZNAKY
// ============================================

void priklad_21_specialni_znaky()
{
    printf("Tab:\tToto je za tabem\n");       // Tab
    printf("Novy\nradek\n");                  // Nový řádek
    printf("Backspace:\bX\n");                // Backspace (smaže znak)
    printf("Uvozovka: \"Ahoj\"\n");           // Dvojité uvozovky
    printf("Apostrof: \'A\'\n");              // Apostrof
    printf("Backslash: \\\n");                // Backslash
}

// Barvy v terminálu (ANSI escape sequences)
void priklad_22_barvy()
{
    printf("\033[31mCerveny text\033[0m\n");      // Červený
    printf("\033[32mZeleny text\033[0m\n");       // Zelený
    printf("\033[33mZluty text\033[0m\n");        // Žlutý
    printf("\033[34mModry text\033[0m\n");        // Modrý
    printf("\033[1;32mTlustý zelený\033[0m\n");   // Tučný zelený
}

// ============================================
// 13. POROVNÁNÍ PRINTF FORMÁTŮ
// ============================================

void priklad_23_formaty_srovneni()
{
    int n = 42;
    float f = 3.14159;
    char *str = "Ahoj";
    
    // Běžné výstupy
    printf("===== BĚŽNÉ VÝSTUPY =====\n");
    printf("Integer: %d\n", n);
    printf("Float: %f\n", f);
    printf("String: %s\n", str);
    
    // S přesností
    printf("\n===== S PŘESNOSTÍ =====\n");
    printf("Float 2 místa: %.2f\n", f);
    printf("Float 4 místa: %.4f\n", f);
    
    // Se šířkou
    printf("\n===== SE ŠÍŘKOU =====\n");
    printf("Šírka 10: |%10d|\n", n);
    printf("Šírka 10 doleva: |%-10d|\n", n);
    
    // Kombinace
    printf("\n===== KOMBINACE =====\n");
    printf("Komplexní: |%10.2f|\n", f);
    printf("S nulami: |%010d|\n", n);
}

// ============================================
// 14. PŘÍKLADY Z ÚKOLŮ
// ============================================

// Jako v ukolu 03 - statistika čísel
void priklad_24_statistika()
{
    int pocet_cisel = 10;
    int pocet_kladnych = 3;
    int pocet_zapornych = 5;
    int pocet_sudych = 4;
    int pocet_lichych = 6;
    
    float procento_kladnych = ((float)pocet_kladnych / (float)pocet_cisel) * 100;
    float procento_zapornych = ((float)pocet_zapornych / (float)pocet_cisel) * 100;
    float procento_sudych = ((float)pocet_sudych / (float)pocet_cisel) * 100;
    float procento_lichych = ((float)pocet_lichych / (float)pocet_cisel) * 100;
    
    printf("Statistika:\n");
    printf("Kladnych: %d (%.1f%%)\n", pocet_kladnych, procento_kladnych);
    printf("Zapornych: %d (%.1f%%)\n", pocet_zapornych, procento_zapornych);
    printf("Sudych: %d (%.1f%%)\n", pocet_sudych, procento_sudych);
    printf("Lichych: %d (%.1f%%)\n", pocet_lichych, procento_lichych);
}

// ============================================
// 15. DYNAMICKÉ FORMÁTOVÁNÍ
// ============================================

void priklad_25_dynamicke_formatovani()
{
    int sirka = 15;
    int cislo = 42;
    
    // Dynamická šírka
    printf("Dynamická šírka %d: |%*d|\n", sirka, sirka, cislo);
    
    int presnost = 3;
    float f = 3.14159;
    
    // Dynamická přesnost
    printf("Dynamická přesnost %d: |%.*f|\n", presnost, presnost, f);
}

// ============================================
// SHRNUTÍ - Nejčastěji používané
// ============================================

/*
PRINTF - Základní:
  printf("text: %d\n", n);
  printf("Retezec: %s\n", str);
  printf("Float: %.2f\n", f);

FPRINTF - Chyby:
  fprintf(stderr, "Error: ...\n");
  fprintf(file, "text: %d\n", n);

PUTCHAR / PUTS:
  putchar('A');
  puts("Ahoj");

SPRINTF - Do řetězce:
  sprintf(buffer, "text: %d", n);
  snprintf(buffer, size, "text: %d", n);

FORMÁTY:
  %d        - integer
  %f        - float (default 6 míst)
  %.2f      - float 2 místa
  %s        - string
  %c        - char
  %x / %X   - hexa
  %o        - okta
  %u        - unsigned

MODIFIKÁTORY:
  %5d       - šírka 5
  %-5d      - doleva
  %05d      - nuly
  |%*d|     - dynamická šírka
  %.*f      - dynamická přesnost

SPECIÁLNÍ:
  \n        - newline
  \t        - tab
  %%        - procento
  \"        - uvozovka
  \\        - backslash
*/
