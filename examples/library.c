/*
 * ÚLOHA: Validace IPv4 adresy
 * - Načti řetězec ve formátu A.B.C.D ze stdin.
 * - Validuj: každá část je int 0-255, přesně 4 části oddělené tečkami.
 * - Vypiš "Valid" nebo "Invalid".
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char buf[256];
    if (scanf("%255s", buf) != 1) { printf("Invalid\n"); return 0; }

    int parts[4];
    int cnt = 0;
    char *start = buf;
    
    for (char *p = buf; cnt < 5; ++p)
    {
        if (*p == '.' || *p == '\0')
        {
            if (p == start) { printf("Invalid\n"); return 0; }
            if (cnt >= 4) { printf("Invalid\n"); return 0; }
            
            char part[256];
            int len = p - start;
            if (len > 255) { printf("Invalid\n"); return 0; }
            strncpy(part, start, len);
            part[len] = '\0';
            
            for (int i = 0; i < len; i++)
                if (!isdigit((unsigned char)part[i])) { printf("Invalid\n"); return 0; }
            
            int val = atoi(part);
            if (val > 255) { printf("Invalid\n"); return 0; }
            parts[cnt++] = val;
            
            if (*p == '\0') break;
            start = p + 1;
        }
    }

    if (cnt != 4) { printf("Invalid\n"); return 0; }
    printf("Valid\n");
    return 0;
}
