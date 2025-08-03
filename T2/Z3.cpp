#include <iostream>
#include <complex>
int main ()
{
	int n;
	std::cout<<"Unesite broj elemenata: "<<std::endl;
	std::cin>>n;
	std::complex<double> suma(0,0);
	for(int i=0;i<n;i++) {
	    std::complex<double> z;
	    std::cout<<"Z_"<<i+1<<" = ";
	    std::cin>>z;
	    suma += 1./z;
	}
	std::cout<<std::endl<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<<1./suma<<".";
	return 0;
}
