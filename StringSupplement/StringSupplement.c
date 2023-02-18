#include <stdlib.h>
#include <string.h>

#if __WIN32
    #define DIR_SEPERATOR "\\"
#else
    #define DIR_SEPERATOR "/"
#endif

char* strskw(const char* str, const char* keyword, const char* substitute, const size_t max_len)
{
    if(!str || !keyword || !substitute || max_len == 0)
        return NULL;

    char* keyword_ptr = strstr(str, keyword);
    if(!keyword_ptr)
        return NULL;

    size_t base_len = keyword_ptr - str;
    if(base_len + strlen(substitute) >= max_len)
        return NULL;

    char* new_str = calloc(max_len, sizeof(char));
    if(!new_str)
        return NULL;

    strncpy(new_str, str, base_len);
    strncat(new_str, substitute, max_len - 1);
    strncat(new_str, keyword_ptr + strlen(keyword), max_len - 1);

    return new_str;
}

char* strikw(const char* str, const char* keyword, const char* insert, size_t max_len)
{
    if(!str || !keyword || !insert || max_len == 0)
        return NULL;

    char* keyword_ptr = strstr(str, keyword);
    if(!keyword_ptr)
        return NULL;

    size_t base_len = keyword_ptr - str + strlen(keyword);
    if(strlen(str) + strlen(insert) >= max_len)
        return NULL;

    char* new_str = calloc(max_len, sizeof(char));
    if(!new_str)
        return NULL;

    strncpy(new_str, str, base_len);
    strncat(new_str, insert, max_len - 1);
    strncat(new_str, str + base_len, max_len - 1);

    return new_str;
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

    strncpy(path, current_path, max_len - 1);
    strncat(path, DIR_SEPERATOR, max_len - 1);
    strncat(path, new_entry, max_len - 1);

    return path;
}
