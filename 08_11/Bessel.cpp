#include <cmath>
#include <iostream>

double f (double x);
double Simpson (double a, double b, int n);
double Bessel(double alpha, double x);

const double ErrorMax = 1e-7;

int main(void) {
	 //std::cout.precision(16); std::cout.setf(std::ios::scientific);

	double alpha = 0, x  ; 

	for(x = 0; x <= 10; x+=0.1){
		std::cout << x << " "  << Bessel(alpha,x) << std::endl;
	}


}

double f (double alpha, double x, double t){
	return cos(alpha*t-x*sin(t));
}

double Simpson (double alpha, double x, double a, double b, int n)
{
	double t,h,suma;
	int i;
	n *=2;
	h = (b-a)/n;
	for(suma=0,i=0;i<=n;i++){
		t= a+i*h;
		if(i==0 || i==n){ // Primero o último
			suma+= f(alpha,x,t);
		}
		else if(i%2 == 0){ // Par
			suma += 2*f(alpha,x,t);
		}
		else{ // Impar
			suma += 4*f(alpha,x,t);
		}
	}
	return suma*h/3;
}

double Bessel(double alpha, double x){
	double a = 0, b = M_PI;
	int n = 50;
	return 1.0/M_PI*Simpson(alpha,x,a,b,n);
}
