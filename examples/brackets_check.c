// Zadání:
// Naprogramujte aplikaci, která kontroluje, zda jsou všechny závorky v textu správně párované a v pořádku.

// Vstup:

// Text na vstupu (libovolně dlouhý, až do EOF)
#include <stdio.h>
#include <stdlib.h>

/*
 * ÚLOHA: Kontrola závorek pomocí LIFO
 * Načti řetězec ze stdin (do EOF). Ověř, že (), [], {} jsou vyvážené a správně zanořené.
 * Využij zásobník (dynamický přes realloc). Vypiš "OK" nebo "NOK".
 */

int main(void)
{
    int ch;
    char *stack = NULL;
    int top = 0;
    int cap = 0;
    int valid = 1;

    while ((ch = getchar()) != EOF && valid)
    {
        if (ch == '(' || ch == '[' || ch == '{')
        {
            if (top + 1 > cap)
            {
                cap = (cap == 0) ? 16 : cap * 2;
                char *tmp = realloc(stack, cap);
                if (!tmp) { free(stack); return 100; }
                stack = tmp;
            }
            stack[top++] = (char)ch;
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (top == 0) { valid = 0; break; }
            char open = stack[--top];
            if ((open == '(' && ch != ')') ||
                (open == '[' && ch != ']') ||
                (open == '{' && ch != '}'))
            {
                valid = 0;
                break;
            }
        }
    }

    if (valid && top == 0)
        printf("OK\n");
    else
        printf("NOK\n");

    free(stack);
    return 0;
}
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