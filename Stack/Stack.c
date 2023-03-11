#include <stdio.h>
#include <stdlib.h>
#include "../StringExtra/StringExtra.c"
#include "Stack.h"

#define INITIAL_STR_LENGTH 100
#define MAX_INT_LENGTH snprintf(NULL, 0, "%d", __INT_MAX__)

Stack* stack_init(const size_t capacity)
{
    if(capacity == 0)
        return NULL;

    Stack* stack = malloc(sizeof(Stack*));
    if(!stack)
        return NULL;

    stack->array = malloc(capacity * sizeof(int));
    if(!stack->array)
    {
        free(stack);
        return NULL;
    }

    stack->capacity = capacity;
    stack->size = 0;

    return stack;
}

void stack_destroy(Stack** stack)
{
    if(!stack || !(*stack))
        return;

    free((*stack)->array);
    free(*stack);
    *stack = NULL;
}

int stack_is_empty(const Stack* stack)
{
    return (!stack || stack->size == 0) ? 1 : 0;
}

int stack_is_full(const Stack* stack)
{
    return (stack && stack->size == stack->capacity) ? 1 : 0;
}

Stack* stack_push(Stack* stack, const int value)
{
    if(!stack)
        return NULL;

    if(!stack_is_full(stack))
    {
        stack->array[stack->size] = value;
        stack->size++;
    }

    return stack;
}

int stack_pop(Stack* stack)
{
    if(!stack)
        return 0;

    int value = 0;
    if(!stack_is_empty(stack))
    {
        value = stack->array[stack->size - 1];
        stack->size--;
    }

    return value;
}

Stack* stack_empty(Stack* stack)
{
    if(!stack)
        return NULL;

    while(!stack_is_empty(stack))
        stack_pop(stack);

    return stack;
}

Stack* stack_clone(Stack* destination, const Stack* source)
{
    if(!source || destination == source || destination->capacity < source->size)
        return NULL;

    if(!destination)
    {
        Stack* temp_stack = stack_init(source->capacity);
        if(!temp_stack)
            return NULL;

        destination = temp_stack;
    }
    else
        stack_empty(destination);

    for(size_t i = 0; i < source->size; ++i)
        stack_push(destination, source->array[i]);

    return destination;
}

int stack_peek(const Stack* stack)
{
    return stack ? stack->array[stack->size - 1] : 0;
}

size_t stack_get_size(const Stack* stack)
{
    return stack? stack->size : 0;
}

size_t stack_get_capacity(const Stack* stack)
{
    return stack ? stack->size : 0;
}

char* stack_to_string(const Stack* stack)
{
    if(!stack)
        return NULL;

    size_t capacity = INITIAL_STR_LENGTH;
    size_t length = 0;
    char* string = calloc(capacity + 1, sizeof(char*));
    if(!string)
        return NULL;

    size_t index = 0;
    while(index < stack->size)
    {
        char temp_string[MAX_INT_LENGTH + 2]; // '/0' + space
        length += snprintf(temp_string, MAX_INT_LENGTH + 2, "%d ", stack->array[index]);

        if(length > capacity)
        {
            capacity = (capacity * 2) + length;
            char* new_ptr = realloc(string, capacity + 1);
            if(!new_ptr)
                return string;

            string = new_ptr;
        }

        strlcat(string, temp_string, capacity + 1);
        ++index;
    }

    return string;
}