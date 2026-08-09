
#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>
#include "include/token.h"
#include "include/ast.h"

void printAST(Token *token, int *current);
static void print(Expr *root, int indent);

Expr *parse_command(Token *token, int *current);
static Expr *logical(Token *token, int *current);
static Expr *pipeline(Token *token, int *current);
static Expr *primaryCommand(Token *token, int *current);
static Expr *commandPart(Token *token, int *current);
static bool match(Token *token, int *current, int count, ...);
static TokenType previous(Token *token, int current);
static bool is_at_end(Token *token, int current);
static int advance(int *current);

#endif

