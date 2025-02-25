#include <stdio.h>

int compare(double a, double b, double epsilon) {
  return (a - b) < epsilon;
}

double test_9(double a, double b, double c, double d);

double test_9_tester(double a, double b, double c, double d)
{
  return a*d - b*c;
}

int main()
{

  for(int i=0; i<100; i++)
    {
      float ret = test_9(i,i+2,i*2,i/3);
      float sol = test_9_tester(i,i+2,i*2,i/3);
      if ( !compare(ret,sol,0.0001) ) {
	printf("test_9(%d) should be %f, but got %f.\n",i,sol,ret);
	return 1;
      }
    }
    
  return 0;
}



