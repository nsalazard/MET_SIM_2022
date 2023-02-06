#include <cmath>
#include <iostream>

double f (double x);
double CerosPorBiseccion (double a, double b);

const double ErrorMax = 1e-7;

int main(void) {
	 std::cout.precision(16); std::cout.setf(std::ios::scientific);

	double x; 
	double a = 2, b = 4;
	
double cero = CerosPorBiseccion(a,b);
std::cout << "El cero es: " << cero << std::endl;
std::cout << f(cero)  << std::endl;
}

double f (double x){
	return sin(x)/x;
}

double CerosPorBiseccion (double a, double b){
	double x, m,fa, fm;
	fa = f(a);
	
while (b-a > ErrorMax){
	m = (b+a)/2;
	fm = f(m);
	if (fa*fm  > 0){
		a = m; // Correr a hasta m
		fa = fm;
		}
	else
		b=m; //Correr b hasta m
		
}
return (a+b)/2;
}
