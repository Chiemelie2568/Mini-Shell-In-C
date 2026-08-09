
#ifndef AST_H
#define AST_H

#include "include/token.h"

// Redirect is not an expression cause it can have many form.

typedef struct {
    TokenType token;
    char *target;
} Redirect;
// End of redirection

typedef struct {
    Expr *left;
    Expr *right;

    TokenType op;
} LogicalExpr;
// End of logical

typedef struct {
    Expr *left;
    Expr *right;
} PipelineExpr;

typedef struct {
    Expr *expression;
} GroupingExpr;

typedef struct {
    char **argv;
    int argc;

    Redirect *redirect;
    int redirect_count;
} CommandExpr;

typedef enum {
    EXPR_COMMAND,
    EXPR_GROUPING,
    EXPR_PIPELINING,
    EXPR_LOGICAL
} ExprType;

typedef struct Expr {
    ExprType type;

    union {
       CommandExpr command;
       GroupingExpr grouping;
       PipelineExpr pipeline;
       LogicalExpr logical;
    } as;
};


Expr *Grouping(Expr *expression);
Expr *Command(char **argv, int argc, Redirect *redirect, int redirect_count);
Expr *PipeLine(Expr *left, Expr *right);
Expr *Logical(Expr *left, Expr *right, TokenType op);


#endif

