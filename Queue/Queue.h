#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct Queue {
    struct LinkedList* front;
    struct LinkedList* back;
    int size;
} Queue;

Queue* queue_init();
Queue* queue_clone(Queue* destination, const Queue* source);

int queue_enqueue(Queue* queue, const int value);
int queue_dequeue(Queue* queue);

int queue_peek(const Queue* queue);
int queue_get_size(const Queue* queue);

int queue_is_empty(const Queue* queue);
int queue_is_full();

char* queue_to_string(const Queue* queue);
void queue_empty(Queue* queue);
void queue_destroy(Queue** queue);

#endif // QUEUE_H_INCLUDED
