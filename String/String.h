#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#define size_t unsigned long

typedef struct String {
    size_t size;
    char* str;
} String;

typedef struct StringArray {
    String** strings;
    size_t size;
} StringArray;

StringArray* string_array_init();
StringArray* string_array_append(StringArray* array, const String* string);
StringArray* string_array_remove(StringArray* array, const size_t index);

int string_array_index_of(const StringArray* array, const String* string);
void string_array_destroy(StringArray** array);

String* string_init(const char* str);
String* string_clone(String* destination, const String* source);
String* string_format(const char* format, ...);

String* string_get_substring(const String* string, const size_t start_index, const size_t end_index);
StringArray* string_split(const String* string, const String* delimiters);
String* string_trim(String* string);

String* string_append(String* destination, const String* source);
String* string_prepend(String* destination, const String* source);
String* string_concat(const String* string1, const String* string2);

String* string_replace(String* destination, const String* keyword, const String* substitute);
String* string_replace_first(String* destination, const String* keyword, const String* substitute);
String* string_replace_last(String* destination, const String* keyword, const String* substitute);

String* string_to_lowercase(String* string);
String* string_to_uppercase(String* string);
String* string_clear(String* string);

int string_compare(const String* string1, const String* string2);
int string_compare_ignore_case(const String* string1, const String* string2);
int string_equals(const String* string1, const String* string2);
int string_equals_ignore_case(const String* string1, const String* string2);

int string_contains(const String* string, const String* substring);
int string_is_empty(const String* string);

int string_starts_with(const String* string, const String* substring);
int string_ends_with(const String* string, const String* substring);

int string_index_of_char(const String* string, const char character);
int string_index_of_char_from(const String* string, const char character, const size_t from_index);

int string_last_index_of_char(const String* string, const char character);
int string_last_index_of_char_from(const String* string, const char character, const size_t from_index);

int string_index_of_str(const String* string, const String* substring);
int string_index_of_str_from(const String* string, const String* substring, const size_t from_index);

int string_last_index_of_str(const String* string, const String* substring);
int string_last_index_of_str_from(const String* string, const String* substring, const size_t from_index);

size_t string_get_length(const String* string);
char string_char_at(const String* string, const size_t index);
char* string_get_chars(const String* string);
char* string_copy_chars(const String* string);

void string_destroy(String** string);

#endif // STRING_H_INCLUDED
