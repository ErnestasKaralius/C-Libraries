#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#if __WIN32
    #define DIR_SEPERATOR "\\"
#else
    #define DIR_SEPERATOR "/"
#endif

int strlcmp(const char* string1, const char* string2, const size_t n)
{
    if(!string1 || !string2)
        return 0;

    size_t i = 0;
    while(string1[i] != '\0' && string2[i] != '\0' && i < n)
    {
        if(string1[i] != string2[i])
            return string1[i] - string2[i]; 
        ++i;
    }

    if((string1[i] == '\0' || string2[i] == '\0') && i != n)
        return strlen(&string1[i]) - strlen(&string2[i]);

    return 0;
}

int strlcmp_l(const char* string1, const char* string2, const size_t n)
{
    if(!string1 || !string2)
        return 0;

    size_t i = 0;
    while(string1[i] != '\0' && string2[i] != '\0' && i < n)
    {
        char lower1 = tolower(string1[i]);
        char lower2 = tolower(string2[i]);
        if(lower1 != lower2)
            return lower1 - lower2; 
        ++i;
    }

    if((string1[i] == '\0' || string2[i] == '\0') && i != n)
        return strlen(&string1[i]) - strlen(&string2[i]);

    return 0;
}

size_t strlcpy(char* destination, const char* source, const size_t dest_size)
{
    if(!destination || !source || dest_size == 0)
        return 0;

    size_t i = 0;
    while(source[i] != '\0' && i < dest_size)
    {
        destination[i] = source[i];
        ++i;
    }

    destination[(i == dest_size) ? i - 1 : i] = '\0';

	return i;
}

size_t strlcat(char* destination, const char* source, const size_t dest_size)
{
    if(!destination || !source || dest_size == 0)
        return 0;

    size_t dest_length = strlen(destination);
    if(dest_length == dest_size - 1)
        return 0;

    size_t i = dest_length;
    while(source[i - dest_length] != '\0' && i < dest_size)
    {
        destination[i] = source[i - dest_length];
        ++i;
    }

    destination[(i == dest_size) ? i - 1 : i] = '\0';

    return i - dest_length;
}

char* strrstr(const char* haystack, const char* needle)
{
    if(!haystack || !needle)
        return NULL;

    char* string;
    char* temp = strstr(haystack, needle);
    size_t needle_len = strlen(needle);

    while(temp)
    {
        string = temp;
        temp = strstr(string + needle_len, needle);
    }

    return string;
}

char* create_path(const char* current_path, const char* new_entry, const size_t max_len)
{
    if(!current_path || !new_entry || max_len == 0)
        return NULL;

    if(strlen(current_path) + strlen(new_entry) + strlen(DIR_SEPERATOR) > max_len - 1)
        return NULL;

    char* path = calloc(max_len, sizeof(char));
    if(!path)
        return NULL;

    strlcpy(path, current_path, max_len);
    strlcat(path, DIR_SEPERATOR, max_len);
    strlcat(path, new_entry, max_len);

    return path;
}