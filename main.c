#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// definice boolean
#define TRUE 1
#define FALSE 0

// pro kompilaci:
// gcc -pedantic -Wall -Werror -std=c17 -O2 main.c -o main
// clang -pedantic -Wall -Werror -std=c99 -O2 main.c -o main

// pro spusteni:
// ./main (Linux/Mac)
// .\main.exe (Windows)

// pro nacteni vstupu ze souboru:
// ./main < input.txt (Linux/Mac)
// .\main.exe < input.txt (Windows)

// pro presmerovani vystupu do souboru:
// ./main > output.txt (Linux/Mac)
// .\main.exe > output.txt (Windows)

// pro oboje soucasne:
// ./main < input.txt > output.txt (Linux/Mac)
// .\main.exe < input.txt > output.txt (Windows)

int main(int argc, char *argv[])
{
    printf("Hello world!\n");

    return 0;
}
