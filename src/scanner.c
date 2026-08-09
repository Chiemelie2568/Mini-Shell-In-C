
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "include/sys_errors.h"
#include "include/scanner.h"
#include "include/token.h"


/* Write the scan token function here. */
static Token *scan_token(char *input, int length, int *current) {
    char c = input[*current];
    Token *token = NULL;

    switch (c) {
        case '|':
            token = create_token(match(input, '|', current, length) ? OR : PIPE, "\0");
            break;
        case '<':
            token = create_token(match(input, '<', current, length) ? HEREDOC : REDIRECT_IN, "\0");
            break;
        case '>':
            token = create_token(match(input, '>', current, length) ? APPEND : REDIRECT_OUT, "\0");
            break;
        case '&':
            token = create_token(match(input, '&', current, length) ? AND : BACKGROUND, "\0");
            break;
        case '(':
            token = create_token(OPEN_BRACKET, "\0");
            advance(current);
            break;
        case ')':
            token = create_token(CLOSE_BRACKET, "\0");
            advance(current);
            break;
        case '\n':
        case '\t':
        case '\v':
        case '\r':
        case '\f':
        case ' ':
            while (!is_at_end(*current, length) && isspace(input[*current]))
                advance(current);
            break;
        default:
            if (input[*current] != '\0')
                token = token_word(input, current, length);
            else 
                advance(current);
            break;
    }
    return token;
}

/* Orchestrator of the scanned tokens */
int scanner(char *input, Token *token_list[]) {

    int current, i, length;
    Token *token = NULL;

    current = i = 0;
    length = strlen(input);

    while (!is_at_end(current, length)) {
        token = scan_token(input, length, &current);
        if (token)
            token_list[i++] = token;
    }

    token_list[i] = create_token(END, "\0");
    return i;  // returns the number of tokens.
}

static bool match(char *input, char c, int *current, int length) {
    if (is_at_end(advance(current), length)) return false;
    if (input[*current] != c) return false;
    advance(current);
    return true;
}


static Token *create_token(TokenType type, char *value) {
    Token *token = (Token *)Malloc(sizeof(Token));
    token->token = type;
    token->value = value;
    return token;
}

/********************************************************************
 * Miscelanous Functions
 ********************************************************************/
// moves to the next character;
static int advance(int *current) {
    return ++(*current);
}

static bool is_at_end(int current, int length) {
    return current > length;
}

static Token *token_word(char *input, int *current, int length) {
    int start = *current;
    int len = 0;
    char *dest = NULL;

    char c = input[*current];

    while (!is_at_end(*current, length) && !istoken(c)) {
        if (c == '"' || c == '\'') {
            // read a string
            advance(current);
            len += read_string(input, current, length, c);
        }
        ++len;
        advance(current);
        c = input[*current];
    }
    if (!len) return NULL;  // case where no word was read.

    dest = (char *)Malloc((++len) * sizeof(char));
    dest[len] = '\0';
    strncpy(dest, input + start, len-1);

    return create_token(WORD, dest);
}

static int read_string(char *input, int *current, int length, char expect) {
    // read qouted strings.
    int len = 0;
    while (!is_at_end(*current, length) && input[*current] != expect) {
        advance(current);
        len++;
    }

    if (input[*current] != expect) {
        fprintf(stderr, "Expected closing %c, one wasn't provided\n", expect);
        exit(EXIT_FAILURE);
    }
    
    return ++len;
}

static int istoken(char c) {
    // This function deals with 
    bool ret = false;
    switch(c) {
        case '|':
        case '<':
        case '>':
        case '&':
        case ')':
        case '(':
            ret = true;
            break;
        default:
            if (isspace(c))
                ret = true;
            break;
    }
    return ret;
}

