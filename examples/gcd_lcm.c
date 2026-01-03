/**
 * PŘÍKLAD: Největší společný dělitel (GCD) více čísel
 * 
 * Úloha: Přečíst N čísel a najít jejich GCD.
 * Dodatečně: Vypočítat GCD a LCM prvních dvou čísel.
 * 
 * Vstup:  N čísel (za sebou)
 * Výstup: GCD všech, GCD&LCM prvních dvou
 * 
 * Klíčové vzory:
 * - Euklidův algoritmus (iterativní a rekurzivní)
 * - Bezpečné čtení pole čísel
 * - Práce se struct pole pro vstup
 * - Vztah GCD a LCM: GCD(a,b) * LCM(a,b) = a*b
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NUMBERS 100

// ===== SHRNUTÍ =====
// GCD(a, b): Dokud b != 0, a, b = b, a % b
// LCM(a, b) = (a * b) / GCD(a, b)
// GCD n čísel = GCD(GCD(...(GCD(a,b), c)...), n)
// Pozor: Přetečení při a*b pro LCM!

// Iterativní Euklidův algoritmus
int gcd(int a, int b)
{
    a = (a < 0) ? -a : a;  // Absolutní hodnota
    b = (b < 0) ? -b : b;

    while (b != 0)
    {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

// LCM: Pozor na přetečení!
long lcm(int a, int b)
{
    int g = gcd(a, b);
    return ((long)a / g) * b;  // Dělíme dříve, aby se zabránilo přetečení
}

int main(void)
{
    int numbers[MAX_NUMBERS];
    int count = 0;

    printf("Zadej cisla (Ctrl+D pro konec): ");

    // 1. Čtení pole
    while (count < MAX_NUMBERS && scanf("%d", &numbers[count]) == 1)
    {
        count++;
    }

    if (count == 0)
    {
        fprintf(stderr, "Chyba: Zadej alespon jedno cislo\n");
        return 1;
    }

    // 2. GCD všech čísel
    int result = numbers[0];
    for (int i = 1; i < count; i++)
    {
        result = gcd(result, numbers[i]);
    }

    printf("GCD vsech: %d\n", result);

    // 3. GCD a LCM prvních dvou
    if (count >= 2)
    {
        int g = gcd(numbers[0], numbers[1]);
        long l = lcm(numbers[0], numbers[1]);

        printf("GCD prvnich dvou: %d\n", g);
        printf("LCM prvnich dvou: %ld\n", l);

        // Ověření vztahu
        printf("Ověření: %d * %ld = %ld, a*b = %ld\n",
               g, l, (long)g * l, (long)numbers[0] * numbers[1]);
    }

    // 4. Dodatečné statistiky
    printf("\nVsechna cisla: ");
    for (int i = 0; i < count; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}

/*
 * SHRNUTÍ KLÍČOVÝCH VZORŮ:
 * 
 * 1. EUKLIDŮV ALGORITMUS:
 *    while (b != 0) {
 *        int tmp = b;
 *        b = a % b;
 *        a = tmp;
 *    }
 *    return a;
 * 
 * 2. LCM BEZ PŘETEČENÍ:
 *    long lcm = ((long)a / gcd_ab) * b;  // Dělíme DŘÍVE
 *    NE: long lcm = (long)a * b / gcd_ab;  // Toto přetéká
 * 
 * 3. VZTAH GCD A LCM:
 *    a * b = GCD(a,b) * LCM(a,b)
 *    LCM(a,b) = (a * b) / GCD(a,b)
 * 
 * 4. GCD POLE:
 *    result = arr[0];
 *    for (int i=1; i<n; i++) result = gcd(result, arr[i]);
 * 
 * 5. PRÁCE SE SCANF:
 *    while (scanf("%d", &num) == 1) { ... }  // Čte až EOF
 * 
 * TESTOVACÍ PŘÍPADY:
 * - GCD(12, 8) = 4
 * - GCD(17, 19) = 1  (prvočísla)
 * - GCD(0, 5) = 5
 * - GCD(-12, 8) = 4  (záporné hodnoty)
 * - LCM(12, 8) = 24
 * - GCD(12, 8, 4) = 4
 */
