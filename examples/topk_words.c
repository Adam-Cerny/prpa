/*
 * ÚLOHA: TOP-K nejčastějších slov
 * - Parametr: K z argv[1].
 * - Čte slova (scanf "%255s") do EOF, case-insensitive.
 * - Vypíše slova seřazená sestupně podle četnosti, při shodě abecedně, ořízne na K položek.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXW 256

typedef struct { char *w; int f; } Item;

static void lower_str(char *s){ for (; *s; ++s) *s=(char)tolower((unsigned char)*s); }

static int cmp_item(const void *a, const void *b)
{
    const Item *x=a, *y=b;
    if (x->f != y->f) return (y->f - x->f); // desc freq
    return strcmp(x->w, y->w); // asc word
}

int main(int argc, char *argv[])
{
    if (argc < 2) return 100;
    int K = atoi(argv[1]);
    if (K < 0) return 100;

    Item *arr=NULL; int cap=0, n=0; char buf[MAXW];
    while (scanf("%255s", buf)==1)
    {
        lower_str(buf);
        int found=-1;
        for (int i=0;i<n;i++) if(strcmp(arr[i].w,buf)==0){found=i;break;}
        if (found>=0) { arr[found].f++; }
        else {
            if (n>=cap){ cap=cap?cap*2:16; Item*tmp=realloc(arr,cap*sizeof(Item)); if(!tmp){free(arr);return 100;} arr=tmp; }
            arr[n].w=strdup(buf); if(!arr[n].w){return 100;}
            arr[n].f=1; n++;
        }
    }

    qsort(arr,n,sizeof(Item),cmp_item);
    int limit = (K==0||K>n)? n : K;
    for (int i=0;i<limit;i++)
        printf("%-20s %d\n", arr[i].w, arr[i].f);

    for (int i=0;i<n;i++) free(arr[i].w);
    free(arr);
    return 0;
}
