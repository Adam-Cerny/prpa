#include <stdio.h>
#include <stdlib.h>

#define ERR_CODE 100

// Pomocná funkce pro ověření, zda závorky tvoří pár
int tvori_par(char otevrena, char zavrena)
{
    if (otevrena == '(' && zavrena == ')')
        return 1;
    if (otevrena == '[' && zavrena == ']')
        return 1;
    if (otevrena == '{' && zavrena == '}')
        return 1;
    return 0;
}

int main(void)
{
    // Dynamický zásobník (stack)
    char *stack = NULL;
    size_t stack_len = 0;
    size_t stack_cap = 0;

    int ch;
    int pozice = 0;

    while ((ch = getchar()) != EOF)
    {
        pozice++; // Sledujeme pozici každého znaku od začátku

        // 1. Pokud je to otevírací závorka -> PUSH na zásobník
        if (ch == '(' || ch == '[' || ch == '{')
        {
            if (stack_len + 1 > stack_cap)
            {
                stack_cap = (stack_cap == 0) ? 32 : stack_cap * 2;
                char *tmp = realloc(stack, stack_cap);
                if (!tmp)
                {
                    fprintf(stderr, "Chyba pameti\n");
                    free(stack);
                    return ERR_CODE;
                }
                stack = tmp;
            }
            stack[stack_len++] = (char)ch;
        }

        // 2. Pokud je to zavírací závorka -> Kontrola a POP
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            // Chyba: Zavírací závorka, ale zásobník je prázdný
            if (stack_len == 0)
            {
                fprintf(stderr, "Chyba: necekana zavorka '%c' na pozici %d\n", ch, pozice);
                free(stack);
                return ERR_CODE;
            }

            char vrchol = stack[stack_len - 1];
            if (tvori_par(vrchol, (char)ch))
            {
                stack_len--; // V pořádku, odebereme otevírací závorku ze zásobníku
            }
            else
            {
                // Chyba: Nesouhlasí typ závorky (např. (] )
                fprintf(stderr, "Chyba: nesouhlasi zavorka '%c' na pozici %d\n", ch, pozice);
                free(stack);
                return ERR_CODE;
            }
        }

        // Ostatní znaky ignorujeme
    }

    // 3. Kontrola po dočtení celého souboru
    if (stack_len > 0)
    {
        // Chyba: Některé závorky zůstaly otevřené
        fprintf(stderr, "Chyba: neukoncena zavorka '%c' na konci souboru\n", stack[stack_len - 1]);
        free(stack);
        return ERR_CODE;
    }

    // Vše v pořádku
    printf("OK\n");
    free(stack);
    return 0;
}