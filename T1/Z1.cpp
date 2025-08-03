#include <iostream>
#include <cmath>
int main ()
{
	int a,b,c,d;
	std::cout << "Unesite duzinu, sirinu i dubinu bazena u metrima: ";
	std::cin >> a >> b >> c;
	std::cout << "Unesite sirinu plocice u centimetrima: ";
	std::cin >> d;
	std::cout<<std::endl; //novi red
  
	int P = 0;
	P = (a*b + 2*a*c + 2*b*c) * 10000;
	
	if(P%(d*d)==0 && (a*100)%d==0 && (b*100)%d==0 && (c*100)%d==0) {
    int broj_plocica = 0;
    broj_plocica = P/(d*d);
    
    std::cout << "Za poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<std::endl
              <<"potrebno je "<<broj_plocica<<" plocica."<<std::endl;
    }
    
    else
    std::cout << "Poplocavanje bazena dimenzija "<<a<<"x"<<b<<"x"<<c<<"m sa plocicama dimenzija "<<d<<"x"<<d<<"cm"<<std::endl
              << "nije izvodljivo bez lomljenja plocica!"<<std::endl;
    
    return 0;
	
}