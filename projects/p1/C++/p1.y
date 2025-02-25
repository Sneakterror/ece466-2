%{
#include <cstdio>
#include <list>
#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <stdexcept>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/SystemUtils.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/FileSystem.h"

using namespace llvm;
using namespace std;
 
// Need for parser and scanner
extern FILE *yyin;
int yylex();
void yyerror(const char*);
int yyparse();

// Needed for LLVM
string funName;
Module *M;
LLVMContext TheContext;
IRBuilder<> Builder(TheContext);

%}

%union {
  int dummy;
}

%define parse.trace

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

unique_ptr<Module> parseP1File(const string &InputFilename)
{
  string modName = InputFilename;
  if (modName.find_last_of('/') != string::npos)
    modName = modName.substr(modName.find_last_of('/')+1);
  if (modName.find_last_of('.') != string::npos)
    modName.resize(modName.find_last_of('.'));

  // unique_ptr will clean up after us, call destructor, etc.
  unique_ptr<Module> Mptr(new Module(modName.c_str(), TheContext));

  // set global module
  M = Mptr.get();
  
  /* this is the name of the file to generate, you can also use
     this string to figure out the name of the generated function */

  if (InputFilename == "--")
    yyin = stdin;
  else	  
    yyin = fopen(InputFilename.c_str(),"r");

  //yydebug = 1;
  if (yyparse() != 0) {
    // Dump LLVM IR to the screen for debugging
    M->print(errs(),nullptr,false,true);
    // errors, so discard module
    Mptr.reset();
  } else {

  }
  
  return Mptr;
}

void yyerror(const char* msg)
{
  printf("%s\n",msg);
}
