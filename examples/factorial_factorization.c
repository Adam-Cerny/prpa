/**
 * PŘÍKLAD: Výpočet faktoriálu s faktorizací
 * 
 * Úloha: Přečíst číslo N, vypočítat N! a rozložit jej na prvočísla.
 * Bonus: Počet nul na konci N! (počet faktorů 10 = min(faktory 2, faktory 5))
 * 
 * Vstup:  N (číslo)
 * Výstup: N!, faktorizace, počet nul
 * 
 * Klíčové vzory:
 * - Práce s velkými čísly (unsigned long long)
 * - Detekce přetečení (N! roste velmi rychle)
 * - Faktorizace čísla (Pollard, trial division)
 * - Legendre vzorec pro počet prvočísel v N!
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_PRIME 100  // Maximálně prvočísla do MAX_PRIME

// ===== SHRNUTÍ =====
// N! přetéká při relativně malých N (20! ≈ 2.4e18)
// unsigned long long: do N=20 bez přetečení
// Počet nul v N! = počet 10 = min(2faktory, 5faktory)
// Legendre vzorec: počet p v N! = floor(N/p) + floor(N/p²) + ...

// Eratosthenes: Najdi prvočísla do limit
void sieve(int *primes, int *count, int limit)
{
    char is_prime[limit + 1];
    for (int i = 0; i <= limit; i++)
        is_prime[i] = 1;

    is_prime[0] = is_prime[1] = 0;

    for (int i = 2; i * i <= limit; i++)
    {
        if (is_prime[i])
        {
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = 0;
        }
    }

    *count = 0;
    for (int i = 2; i <= limit; i++)
    {
        if (is_prime[i])
            primes[(*count)++] = i;
    }
}

// Faktoriál (s detekací přetečení)
int factorial_safe(int n, unsigned long long *result)
{
    if (n < 0)
    {
        fprintf(stderr, "Faktorial pro zaporne cislo neni definovan\n");
        return -1;
    }

    *result = 1;
    for (int i = 2; i <= n; i++)
    {
        // Jednoduchá detekce přetečení
        if (*result > ULLONG_MAX / i)
        {
            fprintf(stderr, "Preteceni pri vypoctu %d!\n", n);
            return -1;
        }
        *result *= i;
    }
    return 0;
}

// Legendre vzorec: Počet prvočísla p v N!
int count_prime_in_factorial(int n, int p)
{
    int count = 0;
    long long power = p;

    while (power <= n)
    {
        count += n / power;
        if (power > n / p)  // Prevence přetečení
            break;
        power *= p;
    }
    return count;
}

int main(void)
{
    int n;

    printf("Zadej cislo N: ");
    if (scanf("%d", &n) != 1 || n < 0)
    {
        fprintf(stderr, "Chyba: Zadej nezaporne cislo\n");
        return 1;
    }

    if (n > 20)
    {
        printf("Upozorneni: N > 20 => N! presahuje unsigned long long\n");
    }

    // 1. Vypočet N!
    unsigned long long fact;
    if (factorial_safe(n, &fact) != 0)
    {
        return 1;
    }

    printf("N! = %llu\n", fact);

    // 2. Počet nul na konci (Legendre pro 5)
    int count_5 = count_prime_in_factorial(n, 5);
    int count_2 = count_prime_in_factorial(n, 2);
    int trailing_zeros = (count_5 < count_2) ? count_5 : count_2;

    printf("Pocet nul na konci: %d (5faktory=%d, 2faktory=%d)\n",
           trailing_zeros, count_5, count_2);

    // 3. Faktorizace N! - všechna prvočísla do N
    int primes[MAX_PRIME];
    int prime_count = 0;

    sieve(primes, &prime_count, n);

    if (prime_count > 0)
    {
        printf("Faktorizace N! na prvocisla do %d:\n", n);

        for (int i = 0; i < prime_count && i < 20; i++)  // Maximálně 20 řádků
        {
            int cnt = count_prime_in_factorial(n, primes[i]);
            printf("  %d^%d", primes[i], cnt);

            if ((i + 1) % 5 == 0)
                printf("\n");
            else
                printf(" * ");
        }
        printf("\n");
    }

    // 4. Bonusové údaje
    printf("\nBonusove info:\n");
    printf("  Pocet prvocisel <= N: %d\n", prime_count);

    // Součet exponentů v N!
    int sum_exponents = 0;
    for (int i = 0; i < prime_count; i++)
    {
        sum_exponents += count_prime_in_factorial(n, primes[i]);
    }
    printf("  Soucet exponenty v N!: %d\n", sum_exponents);

    return 0;
}

/*
 * SHRNUTÍ KLÍČOVÝCH VZORŮ:
 * 
 * 1. DETEKCE PŘETEČENÍ:
 *    if (result > ULLONG_MAX / i)  // Dělíme, aby se zabránilo přetečení
 *        fprintf(stderr, "Overflow\n");
 * 
 * 2. LEGENDRE VZOREC (počet p v N!):
 *    int count = 0;
 *    long long power = p;
 *    while (power <= n) {
 *        count += n / power;
 *        if (power > n / p) break;  // Prevence přetečení
 *        power *= p;
 *    }
 * 
 * 3. ERATOSTHENES:
 *    char is_prime[limit+1];
 *    ...标记 není prvočíslo ...
 * 
 * 4. POČET NUL V N!:
 *    zeros = min(count(2), count(5))  // Obvykle count(5) je menší
 * 
 * TESTOVACÍ PŘÍPADY:
 * - N=5:  5! = 120, nul=1, faktory: 2²·3·5
 * - N=10: 10! = 3628800, nul=2
 * - N=0:  0! = 1
 * - N=1:  1! = 1
 * - N=20: blízko k ULLONG_MAX
 * - N=21: Overflow
 */
