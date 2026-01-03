/**
 * ŘÍDÍCÍ STRUKTURY V C
 * 
 * Obsah:
 * 1. IF/ELSE - Podmíněné větvení
 * 2. SWITCH/CASE - Výběr z více možností
 * 3. FOR LOOP - Cyklus s pevným počtem iterací
 * 4. WHILE LOOP - Cyklus s podmínkou na začátku
 * 5. DO-WHILE LOOP - Cyklus s podmínkou na konci
 * 6. BREAK/CONTINUE - Řízení toku v cyklech
 * 7. GOTO - Skok na etiketu (izolovaně používání!)
 */

#include <stdio.h>
#include <stdlib.h>

// ============================================================
// 1. IF/ELSE - Podmíněné větvení
// ============================================================

void example_if_else(void)
{
    printf("\n=== 1. IF/ELSE ===\n");

    int age = 20;

    // Základní if
    if (age >= 18)
        printf("Dospělý\n");

    // if-else
    if (age < 18)
        printf("Nezletilý\n");
    else
        printf("Dospělý\n");

    // Vnořené if-else
    if (age >= 65)
        printf("Senior\n");
    else if (age >= 18)
        printf("Dospělý\n");
    else if (age >= 13)
        printf("Teenager\n");
    else
        printf("Dítě\n");

    // Ternární operátor (zkrácená forma if-else)
    const char *status = (age >= 18) ? "Dospělý" : "Nezletilý";
    printf("Status: %s\n", status);

    // Multiple conditions
    int score = 75;
    if (score >= 90 && age >= 18)  // AND (&&)
        printf("Vyborny student\n");

    if (score < 50 || age < 13)    // OR (||)
        printf("Potrebuje podporu\n");

    if (!(score < 60))             // NOT (!)
        printf("Pozitivny vysledek\n");
}

// ============================================================
// 2. SWITCH/CASE - Výběr z více možností
// ============================================================

void example_switch(void)
{
    printf("\n=== 2. SWITCH/CASE ===\n");

    int day = 3;

    // Základní switch
    switch (day)
    {
    case 1:
        printf("Pondělí\n");
        break;  // POZOR: bez break padá dál (fall-through)
    case 2:
        printf("Úterý\n");
        break;
    case 3:
        printf("Středa\n");
        break;
    case 4:
        printf("Čtvrtek\n");
        break;
    case 5:
        printf("Pátek\n");
        break;
    case 6:
    case 7:
        printf("Víkend\n");  // Oba případy (6 a 7) spadají sem
        break;
    default:
        printf("Neplatný den\n");
        break;
    }

    // Switch s caractery
    char grade = 'B';
    switch (grade)
    {
    case 'A':
        printf("Výborný\n");
        break;
    case 'B':
        printf("Velmi dobrý\n");
        break;
    case 'C':
        printf("Dobrý\n");
        break;
    default:
        printf("Neznámá známka\n");
    }

    // Fall-through (záměrné)
    int level = 2;
    switch (level)
    {
    case 3:
        printf("3. úroveň: ");
    case 2:
        printf("2. úroveň: ");
    case 1:
        printf("1. úroveň\n");
        break;
    default:
        printf("Neznámá úroveň\n");
    }
}

// ============================================================
// 3. FOR LOOP - Cyklus s pevným počtem iterací
// ============================================================

void example_for_loop(void)
{
    printf("\n=== 3. FOR LOOP ===\n");

    // Základní for
    printf("Počítání 1-5: ");
    for (int i = 1; i <= 5; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    // Sestupný for
    printf("Odpočítávání 5-1: ");
    for (int i = 5; i >= 1; i--)
    {
        printf("%d ", i);
    }
    printf("\n");

    // For s krokem > 1
    printf("Sudá čísla 0-10: ");
    for (int i = 0; i <= 10; i += 2)
    {
        printf("%d ", i);
    }
    printf("\n");

    // Vnořené for (tabulka)
    printf("Malá tabulka násobení:\n");
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            printf("%3d ", i * j);
        }
        printf("\n");
    }

    // Matice (2D pole)
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}};

    printf("Matice:\n");
    for (int row = 0; row < 2; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }

    // For bez inicializace
    int i = 1;
    for (; i <= 3; i++)
    {
        printf("i=%d ", i);
    }
    printf("\n");

    // For bez podmínky (nekonečný - POZOR!)
    // for (int x = 0; ; x++) { ... }  // Používej break!

    // For bez posunu
    for (int k = 1; k <= 5; )
    {
        printf("k=%d ", k);
        k += 2;
    }
    printf("\n");
}

// ============================================================
// 4. WHILE LOOP - Cyklus s podmínkou na začátku
// ============================================================

void example_while_loop(void)
{
    printf("\n=== 4. WHILE LOOP ===\n");

    // Základní while
    printf("Počítání 1-5 (while): ");
    int i = 1;
    while (i <= 5)
    {
        printf("%d ", i);
        i++;
    }
    printf("\n");

    // While s čtením vstupu
    printf("Zadej čísla (0 = stop): ");
    int num;
    int sum = 0;
    while (scanf("%d", &num) == 1 && num != 0)
    {
        sum += num;
    }
    printf("Součet: %d\n", sum);

    // Nekonečný while (se break)
    printf("Iterace s break:\n");
    int counter = 0;
    while (1)
    {
        printf("  Iterace %d\n", counter);
        counter++;
        if (counter >= 3)
            break;
    }

    // While s podmínkou
    int health = 100;
    printf("Health points: ");
    while (health > 0)
    {
        printf("%d ", health);
        health -= 25;
    }
    printf("(Game Over)\n");
}

// ============================================================
// 5. DO-WHILE LOOP - Cyklus s podmínkou na konci
// ============================================================

void example_do_while(void)
{
    printf("\n=== 5. DO-WHILE LOOP ===\n");

    // Základní do-while
    printf("Počítání 1-5 (do-while): ");
    int i = 1;
    do
    {
        printf("%d ", i);
        i++;
    } while (i <= 5);
    printf("\n");

    // Do-while s menu (klasické použití!)
    printf("\nMenu (do-while):\n");
    int choice;
    do
    {
        printf("1. Možnost A\n");
        printf("2. Možnost B\n");
        printf("3. Konec\n");
        printf("Vyber (1-3): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("  Vybrals A\n");
            break;
        case 2:
            printf("  Vybrals B\n");
            break;
        case 3:
            printf("  Konec\n");
            break;
        default:
            printf("  Neplatná volba\n");
        }
    } while (choice != 3);

    // Do-while: tělo se spustí minimálně jednou
    int x = 10;
    printf("Do-while s x=10 (x<5): ");
    do
    {
        printf("Běží! ");
        x--;
    } while (x < 5);  // FALSE, ale tělo se spustilo
    printf("\n");
}

// ============================================================
// 6. BREAK a CONTINUE - Řízení toku v cyklech
// ============================================================

void example_break_continue(void)
{
    printf("\n=== 6. BREAK a CONTINUE ===\n");

    // BREAK - ukončí cyklus
    printf("Break (stop na 3): ");
    for (int i = 1; i <= 10; i++)
    {
        if (i == 3)
            break;  // Ukončit cyklus
        printf("%d ", i);
    }
    printf("\n");

    // CONTINUE - skočí na další iteraci
    printf("Continue (přeskočit 3): ");
    for (int i = 1; i <= 5; i++)
    {
        if (i == 3)
            continue;  // Skočit na dalš iteraci
        printf("%d ", i);
    }
    printf("\n");

    // Break ve vnořeném cyklu (přeruší pouze vnitřní!)
    printf("Break ve vnořeném cyklu:\n");
    for (int i = 1; i <= 3; i++)
    {
        printf("Vnější: %d, ", i);
        for (int j = 1; j <= 5; j++)
        {
            if (j == 3)
                break;  // Přerušuje jen vnitřní cyklus!
            printf("%d ", j);
        }
        printf("\n");
    }

    // Continue ve vnořeném cyklu
    printf("Continue ve vnořeném cyklu:\n");
    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            if (j == 2)
                continue;  // Skočí na j++
            printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }

    // Běžný usecase: Hledání v poli
    printf("Hledání prvku:\n");
    int arr[] = {10, 20, 30, 40, 50};
    int target = 30;
    int found = 0;

    for (int i = 0; i < 5; i++)
    {
        if (arr[i] == target)
        {
            printf("Našli jsme %d na indexu %d\n", target, i);
            found = 1;
            break;  // Můžeme skončit
        }
    }

    if (!found)
        printf("Nenalezeno\n");
}

// ============================================================
// 7. GOTO - Skok na etiketu (používej velmi opatrně!)
// ============================================================

void example_goto(void)
{
    printf("\n=== 7. GOTO (opatrně!) ===\n");

    // Základní goto
    int i = 0;
    printf("Počítání s goto: ");

start_loop:
    printf("%d ", i);
    i++;

    if (i <= 3)
        goto start_loop;

    printf("\nHotovo\n");

    // Goto pro chybové stavy (je to ok v C!)
    printf("\nGoto pro cleanup:\n");

    FILE *f = fopen("/tmp/test.txt", "w");
    if (!f)
    {
        fprintf(stderr, "Chyba: Nemohu otevřít soubor\n");
        goto cleanup;
    }

    fprintf(f, "Test\n");

    // Další chyba?
    if (feof(f))
    {
        fprintf(stderr, "Chyba: EOF\n");
        goto close_file;
    }

close_file:
    if (f)
        fclose(f);

cleanup:
    printf("Cleanup hotovo\n");
}

// ============================================================
// PRAKTICKÉ USE-CASES
// ============================================================

// USE-CASE 1: Validace vstupu s while
void validate_input_example(void)
{
    printf("\n=== USE-CASE 1: Validace vstupu ===\n");

    int age = -1;
    while (age < 0 || age > 150)
    {
        printf("Zadej věk (0-150): ");
        if (scanf("%d", &age) != 1)
        {
            fprintf(stderr, "Chyba: Očekávám číslo\n");
            while (getchar() != '\n')
                ;  // Vyčistit buffer
            age = -1;
            continue;
        }

        if (age < 0 || age > 150)
            printf("Neplatný věk. Zkus znovu.\n");
    }
    printf("Přijatý věk: %d\n", age);
}

// USE-CASE 2: Hledání v matici
void matrix_search_example(void)
{
    printf("\n=== USE-CASE 2: Hledání v matici ===\n");

    int matrix[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int target = 5;
    int found = 0;

    for (int row = 0; row < 3 && !found; row++)
    {
        for (int col = 0; col < 3 && !found; col++)
        {
            if (matrix[row][col] == target)
            {
                printf("Našli jsme %d na [%d][%d]\n", target, row, col);
                found = 1;  // Signál pro vnější cyklus
            }
        }
    }

    if (!found)
        printf("Nenalezeno\n");
}

// USE-CASE 3: Čítač se skip podmínkami
void counter_with_conditions(void)
{
    printf("\n=== USE-CASE 3: Počítání s podmínkami ===\n");

    int count = 0;
    int sum = 0;

    for (int i = 1; i <= 20; i++)
    {
        if (i % 2 == 0)
            continue;  // Přeskočit sudá čísla

        if (i % 5 == 0)
            break;  // Zastavit na násobcích 5

        count++;
        sum += i;
    }

    printf("Počet: %d, Součet: %d\n", count, sum);
}

// USE-CASE 4: Vnořené smyčky s příznakem
void nested_with_flag(void)
{
    printf("\n=== USE-CASE 4: Vnořené smyčky s příznakem ===\n");

    int found = 0;

    for (int i = 1; i <= 3 && !found; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            if (i * j == 6)
            {
                printf("Našli jsme: %d * %d = 6\n", i, j);
                found = 1;
                break;
            }
        }
    }
}

// ============================================================
// MAIN
// ============================================================

int main(void)
{
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║        ŘÍDÍCÍ STRUKTURY V PROGRAMU C              ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    example_if_else();
    example_switch();
    example_for_loop();
    example_while_loop();
    example_do_while();
    example_break_continue();
    example_goto();

    printf("\n╔════════════════════════════════════════════════════╗\n");
    printf("║              PRAKTICKÉ PŘÍKLADY                    ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");

    validate_input_example();
    matrix_search_example();
    counter_with_conditions();
    nested_with_flag();

    return 0;
}

/*
 * ═══════════════════════════════════════════════════════════════════════════
 * SHRNUTÍ: Nejčastěji používané řídící struktury na zkoušce
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * 1. IF/ELSE
 *    - Základní větvení
 *    - Vnořené podmínky: if-else if-else
 *    - Ternární operátor: (cond) ? true_val : false_val
 *    - Logické operátory: &&, ||, !
 * 
 * 2. SWITCH/CASE
 *    - Výběr z diskrétních možností (int, char)
 *    - POZOR: Bez break padá dál (fall-through)
 *    - default pro neznámé případy
 * 
 * 3. FOR LOOP
 *    - for (init; condition; increment)
 *    - Nejčastěji: for (int i=0; i<n; i++)
 *    - Vnořené for: Matice, tabulky
 *    - Iterace přes pole
 * 
 * 4. WHILE LOOP
 *    - while (condition) { ... }
 *    - Používá se když počet iterací není znám
 *    - Čtení vstupu: while (scanf(...) == 1)
 * 
 * 5. DO-WHILE LOOP
 *    - do { ... } while (condition);
 *    - Tělo se spustí minimálně jednou
 *    - Ideální pro menu: "Vyber volbu" - načítání opakovat dokud není OK
 * 
 * 6. BREAK
 *    - Přeruší cyklus (for, while, do-while)
 *    - Přeruší switch
 *    - Ve vnořeném cyklu přeruší jen vnitřní
 * 
 * 7. CONTINUE
 *    - Skočí na další iteraci
 *    - Přeskočí zbytek těla cyklu
 *    - Vhodné pro filtrování
 * 
 * 8. GOTO
 *    - Skok na etiketu
 *    - Používej jen pro cleanup (chyby, úklid) nebo escape vnořených smyček
 *    - "spaghetti code" - vyhni se!
 * 
 * ═══════════════════════════════════════════════════════════════════════════
 * TYPICKÉ CHYBY
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * ✗ CHYBA: switch bez break (padá dál)
 *   switch (x) {
 *     case 1: printf("1"); // Padá dál!
 *     case 2: printf("2"); break;
 *   }
 *
 * ✓ SPRÁVNĚ:
 *   switch (x) {
 *     case 1: printf("1"); break;
 *     case 2: printf("2"); break;
 *   }
 * 
 * ✗ CHYBA: Přetečení v for (int i; i<=n)
 *   int n = 5;
 *   for (int i = n; i <= n+5; i++)  // i > INT_MAX
 * 
 * ✓ SPRÁVNĚ:
 *   for (int i = n; i < n+5; i++)  // nebo: i <= n+4
 * 
 * ✗ CHYBA: Nekonečný cyklus bez break
 *   for (int i=0; ; i++) printf("%d", i);  // Zacyklit se!
 * 
 * ✗ CHYBA: Scanf v while bez check
 *   while (scanf("%d", &x))  // Špatně - vrací 1 nebo EOF
 * 
 * ✓ SPRÁVNĚ:
 *   while (scanf("%d", &x) == 1)  // Vždy CHECK návratovou hodnotu
 * 
 * ═══════════════════════════════════════════════════════════════════════════
 * VÝKONNOSTNÍ TIPY
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * - For je nejrychlejší (pevný počet iterací)
 * - While je o něco pomalejší (podmínka se kontroluje pokaždé)
 * - Do-while je podobně rychlý jako while
 * - Vyhni se nekonečným cyklům
 * - Switch je rychlejší než if-else if-else... (lookup table)
 * - Break/continue jsou "levné" operace
 * 
 * ═══════════════════════════════════════════════════════════════════════════
 * TESTOVACÍ ČEKLIST
 * ═══════════════════════════════════════════════════════════════════════════
 * 
 * ☐ If-else s vnořením - OK?
 * ☐ Switch s break - Všude break?
 * ☐ For s polem - Index v pořádku (0..n-1)?
 * ☐ While podmínka - Končí někdy?
 * ☐ Do-while - Tělo se spustí?
 * ☐ Break/Continue - Přerušuje správný cyklus?
 * ☐ Scanf v cyklu - Kontroluješ return?
 * ☐ Vnořené cykly - Správně se zavírají?
 */
