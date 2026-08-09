
#include <stdlib.h>
#include "include/ast.h"
#include "include/sys_errors.h"

Expr *new_expr(ExprType type) {
    Expr *new = (Expr *)Malloc(sizeof(Expr));
    new->type = type;
    return new;
}

Expr *Grouping(Expr *expression) {
    Expr *new = new_expr(EXPR_GROUPING);
    new->as.grouping.expression = expression;
    return new;
}

Expr *Command(char **argv, int argc, Redirect *redirect, int redirect_count) {
    Expr *new = new_expr(EXPR_COMMAND);
    new->as.command.argv = argv;
    new->as.command.argc = argc;
    new->as.command.redirect = redirect;
    new->as.command.redirect_count = redirect_count;
    return new;
}

Expr *PipeLine(Expr *left, Expr *right) {
    Expr *new = new_expr(EXPR_PIPELINING);
    new->as.pipeline.left = left;
    new->as.pipeline.right = right;
    return new;
}

Expr *Logical(Expr *left, Expr *right, TokenType op) {
    Expr *new = new_expr(EXPR_LOGICAL);
    new->as.logical.left = left;
    new->as.logical.right = right;
    new->as.logical.op = op;
    return new;
}

