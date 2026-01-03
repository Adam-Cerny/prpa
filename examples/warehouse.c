// 1. Cíl úlohy
// Napište program v jazyce C, který načte data o zboží ze souboru do dynamicky alokovaného pole, provede filtraci a seřazení dat a výsledek vypíše na obrazovku i do výstupního souboru.

// 2. Datová struktura
// Definujte strukturu Polozka, která obsahuje:

// id (celé číslo)

// nazev (řetězec, max. 50 znaků)

// mnozstvi (celé číslo)

// cena (desetinné číslo typu double)

// 3. Funkční požadavky
// Načítání (Dynamická alokace):

// Program načte data ze souboru input.txt.

// Počet položek není předem znám. Použijte dynamickou alokaci (malloc) a v případě potřeby pole zvětšujte (realloc). Začněte s počáteční kapacitou 2.

// Zpracování dat:

// Program načte od uživatele z stdin hodnotu minCena (minimální cena pro filtr).

// Seřaďte všechny načtené položky sestupně podle ceny (doporučeno použít funkci qsort ze standardní knihovny).

// Výstup:

// Vypište na obrazovku formátovanou tabulku všech položek, které mají cenu vyšší nebo rovnu minCena.

// Tyto vyfiltrované a seřazené položky zároveň uložte do souboru vystup.txt ve stejném formátu, v jakém byly na vstupu.

// Správa paměti a souborů:

// Korektně uzavřete všechny otevřené soubory.

// Uvolněte veškerou dynamicky alokovanou paměť (free).

// 4. Technické detaily a robustnost
// Ošetřete chybu otevření souboru (pokud input.txt neexistuje, vypište chybu na stderr a ukončete program s kódem 100).

// Ošetřete selhání funkcí malloc a realloc.

// Při načítání řetězců zajistěte, aby nedošlo k přetečení bufferu (ořízněte název na 50 znaků).

// Program musí být odolný proti prázdnému souboru.

// Ukázkový vstup (input.txt):
// Plaintext

// 101 Rohlik 50 2.90
// 205 Chleba 20 35.50
// 302 Maslo 10 55.00
// 410 Mleko 15 22.90

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR 100

// Struktura reprezentující uzel spojového seznamu (Bod 5 a 9 osnovy)
typedef struct Polozka
{
    int id;
    char nazev[51];
    int mnozstvi;
    double cena;
    struct Polozka *dalsi; // Ukazatel na další prvek v seznamu
} T_Polozka;

// Funkce pro přidání na konec seznamu (Bod 9)
// Používáme dvojitý ukazatel, abychom mohli změnit 'hlava' v main
void pridej_na_konec(T_Polozka **hlava, int id, char *nazev, int mnozstvi, double cena)
{
    T_Polozka *novy = (T_Polozka *)malloc(sizeof(T_Polozka));
    if (!novy)
        return;

    novy->id = id;
    strncpy(novy->nazev, nazev, 50);
    novy->mnozstvi = mnozstvi;
    novy->cena = cena;
    novy->dalsi = NULL;

    if (*hlava == NULL)
    {
        *hlava = novy; // Seznam byl prázdný, nový prvek je hlava
    }
    else
    {
        T_Polozka *aktualni = *hlava;
        while (aktualni->dalsi != NULL)
        {
            aktualni = aktualni->dalsi; // Najdeme poslední prvek
        }
        aktualni->dalsi = novy;
    }
}

// Funkce pro uvolnění veškeré paměti (Klíčové pro body za kvalitu kódu)
void uvolni_seznam(T_Polozka *hlava)
{
    while (hlava != NULL)
    {
        T_Polozka *tmp = hlava;
        hlava = hlava->dalsi;
        free(tmp);
    }
}

int main(int argc, char *argv[])
{
    // Pokud chceš program spouštět jako ./main < input.txt, čti ze stdin
    // Pokud jako ./main input.txt, čti z fopen(argv[1], "r")
    FILE *vstup = (argc > 1) ? fopen(argv[1], "r") : stdin;

    if (!vstup)
    {
        fprintf(stderr, "Chyba: Nelze otevrit vstup!\n");
        return ERROR;
    }

    T_Polozka *sklad = NULL; // Začátek spojového seznamu
    int id, mnozstvi;
    char nazev[51];
    double cena;

    // Načítání dokud fscanf vrací 4 úspěšně načtené hodnoty
    while (fscanf(vstup, "%d %50s %d %lf", &id, nazev, &mnozstvi, &cena) == 4)
    {
        pridej_na_konec(&sklad, id, nazev, mnozstvi, cena);
    }

    // Pokud jsme četli ze souboru (ne stdin), zavřeme ho
    if (vstup != stdin)
        fclose(vstup);

    // Výpis na obrazovku (Bod 3)
    printf("\n%-5s | %-15s | %-10s | %-10s\n", "ID", "Nazev", "Mnozstvi", "Cena");
    printf("----------------------------------------------------\n");

    T_Polozka *akt = sklad;
    while (akt != NULL)
    {
        printf("%-5d | %-15s | %-10d | %-10.2f\n",
               akt->id, akt->nazev, akt->mnozstvi, akt->cena);
        akt = akt->dalsi;
    }

    uvolni_seznam(sklad); // Vždy uklidit!
    return 0;
}
