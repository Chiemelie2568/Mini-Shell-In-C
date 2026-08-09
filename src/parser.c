
#include "include/parser.h"

void printAST(Token *token, int *current) {
    Expr *root = parse_command(token, current);
    print(root, 0);
}

static void print(Expr *root, int indent) {
    if (!root) return;

    switch(root->type) {
        case EXPR_COMMAND:
            break;
        case EXPR_GROUPING:
            break;
        case EXPR_LOGICAL:
            if (root->as.logical.op == AND)
                printf("&&\n");
            else
                printf("||\n");
            print(root->as.logical.left);
            print(root->as.logical.right);
            break;
        case EXPR_PIPELINING:
            break;
    }
}

Expr *parse_command(Token *token, int *current) {
    return logical(token, current);
}

static Expr *logical(Token *token, int *current) {
    Expr *expr = pipeline(token, current);

    while (match(token, current, 2, AND, OR)) {
        if (!expr) {
            printf("Error printing in operator\n");
            return NULL;
        }

        TokenType op = previous(token, *current);
        Expr *right = pipeline(token, current);
        /*
         *  When the right hand side of the Logical operator is missing,
         *  you need to prompt with the '>' character and tell the user
         *  to complete the command. When it is completed, you will free all
         *  memory you created and append the need command to the old one.
         *  and start all over again.
         */
        expr = Logical(expr, right, op);
    }
    return expr;
}

static Expr *pipeline(Token *token, int *current) {
    Expr *expr = primaryCommand(token, current);

    while (match(token, current, 1, PIPE)) {
        if (!expr) {
            printf("Error printing in pipe\n");
            return NULL;
        }
        TokenType op = previous(token, *current);
        Expr *right = primaryCommand(token, current);
        /*
         *  When the right hand side of the Logical operator is missing,
         *  you need to prompt with the '>' character and tell the user
         *  to complete the command. When it is completed, you will free all
         *  memory you created and append the need command to the old one.
         *  and start all over again.
         */
        expr = PipeLine(expr, right);
    }
    return expr;
}

static Expr *primaryCommand(Token *token, int *current) {
    if (match(token, current, 1, OPEN_BRACKET)) {
        expr = command(token, current);
        /* 
         * right here you check if the current token is
         * a closing bracket if not:
         * 1. you might choose to return an error
         *    so you don't over complicate things.
         * 2. you might choose to prompt like before.
         */
        return Grouping(expr);
    }
    return commandPart(token, current);
}

static Expr *commandPart(Token *token, int *current) {

    char **argv = (char **)Malloc(9 * sizeof(char *));
    Redirect *redirect = (Redirect *)Malloc(9 * sizeof(Redirect));

    TokenType op;
    int argc = 0;
    int re_count = 0;
    int hold = *current;

    while (match(token, current, 1, WORD)) {
        argv[argc++] = token[hold++]->value;
        // build argv here.
    }

    while (match(token, current, 4, REDIRECT_IN, REDIRECT_OUT, APPEND, HEREDOC)) {
        // build redirect here.
        op = previous(token, *current);
        redirect[re_count].token = op;
        redirect[re_count++].target = token[*current].value;
        // there are some edge cases here, what if the argument to the redirect is a qouted string.
        if (token[*current].value)
            printf("print an error here and exit.\n");
        // after each redirect, check and make sure the next token if not a word.
    }

    if (argc == 0 && re_count == 0) {
        return NULL;
    }
    return Command(argv, argc, redirect, re_count);
}

static bool match(Token *token, int *current, int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i=0; i<count; i++) {
        if (!is_at_end(token, *current) && token[*current]->token == args[i]) {
            advance(current);
            return true;
        }
    }

    va_end(args);

    return false;
}

static TokenType previous(Token *token, int current) {
    return token[--current]->token;
}

static bool is_at_end(Token *token, int current) {
    return (token[current]->token == END);
}

static int advance(int *current) {
    return *(++current);
}

