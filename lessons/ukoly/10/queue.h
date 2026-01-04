#ifndef __QUEUE_H__
#define __QUEUE_H__
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
typedef struct {
    int capacity;
    int item_number;
    int rear;
    int tail;
    void **data;
} queue_t;
 
queue_t* create_queue(int capacity);

void delete_queue(queue_t *queue);
 
bool push_to_queue(queue_t *queue, void *data);
 
void* pop_from_queue(queue_t *queue);
 
void* get_from_queue(queue_t *queue, int idx);
 
int get_queue_size(queue_t *queue);
 
#endif 
