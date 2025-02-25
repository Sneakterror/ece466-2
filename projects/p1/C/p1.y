%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "llvm-c/Core.h"
  
// Need for parser and scanner
extern FILE *yyin;
int yylex();
void yyerror(const char*);
int yyparse();
 
// Needed for LLVM
char* funName;
LLVMModuleRef M;
LLVMBuilderRef  Builder;


%}

%union {
  int dummy;
}

/*%define parse.trace*/


%token ERROR

%token DOUBLE
%token INT
%token ID
%token SEMI COMMA
%token ASSIGN
%token LBRACKET RBRACKET
%token LPAREN RPAREN 
%token LBRACE RBRACE 

%token ABS ROWS COLS MEAN PROD SUM BLOCK ROW COL
%token MIN MAX TRACE IS_ZERO 
%token ZEROS ONES IDENTITY RANDOM MATRIX
%token DET TRANSPOSE INVERSE 

%token IF WHILE FOR ELSE RETURN PRINT

%token PLUS MINUS STAR DIV DOT
%token TO_INT TO_DOUBLE
%token CMP_EQ CMP_NE CMP_LT CMP_LTE CMP_GT CMP_GTE

%left CMP_EQ CMP_NE CMP_LT CMP_LTE CMP_GT CMP_GTE
%left PLUS MINUS
%left STAR DIV
%left TRANSPOSE

%start program

%%


program: function | program function;

function: ID LPAREN params_list_opt RPAREN LBRACE statements_opt RBRACE
;

params_list_opt:  params_list 
| %empty
;

params_list: param
| params_list COMMA param
;

param:   ID
| STAR ID
;

statements_opt: %empty
            | statements
;

statements:   statement | statements statement
;

statement:
  ID ASSIGN expr SEMI
| ID LBRACKET expr COMMA expr RBRACKET ASSIGN expr SEMI
| IF LPAREN expr RPAREN LBRACE statements_opt RBRACE ELSE LBRACE statements_opt RBRACE
| WHILE LPAREN expr RPAREN LBRACE statements_opt RBRACE
| RETURN expr SEMI
| PRINT LPAREN expr RPAREN SEMI
;

dim: LBRACKET expr COMMA expr RBRACKET
;

matrix: ONES LPAREN dim RPAREN
| ZEROS LPAREN dim RPAREN
| IDENTITY LPAREN dim RPAREN
| RANDOM LPAREN dim RPAREN
| MATRIX LPAREN dim COMMA LBRACE initializer_list RBRACE RPAREN
;

initializer_list: expr | initializer_list COMMA expr
;

expr_list_opt: expr_list | %empty
;


expr_list: expr | expr_list COMMA expr
;

expr: ID
| DOUBLE
| INT
| expr PLUS expr
| expr MINUS expr
| expr STAR expr
| expr DIV expr
| MINUS expr
| DET LPAREN expr RPAREN
| INVERSE LPAREN expr RPAREN
| ABS LPAREN expr RPAREN
| expr TRANSPOSE
| ID LBRACKET expr COMMA expr RBRACKET
| MIN LPAREN expr RPAREN
| MAX LPAREN expr RPAREN
| SUM LPAREN expr RPAREN
| MEAN LPAREN expr RPAREN
| TRACE LPAREN expr RPAREN
| ROW LPAREN expr COMMA expr RPAREN
| COL LPAREN expr COMMA expr RPAREN
| LPAREN expr RPAREN
| ID DOT ROWS
| DOT COLS
| TO_INT LPAREN expr RPAREN
| TO_DOUBLE LPAREN expr RPAREN
| ID LPAREN expr_list_opt RPAREN
| IS_ZERO LPAREN expr RPAREN
| expr CMP_EQ expr
| expr CMP_NE expr
| expr CMP_LT expr
| expr CMP_LTE expr
| expr CMP_GT expr
| expr CMP_GTE expr
| matrix
;



%%

LLVMModuleRef parseP1File(const char* InputFilename)
{
  // Figure out module name
  char *pos = strrchr(InputFilename,'/');
  const char *modName;
  if (pos)
    modName = strdup(pos+1);
  else 
    modName = strdup(InputFilename);
  pos = strchr(modName,'.');
  if (pos) *pos = 0;

  // Make Module
  M = LLVMModuleCreateWithName(modName);
  free((void*)modName);
  
  if (strcmp(InputFilename,"--")==0)
    yyin = stdin;
  else
    yyin = fopen(InputFilename,"r");

  //yydebug = 1;
  if (yyparse() != 0) {
    // errors, so discard module
    return NULL;
  } else {
    LLVMDumpModule(M);
    return M;
  }
}

void yyerror(const char* msg)
{
  printf("%s\n",msg);
}
