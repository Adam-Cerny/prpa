#include <stdio.h>
#include <stdlib.h> 

// definice boolean
#define TRUE 1
#define FALSE 0

// definice error kodu a zpravy
#define ERROR 100
#define ERROR_MESSAGE "Error: Chybny vstup!\n"

// definice maximalni velikosti LIFO
#define VELIKOST 100

// struktura pro matici
typedef struct {
    int n;
    int m;
    int **data;
} Matice;

// pomocna funkce pro vypis chybove hlasky a ukonceni programu
int error(char *message, int code)
{
    fprintf(stderr, "%s", message);
    exit(code);
}

// funkce pro validaci rozmeru matic
int validaceObecna(int n, int m)
{
    if (n <= 0 || m <= 0)
    {
        error(ERROR_MESSAGE, ERROR);
    }
    return 0;
}

// funkce pro validaci rozmeru matic pro scitani a odcitani
int validaceA(int n, int m, int n2, int m2)
{
    if (n != n2 || m != m2)
    {
        error(ERROR_MESSAGE, ERROR);
    }
    return TRUE;
}

// funkce pro validaci rozmeru matic pro nasobeni
int validaceB(int n, int m, int n2, int m2)
{
    if (m != n2)
    {
        error(ERROR_MESSAGE, ERROR);
    }
    return TRUE;
}

// funkce pro alokaci matice
Matice *alokovaniMatice(int n, int m)
{
    // alokace pameti pro strukturu Matice
    Matice *matice = malloc(sizeof(Matice));
    if (matice == NULL)
        error(ERROR_MESSAGE, ERROR);

    // nastaveni rozmeru matice
    matice->n = n;
    matice->m = m;

    // alokace pameti pro data matice
    matice->data = malloc(n * sizeof(int *));
    if (matice->data == NULL)
    {
        free(matice);
        error(ERROR_MESSAGE, ERROR);
    }

    // alokace pameti pro jednotlive radky matice
    for (int i = 0; i < n; i++)
    {
        matice->data[i] = malloc(m * sizeof(int));
        if (matice->data[i] == NULL)
        {
            error(ERROR_MESSAGE, ERROR);
        }
    }

    return matice;
}

// funkce pro uvolneni matice
void uvolneniMatice(Matice *matice)
{
    // uvolneni pameti pro jednotlive radky matice
    for (int i = 0; i < matice->n; i++)
    {
        free(matice->data[i]);
    }
    // uvolneni pameti pro data matice a strukturu Matice
    free(matice->data);
    free(matice);
}

// funkce pro nacteni matice
void nacteniMatice(Matice *matice)
{
    for (int i = 0; i < matice->n; i++)
    {
        for (int j = 0; j < matice->m; j++)
        {
            if (scanf("%d", &matice->data[i][j]) != 1)
            {
                uvolneniMatice(matice);
                error(ERROR_MESSAGE, ERROR);
            }
        }
    }
}

// funkce pro vypis matice
void vypisMatice(Matice *matice)
{
    printf("%i %i\n", matice->n, matice->m);

    for (int i = 0; i < matice->n; i++)
    {
        for (int j = 0; j < matice->m; j++)
        {
            printf("%d", matice->data[i][j]);

            if (j < matice->m - 1)
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}

// funkce pro scitani matic
Matice *soucetMatic(Matice *prvniMatice, Matice *druhaMatice)
{
    Matice *vyslednaMatice = alokovaniMatice(prvniMatice->n, prvniMatice->m);

    for (int i = 0; i < prvniMatice->n; i++)
    {
        for (int j = 0; j < prvniMatice->m; j++)
        {
            vyslednaMatice->data[i][j] = prvniMatice->data[i][j] + druhaMatice->data[i][j];
        }
    }
    return vyslednaMatice;
}


// funkce pro odcitani matic
Matice *rozdilMatic(Matice *prvniMatice, Matice *druhaMatice)
{
    Matice *vyslednaMatice = alokovaniMatice(prvniMatice->n, prvniMatice->m);

    for (int i = 0; i < prvniMatice->n; i++)
    {
        for (int j = 0; j < prvniMatice->m; j++)
        {
            vyslednaMatice->data[i][j] = prvniMatice->data[i][j] - druhaMatice->data[i][j];
        }
    }
    return vyslednaMatice;
}

// funkce pro nasobeni matic
Matice *soucinMatic(Matice *prvniMatice, Matice *druhaMatice)
{
    Matice *vyslednaMatice = alokovaniMatice(prvniMatice->n, druhaMatice->m);

    for (int i = 0; i < prvniMatice->n; i++)
    {
        for (int j = 0; j < druhaMatice->m; j++)
        {
            vyslednaMatice->data[i][j] = 0;
            for (int k = 0; k < prvniMatice->m; k++)
            {
                vyslednaMatice->data[i][j] += prvniMatice->data[i][k] * druhaMatice->data[k][j];
            }
        }
    }
    return vyslednaMatice;
}

// LIFO struktury pro matice a operatory
Matice *maticeLIFO[VELIKOST];
int maticeTop = -1;
char operatorLIFO[VELIKOST];
int operatorTop = -1;

// funkce pro praci s LIFO strukturami
void pushMatice(Matice *matice)
{
    if (maticeTop < VELIKOST - 1)
    {
        maticeLIFO[++maticeTop] = matice;
    }
    else
    {
        error(ERROR_MESSAGE, ERROR);
    }
}

Matice *popMatice()
{
    if (maticeTop >= 0)
    {
        return maticeLIFO[maticeTop--];
    }
    else
    {
        error(ERROR_MESSAGE, ERROR);
        return NULL;
    }
}

void pushOperator(char operator)
{
    if (operatorTop < VELIKOST - 1)
    {
        operatorLIFO[++operatorTop] = operator;
    }
    else
    {
        error(ERROR_MESSAGE, ERROR);
    }
}

char popOperator()
{
    if (operatorTop >= 0)
    {
        return operatorLIFO[operatorTop--];
    }
    else
    {
        error(ERROR_MESSAGE, ERROR);
        return '\0';
    }
}

char peekOperator()
{
    if (operatorTop >= 0)
    {
        return operatorLIFO[operatorTop];
    }
    else
    {
        return '\0';
    }
}

// funkce pro urceni priority operatoru
int prioritaOperatoru(char operator)
{
    if (operator == '*')
    {
        return 2;
    }
    else if (operator == '+' || operator == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// funkce pro vyhodnoceni operace
Matice *vyhodnoceni()
{
    char operator = popOperator();
    Matice *druhaMatice = popMatice();
    Matice *prvniMatice = popMatice();

    Matice *vyslednaMatice = NULL;

    if (operator == '+')
    {
        validaceA(prvniMatice->n, prvniMatice->m, druhaMatice->n, druhaMatice->m);
        vyslednaMatice = soucetMatic(prvniMatice, druhaMatice);
    }
    else if (operator == '-')
    {
        validaceA(prvniMatice->n, prvniMatice->m, druhaMatice->n, druhaMatice->m);
        vyslednaMatice = rozdilMatic(prvniMatice, druhaMatice);
    }
    else if (operator == '*')
    {
        validaceB(prvniMatice->n, prvniMatice->m, druhaMatice->n, druhaMatice->m);
        vyslednaMatice = soucinMatic(prvniMatice, druhaMatice);
    }

    uvolneniMatice(prvniMatice);
    uvolneniMatice(druhaMatice);

    return vyslednaMatice;
}

int main(void)
{   
    int n, m;

    while (TRUE)
    {
        if (scanf("%d %d", &n, &m) != 2)
        {
            break;
        }

        validaceObecna(n, m);

        Matice *prvniMatice = alokovaniMatice(n, m);
        nacteniMatice(prvniMatice);

        pushMatice(prvniMatice);

        char operator;

        if (scanf(" %c", &operator) != 1)
        {
            break;
        }

        int priorita = prioritaOperatoru(operator);

        if (priorita == 0)
        {
            error(ERROR_MESSAGE, ERROR);
        }

        while (operatorTop != -1 && prioritaOperatoru(peekOperator()) >= priorita)
        {
            Matice *Result = vyhodnoceni ();
            pushMatice(Result);
        }

        pushOperator(operator);
    }

    while (operatorTop != -1)
    {
        Matice *vyslednaMatice = vyhodnoceni ();
        pushMatice(vyslednaMatice);
    }

    if (maticeTop != 0)
    {
        error(ERROR_MESSAGE, ERROR);
    }

    Matice *finalniMatice = popMatice();
    vypisMatice(finalniMatice);
    uvolneniMatice(finalniMatice);

    return 0;
}
