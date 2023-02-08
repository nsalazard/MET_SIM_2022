#include "Random64.h"
#include <cmath>

using namespace std;
const int Lx = 1024;
const double p = 0.5;
const int Q = 2;

//----------- Clase LatticeGas
class LatticeGas {
private:
  int V[Q];                  // V[i] i=0 R i=1 L
  int n[Lx][Q], nnew[Lx][Q]; // n[ix][i]
public:
  LatticeGas(void);
  void Clean(void);
  void Inicie(int N, double mu, double sigma, Crandom &ran64);
  void Show(void);
  void Colisione(Crandom &ran64);
  void Adveccione(void);
  double rho(int ix) { return n[ix][0] + n[ix][1]; };
  double Varianza(void);
  void GrafiqueRho(void);
};

//----------Implementacion---

LatticeGas::LatticeGas(void) {
  V[0] = 1;
  V[1] = -1;
}

void LatticeGas::Clean(void) {
  for (int ix = 0; ix < Lx; ix++)
    for (int ii = 0; ii < Q; ii++)
      n[ix][ii] = nnew[ix][ii] = 0;
}

void LatticeGas::Inicie(int N, double mu, double sigma, Crandom &ran64) {
  int ix, ii;
  while (N > 0) {
    ix = (int)ran64.gauss(mu, sigma); // Escoger celda al azar
    if (ix < 0) ix = 0;
    if (ix > Lx - 1) ix = Lx - 1;

    ii = (int)Q * ran64.r(); // Escoger dirección al azar
    if (n[ix][ii] == 0) {
      n[ix][ii] = 1;
      N--;
    }
  }
}

void LatticeGas::Show(void) {
  for (int ii = 0; ii < Q; ii++) {
    for (int ix = 0; ix < Lx; ix++) {
      cout << n[ix][ii];
    }
    cout << "\n";
  }
  cout << "\n";
}

void LatticeGas::Colisione(Crandom &ran64) {
  for (int ix = 0; ix < Lx; ix++) {
    if (ran64.r() > p) { // Genero un numero aleatorio. Si es menor que p volteo
      nnew[ix][0] = n[ix][1];
      nnew[ix][1] = n[ix][0];
    } else {
      nnew[ix][0] = n[ix][0];
      nnew[ix][1] = n[ix][1];
    } // dejelo igual;
  }
}
void LatticeGas::Adveccione(void) {
  for (int ix = 0; ix < Lx; ix++) // para cada celda
    for (int ii = 0; ii < Q; ii++)
      n[(ix + V[ii] + Lx) % Lx][ii] = nnew[ix][ii]; // fronteras periódicas
}
double LatticeGas::Varianza(void) {
  int ix;
  double N, Xprom, Sigma2;
  // Calcular N
	for (N = 0, ix = 0; ix < Lx; ix++) 
		N += rho(ix);
	//Calcular Xprom
  for (Xprom = 0, ix = 0; ix < Lx; ix++){
    Xprom += ix * rho(ix);
  }
  Xprom /= N;
  // Calcular Sigma2
  for (Sigma2 = 0, ix = 0; ix < Lx; ix++) {
    Sigma2 += pow(ix - Xprom, 2.0) * rho(ix);
  }
  Sigma2 /= (N - 1);

  return Sigma2;
}

void LatticeGas::GrafiqueRho(void) {
  for (int ix = 0; ix < Lx; ix++) {
    cout << ix << "	" << rho(ix) << endl;
  }
}

//------- Programa Principal

int main() {
  LatticeGas Difusion;
  Crandom ran64(1);
  int N = 400;
  double mu = Lx / 2, sigma = Lx / 8;
  int t, tmax = 400;

  Difusion.Clean();
  Difusion.Inicie(N, mu, sigma, ran64);
  for (t = 0; t < tmax; t++) {
    cout << t << "\t" << Difusion.Varianza() << "\n";
    Difusion.Colisione(ran64);
    Difusion.Adveccione();
  }
  return 0;
}
