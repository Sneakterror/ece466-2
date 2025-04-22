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

[ \t\n]        { /* Ignore whitespace */ }

[Rr][0-7]      { printf("REG: %s\n", yytext); }             // ✔️ uses yytext
[0-9]+         { printf("IMMEDIATE: %s\n", yytext); }      // ✔️ uses yytext

"="            { printf("ASSIGN\n"); }
";"            { printf("SEMI\n"); }
","            { printf("COMMA\n"); }

"("            { printf("LPAREN\n"); }
")"            { printf("RPAREN\n"); }
"["            { printf("LBRACKET\n"); }
"]"            { printf("RBRACKET\n"); }

"+"            { printf("PLUS: %s\n", yytext); }           // ✔️ uses yytext
"-"            { printf("MINUS\n"); }
"*"            { printf("STAR\n"); }
"/"            { printf("SLASH\n"); }


"//"[^\n]*    { printf("COMMENT\n"); }

.            { printf("ERROR: invalid character '%s'\n", yytext); }

%% // end tokens

#ifdef SCANNER_ONLY

int main(int argc, char *argv[])
{
  yylex();
  return 0;
}

#endif
