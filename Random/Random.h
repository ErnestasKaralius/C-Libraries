#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

int rand_int(const int low, const int high);
double rand_float(const int low, const int high);
char rand_char();
char* rand_str(const size_t length);

#endif // RANDOM_H_INCLUDED
