// validace scanf
int ret = scanf("%d", &n);
if (ret != 1)
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
}

// validace intervalu
if (n <= 0 || n > MAX_VALUE)
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
}

// validace znaku (pismeno A-Z, a-z)
if (isalpha(c) == 0)
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
}
// isdigit(c) - je číslo 0 - 9 isalnum(c) - je písmeno nebo číslo isspace(c) - je mezera, tab, newline isupper(c) - je velké písmeno islower(c) - je malé písmeno toupper(c) - převede na velké písmeno tolower(c) - převede na malé písmeno

// validace alokace pameti
int *array = malloc(n * sizeof(int));
if (array == NULL)
{
    fprintf(stderr, "Error: Nedostatek pameti!\n");
    return 100;
}

// dalsi uzitecne validace ...
// 1. Dělení nulou
if (delitel == 0)
{
    fprintf(stderr, "Error: Deleni nulou!\n");
    return 100;
}

// 2. Kontrola scanf s více hodnotami najednou
int ret = scanf("%d %d", &a, &b);
if (ret != 2) // Musí se načíst obě hodnoty!
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
}

// 3. Čtení řetězce - maximální délka
char str[50];
if (scanf("%49s", str) != 1) // 49 znaků + null terminator
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
}

// 4. Kontrola délky řetězce
if (strlen(str) == 0 || strlen(str) > MAX_LENGTH)
{
    fprintf(stderr, "Error: Chybna delka!\n");
    return 100;
}

// 5. Povinný interval mezi MIN a MAX
if (n < MIN || n > MAX)
{
    fprintf(stderr, "Error: Vstup mimo interval <%d, %d>!\n", MIN, MAX);
    return 100;
}

// 6. Pouze kladná čísla
if (n <= 0)
{
    fprintf(stderr, "Error: Vstup musi byt kladny!\n");
    return 100;
}

// 7. Čtení postupně do EOF (neznámý počet prvků)
int x;
while (scanf("%d", &x) == 1)
{
    // zpracuj x
}

// 8. Kontrola speciálních znaků (ne mezera, ne tab)
if (isspace(c) || c == '\n')
{
    fprintf(stderr, "Error: Zakázaný znak!\n");
    return 100;
}

// 9. Malá a velká písmena (case-insensitive porovnání)
if (tolower(c) >= 'a' && tolower(c) <= 'z')
{
    // Je to písmeno
}

// 10. Rozsah znaků
if (c < 'A' || c > 'Z')
{
    fprintf(stderr, "Error: Mimo rozsah A-Z!\n");
    return 100;
}

// 11. Kontrola součtu či součinu před přetečením
if (n > INT_MAX / n) // Kontrola před n * n
{
    fprintf(stderr, "Error: Přetečení!\n");
    return 100;
}

// 12. Kontrola kompatibility rozměrů (matice)
if (m1_cols != m2_rows)
{
    fprintf(stderr, "Error: Nekompatibilní rozměry!\n");
    return 100;
}

// 1. Dělení nulou
if (delitel == 0)
{
    fprintf(stderr, "Error: Deleni nulou!\n");
    return 100;
}

// 2. Kontrola scanf s více hodnotami najednou
int ret = scanf("%d %d", &a, &b);
if (ret != 2) // Musí se načíst obě hodnoty!
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
}

// 3. Čtení řetězce - maximální délka
char str[50];
if (scanf("%49s", str) != 1) // 49 znaků + null terminator
{
    fprintf(stderr, "Error: Chybny vstup!\n");
    return 100;
}

// 4. Kontrola délky řetězce
if (strlen(str) == 0 || strlen(str) > MAX_LENGTH)
{
    fprintf(stderr, "Error: Chybna delka!\n");
    return 100;
}

// 5. Povinný interval mezi MIN a MAX
if (n < MIN || n > MAX)
{
    fprintf(stderr, "Error: Vstup mimo interval <%d, %d>!\n", MIN, MAX);
    return 100;
}

// 6. Pouze kladná čísla
if (n <= 0)
{
    fprintf(stderr, "Error: Vstup musi byt kladny!\n");
    return 100;
}

// 7. Čtení postupně do EOF (neznámý počet prvků)
int x;
while (scanf("%d", &x) == 1)
{
    // zpracuj x
}

// 8. Kontrola speciálních znaků (ne mezera, ne tab)
if (isspace(c) || c == '\n')
{
    fprintf(stderr, "Error: Zakázaný znak!\n");
    return 100;
}

// 9. Malá a velká písmena (case-insensitive porovnání)
if (tolower(c) >= 'a' && tolower(c) <= 'z')
{
    // Je to písmeno
}

// 10. Rozsah znaků
if (c < 'A' || c > 'Z')
{
    fprintf(stderr, "Error: Mimo rozsah A-Z!\n");
    return 100;
}

// 11. Kontrola součtu či součinu před přetečením
if (n > INT_MAX / n) // Kontrola před n * n
{
    fprintf(stderr, "Error: Přetečení!\n");
    return 100;
}

// 12. Kontrola kompatibility rozměrů (matice)
if (m1_cols != m2_rows)
{
    fprintf(stderr, "Error: Nekompatibilní rozměry!\n");
    return 100;
}