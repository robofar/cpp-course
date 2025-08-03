#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
template <typename NekiTip>
//treba nam STRIKTNO POKAZIVAC al na ono KOJEG JE TIPA ELEMENT ovog NekiTip
auto KreirajIzvrnutiNiz(NekiTip p1, NekiTip p2) -> typename std::remove_reference<decltype(*p1)>::type* {
	typename std::remove_reference<decltype(*p1)>::type* niz;
	NekiTip a=p1;
	NekiTip b=p2;
	int n=0;
	while(a!=b) {
		n++;
		a++;
	}
	try {
		int i=0;
		niz=new typename std::remove_reference<decltype(*p1)>::type[n]; //ili std remove reference
		while(p1!=p2) {
			niz[n-1-i]=*p1;
			p1++;
			i++;
		}
	}
	catch(std::bad_alloc) {
		throw;
	}
	return niz;
}
int main ()
{
	int n;
	std::cout<<"Koliko zelite elemenata: ";
	std::cin>>n;
	try {
		std::vector<double> v(n);
		std::cout<<"Unesite elemente: ";
		for(int i=0;i<n;i++) std::cin>>v.at(i);
		double *p=nullptr;
		p=KreirajIzvrnutiNiz(v.begin(),v.end());
		std::cout<<"Kreirani niz: ";
		for(int i=0;i<n;i++) std::cout<<p[i]<<" ";
		delete[] p;
	}
	catch(...) {
		std::cout<<"Nedovoljno memorije!";
	}
	
	return 0;
}