#include <complex>
#include <cstdio>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

class Signal{
    private:
        int esp;
        int senal;
    public:
        Signal(int *secuencia, complex<double> *espectro,int N);
        void FastFourierTransform(complex<double> *x, int N);

};

Signal::Signal(int *secuencia,complex<double> *espectro,int N)
{
    // Make copy of array and apply window
	for (int i = 0; i < N; i++) {
		espectro[i] = std::complex<double>(secuencia[i], 0);
		espectro[i] *= 1; // Window
	}

	// Start recursion
	FastFourierTransform(espectro, N);
}

void Signal::FastFourierTransform(complex<double> *F, int N){
   
	if (N == 1) 
		return;
	
    complex<double> Wn = exp(complex<double>(0, (-2 * M_PI)/ N));
    complex <double> w (1.0,0.0);

	// Separamos muestras pares de impares
	complex<double> impar[N/2];
	complex<double> par[N/2];
	for (int i = 0; i < N / 2; i++) {
		par[i] = F[i*2];
		impar[i] = F[i*2+1];
	}

	FastFourierTransform(par, N/2);
	FastFourierTransform(impar, N/2);

	for (int k = 0; k < N / 2; k++) {
        F[k] = par[k]+(w*impar[k]);
		F[N / 2 + k] = par[k] -(w*impar[k]);
        w = w*Wn;
	}

}

int main(int argc, char const *argv[])
{
    int N = 32; //Número de muestras potencua de 2
    int sig [N]; //Señal, secuecnia de digitos
    complex<double> espectro[N]; //Espectro
    Signal s (sig,espectro,N);

    // Salida
    for(int i=0; i<N; i++)
        cout<<"X["<<i<<"] = "<<"RE["<<espectro[i].real()<<"] IM["<<espectro[i].imag()<<"]"<<endl;

    return 0;
}
