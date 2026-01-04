// definice error kodu a zpravy
#define ERROR 100
#define ERROR_MESSAGE "Error: Chybny vstup!\n"

// pomocna funkce pro vypis chybove hlasky a ukonceni programu
int error(char *message, int code)
{
    fprintf(stderr, "%s", message);
    exit(code);
}

// priklad pouziti pomocne funkce error
error(ERROR_MESSAGE, ERROR);
