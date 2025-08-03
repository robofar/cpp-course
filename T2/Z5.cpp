#include <iostream>
#include <complex>
#include <cmath>
int main ()
{
    const double PI = 4*atan(1);
    int n;
    std::cout<<"Unesi broj elemenata: "<<std::endl;
    std::cin>>n;
    std::complex<double> z;
    std::complex<double> suma(0,0);
    for(int i=0;i<n;i++) {
        double zk,fi;
        std::cout<<"Z"<<i+1<<" = ";
        std::cin>>zk;
        std::cout<<"fi"<<i+1<<" = "<<std::endl;
        std::cin>>fi; //fi je u radijanima, pa ga moramo i pretvoriti u radijane(jer ga unosimo kao stepene)
        double fi_rad = (fi*PI)/180; 
        z=std::polar(zk,fi_rad);
        suma += 1./z;
    }
    suma = 1./suma;
    std::cout<<"Paralelna veza ovih elemenata ima Z = "<<std::abs(suma)
            <<" i fi = "<<std::arg(suma)*180/PI<<".";
	return 0;
}