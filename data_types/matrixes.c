// ============================================
// MATICE (2D POLE) - Úplný průvodce
// ============================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ============================================
// 1. STATICKÉ 2D POLE - Pevná velikost
// ============================================

/*
STATICKÉ 2D POLE:
  int matice[3][4];
  - Velikost známa při kompilaci
  - Byt na STACKU
  - Paměť lineární - matice[i][j] = matice[i*m + j]
  - Musí se znát počet sloupců!
*/

// Příklad 1: Základní statické 2D pole
void priklad_1_staticke_2d()
{
    // 2D pole 3x4 (3 řádky, 4 sloupce)
    int matice[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    // Přístup: matice[řádek][sloupec]
    printf("Prvek [0][0]: %d\n", matice[0][0]);  // 1
    printf("Prvek [1][2]: %d\n", matice[1][2]);  // 7
    printf("Prvek [2][3]: %d\n", matice[2][3]);  // 12
}

// Příklad 2: Inicializace a výpis
void priklad_2_inicializace()
{
    int m = 3, n = 3;
    int matice[3][3];
    
    // Naplnění matice
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matice[i][j] = i * n + j + 1;
        }
    }
    
    // Výpis matice
    printf("Matice:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matice[i][j]);
        }
        printf("\n");
    }
}

// Výstup:
//   1   2   3
//   4   5   6
//   7   8   9

// Příklad 3: Práce se statickým 2D polem
void priklad_3_operace()
{
    // Násobení všech prvků 2
    int matice[2][2] = {{1, 2}, {3, 4}};
    
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            matice[i][j] *= 2;
        }
    }
    
    // Výpis
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", matice[i][j]);
        }
        printf("\n");
    }
}

// ============================================
// 2. DYNAMICKÉ 2D POLE - Běhová velikost
// ============================================

/*
DYNAMICKÉ 2D POLE - Metoda 1: Pole ukazatelů
  int **matice = malloc(m * sizeof(int *));
  for (i < m) matice[i] = malloc(n * sizeof(int));

- Flexibilní řádky
- Pomalejší přístup
- Více paměti (fragmentace)
*/

// Příklad 4: Dynamické 2D pole - metoda 1
void priklad_4_dynamicke_v1()
{
    int m = 3, n = 4;
    
    // Alokuj pole ukazatelů na řádky
    int **matice = (int **)malloc(m * sizeof(int *));
    
    if (matice == NULL)
    {
        fprintf(stderr, "Chyba: malloc!\n");
        return;
    }
    
    // Alokuj každý řádek
    for (int i = 0; i < m; i++)
    {
        matice[i] = (int *)malloc(n * sizeof(int));
        
        if (matice[i] == NULL)
        {
            fprintf(stderr, "Chyba: malloc!\n");
            // Uvolni už alokované řádky
            for (int j = 0; j < i; j++)
                free(matice[j]);
            free(matice);
            return;
        }
    }
    
    // Naplnění
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matice[i][j] = i * n + j + 1;
        }
    }
    
    // Výpis
    printf("Dynamická matice:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matice[i][j]);
        }
        printf("\n");
    }
    
    // Uvolnění - nejdřív řádky, pak pole ukazatelů
    for (int i = 0; i < m; i++)
    {
        free(matice[i]);
    }
    free(matice);
    matice = NULL;
}

/*
DYNAMICKÉ 2D POLE - Metoda 2: Lineární pole
  int *matice = malloc(m * n * sizeof(int));
  přístup: matice[i*n + j]

- Jedna alokace
- Rychlejší přístup (cache)
- Méně paměti
- Musíš počítat index ručně
*/

// Příklad 5: Dynamické 2D pole - metoda 2 (lineární)
void priklad_5_dynamicke_v2()
{
    int m = 3, n = 4;
    
    // Alokuj jako lineární pole
    int *matice = (int *)malloc(m * n * sizeof(int));
    
    if (matice == NULL)
    {
        fprintf(stderr, "Chyba: malloc!\n");
        return;
    }
    
    // Naplnění
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Indexování: [i][j] -> [i*n + j]
            matice[i * n + j] = i * n + j + 1;
        }
    }
    
    // Výpis
    printf("Lineární matice:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matice[i * n + j]);  // Ručnī index
        }
        printf("\n");
    }
    
    free(matice);
    matice = NULL;
}

/*
DYNAMICKÉ 2D POLE - Metoda 3: Pole ukazatelů s jedním malloc
  int *data = malloc(m * n * sizeof(int));
  int **matice = malloc(m * sizeof(int *));
  for (i < m) matice[i] = data + i*n;

- Jedno lineární pole
- Ale 2D indexování
- Nejrychlejší + nejflexibilnější
*/

// Příklad 6: Dynamické 2D pole - metoda 3 (nejlepší)
void priklad_6_dynamicke_v3()
{
    int m = 3, n = 4;
    
    // Alokuj lineární data
    int *data = (int *)malloc(m * n * sizeof(int));
    
    // Alokuj pole ukazatelů
    int **matice = (int **)malloc(m * sizeof(int *));
    
    if (data == NULL || matice == NULL)
    {
        fprintf(stderr, "Chyba: malloc!\n");
        free(data);
        free(matice);
        return;
    }
    
    // Nastav ukazatele na každý řádek
    for (int i = 0; i < m; i++)
    {
        matice[i] = data + i * n;  // Ukazatel na i-tý řádek
    }
    
    // Naplnění - nyní můžeš psát matice[i][j]!
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matice[i][j] = i * n + j + 1;  // 2D indexování!
        }
    }
    
    // Výpis
    printf("Hybridní matice:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matice[i][j]);
        }
        printf("\n");
    }
    
    // Uvolnění - jednoduše
    free(data);
    free(matice);
}

// ============================================
// 3. INDEXOVÁNÍ - Jak se počítá pozice
// ============================================

/*
PAMĚŤOVÝ LAYOUT matice 3x4:

Matice v paměti (lineárně):
┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
│ 1│ 2│ 3│ 4│ 5│ 6│ 7│ 8│ 9│10│11│12│
└──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘
 0  1  2  3  4  5  6  7  8  9 10 11

Matice logicky (2D):
┌──┬──┬──┬──┐
│ 1│ 2│ 3│ 4│  řádek 0
├──┼──┼──┼──┤
│ 5│ 6│ 7│ 8│  řádek 1
├──┼──┼──┼──┤
│ 9│10│11│12│  řádek 2
└──┴──┴──┴──┘
 0  1  2  3
 sloupce

INDEX: matice[i][j] = matice[i*sloupce + j]
*/

// Příklad 7: Výpočet indexu
void priklad_7_index()
{
    int m = 3, n = 4;  // 3 řádky, 4 sloupce
    int matice[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    printf("Index [1][2] (řádek 1, sloupec 2):\n");
    printf("  Lineární index: 1*4 + 2 = %d\n", 1*4 + 2);  // 6
    printf("  Hodnota: %d\n", matice[1][2]);  // 7 (prvek na pozici 6)
    
    printf("\nIndex [2][3] (řádek 2, sloupec 3):\n");
    printf("  Lineární index: 2*4 + 3 = %d\n", 2*4 + 3);  // 11
    printf("  Hodnota: %d\n", matice[2][3]);  // 12 (prvek na pozici 11)
}

// ============================================
// 4. PŘEDÁVÁNÍ MATICE DO FUNKCE
// ============================================

// Příklad 8: Statické 2D pole - předání do funkce
void tiskniMatici(int matice[3][4], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matice[i][j]);
        }
        printf("\n");
    }
}

void priklad_8_predani_staticke()
{
    int m[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };
    
    tiskniMatici(m, 3, 4);
}

// Příklad 9: Dynamické 2D pole - předání do funkce
void tiskniDynamickou(int **matice, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d ", matice[i][j]);
        }
        printf("\n");
    }
}

void priklad_9_predani_dynamicke()
{
    int m = 2, n = 3;
    
    // Alokuj
    int **matice = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        matice[i] = (int *)malloc(n * sizeof(int));
    
    // Naplnění
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matice[i][j] = i * n + j + 1;
    
    // Předej do funkce
    tiskniDynamickou(matice, m, n);
    
    // Uvolnění
    for (int i = 0; i < m; i++)
        free(matice[i]);
    free(matice);
}

// ============================================
// 5. OPERACE S MATICEMI - Sčítání, odčítání
// ============================================

// Příklad 10: Sčítání matic
void sectiMatice(int **a, int **b, int **c, int m, int n)
{
    // c = a + b
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void priklad_10_scitani()
{
    int m = 2, n = 2;
    
    // Alokuj tři matice 2x2
    int **a = (int **)malloc(m * sizeof(int *));
    int **b = (int **)malloc(m * sizeof(int *));
    int **c = (int **)malloc(m * sizeof(int *));
    
    for (int i = 0; i < m; i++)
    {
        a[i] = (int *)malloc(n * sizeof(int));
        b[i] = (int *)malloc(n * sizeof(int));
        c[i] = (int *)malloc(n * sizeof(int));
    }
    
    // Naplnění
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;
    
    b[0][0] = 5; b[0][1] = 6;
    b[1][0] = 7; b[1][1] = 8;
    
    // Sčítání
    sectiMatice(a, b, c, m, n);
    
    // Výpis
    printf("A + B = C:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%3d ", c[i][j]);
        printf("\n");
    }
    
    // Uvolnění
    for (int i = 0; i < m; i++)
    {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
}

// Příklad 11: Násobení matic
void nasobMatice(int **a, int **b, int **c, int m, int k, int n)
{
    // c = a (m×k) × b (k×n) = c (m×n)
    // c[i][j] = suma(a[i][x] * b[x][j]) pro x=0 do k-1
    
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            c[i][j] = 0;
            for (int x = 0; x < k; x++)
            {
                c[i][j] += a[i][x] * b[x][j];
            }
        }
    }
}

void priklad_11_nasobeni()
{
    int m = 2, k = 3, n = 2;
    
    // A: 2×3, B: 3×2, C: 2×2
    int **a = (int **)malloc(m * sizeof(int *));
    int **b = (int **)malloc(k * sizeof(int *));
    int **c = (int **)malloc(m * sizeof(int *));
    
    for (int i = 0; i < m; i++)
    {
        a[i] = (int *)malloc(k * sizeof(int));
        c[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < k; i++)
        b[i] = (int *)malloc(n * sizeof(int));
    
    // Naplnění
    a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
    a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;
    
    b[0][0] = 7; b[0][1] = 8;
    b[1][0] = 9; b[1][1] = 10;
    b[2][0] = 11; b[2][1] = 12;
    
    // Násobení
    nasobMatice(a, b, c, m, k, n);
    
    // Výpis
    printf("A × B = C:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%3d ", c[i][j]);
        printf("\n");
    }
    
    // Uvolnění
    for (int i = 0; i < m; i++)
    {
        free(a[i]);
        free(c[i]);
    }
    for (int i = 0; i < k; i++)
        free(b[i]);
    free(a);
    free(b);
    free(c);
}

// ============================================
// 6. SPECIÁLNÍ MATICE
// ============================================

// Příklad 12: Jednotková matice (identity)
void vytvorJednotkouMatici(int **m, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m[i][j] = (i == j) ? 1 : 0;
        }
    }
}

void priklad_12_jednotkova()
{
    int n = 3;
    int **m = (int **)malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++)
        m[i] = (int *)malloc(n * sizeof(int));
    
    vytvorJednotkouMatici(m, n);
    
    printf("Jednotková matice 3×3:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
    
    // Uvolnění
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

// Příklad 13: Nulová matice
void vytvorNulovouMatici(int **m, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            m[i][j] = 0;
}

// Příklad 14: Diagonální matice
void vytvorDiagonalni(int **m, int n, int *diagonal)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            m[i][j] = (i == j) ? diagonal[i] : 0;
        }
    }
}

// ============================================
// 7. PŘÍKLAD Z ÚKOLU 07 - Maticové operace
// ============================================

// Struktura pro matici (z vašeho úkolu 07)
typedef struct {
    int n;      // počet řádků
    int m;      // počet sloupců
    int **data; // dynamická 2D pole
} Matice;

// Příklad 15: Alokace matice (z ukolu 07)
Matice* alokovaniMatice(int n, int m)
{
    Matice *matice = (Matice *)malloc(sizeof(Matice));
    
    if (matice == NULL)
        return NULL;
    
    matice->n = n;
    matice->m = m;
    
    // Alokuj řádky
    matice->data = (int **)malloc(n * sizeof(int *));
    
    if (matice->data == NULL)
    {
        free(matice);
        return NULL;
    }
    
    // Alokuj sloupce
    for (int i = 0; i < n; i++)
    {
        matice->data[i] = (int *)malloc(m * sizeof(int));
        
        if (matice->data[i] == NULL)
        {
            // Uvolni již alokované řádky
            for (int j = 0; j < i; j++)
                free(matice->data[j]);
            free(matice->data);
            free(matice);
            return NULL;
        }
    }
    
    return matice;
}

// Uvolnění matice
void uvolneniMatice(Matice *matice)
{
    if (matice != NULL)
    {
        for (int i = 0; i < matice->n; i++)
        {
            free(matice->data[i]);
        }
        free(matice->data);
        free(matice);
    }
}

// Výpis matice
void tiskniMaticu(Matice *m)
{
    printf("Matice %dx%d:\n", m->n, m->m);
    for (int i = 0; i < m->n; i++)
    {
        for (int j = 0; j < m->m; j++)
        {
            printf("%3d ", m->data[i][j]);
        }
        printf("\n");
    }
}

void priklad_15_ukol07()
{
    // Vytvoř matici 2x3
    Matice *m = alokovaniMatice(2, 3);
    
    if (m == NULL)
    {
        fprintf(stderr, "Chyba!\n");
        return;
    }
    
    // Naplnění
    m->data[0][0] = 1; m->data[0][1] = 2; m->data[0][2] = 3;
    m->data[1][0] = 4; m->data[1][1] = 5; m->data[1][2] = 6;
    
    tiskniMaticu(m);
    
    // Uvolnění
    uvolneniMatice(m);
}

// ============================================
// SHRNUTÍ - Klíčové body
// ============================================

/*
STATICKÉ 2D POLE:
  int m[3][4];
  - Paměť: 3 * 4 * sizeof(int) bajtů
  - Indexování: m[i][j]
  - Lineárně: m[0][0], m[0][1], ..., m[0][3], m[1][0], ...
  - Lineární index: i*sloupce + j

DYNAMICKÉ 2D POLE - Metoda 1:
  int **m = malloc(rows * sizeof(int *));
  for (i=0; i<rows; i++) m[i] = malloc(cols * sizeof(int));
  - Indexování: m[i][j]
  - Různé délky řádků
  - Fragmentace paměti

DYNAMICKÉ 2D POLE - Metoda 2:
  int *m = malloc(rows * cols * sizeof(int));
  - Indexování: m[i*cols + j]
  - Lineární v paměti
  - Rychlejší

DYNAMICKÉ 2D POLE - Metoda 3:
  int *data = malloc(rows * cols * sizeof(int));
  int **m = malloc(rows * sizeof(int *));
  for (i<rows) m[i] = data + i*cols;
  - Indexování: m[i][j]
  - Beste of both - 2D indexování + lineární paměť
  - DOPORUČUJE SE!

OPERACE:
  Sčítání: c[i][j] = a[i][j] + b[i][j]
  Násobení: c[i][j] = suma(a[i][k] * b[k][j])
  Transponování: t[j][i] = m[i][j]

STRUKTURA S MATICÍ:
  typedef struct {
      int n, m;
      int **data;
  } Matice;
*/
