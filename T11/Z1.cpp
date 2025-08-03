#include <iostream>

class NeobicnaKlasa {
	int broj;
public:
/* Morali smo u jednom staviti const int& u drugom int&& da bi se razlikovale po broju parametara */
	NeobicnaKlasa(const int &x) { //veze se za l-vrijednost => npr: NK a=5 => ovo 5 nije r-vrijednost nego ce 
	//se prvo ovo 5 pozivom ovog konstruktora pretvorit u NeobicnaKlasa(5) sto sad predstavlja l-vrijednost
		broj=x;
		std::cout<<"Kopirajuca inicijalizacija";
	}
	explicit NeobicnaKlasa(int &&x) { //veze se samo za r-vrijednost
		broj=x;
		std::cout<<"Direktna inicijalizacija"<<std::endl;
	}
};
int main ()
{
	return 0;
}