#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

#define INITIAL_STR_LENGTH 100
#define MAX_INT_LENGTH 11

Node* list_create_node(const int value)
{
    Node* node = malloc(sizeof(Node*));
    if(!node)
        return NULL;

    node->value = value;
    node->next = NULL;

    return node;
}

int list_insert(Node** head, const int index, const int value)
{
    if(!head || index < 0)
        return 0;

    Node* start_node = *head;
    Node* previous_node = NULL;
    Node* new_node = list_create_node(value);
    if(!new_node)
        return 0;

    if(index == 0)
    {
        new_node->next = start_node;
        *head = new_node;
        return 1;
    }

    for(int i = 0; i < index; ++i)
    {
        previous_node = start_node;
        if(!previous_node)
        {
            free(new_node);
            return 0;
        }

        start_node = start_node->next;
    }

    previous_node->next = new_node;
    new_node->next = start_node;

    return 1;
}

int list_delete(Node** head, const int index)
{
    if(!head || !(*head) || index < 0)
        return 0;

    Node* start_node = *head;
    Node* previous_node;

    if(index == 0)
    {
        *head = (*head)->next;
        free(start_node);
        return 1;
    }

    for(int i = 0; i < index; ++i)
    {
        previous_node = start_node;
        start_node = start_node->next;
    }

    previous_node->next = start_node->next;
    free(start_node);

    return 1;
}

int list_append(Node** head, const int value)
{
    if(!head)
        return 0;

    Node* start_node = *head;
    Node* previous_node = NULL;
    Node* new_node = list_create_node(value);
    if(!new_node)
        return 0;

    if(!start_node)
    {
        *head = new_node;
        return 1;
    }

    while(start_node)
    {
        previous_node = start_node;
        start_node = start_node->next;
    }

    previous_node->next = new_node;

    return 1;
}

int list_find_index(Node* head, const int value)
{
    int i = 0;
    while(head)
    {
        if(head->value == value)
            return i;

        head = head->next;
        ++i;
    }

    return -1;
}

int list_set_value(Node* head, const int index, const int value)
{
    if(index < 0 || !head)
        return 0;

    for(int i = 0; i < index; ++i)
    {
        head = head->next;
        if(!head)
            return 0;
    }

    head->value = value;

    return 1;
}

int list_set_first(Node* head, const int value)
{
    return list_set_value(head, 0, value);
}

int list_set_last(Node* head, const int value)
{
    Node* previous_node = NULL;
    while(head)
    {
       previous_node = head;
       head = head->next;
    }

    if(!previous_node)
        return 0;

    previous_node->value = value;

    return 1;
}

int list_get_value(Node* head, const int index)
{
    for(int i = 0; i < index && head; ++i)
        head = head->next;

    return head->value;
}

int list_get_first(Node* head)
{
    return head->value;
}

int list_get_last(Node* head)
{
    Node* previous_node = NULL;
    while(head)
    {
       previous_node = head;
       head = head->next;
    }

    return previous_node->value;
}

int list_get_size(Node* head)
{
    int size = 0;
    while(head)
    {
        head = head->next;
        ++size;
    }

    return size;
}

int list_is_empty(Node* head)
{
    return (list_get_size(head) == 0) ? 1 : 0;
}

int list_is_full()
{
    Node* temp_node = list_create_node(0);
    if(!temp_node)
        return 1;

    free(temp_node);
    return 0;
}

Node* list_clone(Node** destination, Node* source)
{
    if(!source || *destination == source)
        return NULL;

    if(!destination)
    {
        Node* temp_dest = NULL;
        destination = &temp_dest;
    }
    else
        list_destroy(destination);

    while(source)
    {
        if(!list_append(destination, list_get_first(source)))
            return NULL;

        source = source->next;
    }

    return *destination;
}

void list_destroy(Node** head)
{
    if(!head || !(*head))
        return;

    Node* temp_node = NULL;
    while(*head)
    {
        temp_node = *head;
        *head = (*head)->next;
        free(temp_node);
    }
}

char* list_to_string(Node* head)
{
    char* string = calloc(INITIAL_STR_LENGTH, sizeof(char*));
    size_t buffer_capacity = INITIAL_STR_LENGTH;
    size_t length = 0;

    if(!head || !string)
        return NULL;

    while(head)
    {
        char temp_string[MAX_INT_LENGTH + 1];
        length += snprintf(temp_string, MAX_INT_LENGTH, "%d ", list_get_first(head));

        if(length > buffer_capacity - 1)
        {
            buffer_capacity = buffer_capacity * 2 + length;
            char* new_ptr = realloc(string, buffer_capacity);
            if(!new_ptr)
                return string;

            string = new_ptr;
        }

        strncat(string, temp_string, buffer_capacity - 1);
        head = head->next;
    }

    return string;
}

Node* split_after(Node* head, const int amount)
{
    Node* rest = head;
    Node** prev = NULL;

    for(int i = 0; rest && i < amount; ++i)
    {
        prev = &rest->next;
        rest = rest->next;
    }

    if(prev)
        *prev = NULL;

    return rest;
}

void merge_lists(Node*** out_tail, Node* head1, Node* head2)
{
    while(head1 || head2)
    {
        Node** min_node = !head2 || (head1 && head1->value <= head2->value) ? &head1 : &head2;
        **out_tail = *min_node;
        *min_node = (*min_node)->next;
        (**out_tail)->next = NULL;
        *out_tail = &(**out_tail)->next;
    }
}

void list_sort(Node** head)
{
    if(!head || !(*head))
        return;

    Node* current = *head;
    int length = 1, sorted = 0;

    while(!sorted)
    {
        Node* out_head = NULL;
        Node** out_tail = &out_head;
        sorted = 1;

        while(current)
        {
            Node* head1 = current;
            Node* head2 = split_after(head1, length);
            current = split_after(head2, length);

            if(sorted && head2)
                sorted = 0;

            merge_lists(&out_tail, head1, head2);
        }
        length *= 2;
        current = out_head;
    }
    *head = current;
}
