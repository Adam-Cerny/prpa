#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct
{
    int data;
    struct node_struct* ptr_next;
} node_t;

void push(node_t* ptr_list, int data)
{
    node_t* tmp = ptr_list;

    while (tmp->ptr_next != NULL)
    {
        tmp = tmp->ptr_next;
    }

    node_t* new_entry = (node_t*)malloc(sizeof(node_t));
    new_entry->data = data;
    new_entry->ptr_next = NULL;

    tmp->ptr_next = new_entry;
}

int pop(node_t* ptr_list)
{
    node_t* tmp = ptr_list;

    int data;

    int list_lenghth = 0;

    while (tmp->ptr_next != NULL)
    {
        tmp = tmp->ptr_next;
        list_lenghth++;
    }

    data = tmp->data;
    free(tmp);

    tmp = ptr_list;
    for (int i = 0; i < list_lenghth - 1; i++)
    {
        tmp = tmp->ptr_next;
    }
    tmp->ptr_next = NULL;

    return data;
}

void insert(node_t* ptr_list, int data, int pos)
{
    int list_length = 0;
    node_t* tmp = ptr_list;

    while (tmp->ptr_next != NULL)
    {
        tmp = tmp->ptr_next;
        list_length++;
    }

    if (pos < 1)
    {
        printf("Neplatny zapis do seznamu!\n");
        return;
    }

    else if (pos > list_length)
    {
        printf("Pozice je vetsi nez delka seznamu, pridan na konec!\n");
        push(ptr_list, data);
        return;
    }
    
    tmp = ptr_list;

    for (int i = 1; i < pos; i++)
    {
        tmp = tmp->ptr_next;
    }

    node_t previous = *tmp;
    node_t* shifted = (node_t*)malloc(sizeof(node_t));

    tmp->data = data;
    tmp->ptr_next = shifted;

    *shifted = previous;

}

void print_list(node_t* ptr_list)
{
    node_t* tmp = ptr_list;
    int i = 0;
    while (tmp != NULL)
    {
        printf("[%i] (ADDR %p) Data: %3i Ptr Next: %p\n", i, tmp, tmp->data, tmp->ptr_next);
        tmp = tmp->ptr_next;
        i++;
    }
}

void destroy_list(node_t* ptr_list)
{
    node_t* tmp = ptr_list;
    node_t* destroy = NULL;

    while (tmp != NULL)
    {
        destroy = tmp;
        tmp = tmp->ptr_next;
        free(destroy);
    }
}

int main(void)
{
    node_t* list = (node_t*)malloc(sizeof(node_t));
    list->data = 0;
    list->ptr_next = NULL;

    push(list, 10);
    push(list, 20);
    push(list, 30);

    print_list(list);   

    printf("Pop: %i\n", pop(list));
    printf("Pop: %i\n", pop(list));

    push(list, 50);
    push(list, 75);
    push(list, 100);

    print_list(list);

    printf("Inserting 42 at position 2\n");
    insert(list, 42, 1);

    printf("Inserting 1000 at position 50 (invalid)\n");
    insert(list, 1000, 50);

    print_list(list);

    destroy_list(list);

    return 0;
}
