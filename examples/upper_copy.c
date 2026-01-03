/*
 * ÚLOHA: Uppercase kopie stdin -> stdout
 * Načti text do EOF, každý znak převed' na upper (toupper) a vypiš.
 */

#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int ch;
    while ((ch = getchar()) != EOF)
    {
        putchar(toupper(ch));
    }
    return 0;
}
