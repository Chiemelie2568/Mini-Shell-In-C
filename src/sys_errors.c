
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   // required for strerror
#include <errno.h>    // required for errno
#include "include/sys_errors.h"

void unix_error(char *msg) {
    fprintf(stderr, "[System error] failed to %s: %s\n", msg, strerror(errno));
    exit(EXIT_FAILURE);
}

void *Malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr == NULL) {
        // malloc automatically sets errno to ENOMEM on failure
        unix_error("allocate memory via malloc.\n");
    }
    return ptr;
}

int Fgets(char *str, int n, FILE *stream) {
    printf("ms> ");
    char *buffer = fgets(str, n, stream);
    if (!buffer || ferror(stdin)) {
        unix_error("read text line to buffer.\n");
        return 1;
    }
    return 0;
}













