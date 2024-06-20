
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "data.h"
#include "decl.h"

// Function prototypes
struct ASTnode *do_while_statement(void);

void statements(void) {
    struct ASTnode *tree;

    while (1) {
        switch (Token.token) {
            case T_PRINT:
                tree = print_statement();
                break;
            case T_INT:
                tree = var_declaration();
                break;
            case T_IDENT:
                tree = assignment_statement();
                break;
            case T_IF:
                tree = if_statement();
                break;
            case T_WHILE:
                tree = while_statement();
                break;
            case T_DO:
                tree = do_while_statement();
                break;
            case T_LBRACE:
                tree = compound_statement();
                break;
            case T_EOF:
                return;
            default:
                fatal("syntax error in statements()");
        }
        genAST(tree, NOLABEL, 0);
        freeAST(tree);
    }
}

struct ASTnode *do_while_statement(void) {
    struct ASTnode *condAST, *bodyAST;
    int Lstart, Lend;

    // Must have 'do'
    match(T_DO);

    // Create new labels for this do while loop
    Lstart = genlabel();
    Lend = genlabel();
    // Output the start label
    cglabel(Lstart);

    // Parse the compound statement
    bodyAST = compound_statement();

    // Must have 'while' '(' after the body
    match(T_WHILE);
    match(T_LPAREN);

    // Parse the condition
    condAST = binexpr(0);
    if (condAST->type != P_BOOL)
        fatal("do while: condition is not boolean");

    // Must have ')'
    match(T_RPAREN);
    match(T_SEMI); // Must have a semicolon at the end

    // Generate the code for the body
    genAST(bodyAST, NOLABEL, NOLABEL, NOLABEL);

    // Generate the code to evaluate the condition
    genAST(condAST, Lstart, NOLABEL, Lend);

    // Output the end label
    cglabel(Lend);

    return NULL;
}
