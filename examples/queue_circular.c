/*
 * ÚLOHA: Kruhová fronta v poli (HW10 styl)
 * - Implementuje push/pop/size/empty nad polem int.
 * - Kapacita se zvětšuje reallocem.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int head; // index prvního
    int tail; // index za posledním
    int cap;
} Queue;

static int queue_init(Queue *q, int cap)
{
    q->cap = (cap > 0) ? cap : 4;
    q->head = q->tail = 0;
    q->data = malloc(q->cap * sizeof(int));
    return q->data ? 0 : -1;
}

static int queue_empty(const Queue *q)
{
    return q->head == q->tail;
}

static int queue_size(const Queue *q)
{
    return (q->tail - q->head + q->cap) % q->cap;
}

static int queue_grow(Queue *q)
{
    int old_cap = q->cap;
    int new_cap = q->cap * 2;
    int *tmp = realloc(q->data, new_cap * sizeof(int));
    if (!tmp) return -1;
    // pokud je fronta přelomená, narovnej druhý blok za konec
    if (q->tail < q->head)
    {
        int block = q->tail;
        for (int i = 0; i < block; i++)
            tmp[old_cap + i] = tmp[i];
        q->tail = old_cap + block;
    }
    q->data = tmp;
    q->cap = new_cap;
    return 0;
}

static int queue_push(Queue *q, int v)
{
    int next = (q->tail + 1) % q->cap;
    if (next == q->head)
    {
        if (queue_grow(q) != 0) return -1;
        next = (q->tail + 1) % q->cap;
    }
    q->data[q->tail] = v;
    q->tail = next;
    return 0;
}

static int queue_pop(Queue *q, int *out)
{
    if (queue_empty(q)) return -1;
    *out = q->data[q->head];
    q->head = (q->head + 1) % q->cap;
    return 0;
}

static void queue_free(Queue *q)
{
    free(q->data);
    q->data = NULL;
    q->head = q->tail = q->cap = 0;
}

int main(void)
{
    Queue q;
    if (queue_init(&q, 0) != 0) return 100;

    // demo: push 5, pop all
    for (int i = 0; i < 5; i++) queue_push(&q, i * 10);
    while (!queue_empty(&q))
    {
        int v; queue_pop(&q, &v);
        printf("%d\n", v);
    }

    queue_free(&q);
    return 0;
}
