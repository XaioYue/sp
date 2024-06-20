
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "defs.h"
#include "data.h"
#include "decl.h"

static int chrpos(char *s, int c) {
    char *p;
    p = strchr(s, c);
    return (p ? p - s : -1);
}

int next(void) {
    int c;

    // Skip whitespace
    while ((c = nextch()) != EOF && isspace(c))
        ;
    if (c == EOF)
        return (Token.token = T_EOF);

    switch (c) {
        case '+':
            return (Token.token = T_PLUS);
        case '-':
            return (Token.token = T_MINUS);
        case '*':
            return (Token.token = T_STAR);
        case '/':
            return (Token.token = T_SLASH);
        case '=':
            if ((c = nextch()) == '=')
                return (Token.token = T_EQ);
            putback(c);
            return (Token.token = T_ASSIGN);
        case '!':
            if ((c = nextch()) == '=')
                return (Token.token = T_NE);
            fatalc("unrecognized character", c);
        case '<':
            if ((c = nextch()) == '=')
                return (Token.token = T_LE);
            putback(c);
            return (Token.token = T_LT);
        case '>':
            if ((c = nextch()) == '=')
                return (Token.token = T_GE);
            putback(c);
            return (Token.token = T_GT);
        case ';':
            return (Token.token = T_SEMI);
        case '(':
            return (Token.token = T_LPAREN);
        case ')':
            return (Token.token = T_RPAREN);
        case '{':
            return (Token.token = T_LBRACE);
        case '}':
            return (Token.token = T_RBRACE);
    }

    if (isdigit(c)) {
        Token.intvalue = scanint(c);
        Token.token = T_INTLIT;
        return Token.token;
    }

    if (isalpha(c)) {
        scanident(c, Text);
        if (!strcmp(Text, "print"))
            return (Token.token = T_PRINT);
        if (!strcmp(Text, "int"))
            return (Token.token = T_INT);
        if (!strcmp(Text, "if"))
            return (Token.token = T_IF);
        if (!strcmp(Text, "else"))
            return (Token.token = T_ELSE);
        if (!strcmp(Text, "while"))
            return (Token.token = T_WHILE);
        if (!strcmp(Text, "do"))
            return (Token.token = T_DO);
        return (Token.token = T_IDENT);
    }

    fatalc("unrecognized character", c);
    return (Token.token = T_EOF);
}
