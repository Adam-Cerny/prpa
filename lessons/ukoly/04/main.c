#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(void)
{
    // nacteni vstupu
    char vstup[100];
    scanf("%s", vstup);

    // pomocne promenne
    char vystup[100] = "";
    char prev = vstup[0];
    int score = 0;
    int platny = TRUE;

    // hlavni cyklus, iterace retezcem po znaku
    for(int i = 0; i < (strlen(vstup) + 1); i++)
    {
        // momentalni znak
        char curr = vstup[i];

        // kdyz se momentalni znak rovna predchozimu pricteme skore
        if(curr == prev)
        {
            score++;
        }
        // pokud se nerovnaji
        else
        {
            // a skore se rovna 1
            if(score == 1)
            {
                // pridej do vystupu prvek
                char tmp[2];
                tmp[0] = prev;
                tmp[1] = '\0';
                strcat(vystup, tmp);
            }
            // skore se rovna 2
            else if(score == 2)
            {
                // pridej ho tam dvakrat
                for(int j = 0; j < 2; j++)
                {
                    char tmp[2];
                    tmp[0] = prev;
                    tmp[1] = '\0';
                    strcat(vystup, tmp);                  
                }
            }
            // skore je vetsi nez 2
            else 
            {
                // pridej prvek nejdrive
                char tmp[2];
                tmp[0] = prev;
                tmp[1] = '\0';
                strcat(vystup, tmp);

                // pote prevod cisla na string a nasledne pridani 
                char buffer[10];
                sprintf(buffer, "%i", score);
                strcat(vystup, buffer);
            }
            
            // reset skore a presun prvku
            score = 1; 
            prev = curr;
            }
        
        // kontrola zdali je prvek v intervalu
        if(curr != '\0' && ((curr < 'A') || (curr > 'Z')))
        {
            printf("%s", vystup);
            fprintf(stderr, "Error: Neplatny symbol!\n");
            platny = FALSE;
            return 100;
        }
    }

    // vypis vystupiho retezce
    printf("%s\n", vystup);

    // pokud kod neskoncil na nevalidnim intervalu, dopocita promenne a napise ja ns stderr 
    if(platny == TRUE)
    {
        int pocet_symbolu = strlen(vstup);
        int pocet_zakodovanych = strlen(vystup);
        float kompresni_pomer = (float)pocet_zakodovanych / (float)pocet_symbolu;
        fprintf(stderr, "Pocet vstupnich symbolu: %i\n", pocet_symbolu);
        fprintf(stderr, "Pocet zakodovanych symbolu: %i\n", pocet_zakodovanych);
        fprintf(stderr, "Kompresni pomer: %.2f\n", kompresni_pomer);
    }

    return 0;
}
