# Queue Documentation
![image](https://user-images.githubusercontent.com/78487146/219938452-c9d11448-ae37-46ef-9fca-4e4f06717497.png)


| Function                                                          | Description                                                                                                            |
|-------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------|
|Queue* queue_init();                                               | Returns a pointer to an empty Queue, otherwise NULL |
|Queue* queue_clone(Queue* destination, const Queue* source);       | Clones the source Queue to destination. Returns a pointer to the cloned Queue, otherwise NULL. Destination can be NULL |
|int queue_enqueue(Queue* queue, const int value);                  | Appends an element to the Back of the Queue. Returns 1 on success, otherwise 0 |
|int queue_dequeue(Queue* queue);                                   | Deletes the element at the Front of the Queue. Returns 1 on success, otherwise 0 |
|int queue_peek(const Queue* queue);                                | Returns the value at the Front of the Queue |
|int queue_get_size(const Queue* queue);                            | Returns the size of the Queue |
|int queue_is_empty(const Queue* queue);                            | Returns 1 if the size of the Queue is 0, otherwise 0
|int queue_is_full();                                               | Returns 1 if no memory can be allocated for a new element, otherwise 0
|char* queue_to_string(const Queue* queue);                         | Converts the values of a Queue to a string. Returns a pointer to the start of the string, otherwise NULL
|void queue_empty(Queue* queue);                                    | Empties the Queue |
|void queue_destroy(Queue** queue);                                 | Frees the Queue and its elements from memory |
