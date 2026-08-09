
#ifndef SYS_ERRORS_H
#define SYS_ERRORS_H

#include <stddef.h>

// Wrapper function declarations
void *Malloc(size_t size);
int Fgets(char *str, int n, FILE *stream);
void unix_error(char *msg);

#endif

