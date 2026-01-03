// ============================================
// INPUT - Všechny způsoby čtení vstupu v C
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. ZÁKLADNÍ ČTENÍ - scanf()
// ============================================

// Jedno číslo
void priklad_1_jedno_cislo()
{
    int n;
    scanf("%d", &n);
    printf("Nacetl jsem: %d\n", n);
}

// Dvě čísla (oddělená mezerou)
void priklad_2_dve_cisla()
{
    int n1, n2;
    scanf("%d %d", &n1, &n2);
    printf("Nacetl jsem: %d a %d\n", n1, n2);
}

// Řetězec (bez mezer)
void priklad_3_retezec()
{
    char str[100];
    scanf("%s", str);
    printf("Nacetl jsem: %s\n", str);
}

// ============================================
// 2. KONTROLA NÁVRATOVÉ HODNOTY scanf()
// ============================================

void priklad_4_kontrola_ret()
{
    int n;
    int ret = scanf("%d", &n);
    
    if (ret != 1)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return;  // nebo return 100;
    }
    printf("Vstup je OK: %d\n", n);
}

// Dvě čísla - obě musí být načteny
void priklad_5_kontrola_dve()
{
    int n1, n2;
    int ret = scanf("%d %d", &n1, &n2);
    
    if (ret != 2)
    {
        fprintf(stderr, "Error: Musi byt zadana 2 cisla!\n");
        return;
    }
    printf("OK: %d, %d\n", n1, n2);
}

// ============================================
// 3. ČTENÍ V CYKLU - Postupně do EOF
// ============================================

void priklad_6_cyklus_cisla()
{
    int cislo;
    int pocet = 0;
    int suma = 0;
    
    // Čtení dokud přichází data
    while (scanf("%d", &cislo) == 1)
    {
        pocet++;
        suma += cislo;
        printf("Nacetl jsem %d-te cislo: %d\n", pocet, cislo);
    }
    
    printf("Celkem: %d cisel, suma: %d\n", pocet, suma);
}

// Čtení řetězců v cyklu
void priklad_7_cyklus_retezce()
{
    char slovo[100];
    int pocet = 0;
    
    while (scanf("%s", slovo) == 1)
    {
        pocet++;
        printf("%d. slovo: %s (delka %lu)\n", pocet, slovo, strlen(slovo));
    }
}

// ============================================
// 4. ČTENÍ ŘETĚZCE SE ZNAKEM ZA NÍM
// ============================================

void priklad_8_retezec_se_znakem()
{
    char str[100];
    char extra;
    
    int ret = scanf("%99s%c", str, &extra);
    
    if (ret != 2 || extra != '\n')
    {
        fprintf(stderr, "Error: Nevalidni format!\n");
        return;
    }
    printf("Retezec: %s\n", str);
}

// ============================================
// 5. ČTENÍ S RŮZNÝMI FORMÁTY
// ============================================

void priklad_9_formaty()
{
    int n_dec, n_hex, n_oct;
    float f;
    char c;
    
    // Desítková soustava
    scanf("%d", &n_dec);      // 42
    
    // Šestnáctková soustava
    scanf("%x", &n_hex);      // FF
    
    // Osmičková soustava
    scanf("%o", &n_oct);      // 77
    
    // Plovoucí čárka
    scanf("%f", &f);          // 3.14
    
    // Jeden znak
    scanf("%c", &c);          // A
}

// ============================================
// 6. ČTENÍ S LIMITACÍ (bezpečně)
// ============================================

void priklad_10_limitace()
{
    char str[100];
    
    // Max 99 znaků + null terminator
    scanf("%99s", str);
    printf("Bezpecne nacten: %s\n", str);
}

// Řetězec s mezerami (limitace)
void priklad_11_retezec_s_mezerami()
{
    char line[100];
    
    // Přečte řádek (včetně mezer) až do \n
    fgets(line, sizeof(line), stdin);  // Bezpečnější než scanf s mezery
    
    // Odstraň newline na konci
    line[strcspn(line, "\n")] = 0;
    printf("Nacten: %s\n", line);
}

// ============================================
// 11b. NAČTENÍ ODSTAVCE (VÍCE ŘÁDKŮ)
// ============================================

void priklad_11b_odstavec()
{
    // Načte až do prázdného řádku nebo EOF, ukládá do dynamického bufferu
    char buffer[256];
    size_t cap = 0;
    size_t len = 0;
    char *text = NULL;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // Prázdný řádek = konec odstavce
        if (buffer[0] == '\n' || buffer[0] == '\r')
            break;

        size_t chunk = strlen(buffer);
        if (len + chunk + 1 > cap)
        {
            cap = (cap == 0) ? 512 : cap * 2;
            char *tmp = realloc(text, cap);
            if (!tmp)
            {
                free(text);
                fprintf(stderr, "Error: Nedostatek pameti!\n");
                return;
            }
            text = tmp;
        }

        memcpy(text + len, buffer, chunk);
        len += chunk;
        text[len] = '\0';
    }

    if (text == NULL)
    {
        printf("Nic nebylo zadano (EOF nebo prazdny prvni radek).\n");
        return;
    }

    printf("Nacteny odstavec:\n%s\n", text);
    free(text);
}

// ============================================
// 11c. NAČTENÍ ODSTAVCE PŘES getchar()
// ============================================

void priklad_11c_odstavec_getchar()
{
    // Čte znak po znaku až do prázdného řádku nebo EOF, dynamicky zvětšuje buffer
    size_t cap = 0;
    size_t len = 0;
    char *text = NULL;

    int prev_was_newline = 0; // detekce prázdného řádku
    int ch;

    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            if (prev_was_newline)
                break; // dva newliny za sebou => prázdný řádek
            prev_was_newline = 1;
        }
        else if (ch == '\r')
        {
            // ignoruj CR (Windows konce řádků)
            continue;
        }
        else
        {
            prev_was_newline = 0;
        }

        // zvětši buffer pokud je třeba (+1 pro '\0')
        if (len + 2 > cap)
        {
            cap = (cap == 0) ? 512 : cap * 2;
            char *tmp = realloc(text, cap);
            if (!tmp)
            {
                free(text);
                fprintf(stderr, "Error: Nedostatek pameti!\n");
                return;
            }
            text = tmp;
        }

        text[len++] = (char)ch;
        text[len] = '\0';

        if (ch == '\n')
            continue;
    }

    if (text == NULL || len == 0)
    {
        printf("Nic nebylo zadano (EOF nebo prazdny prvni radek).\n");
        free(text);
        return;
    }

    printf("Nacteny odstavec (getchar):\n%s\n", text);
    free(text);
}

// ============================================
// 7. ČTENÍ POLE S DYNAMICKOU ALOKACÍ
// ============================================

void priklad_12_pole_s_reallocem()
{
    int *cisla = NULL;
    int kapacita = 0;
    int pocet = 0;
    int cislo;
    
    // Čtení do EOF
    while (scanf("%d", &cislo) == 1)
    {
        // Kontrola, je-li pole plné
        if (pocet >= kapacita)
        {
            if (kapacita == 0)
                kapacita = 5;  // Počáteční kapacita
            else
                kapacita *= 2;  // Zdvojnásob
            
            // Realokace paměti
            int *new = realloc(cisla, kapacita * sizeof(int));
            if (new == NULL)
            {
                fprintf(stderr, "Error: Nedostatek pameti!\n");
                free(cisla);
                return;
            }
            cisla = new;
        }
        
        cisla[pocet++] = cislo;
    }
    
    printf("Nacteno %d cisel\n", pocet);
    
    // Vypis
    for (int i = 0; i < pocet; i++)
    {
        printf("%d ", cisla[i]);
    }
    printf("\n");
    
    free(cisla);  // Uvolni paměť!
}

// ============================================
// 8. ČIŠTĚNÍ BUFFERU PO CHYBĚ
// ============================================

void priklad_13_cisteni_bufferu()
{
    int n;
    int ret = scanf("%d", &n);
    
    if (ret != 1)
    {
        // Vymaž zbytek řádku
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        fprintf(stderr, "Error: Chybny vstup!\n");
        return;
    }
    printf("OK: %d\n", n);
}

// ============================================
// 9. ČTENÍ Z PŘÍKAZOVÉ ŘÁDKY (argc/argv)
// ============================================

void priklad_14_argv()
{
    // int main(int argc, char *argv[])
    // {
    //     if (argc < 2)
    //     {
    //         fprintf(stderr, "Error: Chybi argument!\n");
    //         return 100;
    //     }
    //     
    //     printf("Program: %s\n", argv[0]);      // Jméno programu
    //     printf("Argument 1: %s\n", argv[1]);   // První argument
    //     
    //     if (argc > 2)
    //         printf("Argument 2: %s\n", argv[2]); // Druhý argument
    // }
}

// ============================================
// 10. BEZPEČNÝ PŘEVOD ŘETĚZCE NA ČÍSLO
// ============================================

void priklad_15_strtol()
{
    // int main(int argc, char *argv[])
    // {
    //     char *endptr;
    //     long num = strtol(argv[1], &endptr, 10);  // Desítková soustava
    //     
    //     if (*endptr != '\0')
    //     {
    //         fprintf(stderr, "Error: Nespravny format!\n");
    //         return 100;
    //     }
    //     
    //     if (num <= 0)
    //     {
    //         fprintf(stderr, "Error: Cislo musi byt kladne!\n");
    //         return 100;
    //     }
    //     
    //     printf("Nacetl jsem: %ld\n", num);
    // }
}

// ============================================
// 11. ČTENÍ ZNAKŮ S KONTROLOU
// ============================================

void priklad_16_znaky()
{
    char c;
    int ret = scanf("%c", &c);
    
    if (ret != 1)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return;
    }
    
    // Kontrola, zda je to písmeno
    if (c >= 'A' && c <= 'Z')
    {
        printf("Velke pismeno: %c\n", c);
    }
    else if (c >= 'a' && c <= 'z')
    {
        printf("Male pismeno: %c\n", c);
    }
    else if (c >= '0' && c <= '9')
    {
        printf("Cislo: %c\n", c);
    }
}

// ============================================
// 12. ČTENÍ ŘETĚZCE S VALIDACÍ DÉLEK
// ============================================

void priklad_17_validace_delky()
{
    char str[50];
    
    if (scanf("%49s", str) != 1)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return;
    }
    
    int len = strlen(str);
    
    if (len == 0)
    {
        fprintf(stderr, "Error: Prazdny retezec!\n");
        return;
    }
    
    if (len > 30)
    {
        fprintf(stderr, "Error: Retezec je prilis dlouhy!\n");
        return;
    }
    
    printf("Spravny retezec: %s (delka %d)\n", str, len);
}

// ============================================
// 13. ČTENÍ S KONTROLOU ROZSAHU
// ============================================

void priklad_18_rozsah()
{
    #define MIN -1000
    #define MAX 1000
    
    int n;
    int ret = scanf("%d", &n);
    
    if (ret != 1)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return;
    }
    
    if (n < MIN || n > MAX)
    {
        fprintf(stderr, "Error: Vstup mimo interval <%d, %d>!\n", MIN, MAX);
        return;
    }
    
    printf("Spravny vstup: %d\n", n);
}

// ============================================
// 14. ČTENÍ ČÍSLA S KONTROLOU NA DĚLENÍ NULOU
// ============================================

void priklad_19_deleni_nulou()
{
    int a, b;
    int ret = scanf("%d %d", &a, &b);
    
    if (ret != 2)
    {
        fprintf(stderr, "Error: Chybny vstup!\n");
        return;
    }
    
    if (b == 0)
    {
        fprintf(stderr, "Error: Deleni nulou!\n");
        return;
    }
    
    printf("Vysledek: %d / %d = %d\n", a, b, a / b);
}

// ============================================
// 15. ČTENÍ SOUBORU
// ============================================

void priklad_20_cteni_souboru()
{
    FILE *file = fopen("input.txt", "r");
    
    if (file == NULL)
    {
        fprintf(stderr, "Error: Nelze otevrit soubor!\n");
        return;
    }
    
    int n;
    while (fscanf(file, "%d", &n) == 1)
    {
        printf("Nacteno z souboru: %d\n", n);
    }
    
    fclose(file);
}

// ============================================
// SHRNUTÍ - Nejčastěji používané
// ============================================

/*
1. Základní čtení:
   int n;
   scanf("%d", &n);

2. Kontrola chyby:
   if (scanf("%d", &n) != 1) { ... }

3. Čtení v cyklu:
   while (scanf("%d", &n) == 1) { ... }

4. Bezpečné čtení řetězce:
   char str[100];
   scanf("%99s", str);

5. Čištění bufferu:
   int c;
   while ((c = getchar()) != '\n' && c != EOF);

6. Dynamické pole:
   int *arr = NULL;
   int cap = 0, cnt = 0;
   // realloc když třeba...

7. Z příkazové řádky:
   int main(int argc, char *argv[])

8. Bezpečný převod:
   long n = strtol(argv[1], &endptr, 10);
*/
