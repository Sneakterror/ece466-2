%{
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "expr.y.hpp"

#define print quiet

void quiet(const char *, ...) {
}
%}

%option noyywrap

%% // begin tokens

[Rr][0-7]      { yylval.reg = atoi(yytext + 1); return REG; }
[0-9]+         { yylval.reg = atoi(yytext); return IMMEDIATE; }

"="            { return ASSIGN; }
";"            { return SEMI; }
"+"            { return PLUS; }
"-"            { return MINUS; }
"("            { return LPAREN; }
")"            { return RPAREN; }
"["            { return LBRACKET; }
"]"            { return RBRACKET; }

[ \t\n]+       { /* ignore whitespace */ }

"//"[^\n]*     { /* skip comments */ }

.              { printf("ERROR: invalid character '%s'\n", yytext); }

%% // end tokens

#ifdef SCANNER_ONLY

int main(int argc, char *argv[])
{
  yylex();
  return 0;
}

#endif
