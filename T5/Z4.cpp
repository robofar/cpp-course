#include <iostream>
#include <algorithm>
#include <cmath>
#include <deque>
int main ()
{
	int n;
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>n;
	std::deque<int> d(n);
	std::cout<<"Unesite elemente: ";
	/* Prva stvar: Za for_each, kontenjer mora imati vec specificiranu velicinu */
	/* Druga stvar: morao sam preko referenci unositi brojeve, jer tako mjenjam
	vec postojece nule deka(jer dek ima n nula) */
	/* Treca stvar: da sam stavljao kopije i onda ih push_back-ovo dek bi mi imao
	2*n elemenata(prvih n nula, i onda n ovih unesenih elemenata) */
	/* Za for_each funkcija kriterija MORA BITI TIPA void (jer nigdje ne smjestas rezultat te funckije)
	i MORA IMATI SAMO 1 PARAMETAR jer se jedan po jedan prosljedjuje u funkciju */
	std::for_each(d.begin(),d.end(),[](int &a)->void {
		std::cin>>a;
	});
	int a=*std::max_element(d.begin(),d.end());
	int b=*std::min_element(d.begin(),d.end());
	int c=std::count_if(d.begin(),d.end(),[](int n) -> bool {
		double broj=sqrt(n);
		int broj2=broj;
		if(broj2==broj) return true;
		return false;
	});
	int e=*std::min_element(d.begin(),d.end(),[](int n,int m) -> bool {
		int brojacN,brojacM;
		brojacN = int(log10(int(fabs(n)))+1);
		brojacM = int(log10(int(fabs(m)))+1);
		if(brojacN<brojacM) return true;
		return false;
	});
	std::cout<<"Najveci element deka je "<<a<<std::endl;
	std::cout<<"Najmanji element deka se pojavljuje "<<std::count(d.begin(),d.end(),b)<<" puta u deku"<<std::endl;
	std::cout<<"U deku ima "<<c<<" brojeva koji su potpuni kvadrati"<<std::endl;
	std::cout<<"Prvi element sa najmanjim brojem cifara je "<<e<<std::endl;
	std::cout<<"Elementi koji nisu trocifreni su: ";
	std::deque<int> d2(n);
	std::deque<int>::iterator kraj = std::remove_copy_if(d.begin(),d.end(),d2.begin(),[](int n) -> bool {
		if(abs(n)>=100 && abs(n)<=999) return true;
		return false;
	});
	/* ili resizam pa onda umjesto kraj idem do d2.end() */
	std::for_each(d2.begin(),kraj,[](int n) -> void {
		std::cout<<n<<" ";
	});
	return 0;
}