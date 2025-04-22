%{
#include <cstdio>
#include <list>
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Bitcode/BitcodeWriter.h"

using namespace llvm;

static LLVMContext TheContext;
static IRBuilder<> Builder(TheContext);
static Module *TheModule;
static Value* regs[8];

using namespace std;

extern FILE *yyin;
int yylex();
void yyerror(const char*);

extern "C" {
  int yyparse();
}

template<typename ... Args>
std::string format(const std::string& format, Args ... args) {
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
    if (size <= 0) throw std::runtime_error("Error during formatting.");
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1);
}

int getReg() {
  static int cnt = 8;
  return cnt++;
}
%}

%verbose
%define parse.trace

%union {
  int reg;
  int imm;
  void* val;  // using void* instead of Value*
}

%token <reg> REG ARG
%token <imm> IMMEDIATE
%token ASSIGN SEMI PLUS MINUS LPAREN RPAREN LBRACKET RBRACKET RETURN

%type <val> expr

%left PLUS MINUS

%%

program:
    REG ASSIGN expr SEMI {
        regs[$1] = static_cast<Value*>($3);
    }
  | program REG ASSIGN expr SEMI {
        regs[$2] = static_cast<Value*>($4);
    }
  | program RETURN REG SEMI {
        Builder.CreateRet(regs[$3]);
        return 0;
    }
;

expr:
    IMMEDIATE { $$ = Builder.getInt32($1); }
  | REG       { $$ = regs[$1]; }
  | ARG       {
        Function *F = Builder.GetInsertBlock()->getParent();
        $$ = F->getArg($1);
    }
  | expr PLUS expr  {
        $$ = Builder.CreateAdd(static_cast<Value*>($1), static_cast<Value*>($3));
    }
  | expr MINUS expr {
        $$ = Builder.CreateSub(static_cast<Value*>($1), static_cast<Value*>($3));
    }
  | MINUS expr {
        $$ = Builder.CreateNeg(static_cast<Value*>($2));
    }
  | LPAREN expr RPAREN {
        $$ = $2;
    }
  | LBRACKET expr RBRACKET {
        Value *ptr = Builder.CreateIntToPtr(static_cast<Value*>($2), PointerType::get(Builder.getInt32Ty(), 0));
        $$ = Builder.CreateLoad(Builder.getInt32Ty(), ptr);
    }
;

%%

void yyerror(const char* msg) {
  printf("%s", msg);
}

int main(int argc, char *argv[]) {
  yydebug = 0;
  yyin = stdin;

  TheModule = new Module("Tutorial3", TheContext);
  Type *i32 = Builder.getInt32Ty();
  std::vector<Type*> args(4, i32);
  FunctionType *FT = FunctionType::get(i32, args, false);
  Function *F = Function::Create(FT, Function::ExternalLinkage, "myfunction", TheModule);
  BasicBlock *BB = BasicBlock::Create(TheContext, "entry", F);
  Builder.SetInsertPoint(BB);

  for (int i = 0; i < 8; ++i)
    regs[i] = Builder.getInt32(0);

  if (yyparse() == 0) {
    std::error_code EC;
    raw_fd_ostream OS("main.bc", EC, sys::fs::OF_None);
    WriteBitcodeToFile(*TheModule, OS);
    TheModule->print(errs(), nullptr);
  } else {
    printf("There was a problem! Read error messages above.\n");
  }

  return 0;
}
