#include <stdio.h>
#include <math.h>

int compare(double a, double b, double epsilon) {
  return fabs(a - b) < epsilon;
}


double mytest(); // this comes form your code generator


double mytest_tester()
{
  // C implementation of your test case
  return 0.0;
}

int main()
{
  float ret = mytest();
  float sol = mytest_tester();
  if ( !compare(ret,sol,0.0001) ) {
    printf("test_mytest should be %f, but got %f.\n",sol,ret);
    return 1;
  }
    
  return 0;
}
