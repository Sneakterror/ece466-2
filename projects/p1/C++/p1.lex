%{
#include <stdio.h>
#include <math.h>
#include <cstdio>
#include <list>
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/IRBuilder.h"

#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/SystemUtils.h"
#include "llvm/Support/ToolOutputFile.h"
#include "llvm/Support/FileSystem.h"

using namespace std;
using namespace llvm;
 
#include "p1.y.hpp"
%}

  //%option debug

%%

[ \t\n]         //ignore

matrix       
random       
identity     
ones         
zeros        

det          
"^T"         
"'"          
inverse      
abs          

row          
col          

sum          
prod         
mean         
min          
max          
trace        

rows         
cols         

"zero?"      

return       
if           
else         
while        
print        

to_int       
to_double    


[a-zA-Z_][a-zA-Z_0-9]* 

[0-9]+        
[0-9]+("."[0-9]*) 

"["           
"]"           
"{"           
"}"           
"("           
")"           

"="           
"*"           
"/"           
"+"           
"-"           
"."           

","           

";"           

"=="          
"!="          
"<"           
"<="          
">"           
">="          


"//".*\n      { }

.             { return ERROR; }
%%

int yywrap()
{
  return 1;
}
