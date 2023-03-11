#ifndef STRINGSUPPLEMENT_H_INCLUDED
#define STRINGSUPPLEMENT_H_INCLUDED

#define size_t unsigned long

int strlcmp(const char* string1, const char* string2, const size_t n);
int strlcmp_l(const char* string1, const char* string2, const size_t n);

size_t strlcpy(char* destination, const char* source, const size_t dest_size);
size_t strlcat(char* destination, const char* source, const size_t dest_size);

char* strrstr(const char* haystack, const char* needle);
char* create_path(const char* current_path, const char* new_entry, const size_t max_len);

#endif // STRINGSUPPLEMENT_H_INCLUDED
