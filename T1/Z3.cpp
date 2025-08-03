#include <iostream>
#include <cmath>
#include <iomanip>

int main ()
{
    int a,b;
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    do {
        std::cin >> a >> b;
    } while(a>9999 || b>9999 || a>b);
    std::cout<<std::endl;
    
    std::cout<<"+---------+----------+----------+-----------+"<<std::endl;
    std::cout<<"| Brojevi | Kvadrati | Korijeni | Logaritmi |"<<std::endl;
    std::cout<<"+---------+----------+----------+-----------+"<<std::endl;
    
    for(int i=a;i<=b;i++) {
        std::cout<<"| "<<std::left<<std::setw(8)<<i
                 <<"|"<<std::right<<std::setw(9)<<i*i
                 <<" |"<<std::right<<std::setw(9)<<std::fixed<<std::setprecision(3)<<std::sqrt(i)<<" |"
                 <<std::right<<std::setw(10)<<std::fixed<<std::setprecision(5)<<std::log(i)<<" |"<<std::endl;
    }
    
    std::cout<<"+---------+----------+----------+-----------+"<<std::endl;
        
	return 0;
}