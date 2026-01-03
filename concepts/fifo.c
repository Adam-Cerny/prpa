// Kdy FIFO : když potřebuješ pořadí „první dovnitř, první ven“ — např.BFS, fronty úloh, producent / konzument, plánovač, buffery.Co umí : queue_init, queue_push, queue_pop, queue_front, queue_empty, queue_size, queue_free.Implementace je kruhové pole s bezpečným realloc.Použití v kódu : Vytvoř Queue q;
// queue_init(&q, 0);
// queue_push(&q, ptr);
// (ukládáš void *, takže vkládej ukazatele; pro prosté int můžeš malloc int a uložit ukazatel, nebo si přetypuj implementaci na int *data).Čti : while (!queue_empty(&q))
// {
//     void *p = queue_pop(&q);
//     ...
// }
// Pokud ukládáš heap data, po pop je uvolni(free).Nakonec queue_free(&q);
// Adaptace na hodnotové typy : chceš - li frontu čistě na int, přepiš void **data → int *data, signatury na int / const int *, a push / pop / top vracej / berou int.Bezpečnost : fronta se sama zvětší;
// queue_push vrací - 1 při selhání(realloc).Při queue_pop na prázdné frontě dostaneš NULL.

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    void **data;
    int head; // index prvniho prvku
    int tail; // index za poslednim prvkem (pozice pro zapis)
    int cap;  // kapacita pole
} Queue;

// Inicializace fronty
int queue_init(Queue *q, int initial_cap)
{
    q->head = 0;
    q->tail = 0;
    q->cap = (initial_cap > 0) ? initial_cap : 4;
    q->data = malloc(q->cap * sizeof(void *));
    return q->data ? 0 : -1;
}

// Vnitřní funkce: zvětši kapacitu (bezpečný realloc)
static int queue_grow(Queue *q)
{
    int old_cap = q->cap;
    int new_cap = q->cap * 2;
    void **tmp = realloc(q->data, new_cap * sizeof(void *));
    if (!tmp)
        return -1;

    // Pokud dojde k realokaci, data jsou stále v pořadí head..tail-1 (mod old_cap)
    // Potřebujeme je případně "narovnat" pokud se fronta přelila přes konec pole.
    if (q->tail < q->head)
    {
        // Přesuň blok z [0, tail) na konec nového pole
        int block = q->tail;
        for (int i = 0; i < block; i++)
        {
            tmp[old_cap + i] = tmp[i];
        }
        q->tail = old_cap + block; // tail ukazuje za posledni prvek
    }

    q->data = tmp;
    q->cap = new_cap;
    return 0;
}

int queue_empty(const Queue *q)
{
    return q->head == q->tail;
}

int queue_size(const Queue *q)
{
    return (q->tail - q->head + q->cap) % q->cap;
}

// Enqueue (vložit na konec)
int queue_push(Queue *q, void *item)
{
    // Fronta je plná, pokud by další tail==head (po posunu)
    int next_tail = (q->tail + 1) % q->cap;
    if (next_tail == q->head)
    {
        if (queue_grow(q) != 0)
            return -1;
        next_tail = (q->tail + 1) % q->cap;
    }
    q->data[q->tail] = item;
    q->tail = next_tail;
    return 0;
}

// Peek (přečti první prvek bez odebrání)
void *queue_front(const Queue *q)
{
    if (queue_empty(q))
        return NULL;
    return q->data[q->head];
}

// Dequeue (odeber a vrať první prvek)
void *queue_pop(Queue *q)
{
    if (queue_empty(q))
        return NULL;
    void *item = q->data[q->head];
    q->head = (q->head + 1) % q->cap;
    return item;
}

void queue_free(Queue *q)
{
    free(q->data);
    q->data = NULL;
    q->head = q->tail = q->cap = 0;
}

// ============================================
// DEMO: fronta int hodnot (ulozene jako heap int*)
// ============================================

int main(void)
{
    Queue q;
    if (queue_init(&q, 0) != 0)
    {
        fprintf(stderr, "Init fail\n");
        return 100;
    }

    // push 5 hodnot
    for (int i = 0; i < 5; i++)
    {
        int *v = malloc(sizeof(int));
        if (!v)
            return 101;
        *v = i * 10;
        if (queue_push(&q, v) != 0)
        {
            fprintf(stderr, "Push fail\n");
            return 102;
        }
    }

    // pop & tisk
    while (!queue_empty(&q))
    {
        int *v = queue_pop(&q);
        printf("%d\n", *v);
        free(v);
    }

    queue_free(&q);
    return 0;
}
