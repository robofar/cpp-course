#include <iostream>
#include <vector>

unsigned long long int Obrni(unsigned long long int a) {
	unsigned long long int novi=0;
	while(a!=0) {
		int n=a%10;
		novi=novi*10 + n;
		a/=10;
	}
	return novi;
}

std::vector<int> PalindromskaOtpornost(std::vector<int> v) {
	std::vector<int> p;
	int brojac=0;
	for(int i=0;i<v.size();i++) {
		brojac=0;
		unsigned long long int a=llabs(v.at(i));
		unsigned long long int b=Obrni(a);
		if(a==b) p.push_back(0);
		else {
			for(;;) {
				brojac++;
				unsigned long long int c=a+b;
				unsigned long long int d=Obrni(c);
				if(c==d) break;
				a=c;
				b=Obrni(a);
			}
			p.push_back(brojac);
		}
	}
	return p;
}

int main ()
{
	int n;
	std::vector<int> v;
	std::cout<<"Koliko zelite unijeti elemenata: ";
	std::cin>>n;
	std::cout<<"Unesite elemente: ";
	for(int i=0;i<n;i++) {
		int broj;
		std::cin>>broj;
		v.push_back(broj);
	}
	std::vector<int> a;
	a=PalindromskaOtpornost(v);
	for(int i=0;i<a.size();i++) {
		std::cout<<"Palindromska otpornost broja "<<v.at(i)<<" iznosi "<<a.at(i)<<" "<<std::endl;
	}
	return 0;
}