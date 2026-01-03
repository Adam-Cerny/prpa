/**
 * PŘÍKLAD: Rotace řetězce
 * 
 * Úloha: Přečíst řetězec a počet pozic, poté řetězec rotovat doleva.
 * Vstup:  řetězec + počet rotací
 * Výstup: rotovaný řetězec
 * 
 * Příklad:
 *   Vstup:   "hello" s rotací 2
 *   Výstup:  "llohe"
 * 
 * Klíčové vzory:
 * - Cirkulární indexování (modulo aritmetika)
 * - Práce s délkou řetězce
 * - Validace vstupu (rotace > délka)
 * - Alternativní algoritmy (in-place vs. buffer)
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR 1000

// ===== SHRNUTÍ =====
// Rotace doleva = posun všech znaků v cyklu
// Algoritmus 1: Pomocí temp bufferu (jednoduší)
// Algoritmus 2: In-place s GCD (optimálnější paměť)
// Pozor: Modulo operace pro indexy!

int main(void)
{
    char str[MAX_STR];
    int rotations;

    // 1. Vstup
    printf("Zadej retezec: ");
    if (!fgets(str, MAX_STR, stdin))
    {
        fprintf(stderr, "Chyba pri cteni retezce\n");
        return 1;
    }

    // Odstranění newline
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[--len] = '\0';
    }

    // Prázdný řetězec
    if (len == 0)
    {
        printf("Prazdny retezec\n");
        return 0;
    }

    printf("Zadej pocet rotaci: ");
    if (scanf("%d", &rotations) != 1)
    {
        fprintf(stderr, "Chyba: Ocekavam cislo\n");
        return 1;
    }

    // 2. Normalizace rotací (kladný zbytek)
    if (len > 0)
    {
        rotations = rotations % len;
        if (rotations < 0)
            rotations += len;
    }

    // 3. ALGORITMUS 1: Pomocí bufferu (snadnější)
    char temp[MAX_STR];

    // Zkopíruj druhý díl: [rotations...len) → temp
    strncpy(temp, &str[rotations], len - rotations);
    // Zkopíruj první díl: [0...rotations) → temp[len-rotations...]
    strncpy(&temp[len - rotations], str, rotations);
    temp[len] = '\0';

    printf("Vysledek: %s\n", temp);

    // ===== ALTERNATIVA: In-place s GCD =====
    // Užitečné pro výuku, ale složitější
    // (viz dokumentace algoritmu "Array Rotation")

    return 0;
}

/*
 * SHRNUTÍ KLÍČOVÝCH VZORŮ:
 * 
 * 1. MODULO PRO NORMALIZACI:
 *    rotations = rotations % len;  // Převede na 0..len-1
 *    if (rotations < 0) rotations += len;  // Pro záporné hodnoty
 * 
 * 2. CIRKULÁRNÍ INDEXOVÁNÍ:
 *    new_index = (old_index + offset) % length;
 * 
 * 3. STRNCPY PRO BEZPEČNOST:
 *    strncpy(dest, src, count);  // Nekopíruje více než count znaků
 * 
 * 4. ROZPOZNÁNÍ NEWLINE:
 *    if (str[len-1] == '\n') str[--len] = '\0';
 * 
 * TESTOVACÍ PŘÍPADY:
 * - "hello" rotace 2 → "llohe"
 * - "abc" rotace 0 → "abc"
 * - "abc" rotace 3 → "abc" (plná rotace)
 * - "abc" rotace 5 → "bca" (5 % 3 = 2)
 * - "" rotace N → "" (prázdný řetězec)
 * - Záporné rotace → převedou se pomocí modula
 */
