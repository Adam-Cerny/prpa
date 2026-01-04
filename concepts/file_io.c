/**
 * FILE I/O V C (fopen/fclose/fread/fwrite/fgets/fprintf)
 * Přehled nejčastějších vzorů práce se soubory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// ===== 1) ZÁKLADNÍ OTEVŘENÍ A ZÁPIS TEXTU =====
// Režimy fopen:
// "r"  - jen čtení, soubor musí existovat
// "w"  - zápis, soubor se vytvoří nebo přepíše
// "a"  - append, zapisuje na konec (vytvoří pokud neexistuje)
// "r+" - čtení i zápis, soubor musí existovat
// "w+" - čtení i zápis, soubor se vymaže/vytvoří znovu
// "b"  - binární mód (např. "rb", "wb")

void example_write_text(void)
{
    FILE *f = fopen("demo.txt", "w");
    if (!f)
    {
        perror("fopen demo.txt");
        return;
    }

    fprintf(f, "Ahoj soubore!\n");
    fprintf(f, "Cislo: %d\n", 42);
    fprintf(f, "Pi: %.2f\n", 3.14159);

    fclose(f);
}

// Append k existujícímu souboru
void example_append_text(void)
{
    FILE *f = fopen("demo.txt", "a");
    if (!f)
    {
        perror("fopen demo.txt (append)");
        return;
    }

    fprintf(f, "Dalsi radek\n");
    fclose(f);
}

// ===== 2) ČTENÍ TEXTU PO ŘÁDCÍCH (fgets) =====
// Vzorec: while (fgets(buffer, sizeof buffer, file)) { ... }

void example_read_lines(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f)
    {
        perror("fopen read");
        return;
    }

    char line[256];
    int line_no = 1;

    while (fgets(line, sizeof line, f))
    {
        // Odstranění newline, pokud tam je
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        printf("%03d: %s\n", line_no++, line);
    }

    if (ferror(f))
        perror("fgets error");

    fclose(f);
}

// ===== 3) KOPIE SOUBORU (TEXT/BIN) =====
// Bezpečný vzor s kontrolou chyb, buffer 4 KB

int copy_file(const char *src, const char *dst)
{
    FILE *in = fopen(src, "rb");
    if (!in)
    {
        perror("fopen src");
        return -1;
    }

    FILE *out = fopen(dst, "wb");
    if (!out)
    {
        perror("fopen dst");
        fclose(in);
        return -1;
    }

    unsigned char buf[4096];
    size_t nread;

    while ((nread = fread(buf, 1, sizeof buf, in)) > 0)
    {
        size_t nwritten = fwrite(buf, 1, nread, out);
        if (nwritten != nread)
        {
            perror("fwrite");
            fclose(in);
            fclose(out);
            return -1;
        }
    }

    if (ferror(in))
        perror("fread");

    fclose(in);
    fclose(out);
    return 0;
}

// ===== 4) BINÁRNÍ ZÁPIS/ČTENÍ STRUKTUR =====
// fwrite / fread pracují s bloky a počtem prvků

typedef struct
{
    int id;
    float value;
} Record;

void example_binary_write_read(void)
{
    Record data[3] = {
        {1, 1.5f},
        {2, 2.5f},
        {3, 3.5f}
    };

    FILE *f = fopen("records.bin", "wb");
    if (!f)
    {
        perror("fopen records.bin");
        return;
    }

    size_t written = fwrite(data, sizeof(Record), 3, f);
    if (written != 3)
        perror("fwrite records.bin");
    fclose(f);

    // Čtení zpět
    f = fopen("records.bin", "rb");
    if (!f)
    {
        perror("fopen records.bin (read)");
        return;
    }

    Record load[3];
    size_t read = fread(load, sizeof(Record), 3, f);
    if (read != 3)
        perror("fread records.bin");
    fclose(f);

    for (size_t i = 0; i < read; i++)
        printf("id=%d value=%.2f\n", load[i].id, load[i].value);
}

// ===== 5) fseek/ftell: velikost souboru =====
// Pozor: na textových souborech nemusí být přesné na všech platformách,
// pro binární je to spolehlivé.

long file_size(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f)
    {
        perror("fopen size");
        return -1;
    }

    if (fseek(f, 0, SEEK_END) != 0)
    {
        perror("fseek");
        fclose(f);
        return -1;
    }

    long size = ftell(f);
    if (size == -1L)
        perror("ftell");

    fclose(f);
    return size;
}

// ===== 6) ČTENÍ ČÍSEL ZE SOUBORU (fscanf) =====
// Vzorec: while (fscanf(f, "%d", &x) == 1) { ... }

void example_read_numbers(const char *path)
{
    FILE *f = fopen(path, "r");
    if (!f)
    {
        perror("fopen numbers");
        return;
    }

    int x;
    int sum = 0;
    int count = 0;

    while (fscanf(f, "%d", &x) == 1)
    {
        sum += x;
        count++;
    }

    if (ferror(f))
        perror("fscanf error");

    fclose(f);

    if (count > 0)
        printf("Prumer: %.2f\n", (double)sum / count);
    else
        printf("Soubor neobsahuje cisla\n");
}

// ===== 7) HLAVNÍ DEMO =====

int main(void)
{
    example_write_text();
    example_append_text();
    example_read_lines("demo.txt");

    copy_file("demo.txt", "demo_copy.txt");
    example_binary_write_read();

    long sz = file_size("demo.txt");
    if (sz >= 0)
        printf("Velikost demo.txt: %ld B\n", sz);

    example_read_numbers("numbers.txt");  // Pokud neexistuje, zobrazí chybu

    return 0;
}

/*
SHRNUTÍ VZORŮ:
- fopen(path, "r"/"w"/"a"/"rb"/"wb"); kontrola NULL, perror
- fclose(f);
- fprintf / fputs / fputc pro textový zápis
- fgets(buffer, size, f) pro čtení řádků
- fread(ptr, size, count, f) / fwrite(ptr, size, count, f) pro binární data
- while (fscanf(f, "%d", &x) == 1) {...} čtení čísel
- fseek(f, offset, origin) + ftell(f) pro zjištění velikosti
- ferror(f) po smyčce pro detekci chyb
- perror("popis") vypíše errno
*/
