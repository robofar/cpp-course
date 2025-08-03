#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

int main ()
{
	int n;
	std::cout<<"Koliko zelite recenica: ";
	std::cin>>n;
	std::cin.ignore(10000,'\n');
	std::cout<<"Unesite recenice: "<<std::endl;
	std::string** p=nullptr; 
	try {
		p=new std::string*[n]{};
		try {
			for(int i=0;i<n;i++) {
			//	std::string s; ZASTO OVO NE BI VALJALO - ZBOG AT-OVA
			//DA PRVO UNESEM STRING NORMALNO I ONDA GA DODIJELIM to *p[i] ???
				p[i]=new std::string;
				std::getline(std::cin,*p[i]);
			//	p[i]=new std::string;
			//	*p[i]=s; //ili gore poslije stavim (s)
			}
		std::sort(p,p+n,[](std::string* a,std::string* b) ->bool {
			return *a<*b;
		});
		std::cout<<"Sortirane recenice: "<<std::endl;
		for(int i=0;i<n;i++) std::cout<<*p[i]<<std::endl; //mora *p[i] jer ovo nije ko za niz charova, da se ispise citav samim stavljanjem pokazivaca
		for(int i=0;i<n;i++) delete p[i]; //ne treba delete[] p[i] jer string nije ko niz charova, tj. nije niz nego jedna promjenjiva
		delete[] p;
		}
		catch(...) {
			for(int i=0;i<n;i++) delete p[i];
			delete[] p;
			throw;
		}
	}
	catch(...) {
		std::cout<<"Problemi s memorijom!";
	}
	return 0;
}