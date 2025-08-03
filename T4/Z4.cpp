#include <iostream>
#include <string>
#include <cmath>

template <typename NekiTip>
void UnosBroja(std::string s1, std::string s2,NekiTip &n) {
    for(;;) {
        std::cout<<s1<<std::endl;
        std::cin>>n;
        if(!std::cin || std::cin.peek()!='\n') { // los unos ili unijet samo enter
            std::cout<<s2<<std::endl;
            std::cin.clear(); //oporavak toka
            std::cin.ignore(1000,'\n');
        }
        else break;
    }
}
int main ()
{
    double baza;
    UnosBroja("Unesite bazu: ","Neispravan unos, pokusajte ponovo...",baza);
    int eksponent;
    UnosBroja("Unesite cjelobrojni eksponent: ","Neispravan unos, pokusajte ponovo...",eksponent);
    double rezultat=1;
    if(eksponent>0) {
        for(int i=0;i<eksponent;i++) {
            rezultat = rezultat*baza;
        }
    }
    else if(eksponent<0) {
        for(int i=0;i<abs(eksponent);i++) {
            rezultat = rezultat/baza;
        }
    }
    std::cout<<baza<<" na "<<eksponent<<" iznosi "<<rezultat;
	return 0;
}