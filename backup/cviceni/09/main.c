#include <stdio.h>
#include <string.h>

int strlen_prpa(char* text)
{
    int length = 0;
    while (*text != '\0')
    {
        length++;
        text++;
    }
    return length;
}

int main(void)
{
    char text1[30] = "Everybody likes PRPA\n";
    char* text2 = "Everytom likes PRPA\n";

    // vypis textu, musi byt pointer
    printf("%s%s", text1, text2);


    printf("delka textoveho retezce je %ld\n", strlen(text2));

    printf("delka textoveho retezce je %d\n", strlen_prpa(text2));

    int diff = strcmp(text1, text2);
    diff = strncmp(text1, text2, 4);
    if (diff == 0)
    {
        printf("retezce jsou stejne\n");
    }
    else
    {
        printf("texty jsou rozdile, rozdil znaku je %d \n", diff);
    }

    return 0;
}
