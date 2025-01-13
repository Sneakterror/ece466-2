#include <iostream>
#include <sys/utsname.h>

int main() {
  utsname u;
  if (uname(&u) != 0)
    return 1;

  std::cout << "Hello from " << u.nodename << "!\n" ;
  return 0;
}
