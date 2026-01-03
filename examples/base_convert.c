/*
 * ÚLOHA: Převod mezi soustavami 2-36
 * - Parametry: vstupní základ BIN (2-36) argv[1], výstupní základ BOUT (2-36) argv[2].
 * - Načti číslo jako řetězec ze stdin (jedno slovo), převed' z BIN do int64, pak do BOUT.
 * - Povolené cifry 0-9A-Z. Při chybě formátu nebo přetečení vytiskni "Error\n" a ukonči 100.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

static int digit_val(char c){ if('0'<=c && c<='9') return c-'0'; if('A'<=c && c<='Z') return c-'A'+10; return -1; }
static char digit_char(int v){ return v<10 ? '0'+v : 'A'+(v-10); }

int main(int argc, char *argv[])
{
    if (argc < 3) return 100;
    int bin = atoi(argv[1]);
    int bout = atoi(argv[2]);
    if (bin < 2 || bin > 36 || bout < 2 || bout > 36) return 100;

    char buf[256];
    if (scanf("%255s", buf) != 1) return 100;

    // to upper
    for (char *p=buf; *p; ++p) *p = (char)toupper((unsigned char)*p);

    // parse to int64 with overflow check
    int sign = 1; int idx=0;
    if (buf[0]=='-'){ sign=-1; idx=1; }
    int64_t val=0;
    for (; buf[idx]; idx++){
        int d = digit_val(buf[idx]);
        if (d < 0 || d >= bin) { printf("Error\n"); return 100; }
        if (val > (INT64_MAX - d) / bin) { printf("Error\n"); return 100; }
        val = val*bin + d;
    }
    val *= sign;

    // handle zero
    if (val == 0){ printf("0\n"); return 0; }

    char out[256]; int len=0; int64_t t = (val<0)? -val : val;
    while (t > 0){ int d = (int)(t % bout); out[len++] = digit_char(d); t /= bout; }
    if (val < 0) out[len++]='-';
    // reverse
    for (int i=0; i<len/2; i++){ char c=out[i]; out[i]=out[len-1-i]; out[len-1-i]=c; }
    out[len]='\0';
    printf("%s\n", out);
    return 0;
}
