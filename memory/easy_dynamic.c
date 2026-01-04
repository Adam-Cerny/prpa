#include <stdio.h>
#include <stdlib.h>

int main()
{
    // 1. PŘÍPRAVA
    int *pole = NULL;    // Zatím nemáme nic
    size_t pocet = 0;    // Obsazeno prvků
    size_t kapacita = 0; // Celková aktuální velikost
    int nactene;

    printf("Zadavej cisla (ukonci pismenem):\n");

    // 2. NAČÍTÁNÍ V CYKLU
    while (scanf("%d", &nactene) == 1)
    {

        // JE POLE PLNÉ? (Na začátku je 0/0, takže je plné vždy)
        if (pocet >= kapacita)
        {
            // Vypočítáme novou kapacitu (pokud je 0, dáme 2, jinak zdvojnásobíme)
            kapacita = (kapacita == 0) ? 2 : kapacita * 2;

            // NAFOUKNEME POLE
            int *tmp = realloc(pole, kapacita * sizeof(int));

            if (tmp == NULL)
            { // Kontrola, jestli se to povedlo
                free(pole);
                return 1;
            }
            pole = tmp;
        }

        // ULOŽÍME ČÍSLO A ZVÝŠÍME POČET
        pole[pocet] = nactene;
        pocet++;
    }

    // 3. PRÁCE S DATY
    printf("Nacetl jsi %zu cisel. Tady jsou:\n", pocet);
    for (size_t i = 0; i < pocet; i++)
    {
        printf("%d ", pole[i]);
    }
    printf("\n");

    // 4. ÚKLID (Povinný!)
    free(pole);

    return 0;
}