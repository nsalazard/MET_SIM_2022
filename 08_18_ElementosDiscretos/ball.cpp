#include <cmath>
#include <iostream>

using namespace std;
//Constantes globales
const double g = 9.8;
//Declaración de las clases
class Cuerpo;
//---- Clase Cuerpo----
class Cuerpo{
	private:
		double x,y,Vx,Vy,Fx,Fy,m,R;
	public:
		void Inicie(double x0,double y0,double Vx0,double Vy0,double m0,double R0);
void Fuerza(void);
void Muevase(double dt);
double Getx(void){return x;};
double Gety(void){return y;};
};
void Cuerpo::Inicie(double x0,double y0,double Vx0,double Vy0,double m0,double R0){
	x = x0; y = y0; Vx = Vx0; Vy = Vy0; m = m0; R=R0;
}
void Cuerpo::Fuerza(){
	Fx = 0; Fy = -m*g;
}
void Cuerpo::Muevase(double dt){
	x += Vx * dt;	Vx += Fx/m * dt;
	y += Vy * dt;	Vy += Fy/m * dt;
}
// ------- Global Functions--------
int main(void) {
	Cuerpo Balon;
	double t, dt= 0.1;
	//Balon.Inicie(x0,y0,Vx0,Vy0,m0,R0);
	Balon.Inicie(0,0,20,15,0.453,0.15);
	for(t=0; t<3.5; t+=dt){
		cout << Balon.Getx() << "\t" << Balon.Gety() << endl;
		Balon.Fuerza();
		Balon.Muevase(dt);
	}
	

 return 0;
}
