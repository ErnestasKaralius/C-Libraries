#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Queue.h"

Queue* queue_init()
{
    Queue* queue = malloc(sizeof(Queue*));
    if(!queue)
        return NULL;

    queue->back = NULL;
    queue->front = NULL;
    queue->size = 0;

    return queue;
}

int queue_get_size(const Queue* queue)
{
    return (!queue) ? 0 : queue->size;
}

int queue_is_empty(const Queue* queue)
{
    return (!queue || queue->size == 0) ? 1 : 0;
}

int queue_is_full()
{
    return list_is_full();
}

int queue_peek(const Queue* queue)
{
    return queue ? queue->front->value : 0;
}

int queue_enqueue(Queue* queue, const int value)
{
    if(!queue || !list_append(&(queue->back), value))
        return 0;

    if(queue_is_empty(queue))
        queue->front = queue->back;
    else
        queue->back = queue->back->next;

    queue->size++;

    return 1;
}

int queue_dequeue(Queue* queue)
{
    int value = queue->front->value;
    if(!queue || !list_delete(&(queue->front), 0))
        return 0;

    queue->size--;

    return value;
}

Queue* queue_clone(Queue* destination, const Queue* source)
{
    if(!source || destination == source)
        return NULL;

    if(!destination)
    {
        Queue* temp_queue = queue_init();
        if(!temp_queue)
            return NULL;

        destination = temp_queue;
    }
    else
        queue_empty(destination);

    Node* source_list = source->front;
    for(int i = 0; i < source->size; ++i)
    {
        queue_enqueue(destination, list_get_first(source_list));
        source_list = source_list->next;
    }

    destination->size = source->size;

    return destination;
}

void queue_empty(Queue* queue)
{
    if(!queue)
        return;

    list_destroy(&(queue->front));
    queue->size = 0;
}

char* queue_to_string(const Queue* queue)
{
    if(!queue)
        return NULL;

    return list_to_string(queue->front);
}

void queue_destroy(Queue** queue)
{
    if(!queue || !(*queue))
        return;

    queue_empty(*queue);
    free(*queue);
    *queue = NULL;
}
