#include "queue.h"
#include <stdio.h>

#define TRUE 1
#define FALSE 0

// funkce pro vytvoreni fronty
queue_t* create_queue(int capacity)
{
    // alokace pameti pro strukturu fronty
    queue_t *q = (queue_t *)malloc(sizeof(queue_t));

    // kontrola uspesnosti alokace struktury
    if (q == NULL) 
    {
        return NULL;
    }

    // nastaveni pocatecnich hodnot struktury fronty
    q->capacity = capacity;
    q->item_number = 0;
    q->rear = 0;
    q->tail = -1;

    // alokace pameti pro data fronty
    q->data = (void **)malloc(capacity * sizeof(void *));

    // kontrola uspesnosti alokace dat fronty
    if (q->data == NULL) 
    {
        // uvolnneni pameti pro strukturu fronty v pripade chyby
        free(q);
        return NULL;
    }
    return q;
}

// funkce pro smazani fronty
void delete_queue(queue_t *queue)
{
    // kontrola, zda neni fronta prazdna
    if (queue != NULL) 
    {
        // uvolneni pameti pro data fronty a strukturu fronty
        free(queue->data);
        free(queue);
    }
}

// funkce pro pridani prvku do fronty
bool push_to_queue(queue_t *queue, void *data)
{
    // kontrola, zda neni fronta plna
    if (queue->item_number >= queue->capacity) 
    {
        // fronta je plna, nelze pridat prvek
        return FALSE; 
    }

    // posun indexu tailho prvku 
    queue->tail = (queue->tail + 1) % queue->capacity;

    // pridani dat do fronty
    queue->data[queue->tail] = data;
    // zvyseni poctu prvku ve fronte
    queue->item_number++;

    return TRUE;
}

// funkce pro odebrani prvku z fronty
void* pop_from_queue(queue_t *queue)
{
    // kontrola, zda neni fronta prazdna
     if (queue->item_number == 0) 
    {
        // fronta je prazdna, nelze odebrat prvek
        return NULL; 
    }

    // odebrani dat z fronty 
    void *data = queue->data[queue->rear];

    // posunuti indexu rearho prvku 
    queue->rear = (queue->rear + 1) % queue->capacity;
    // snizeni poctu prvku ve fronte
    queue->item_number--;

    return data;
}

// funkce pro ziskani prvku z fronty bez odebrani
void* get_from_queue(queue_t *queue, int idx)
{
    // kontrola, zda je index platny
    if (idx < 0 || idx >= queue->item_number)
    {
        // neplatny index, nelze ziskat prvek
        return NULL; 
    }
    // vypocet skutecneho indexu v poli dat
    int real_index = (queue->rear + idx) % queue->capacity;
    
    return queue->data[real_index];
}

// funkce pro ziskani velikosti fronty
int get_queue_size(queue_t *queue)
{
    return queue->item_number;
}
