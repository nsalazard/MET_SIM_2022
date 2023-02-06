#include <cmath>
#include <iostream>

double f (double x);

const double ErrorMax = 1e-7;

int main(void) {
  std::cout.precision(16); std::cout.setf(std::ios::scientific);

	double x; 
	double a = 2, b = 4,m,fa, fm;
	fa = f(a);
	
  while (b-a > ErrorMax){
    m = (b+a)/2;
    fm = f(m);
    if (f(a)*f(m)  > 0){
      a = m;
      fa = fm;
		}
	else{
		b=m;
  }
  }
  std::cout << "El cero es: " << (a+b)/2 << std::endl;
  std::cout << f((a+b)/2)  << std::endl;
}

double f (double x){
	return sin(x)/x;
 }
