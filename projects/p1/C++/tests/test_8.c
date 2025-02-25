
#include <stdio.h>

int compare(float a, float b, float epsilon) {
  return (a - b) < epsilon;
}

double test_8(double a, double b, double c, double d,
	     double e, double f, double g, double h);

double test_8_tester(double a, double b, double c, double d,
		    double e, double f, double g, double h)
{
  return b + f;
}

int main()
{

  for(int i=0; i<100; i++)
    {
      float ret = test_8(i,i+2,i*2,i*3,i,i+1,0,1);
      float sol = test_8_tester(i,i+2,i*2,i*3,i,i+1,0,1);
      if ( !compare(ret,sol,0.0001) ) {
	printf("test_7(%d) should be %f, but got %f.\n",i,sol,ret);
	return 1;
      }

    }
    
  return 0;
}



