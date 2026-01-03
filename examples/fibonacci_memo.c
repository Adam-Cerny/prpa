/**
 * PŘÍKLAD: Fibonacci s memoizací (dynamické programování)
 * 
 * Úloha: Vypočítat N-té Fibonacciho číslo s caching
 * Vstup:  N
 * Výstup: F(N), porovnání naivní vs. memoizované verze
 * 
 * Klíčové vzory:
 * - Rekurze vs. iterace
 * - Memoizace (caching výsledků)
 * - Měření času (clock)
 * - Dynamické programování top-down vs. bottom-up
 * - Přetečení (Fib(N) roste exponenciálně)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_N 50
#define INVALID -1

// ===== SHRNUTÍ =====
// Naivní rekurze: O(2^N) - exponenciální!
// Memoizace: O(N) s O(N) pamětí
// Bottom-up (iterace): O(N) s O(1) pamětí (bez caching)
// Pro N > 90: přetečení i unsigned long long

typedef struct
{
    long long value;
    int computed;
} Memo;

// 1. NAIVNÍ REKURZE - POMALÁ
long long fib_naive(int n)
{
    if (n <= 1)
        return n;
    return fib_naive(n - 1) + fib_naive(n - 2);
}

// 2. MEMOIZACE - TOP-DOWN
long long fib_memo(int n, Memo *memo)
{
    if (n <= 1)
        return n;

    if (memo[n].computed)
        return memo[n].value;

    memo[n].value = fib_memo(n - 1, memo) + fib_memo(n - 2, memo);
    memo[n].computed = 1;

    return memo[n].value;
}

// 3. ITERACE - NEJRYCHLEJŠÍ
long long fib_iterative(int n)
{
    if (n <= 1)
        return n;

    long long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++)
    {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

int main(void)
{
    int n;

    printf("Zadej N (0-90 pro bezpecnost): ");
    if (scanf("%d", &n) != 1 || n < 0)
    {
        fprintf(stderr, "Chyba: Zadej nezaporne cislo\n");
        return 1;
    }

    if (n > 90)
    {
        printf("Upozorneni: N > 90 => Fib(N) presahne unsigned long long\n");
        printf("Fib(90) = 2880067194370816120 (blizko max)\n");
    }

    // 1. ITERATIVNÍ (nejrychlejší)
    clock_t start = clock();
    long long result_iter = fib_iterative(n);
    clock_t end = clock();
    double time_iter = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nIterativní: Fib(%d) = %lld (čas: %.6f s)\n", n, result_iter, time_iter);

    // 2. MEMOIZACE (top-down)
    Memo *memo = calloc(n + 1, sizeof(Memo));
    if (!memo)
    {
        fprintf(stderr, "Alokace selhala\n");
        return 1;
    }

    start = clock();
    long long result_memo = fib_memo(n, memo);
    end = clock();
    double time_memo = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Memoizace:   Fib(%d) = %lld (čas: %.6f s)\n", n, result_memo, time_memo);

    // 3. NAIVNÍ REKURZE - POMALÁ (pouze pro malé N!)
    if (n <= 35)
    {
        start = clock();
        long long result_naive = fib_naive(n);
        end = clock();
        double time_naive = (double)(end - start) / CLOCKS_PER_SEC;

        printf("Naivní:      Fib(%d) = %lld (čas: %.6f s)\n", n, result_naive, time_naive);
        printf("Zrychlení: %.1f×\n", time_naive / time_iter);
    }
    else
    {
        printf("Naivní: Příliš pomalé pro N > 35 (přeskočeno)\n");
    }

    // 4. SEZNAM FIBONACCIHO ČÍSEL
    printf("\nFibonacciho sekvence (0 až %d):\n", n <= 20 ? n : 20);
    for (int i = 0; i <= (n <= 20 ? n : 20); i++)
    {
        printf("F(%2d) = %lld\n", i, fib_iterative(i));
    }

    // 5. OVĚŘENÍ
    if (result_iter == result_memo)
    {
        printf("\n✓ Oba algoritmy daly stejný výsledek\n");
    }
    else
    {
        printf("\n✗ CHYBA: Výsledky se liší!\n");
    }

    free(memo);
    return 0;
}

/*
 * SHRNUTÍ KLÍČOVÝCH VZORŮ:
 * 
 * 1. NAIVNÍ REKURZE (pomalá):
 *    fib(n) = fib(n-1) + fib(n-2)
 *    Složitost: O(2^N) !!!
 * 
 * 2. MEMOIZACE (top-down):
 *    if (memo[n] computed) return memo[n];
 *    result = fib(n-1) + fib(n-2);
 *    memo[n] = result;
 *    Složitost: O(N) s O(N) pamětí
 * 
 * 3. ITERACE (bottom-up):
 *    prev, curr = 0, 1
 *    for i in 2..n: next = prev + curr; prev,curr = curr,next
 *    Složitost: O(N) s O(1) pamětí
 * 
 * 4. MĚŘENÍ ČASU:
 *    clock_t start = clock();
 *    ... code ...
 *    clock_t end = clock();
 *    double time = (double)(end - start) / CLOCKS_PER_SEC;
 * 
 * 5. MEMOIZACE STRUKTURA:
 *    typedef struct { long long value; int computed; } Memo;
 *    Memo *memo = calloc(n+1, sizeof(Memo));
 * 
 * TESTOVACÍ PŘÍPADY:
 * - N=10:  55
 * - N=20:  6765
 * - N=30:  832040
 * - N=40:  102334155
 * - N=50:  12586269025
 * - N=90:  2880067194370816120 (blízko max)
 * 
 * ČASOVÉ POROVNÁNÍ (orientační):
 * - N=30: Naivní ~0.3s, Memoizace ~0.000s
 * - N=40: Naivní ~30s, Memoizace ~0.000s
 * - N=50: Naivní? (příliš dlouho), Memoizace ~0.000s
 */
