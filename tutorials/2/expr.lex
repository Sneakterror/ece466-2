%{
#include <stdio.h>
#include <iostream>
#include <math.h>

#define print quiet

void quiet(const char *, ...) {
}
%}

%option noyywrap

%% // begin tokens

[ \t\n]      { /* ignore whitespace */ }

[Rr][0-7]    { printf("REG: %s\n", yytext); }

[0-9]+       { printf("IMMEDIATE: %s\n", yytext); }

"="          { printf("ASSIGN\n"); }
";"          { printf("SEMI\n"); }
"("          { printf("LPAREN\n"); }
")"          { printf("RPAREN\n"); }
"["          { printf("LBRACKET\n"); }
"]"          { printf("RBRACKET\n"); }
"-"          { printf("MINUS\n"); }
"+"          { printf("PLUS\n"); }

\/\/[^\n]*   { printf("COMMENT\n"); }

// Catch-all for any invalid/unrecognized character:
.            { printf("ERROR: invalid character '%s'\n", yytext); }

%% // end tokens

#ifdef SCANNER_ONLY

int main(int argc, char *argv[])
{
  yylex();
  return 0;
}

#endif
