
#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>

typedef enum {
    WORD,              // any text like commands and file paths

    PIPE,              // |
    REDIRECT_IN,       // <
    REDIRECT_OUT,      // >
    APPEND,            // >>
    HEREDOC,           // <<

    AND,               // &&
    OR,                // ||

    BACKGROUND,        // &

    OPEN_BRACKET,      // (
    CLOSE_BRACKET,     // )

    END
} TokenType;

typedef struct {
    TokenType token;
    char *value;
} Token;

#endif
