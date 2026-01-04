#include <stdio.h>
#include <stdlib.h> // Pro dynamickou alokaci, ale zatím ji použijeme pro jednoduchou inicializaci

// Makro pro zjištění velikosti pole (POZOR: funguje jen pro lokální, ne pro pole v parametru funkce!)
#define VELIKOST_POLE(arr) (sizeof(arr) / sizeof(arr[0]))

int main() {
    printf("=== ZAKLADY POLE V C ===\n\n");

    // --- 1. Deklarace a Inicializace ---

    // Deklarace pole o velikosti 5, prvky nejsou inicializovány (obsahují "smeti")
    int pole_neiniciovane[5]; 
    printf("1. Neinicializovane pole: %d (nahodna hodnota)\n", pole_neiniciovane[0]);

    // Inicializace pri deklaraci (kompilator spocita velikost 4)
    int pole_inicializovane[] = {10, 20, 30, 40};
    printf("2. Inicializovane pole: {10, 20, 30, 40}\n");


    // --- 2. Inicializace VSECH prvků na 0 (Klíčová technika!) ---

    // Kdyz inicializujete jen PRVNI prvek, zbytek je automaticky 0.
    int pole_nuly[6] = {0}; 
    // Nebo: int pole_nuly[6] = {}; (moderni C standard)
    printf("\n3. Pole inicializovane na 0 (velikost 6):\n");
    for (int i = 0; i < 6; i++) {
        printf("%d ", pole_nuly[i]);
    }
    printf("\n");

    // --- 3. Pristup a Modifikace ---

    printf("\n4. Pristup a modifikace:\n");
    int data[] = {5, 15, 25};
    int n = VELIKOST_POLE(data); // Vypocet velikosti pole

    printf("Puvodni druhy prvek (index 1): %d\n", data[1]); // Vystup: 15

    data[1] = 100; // Modifikace hodnoty na indexu 1
    printf("Novy druhy prvek (index 1): %d\n", data[1]); // Vystup: 100
    
    // Upozorneni: Pristup mimo rozsah (napr. data[n] nebo data[-1]) zpusobi nedefinovane chovani!


    // --- 4. Prochazeni Pole (Iterace) ---
    
    printf("\n5. Prochazeni pole (soucet):\n");
    int soucet = 0;
    for (int i = 0; i < n; i++) {
        soucet += data[i]; // Ekvivalent k soucet = soucet + data[i];
    }
    printf("Soucet prvku: %d\n", soucet); // Vystup: 5 + 100 + 25 = 130


    // --- 5. Dvourozmerne Pole (Matice) ---

    // Matice 2x3 (2 radky, 3 sloupce)
    int matice[2][3] = {
        {1, 2, 3}, // Radek 0
        {4, 5, 6}  // Radek 1
    };
    int RADKY = 2;
    int SLOUPCE = 3;

    printf("\n6. Dvourozmerne pole (matice):\n");

    // Prochazeni matice vnořenými cykly
    for (int r = 0; r < RADKY; r++) { // Radek (r)
        for (int s = 0; s < SLOUPCE; s++) { // Sloupec (s)
            // Tiskne prvek matice
            printf("%d ", matice[r][s]);
        }
        printf("\n"); // Po dokonceni radku odradkujeme
    }
    
    // Pristup k prvku (prvek na 2. radku, 3. sloupci)
    printf("Prvek na [1][2] je: %d\n", matice[1][2]); // Vystup: 6

    return 0;
}