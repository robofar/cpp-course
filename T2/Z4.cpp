#include <iostream>
#include <complex>
int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    std::cin>>n;
    double re,im;
    std::complex<double> z;
    std::complex<double> suma(0,0);
    for(int i=0;i<n;i++) {
        std::cout<<"R"<<i+1<<" = ";
        std::cin>>re;
        std::cout<<"X"<<i+1<<" = "<<std::endl;
        std::cin>>im;
        z.real(re);
        z.imag(im);
        suma += 1./z;
    }
    suma = 1./suma;
    std::cout<<"Paralelna veza ovih elemenata ima R = "<<suma.real()
            <<" i "<<"X = "<<suma.imag()<<".";
	return 0;
}
