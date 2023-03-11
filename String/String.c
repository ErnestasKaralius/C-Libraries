#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include "String.h"
#include "../StringExtra/StringExtra.c"

StringArray* string_array_init()
{
    StringArray* str_array = malloc(sizeof(StringArray*));
    if(!str_array)
        return NULL;

    str_array->strings = NULL;
    str_array->size = 0;

    return str_array;
}

StringArray* string_array_append(StringArray* array, const String* string)
{
    if(!array || !string)
        return NULL;

    const size_t new_length = array->size + 1;
    String** temp_strings = realloc(array->strings ? array->strings : NULL, new_length * sizeof(String**));
    if(!temp_strings)
        return NULL;

    array->strings = temp_strings;
    array->size = new_length;
    array->strings[new_length - 1] = string_clone(NULL, string);

    return array;
}

StringArray* string_array_remove(StringArray* array, const size_t index)
{
    if(!array || array->size == 0 || index > array->size - 1)
        return NULL;

    const size_t new_length = array->size - 1;
    array->size = new_length;

    string_destroy(&array->strings[index]);
    array->strings[index] = string_clone(NULL, array->strings[new_length]);
    string_destroy(&array->strings[new_length]);

    return array;
}

int string_array_index_of(const StringArray* array, const String* string)
{
    if(!array || !string)
        return -1;

    for(size_t i = 0; i < array->size; ++i)
        if(string_compare(array->strings[i], string) == 0)
            return i;

    return -1;
}

void string_array_destroy(StringArray** array)
{
    if(!array || !(*array))
        return;

    for(size_t i = 0; i < (*array)->size; ++i)
        string_destroy(&(*array)->strings[i]);

    free((*array)->strings);
    free(*array);
    *array = NULL;  
}

int string_is_empty(const String* string)
{
    return (!string || string->size == 0) ? 1 : 0;
}

size_t string_get_length(const String* string)
{
    return (!string) ? 0 : string->size;
}

char string_char_at(const String* string, const size_t index)
{
    if(string->size == 0 || index > string->size - 1)
        return 0;

    return string->str[index];
}

int string_contains(const String* string, const String* substring)
{
    if(!string || !substring)
        return 0;

    return (strstr(string->str, substring->str) != NULL) ? 1 : 0;
}

String* string_init(const char* str)
{
    if(!str)
        return NULL;

    const size_t length = strlen(str);
    String* string = malloc(sizeof(String*));
    if(!string)
        return NULL;

    string->str = malloc(length + 1);
    if(!string->str)
        return NULL;

    strlcpy(string->str, str, length + 1);
    string->size = length;

    return string;
}

String* string_append(String* destination, const String* source)
{
    if(!destination || !source)
        return NULL;

    const size_t new_length = destination->size + source->size;
    char* new_str = realloc(destination->str, new_length + 1);
    if(!new_str)
        return NULL;

    strlcpy(new_str + destination->size, source->str, source->size + 1);

    destination->str = new_str;
    destination->size = new_length;

    return destination;
}

String* string_prepend(String* destination, const String* source)
{
    if(!destination || !source)
        return NULL;

    const size_t new_length = destination->size + source->size;
    char* new_str = malloc(new_length + 1);
    if(!new_str)
        return NULL;

    strlcpy(new_str, source->str, source->size + 1);
    strlcpy(new_str + source->size, destination->str, destination->size + 1);

    free(destination->str);
    destination->str = new_str;
    destination->size = new_length;

    return destination;
}

String* string_concat(const String* string1, const String* string2)
{
    if(!string1 || !string2)
        return NULL;

    String* new_string = string_init("");
    if(!new_string)
        return NULL;

    string_append(new_string, string1);
    string_append(new_string, string2);

    return new_string;
}

int string_compare(const String* string1, const String* string2)
{
    if(!string1 || !string2)
        return 0;

    return strlcmp(string1->str, string2->str, string1->size);
}

int string_compare_ignore_case(const String* string1, const String* string2)
{
    if(!string1 || !string2)
        return 0;

    return strlcmp_l(string1->str, string2->str, string1->size);
}

int string_equals(const String* string1, const String* string2)
{
    return (string_compare(string1, string2) == 0) ? 1 : 0;
}

int string_equals_ignore_case(const String* string1, const String* string2)
{
    return (string_compare_ignore_case(string1, string2) == 0) ? 1 : 0;
}

String* string_to_lowercase(String* string)
{
    if(!string)
        return NULL;

    for(size_t i = 0; i < string->size; ++i)
        string->str[i] = tolower(string->str[i]);

    return string;
}

String* string_to_uppercase(String* string)
{
    if(!string)
        return NULL;

    for(size_t i = 0; i < string->size; ++i)
        string->str[i] = toupper(string->str[i]);

    return string;
}

void string_destroy(String** string)
{
    if(!string || !(*string))
        return;

    free((*string)->str);
    free(*string);
    *string = NULL;
}

int string_starts_with(const String* string, const String* substring)
{
    if(!string || !substring || substring->size == 0)
        return 0;

    return (strlcmp(string->str, substring->str, string->size) == 0) ? 1 : 0;
}

int string_ends_with(const String* string, const String* substring)
{
    if(!string || !substring || substring->size == 0 || string->size < substring->size)
        return 0;

    return (strlcmp(&string->str[string->size - substring->size], substring->str, substring->size) == 0) ? 1 : 0;
}

int string_index_of_char(const String* string, const char character)
{
    if(!string)
        return -1;

    const char* ptr = strchr(string->str, character);
    return (ptr != NULL) ? ptr - string->str : -1;
}

int string_index_of_char_from(const String* string, const char character, const size_t from_index)
{
    if(!string || from_index > string->size - 1)
        return -1;

    const char* ptr = strchr(&string->str[from_index], character);
    return (ptr != NULL) ? ptr - string->str : -1;
}

int string_last_index_of_char(const String* string, const char character)
{
    if(!string)
        return -1;

    const char* ptr = strrchr(string->str, character);
    return (ptr != NULL) ? ptr - string->str : -1;
}

int string_last_index_of_char_from(const String* string, const char character, const size_t from_index)
{
    if(!string || from_index > string->size - 1)
        return -1;

    const char* ptr = strrchr(&string->str[from_index], character);
    return (ptr != NULL) ? ptr - string->str : -1;
}

int string_index_of_str(const String* string, const String* substring)
{
    if(!string || !substring)
        return -1;

    const char* ptr = strstr(string->str, substring->str);
    return (ptr != NULL) ? ptr - string->str : -1;
}

int string_index_of_str_from(const String* string, const String* substring, const size_t from_index)
{
    if(!string || !substring || string->size == 0 || from_index > string->size - 1)
        return -1;

    const char* ptr = strstr(&string->str[from_index], substring->str);
    return (ptr != NULL) ? ptr - string->str : -1;
}

int string_last_index_of_str(const String* string, const String* substring)
{
    if(!string || !substring)
        return -1;

    const char* ptr = strrstr(string->str, substring->str);
    return (ptr != NULL) ? ptr - string->str : -1;
}

int string_last_index_of_str_from(const String* string, const String* substring, const size_t from_index)
{
    if(!string || !substring || string->size == 0 || from_index > string->size - 1)
        return -1;

    const char* ptr = strrstr(&string->str[from_index], substring->str);
    return (ptr != NULL) ? ptr - string->str : -1;
}

String* string_clear(String* string)
{
    if(!string)
        return NULL;

    memset(string->str, 0, string->size);
    string->size = 0;

    return string;
}

String* string_clone(String* destination, const String* source)
{
    if(!source || destination == source)
        return NULL;

    String* temp_string;
    if(!destination)
    {
        temp_string = string_init("");
        if(!temp_string)
            return NULL;

        destination = temp_string;
    }
    else
        string_clear(destination);

    if(!string_append(destination, source))
    {
        string_destroy(&destination);
        return NULL;
    }

    return destination;
}

static String* string_replace_real(String* destination, const String* keyword, const String* substitute, const char code)
{
    const char* ptr = (code == 0) ? strstr(destination->str, keyword->str) : strrstr(destination->str, keyword->str);
    if(!ptr)
        return destination;

    const size_t new_length = destination->size - keyword->size + substitute->size;
    char* new_string = malloc(new_length + 1);
    if(!new_string)
        return NULL;

    strlcpy(new_string, destination->str, ptr - destination->str + 1);
    strlcat(new_string, substitute->str, new_length + 1);
    strlcat(new_string, ptr + keyword->size, new_length + 1);

    free(destination->str);
    destination->str = new_string;
    destination->size = new_length;

    return destination;
}

String* string_replace_first(String* destination, const String* keyword, const String* substitute)
{
    if(!destination || !keyword || !substitute)
        return NULL;

    return string_replace_real(destination, keyword, substitute, 0);
}

String* string_replace_last(String* destination, const String* keyword, const String* substitute)
{
    if(!destination || !keyword || !substitute)
        return NULL;

    return string_replace_real(destination, keyword, substitute, 1);
}

String* string_replace(String* destination, const String* keyword, const String* substitute)
{
    if(!destination || !keyword || !substitute || string_equals(keyword, substitute))
        return NULL;

     while(destination->str != string_replace_real(destination, keyword, substitute, 0)->str)
        ;

    return destination;
}

String* string_get_substring(const String* string, const size_t start_index, const size_t end_index)
{
    if(!string || string->size == 0 || end_index > string->size - 1 || start_index > string->size - 1 || end_index < start_index)
        return NULL;

    const size_t length = end_index - start_index + 1;
    char* new_str = malloc(length + 1);
    if(!new_str)
        return NULL;

    strlcpy(new_str, &string->str[start_index], length + 1);

    String* new_string = string_init("");
    if(!new_string)
    {
        free(new_str);
        return NULL;
    }

    free(new_string->str);
    new_string->str = new_str;
    new_string->size = length;

    return new_string;
}

String* string_trim(String* string)
{
    static char* whitespace_chars = " \n\r\t\f\v\0";
    if(!string)
        return NULL;

    size_t space_count_front = strspn(string->str, whitespace_chars);
    size_t space_count_back = 0;
    if(space_count_front != string->size)
    {
        while(strchr(whitespace_chars, string->str[string->size - space_count_back - 1]) != NULL)
            ++space_count_back;
    }
    
    const size_t new_length = string->size - space_count_front - space_count_back;
    char* new_str = malloc(new_length + 1);
    if(!new_str)
        return NULL;

    strlcpy(new_str, &string->str[space_count_front], new_length + 1);
    
    free(string->str);
    string->str = new_str;
    string->size = new_length;
    
    return string;
}

char* string_get_chars(const String* string)
{
    if(!str)
        return NULL;

    return string->str;
}

char* string_copy_chars(const String* string)
{
    char* str = malloc(string->size + 1);
    if(!str)
        return NULL;

    strlcpy(str, string->str, string->size + 1);

    return str;
}

StringArray* string_split(const String* string, const String* delimiters)
{
    if(!string || !delimiters)
        return NULL;
    
    StringArray* array = string_array_init();
    if(!array)
        return NULL;

    char* start_ptr = string->str + strspn(string->str, delimiters->str);
    char* end_ptr = NULL;
    if(*start_ptr == '\0')
    {
        free(array);
        return NULL;
    }

    while(1)
    {
        end_ptr = strpbrk(start_ptr, delimiters->str);
        const size_t start_index = start_ptr - string->str;
        const size_t end_index = end_ptr ? end_ptr - string->str - 1 : string->size - 1;

        String* temp_str = string_get_substring(string, start_index, end_index);
        string_array_append(array, temp_str);
        string_destroy(&temp_str);

        if(!end_ptr)
            return array;

        size_t delim_count = strspn(end_ptr, delimiters->str);
        start_ptr = end_ptr + delim_count;
    }

    return array;
}

String* string_format(const char* format, ...)
{
    if(!format)
        return NULL;

    va_list list;
    
    va_start(list, format);
    const size_t length = vsnprintf(NULL, 0, format, list);
    va_end(list);

    char* new_str = malloc(length + 1);
    if(!new_str)
        return NULL;

    va_start(list, format);
    vsnprintf(new_str, length + 1, format, list);
    va_end(list);

    String* new_string = string_init("");
    if(!new_string)
    {
        free(new_string);
        return NULL;
    }

    free(new_string->str);
    new_string->str = new_str;
    new_string->size = length;

    return new_string;
}