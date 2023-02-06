#include <iostream>
#include <cmath>
#include "vector.h"
using namespace std;


int main(void){
	vector3D a,b,c,d,e,f,g;
	a.load(1,0,0);
	b.load(2,4,6);
	c = a+b;
	cout << "Vector a:  con su componenete en x: " << a.x() << endl;
	a.show();
	cout << "Vector c "<< endl;
	c.show();
	cout << a.norm2()<< endl;
	cout << a.norm()<< endl;

	//d = 2*a;
	//d.operator= a;
	d = a.operator* (2);
	d.show();

	
	e.load(0,1,0);
	f = a^e;
	f.show();
	f = a+(a^b);
	f.show();

  return 0;
}
