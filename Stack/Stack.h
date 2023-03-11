#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct Stack {
    int* array;
    size_t size;
    size_t capacity;
} Stack;

Stack* stack_init(const size_t capacity);
Stack* stack_clone(Stack* destination, const Stack* source);
Stack* stack_empty(Stack* stack);

Stack* stack_push(Stack* stack, const int value);
int stack_pop(Stack* stack);
int stack_peek(const Stack* stack);

int stack_is_empty(const Stack* stack);
int stack_is_full(const Stack* stack);

size_t stack_get_size(const Stack* stack);
size_t stack_get_capacity(const Stack* stack);

char* stack_to_string(const Stack* stack);
void stack_destroy(Stack** stack);

#endif // STACK_H_INCLUDED
