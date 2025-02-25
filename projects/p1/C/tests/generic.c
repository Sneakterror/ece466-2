#include <stdio.h>
#include <math.h>
// Compile with these flags
// -DTEST=<funcname> -DRETVAL=<num>

// Or define these macros as appropriate:
//#define FUNC test_0
//#define RETVAL 0

double TEST();

#ifndef RETVAL
#define RETVAL 0.0
#endif

int compare(double a, double b, double epsilon) {
  return (a - b) < epsilon;
}

int main()
{
  float ret = TEST();
  if(!compare(ret,RETVAL,1e-3))
    {
      // error out; make will catch it as error
      printf("Failed ret=%f but should have been %f.\n",ret,RETVAL);
      return 1;
    }
  return 0;
}
