#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

const int Lx=1024;
const double p=0.5;

const int Q=2;

//--------------------- Clase LatticeGas ------------
class LatticeGas{
private:
  int V[Q]; //V[i] i=0 (derecha) i=1 (izquierda)
  double f[Lx][Q],fnew[Lx][Q]; // n[ix][i]
public:
  LatticeGas(void);
  void Borrese(void);
  void Inicie(int N,double mu,double sigma);
  void Show(void);
  void GrafiqueRho(void);
  void Colisione(void);
  void Adveccione(void);
  double rho(int ix);
  double Varianza(void);
};
LatticeGas::LatticeGas(void){
  V[0]=1;  V[1]=-1;
}
void LatticeGas::Borrese(void){
  for(int ix=0;ix<Lx;ix++)
    for(int i=0;i<Q;i++)
      f[ix][i]=fnew[ix][i]=0;
}
void LatticeGas::Inicie(int N,double mu,double sigma){
  for(int ix=0;ix<Lx;ix++){
    double rho=(N/(sigma*sqrt(2*M_PI)))*exp(-0.5*pow((ix-mu)/sigma,2.0));
    for(int i=0;i<Q;i++)
      f[ix][i]=rho/Q;
  }
}
void LatticeGas::Show(void){
	
  for(int i=0;i<Q;i++){
    for(int ix=0;ix<Lx;ix++){
      cout<<f[ix][i];
			}
    cout<<endl;
  }
  cout<<endl;
}
double LatticeGas::rho(int ix){
  double suma; int ii;
	for(ii=0, suma=0; ii<Q; ii++){
		suma+=f[ix][ii];
	}
	return suma;
}
void LatticeGas::GrafiqueRho(void){
  for(int ix=0;ix<Lx;ix++)
    cout<<ix<<" "<<rho(ix)<<endl;
}
void LatticeGas::Colisione(void){
	int ix, ii, jj;
  for(int ix=0;ix<Lx;ix++){//para cada celda
		for(ii=0; ii<Q; ii++){ //Direccion
			jj = (ii+1)%Q;
			fnew[ix][ii] = f[ix][ii]+(1-p)*(f[ix][jj]-f[ix][ii]);
		}    
  }
}
void LatticeGas::Adveccione(void){
  for(int ix=0;ix<Lx;ix++)
    for(int ii=0;ii<Q;ii++)
      f[(ix+V[ii]+Lx)%Lx][ii]=fnew[ix][ii];
}
double LatticeGas::Varianza(void){
  int ix; double N,Xprom,Sigma2;
  //Calcular N
  for(N=0,ix=0;ix<Lx;ix++)
    N+=rho(ix);
  //Calcular Xprom
  for(Xprom=0,ix=0;ix<Lx;ix++)
    Xprom+=ix*rho(ix);
  Xprom/=N;
  //Calcular Sigma2
  for(Sigma2=0,ix=0;ix<Lx;ix++)
    Sigma2+=pow(ix-Xprom,2.0)*rho(ix);
  Sigma2/=(N-1);
  
  return Sigma2;
}

void Grafica(void){
  cout<<"set term pdf"<<endl; 
  cout<<"set out 'B1D.pdf'"<<endl;
	cout<<"set title 'Varianza en 2D'"<<endl;
  cout<<"set ylabel 'Varianza'"<<endl;
	cout<<"set xlabel 't'"<<endl;
	cout<<"set autoscale"<<endl;
	cout<<"set key"<<endl;
	cout<<"set font ',7'"<<endl;
	cout<<"plot 'B_1D.txt' u 1:2 w l"<<endl;
	//cout<<"fit gauss(x) 'HistoHV.txt' via a, sigma, mu"<<endl;
	//cout<<"plot 'HistoHV.txt' u 1:2, gauss(x)"<<endl;
}

//---------------------  Programa Principal ------------

int main(void){
  LatticeGas Difusion;
  int N=400; double mu=Lx/2, sigma=Lx/8;
  int t, tmax=400;

	ofstream B_1D;
  	B_1D.open ("B_1D.txt");

  Difusion.Borrese();
  Difusion.Inicie(N,mu,sigma);
  for(t=0;t<tmax;t++){
    B_1D<<t<<" "<<Difusion.Varianza()<<endl;
    Difusion.Colisione();
    Difusion.Adveccione();
  }
  //Difusion.GrafiqueRho();
	B_1D.close();
	Grafica();
  return 0;
}
