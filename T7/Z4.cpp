#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <memory>

using Dijeljeni = std::shared_ptr<std::string>;
int main ()
{
	int n;
	std::cout<<"Koliko zelite recenica: ";
	std::cin>>n;
	std::cin.ignore(10000,'\n');
	std::cout<<"Unesite recenice: "<<std::endl;
	std::unique_ptr<Dijeljeni[]> p=nullptr;;
	try {
		p=std::unique_ptr<Dijeljeni[]>(new Dijeljeni[n]);				
		try {
			for(int i=0;i<n;i++) {
			//	p[i]=Dijeljeni(new std::string); //ovo je preko eksplicitne konverzije
				p[i]=std::make_shared<std::string>(); //-> ovo () je sastavni dio funkcije make_shared
				std::getline(std::cin,*p[i]);
			}
		/* Sada moramo konvertovat u glupi pokazivac, jer shared_ptr ne podrzava pokazivacku
		aritmetiku - zato jer je namjenjen da pokazuje iskljucivo na objekte pa za njega
		pokazivacka aritmetika nema smisla - a p i p+n su ustvari shared_ptr(jer je to 
		ekvivalento sa p[0] i p[n] tj. to su elementi prvi i zadnji */
		std::sort(p.get(),p.get()+n,[](Dijeljeni a,Dijeljeni b) ->bool {
			return *a<*b;
		});
		std::cout<<"Sortirane recenice: "<<std::endl;
		for(int i=0;i<n;i++) std::cout<<*p[i]<<std::endl; //mora *p[i] jer ovo nije ko za niz charova, da se ispise citav samim stavljanjem pokazivaca
	/* SADA MI NE TREBA DELETE S OBZIROM DA KORISTIM PAMETNE POKAZIVACE */
	//	for(int i=0;i<n;i++) delete p[i]; //ne treba delete[] p[i] jer string nije ko niz charova, tj. nije niz nego jedna promjenjiva
	//	delete[] p;
		}
		catch(...) {
			/* SADA MI NE TREBA DELETE SOBZIROM DA KORISTIM PAMETNE POKAZIVACE */
		//	for(int i=0;i<n;i++) delete p[i];
		//	delete[] p;
			throw;
		}
	}
	catch(...) {
		std::cout<<"Problemi s memorijom!";
	}
	return 0;
}