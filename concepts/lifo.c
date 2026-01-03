// LIFO = Last In, First Out (zásobník/stack). Prvek, který vložíš jako poslední, jde ven jako první.

// Základní operace:

// push(x): vloží prvek na vrchol.
// pop(): vrátí a odebere prvek z vrcholu (pokud je prázdný, vrať NULL/err).
// top()/peek(): vrátí prvek na vrcholu, ale nesmaže ho.
// empty(): jestli je zásobník prázdný.
// size(): počet prvků.
// Implementace:

// Pole + index vrcholu: jednoduché, 
// O
// (
// 1
// )
// O(1) na push/pop, pozor na rozšíření pole (realloc).
// Jednosměrný seznam: každý uzel má data + next; push/pop na začátku seznamu za 
// O
// (
// 1
// )
// O(1), bez nutnosti realloc.
// Typické použití:

// Vyhodnocení výrazů (priorita operátorů), DFS, undo/redo, převod do postfixu, kontrola závorek.
// Bezpečnostní drobnosti:

// U pole vždy hlídej kapacitu a bezpečné realloc (přes dočasný ukazatel).
// U pop na prázdném zásobníku vrať chybu nebo NULL.
// Pokud ukládáš ukazatele, pop vrátí ukazatel – uvolni případnou heap paměť, když prvek už nepotřebuješ.

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void **data;
    int top; // index další volné pozice
    int cap; // kapacita pole
} Stack;

int stack_init(Stack *s, int initial_cap)
{
    s->top = 0;
    s->cap = (initial_cap > 0) ? initial_cap : 4;
    s->data = malloc(s->cap * sizeof(void *));
    return s->data != NULL ? 0 : -1;
}

int stack_push(Stack *s, void *item)
{
    if (s->top >= s->cap)
    {
        int new_cap = s->cap * 2;
        void **tmp = realloc(s->data, new_cap * sizeof(void *));
        if (!tmp)
            return -1; // realloc selhal, data zůstávají v s->data
        s->data = tmp;
        s->cap = new_cap;
    }
    s->data[s->top++] = item;
    return 0;
}

int stack_empty(const Stack *s)
{
    return s->top == 0;
}

void *stack_top(const Stack *s)
{
    if (s->top == 0)
        return NULL;
    return s->data[s->top - 1];
}

void *stack_pop(Stack *s)
{
    if (s->top == 0)
        return NULL;
    return s->data[--s->top];
}

int stack_size(const Stack *s)
{
    return s->top;
}

void stack_free(Stack *s)
{
    free(s->data);
    s->data = NULL;
    s->top = s->cap = 0;
}

int main(void)
{
    Stack st;
    if (stack_init(&st, 0) != 0)
        return 100;

    // push int hodnot (heap)
    for (int i = 0; i < 5; i++)
    {
        int *v = malloc(sizeof(int));
        *v = i * 10;
        stack_push(&st, v);
    }

    // pop
    while (!stack_empty(&st))
    {
        int *v = stack_pop(&st);
        printf("%d\n", *v);
        free(v);
    }

    stack_free(&st);
    return 0;
}
