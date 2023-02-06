#include <cmath>
#include <iostream>

using namespace std;

double f(double t, double x){
  return x;
}

void UnPasoDeEuler(double & t, double & x, double  & dt ){
	double dx = dt*f(t,x);
	x += dx;
	t += dt;
}

int main(){
  double t,x;
	double dt = 0.01;

	for(t=0, x=1; t <=2; ){
		cout << t << "\t" << x << "\t" << exp(t) << endl;

		UnPasoDeEuler(t,x,dt);
	}
	
  return 0;
}
