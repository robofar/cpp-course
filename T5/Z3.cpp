#include <iostream>
#include <algorithm>
#include <cmath>
/* FUNKCIJA KRITERIJA */
bool PotpuniKvadrat(int n) {
	double broj=sqrt(n);
	int broj2=broj;
	if(broj2==broj) return true;
	return false;
}

bool NajmanjiBrojCifara(int n, int m) {
	int brojacN=0;
	int brojacM=0;
	brojacN = int(log10(int(fabs(n)))+1);
	brojacM = int(log10(int(fabs(m)))+1);
	if(brojacN<brojacM) return true;
	return false; //false podrazumijeva >= (JEDNAKO MORA BITI ZA FALSE)
}

bool Trocifren(int n) {
	if(abs(n)>=100 && abs(n)<=999) return true;
	return false;
}

void Ispisi(int n) { //jer ispisujemo element po element koji for_each daje
	std::cout<<n<<" ";
}

void Unesi(int &n) {
	std::cin>>n;
}
int main ()
{
	int niz[1000];
	int n;
	std::cout<<"Unesite broj elemenata (max. 1000): ";
	std::cin>>n;
	std::cout<<"Unesite elemente: ";
	std::for_each(niz,niz+n,Unesi);
	int a=*std::max_element(niz,niz+n);
	int b=*std::min_element(niz,niz+n);
	int c=std::count_if(niz,niz+n,PotpuniKvadrat);
	int d=*std::min_element(niz,niz+n,NajmanjiBrojCifara);
	std::cout<<"Najveci element niza je "<<a<<std::endl;
	std::cout<<"Najmanji element niza se pojavljuje "<<std::count(niz,niz+n,b)<<" puta u nizu"<<std::endl;
	std::cout<<"U nizu ima "<<c<<" brojeva koji su potpuni kvadrati"<<std::endl;
	std::cout<<"Prvi element sa najmanjim brojem cifara je "<<d<<std::endl;
	std::cout<<"Elementi koji nisu trocifreni su: ";
	int niz2[1000];
	int *kraj = std::remove_copy_if(niz,niz+n,niz2,Trocifren);
	std::for_each(niz2,kraj,Ispisi);
	return 0;
}