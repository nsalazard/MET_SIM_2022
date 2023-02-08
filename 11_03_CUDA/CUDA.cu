#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

#define Lx 16
#define Nx 8
const int Mx = (Lx+Nx-1)/Nx;

//-------- Device's Program-----
//-------- Kernels--------------

__global__ void AddTwoVectors(float* d_a, float* d_b, float* d_c){
	//Who am I?
	int ix = blockIdx.x*blockDim.x+threadIdx.x;
	d_c[ix] = d_a[ix] + d_b[ix];
}
//-------- Host's Program-----
int main(void){
	int ix;
	//Declara variables por duplicado
	//---DEVICE---
	float *d_a; cudaMalloc((void**) &d_a, Lx*sizeof(float));
	float *d_b; cudaMalloc((void**) &d_b, Lx*sizeof(float));
	float *d_c; cudaMalloc((void**) &d_c, Lx*sizeof(float));
	//---HOST-----
	float h_a[Lx], h_b[Lx], h_c[Lx];

	//Fill data for proccesing

	for (ix =0; ix < Lx; ix++){
		h_a[ix]=ix; 
		h_b[ix]=2*ix; 
	}

	//Send to Device
	cudaMemcpy(d_a,h_a,Lx*sizeof(float),cudaMemcpyHostToDevice);
cudaMemcpy(d_b,h_b,Lx*sizeof(float),cudaMemcpyHostToDevice);

	//Run in Device
	dim3 BlocksPerGrid(Mx,1,1);
	dim3 ThreadsPerBlock(Nx,1,1);
	AddTwoVectors<<<BlocksPerGrid, ThreadsPerBlock >>>(d_a,d_b,d_c);
	//Return result to Host
	cudaMemcpy(h_c, d_c,Lx*sizeof(float), cudaMemcpyDeviceToHost);
	//Print
		for(ix=0; ix<Lx; ix++){
		cout << h_a[ix] << "\t" << h_b[ix] << "\t" << h_c[ix] << "\n";
		}
	//Free Dynamic memory
	cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
	
	return 0;
}
