/**
 * PŘÍKLAD: CSV parser s výpočty
 * 
 * Úloha: Přečíst CSV soubor (jméno, matematika, fyzika, chemie)
 * Vypočítat průměr pro každého studenta, celkový průměr, nejlepšího studenta.
 * 
 * Vstup:  CSV řádky (jméno;math;phy;chem)
 * Výstup: Tabulka s průměry, statistiky
 * 
 * Klíčové vzory:
 * - Parsování delimiteru (strtok nebo manuální)
 * - Dynamické pole struktur
 * - Validace numerických polí
 * - Práce s float při průměrování
 * - Qsort podle průměru
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 256
#define MAX_STUDENTS 100
#define INIT_CAP 10

typedef struct
{
    char name[50];
    float math, physics, chemistry;
    float average;
} Student;

// ===== SHRNUTÍ =====
// CSV parsování: strtok(line, delim) nebo manuelní s indexem
// Pozor: strtok modifikuje vstupní buffer!
// Validace: sprintf("%f", ...) povinně zkontrolovat vráceno 1
// Střelný průměr: (a + b + c) / 3.0f (pozor na integer dělení!)

// Parsování jednoho CSV řádku
int parse_csv_line(const char *line, Student *s)
{
    char temp[MAX_LINE];
    strncpy(temp, line, MAX_LINE - 1);
    temp[MAX_LINE - 1] = '\0';

    // Ponechej původní řádek neporušený
    char *saveptr;
    char *token = strtok_r(temp, ";", &saveptr);

    if (!token)
        return 0;
    strncpy(s->name, token, 49);
    s->name[49] = '\0';

    // Math
    token = strtok_r(NULL, ";", &saveptr);
    if (!token || sscanf(token, "%f", &s->math) != 1)
        return 0;

    // Physics
    token = strtok_r(NULL, ";", &saveptr);
    if (!token || sscanf(token, "%f", &s->physics) != 1)
        return 0;

    // Chemistry
    token = strtok_r(NULL, ";", &saveptr);
    if (!token || sscanf(token, "%f", &s->chemistry) != 1)
        return 0;

    // Výpočet průměru
    s->average = (s->math + s->physics + s->chemistry) / 3.0f;
    return 1;
}

// Komparátor pro qsort (sestupně podle průměru)
int cmp_avg_desc(const void *a, const void *b)
{
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;

    if (s1->average > s2->average)
        return -1;
    else if (s1->average < s2->average)
        return 1;
    else
        return strcmp(s1->name, s2->name);  // Tiebreak: abecedně
}

int main(void)
{
    Student *students = malloc(sizeof(Student) * INIT_CAP);
    if (!students)
    {
        fprintf(stderr, "Chyba: Alokace selhala\n");
        return 1;
    }

    int count = 0;
    int capacity = INIT_CAP;
    char line[MAX_LINE];

    printf("Zadej CSV radky (jmeno;math;physics;chemistry):\n");
    printf("Konec: Ctrl+D nebo prazdny radek\n\n");

    // 1. Čtení a parsování
    while (fgets(line, MAX_LINE, stdin))
    {
        // Odstranění newline
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        // Prázdný řádek = konec
        if (strlen(line) == 0)
            break;

        // Realloc když je plno
        if (count >= capacity)
        {
            capacity *= 2;
            Student *tmp = realloc(students, sizeof(Student) * capacity);
            if (!tmp)
            {
                fprintf(stderr, "Chyba: Realloc selhala\n");
                free(students);
                return 1;
            }
            students = tmp;
        }

        // Parsování
        if (!parse_csv_line(line, &students[count]))
        {
            fprintf(stderr, "Chyba: Neplatny format radku: %s\n", line);
            continue;
        }

        count++;
    }

    if (count == 0)
    {
        printf("Zadano 0 studentu\n");
        free(students);
        return 0;
    }

    // 2. Výpočty
    float total_avg = 0.0f;
    for (int i = 0; i < count; i++)
    {
        total_avg += students[i].average;
    }
    total_avg /= count;

    // 3. Třídění
    qsort(students, count, sizeof(Student), cmp_avg_desc);

    // 4. Tisk výsledků
    printf("\n=== VÝSLEDKY ===\n");
    printf("%-20s %10s %10s %10s %10s\n",
           "Jmeno", "Math", "Physics", "Chemistry", "Prumer");
    printf("%-20s %10s %10s %10s %10s\n",
           "--------------------", "----------", "----------", "----------", "----------");

    for (int i = 0; i < count; i++)
    {
        printf("%-20s %10.1f %10.1f %10.1f %10.2f\n",
               students[i].name,
               students[i].math,
               students[i].physics,
               students[i].chemistry,
               students[i].average);
    }

    printf("\n=== STATISTIKY ===\n");
    printf("Počet studentů: %d\n", count);
    printf("Celkový průměr: %.2f\n", total_avg);
    printf("Nejlepší student: %s (%.2f)\n", students[0].name, students[0].average);
    printf("Nejhorší student: %s (%.2f)\n", students[count - 1].name,
           students[count - 1].average);

    // 5. Cleanup
    free(students);
    return 0;
}

/*
 * TESTOVACÍ DATA:
 * 
 * Alice;85.5;90.0;88.0
 * Bob;78.0;82.5;80.0
 * Charlie;92.0;94.5;91.0
 * 
 * Výstup:
 * ============
 * Charlie:  92.50 (nejlepší)
 * Alice:    87.83
 * Bob:      80.17 (nejhorší)
 * Celk.prů: 86.83
 * 
 * SHRNUTÍ KLÍČOVÝCH VZORŮ:
 * 
 * 1. STRTOK_R (bezpečné):
 *    strtok_r(buffer, delim, &saveptr);
 *    Alternativa: strtok(buffer, delim) - modifikuje buffer!
 * 
 * 2. SSCANF PRO PARSOVÁNÍ:
 *    if (sscanf(token, "%f", &value) != 1)
 *        fprintf(stderr, "Invalid number\n");
 * 
 * 3. PRŮMĚROVÁNÍ:
 *    avg = (a + b + c) / 3.0f;  // Pozor: dělíme 3.0f, ne 3!
 * 
 * 4. REALLOC SE SAFETY CHECK:
 *    Student *tmp = realloc(students, new_size);
 *    if (!tmp) { fprintf(stderr, ...); free(students); }
 *    students = tmp;
 * 
 * 5. QSORT KOMPARÁTOR SESTUPNĚ:
 *    if (s1->avg > s2->avg) return -1;
 *    if (s1->avg < s2->avg) return 1;
 *    return 0;
 * 
 * 6. PRINTF FORMÁTOVÁNÍ:
 *    printf("%-20s %10.2f\n", str, float);
 *    Vlevo zarovnáno: %-20s
 *    Vpravo zarovnáno, 2 decimální: %10.2f
 */
