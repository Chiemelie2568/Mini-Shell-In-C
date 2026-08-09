
#include <stdio.h>
#include "include/sys_errors.h"
#include "include/scanner.h"

#define MAXV 500

int main(int argc, char *argv[]) {
    char Buffer[MAXV];
    Token *token_list[MAXV];
    int num_tok = 0;

    if (argc == 0) {
        printf("That's just right %s.\n", argv[0]);
    }

    while(!Fgets(Buffer, sizeof(Buffer), stdin)) {
        printf("%s\n", Buffer);
        num_tok = scanner(Buffer, token_list);

        for (int i=0; i<=num_tok; i++) {
            printf("%u: %s\n", token_list[i]->token, token_list[i]->value);
            //printf("%u\n", token_list[i]->token);
        }
    }

}


