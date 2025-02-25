%{
#include <stdio.h>
#include <math.h>

#include "llvm-c/Core.h"
  
#include "p1.y.h"

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
