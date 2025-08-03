#include <iostream>
#include <stdexcept>
#include <cmath>
#include <limits>
template <typename NekiTip>
NekiTip *GenerirajStepeneDvojke(int n) {
	if(n<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
	NekiTip *niz=nullptr;
	try {
		niz = new NekiTip[n];
		NekiTip maks = std::numeric_limits<NekiTip>::max();
		/* Ako je alokacija uspjela */
		for(int i=0;i<n;i++) {
			niz[i]=1; 
			for(int j=0;j<i;j++) niz[i]*=2; //mora ova petlja za racunanje stepena, ne smije pow
			//jer pow ne moze vratiti neke bas velike vrijednosti(jer njegova je najveca verzija long double,
			//a ima jedan at sto testira long long double
			
			if(niz[i]<=0 || (i-1>=0 && niz[i-1]>=maks/2 && niz[i]>maks)) {
				delete[] niz;
				throw std::overflow_error("Prekoracen dozvoljeni opseg");
			}
		}
	}
	catch(std::bad_alloc) {
		throw std::runtime_error("Alokacija nije uspjela");
	}
	return niz;
}

int main() {
	int n;
	std::cout<<"Koliko zelite elemenata: ";
	std::cin>>n;
	int *niz=nullptr;
	try {
		niz=GenerirajStepeneDvojke<int>(n);
		for(int i=0;i<n;i++) std::cout<<niz[i]<<" ";
	}
	catch(std::domain_error izuzetak) {
		std::cout<<"Izuzetak: "<<izuzetak.what();
	}
	catch(std::overflow_error izuzetak) {
		std::cout<<"Izuzetak: "<<izuzetak.what();
	}
	catch(std::runtime_error izuzetak) {
		std::cout<<"Izuzetak: "<<izuzetak.what();
	}
	delete[] niz; //nakon svega ovog deletaj
	return 0;
}