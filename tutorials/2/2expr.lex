%{
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "expr.y.hpp"

#define print quiet
void quiet(const char *, ...) {}
%}

%option noyywrap

%% // begin tokens

[ \t\n]          { /* skip whitespace */ }

[Rr][0-7]        { yylval.reg = atoi(yytext + 1); return REG; }

[0-9]+           { yylval.imm = atoi(yytext); return IMMEDIATE; }

[Aa][0-3]        { yylval.reg = yytext[1] - '0'; return ARG; }

[Rr][Ee][Tt][Uu][Rr][Nn]   { return RETURN; }

"="              { return ASSIGN; }
";"              { return SEMI; }
"+"              { return PLUS; }
"-"              { return MINUS; }
"("              { return LPAREN; }
")"              { return RPAREN; }
"["              { return LBRACKET; }
"]"              { return RBRACKET; }


"//"[^\n]*       { /* skip comment */ }

.                { printf("ERROR: invalid character '%s'\n", yytext); }

%% // end tokens

#ifdef SCANNER_ONLY
int main(int argc, char *argv[]) {
  yylex();
  return 0;
}
#endif
