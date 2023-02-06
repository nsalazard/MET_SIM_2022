#include <cmath>
#include <iostream>

double f (double x);
double Simpson (double a, double b, int n);

const double ErrorMax = 1e-7;

int main(void) {
	 std::cout.precision(16); std::cout.setf(std::ios::scientific);

	double x; 
	double a = 2, b = M_PI/2;
	int n = 50;
	
double cero = Simpson(a,b,n);
std::cout << "La integral es: " << cero << std::endl;

}

double f (double x){
	return cos(x);
}

double Simpson (double a, double b, int n)
{
	double t,h,suma;
	int i;
	n *=2;
	h = (b-a)/n;
	for(suma=0,i=0;i<=n;i++){
		t= a+i*h;
		if(i==0 || i==n){ // Primero o último
			suma+= f(t);
		}
		else if(i%2 == 0){ // Par
			suma += 2*f(t);
		}
		else{ // Impar
			suma += 4*f(t);
		}
	}
	return suma*h/3;
}
