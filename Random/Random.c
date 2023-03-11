#include <stdlib.h>
#include <stdio.h>

int rand_int(const int low, const int high)
{
    if(high < low)
        return 0;

    return low + rand() % (high - low + 1);
}

double rand_float(const int low, const int high)
{
    if(high < low)
        return 0;

    return low + (double)rand() / RAND_MAX * (high - low);
}

char rand_char()
{
    return rand_int(32, 126);
}

char* rand_str(const size_t length)
{
    if(length == 0)
        return NULL;

    char* str = calloc(length + 1, sizeof(char*));
    if(!str)
        return NULL;

    for(size_t i = 0; i < length; ++i)
        str[i] = rand_char();

    str[length] = '\0';

    return str;
}

int main(void)
{
    printf("Hello, world!");

    return 0;
}