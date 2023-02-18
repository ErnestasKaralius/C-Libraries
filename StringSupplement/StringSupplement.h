#ifndef STRINGSUPPLEMENT_H_INCLUDED
#define STRINGSUPPLEMENT_H_INCLUDED

#include <stdio.h>

char* strskw(const char* str, const char* keyword, const char* substitute, const size_t max_len);
char* strikw(const char* str, const char* keyword, const char* insert, size_t max_len);
char* strrstr(const char* haystack, const char* needle);
char* create_path(const char* current_path, const char* new_entry, const size_t max_len);

#endif // STRINGSUPPLEMENT_H_INCLUDED
