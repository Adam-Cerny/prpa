#include <stdio.h>
#include <stdlib.h>

typedef struct node_struct
{
    int data;
    struct node_struct *ptr_next;
} node_t;

void push(node_t *ptr_list, int data)
{
    if (ptr_list->ptr_next == NULL)
    {
        node_t *new_entry = (node_t *)malloc(sizeof(node_t));
        new_entry->data = data;
        new_entry->ptr_next = NULL;

        ptr_list->ptr_next = new_entry;
    }
    else
    {
        push(ptr_list->ptr_next, data);
    }
}

void destroy_list(node_t *ptr_list)
{
    if (ptr_list != NULL)
    {
        destroy_list(ptr_list->ptr_next);
        free(ptr_list);
    }
}

void print_list(node_t *ptr_list)
{
    if (ptr_list != NULL)
    {
        printf("(ADDR %p) Data: %3i Ptr Next: %p\n", ptr_list, ptr_list->data, ptr_list->ptr_next);

        print_list(ptr_list->ptr_next);
    }
}

int main(void)
{
    node_t *list = (node_t *)malloc(sizeof(node_t));
    list->data = 0;
    list->ptr_next = NULL;

    push(list, 10);
    push(list, 20);
    push(list, 30);

    print_list(list);



    destroy_list(list);

    return 0;
}
