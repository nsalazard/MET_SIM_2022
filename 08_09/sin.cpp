#include <cmath>
#include <iostream>

double f (double x);

int main(void) {

  for (double x = 0.1; x <= 10; x += 0.1) {
    std::cout << x << "\t" << f(x) << "\n";
  }

  return 0;
}

double f (double x){
	return sin(x)/x;
}
