#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Complex{
    private:
        double re;
        double im;

    public:
        Complex(double re, double im);
        double getRe();
        double getIm();
        void printComplex();
};
    //MÉTODS DE LA CALSE COMPLEX
    double Complex::getRe(){return re;}
    double Complex::getIm(){return im;}
    Complex::Complex(double real , double ima){
        re=real;
        im=ima;
    }

    void Complex::printComplex(void){
        cout<<"Re["<<re<<"] "<<"Im ["<<im<<"]"<<endl;
    }

class Signal{
    private:
        vector<Complex> signal;
        int muestras;
    public:
        Signal(int s, int m);
        void ejecutaFFT();
        vector<Complex> FastFourierTransform(vector<Complex> &v, int m);
        Complex sumaComplex(Complex a, Complex b);
        Complex restaComplex(Complex a, Complex b);
        Complex multiplicaComplex(Complex a, Complex b);

};

Signal::Signal(int s, int m){
    this->muestras=m;
    for(int i=0;i<s; i++){
        Complex c (i,0);
        signal.push_back(c);
    }
}

void Signal::ejecutaFFT(){
    vector<Complex> espectro= FastFourierTransform(this->signal,this->muestras);
    for(int i=0; i<espectro.size(); i++)
        espectro[i].printComplex();
}

Complex Signal::sumaComplex(Complex a, Complex b){
    double re = a.getRe() + b.getRe();
    double im = a.getIm() + b.getIm();
    Complex z (re,im);
    return z;
}

Complex Signal::restaComplex(Complex a, Complex b){
    double re = a.getRe() - b.getRe();
    double im = a.getIm() - b.getIm();
    Complex z (re,im);
    return z;
}

Complex Signal::multiplicaComplex(Complex a, Complex b){
    // cout<<"Esto se va a multiplicar"<<b.getRe()<<" "<<b.getIm()<<endl;    
    // cout<<"Esto se va a multiplicar"<<a.getRe()<<" "<<a.getIm()<<endl;
    double A = a.getRe() * b.getRe();
    double B = a.getIm()*b.getIm();
    double C = (a.getRe() * b.getIm()) + (a.getIm() * b.getRe());
    if (B != 0)
        A = A + (-1 * (B));
    Complex z (A, C);
    //cout<<"Esta es la salida de multiplicar"<<endl;
    //z.printComplex();
    return z;
}



vector<Complex> Signal::FastFourierTransform(vector<Complex> &v,int N){  
    vector<Complex> espectro;
    if(N==1)
        return v;
    
    
    for(int i=0; i<v.size(); i++){
        Complex com (0,0);
        espectro.push_back(com);
    }

    Complex Wn (cos(2.0*M_PI/N),(-1.0)*sin(2.0*M_PI/N));
    Complex w (1,0);

    vector<Complex> par;
    vector<Complex> impar;

    // Separamos pares de impares
    for(int i=0; i<v.size(); i++){
        if((int)(v[i].getRe())%2 == 0)
            par.push_back(v[i]);
        else
            impar.push_back(v[i]);
    }
    
    // for(int i=0; i<par.size(); i++)
    //     par[i].printComplex();
    // cout<<"-----------------"<<endl;
    cout<<"N "<<N<<endl;
    // cout<<"-----PAR------------"<<endl;
    //     for(int i=0; i<par.size(); i++)
    //     par[i].printComplex();
    // cout<<"-----IMPAR------------"<<endl;
    //     for(int i=0; i<impar.size(); i++)
    //     impar[i].printComplex();

    vector<Complex> A = FastFourierTransform(par, N / 2);
    vector<Complex> B = FastFourierTransform(impar, N / 2);
    // cout<<"TODO EL VECTOR A"<<endl;
    // for(int i=0; i<A.size(); i++)
    //     A[i].printComplex();

    if(!A.empty() && !B.empty())
    {        
        for (int k = 0; k < (N / 2); k++){
            // cout<<"Esto se va a miltiplcar "<<w.getRe()<<" "<<w.getIm()<<endl;    
            // cout<<"Esto se va a miltiplcar "<<B[k].getRe()<<" "<<B[k].getIm()<<endl;
            // cout<<"ESTO ES UN B ";
            // B[k].printComplex();
            espectro[k] = Signal::sumaComplex(A[k],multiplicaComplex(w, B[k]));            
            espectro[k + (N / 2)] = Signal::restaComplex(A[k], multiplicaComplex(w, B[k]));
            w = Signal::multiplicaComplex(w,Wn);
        }
    }
    cout<<"-----ESPECTRO------------"<<endl;
    for(int i=0; i<espectro.size(); i++)
        espectro[i].printComplex();
    return espectro;
}


int main()
{
    Signal s (8,8);
    s.ejecutaFFT();
    // Complex A (0,1);
    // Complex B (2,4);
    // Complex C = s.multiplicaComplex(A,B);
    // C.printComplex();
    return 0;
}
