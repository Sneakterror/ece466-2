%{
#include <math.h>
#include "calc.y.h"
%}


%%

[ \t]          ;
\n             return NEWLINE;

"-"            { return HYPHEN; }
"one"          { return ONE; }
"two"          { return TWO; }
"three"        { return THREE; }
"four"         { return FOUR; }
"five"         { return FIVE; }
"six"          { return SIX; }
"seven"        { return SEVEN; }
"eight"        { return EIGHT; }
"nine"         { return NINE; }
"hundred"      { return HUNDRED; }
"twenty"       { return TWENTY; }
"thirty"       { return THIRTY; }
"forty"        { return FORTY; }
"fifty"        { return FIFTY; }
"sixty"        { return SIXTY; }
"seventy"      { return SEVENTY; }
"eighty"       { return EIGHTY; }
"ninety"       { return NINETY; }
"zero"  return ZERO;

%%
