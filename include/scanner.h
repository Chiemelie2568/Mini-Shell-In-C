
#ifndef SCANNER_H
#define SCANNER_H

#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "include/token.h"

static bool match(char *input, char c, int *current, int length);
static Token *scan_token(char *input, int length, int *current);
int scanner(char *input, Token *token_list[]);
static Token *create_token(TokenType type, char *value);
static int advance(int *current);
static bool is_at_end(int current, int length);
static int istoken(char c);
static int read_string(char *input, int *current, int length, char expect);
static Token *token_word(char *input, int *current, int length);

#endif

