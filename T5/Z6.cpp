#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int SumaCifara(int n) {
	if(n==0) return 0;
	int x=n%10;
	n/=10;
	return x+SumaCifara(n);
}

bool Poredi(int a, int b) {
	if(SumaCifara(abs(a))<SumaCifara(abs(b))) return true;
	else if(SumaCifara(abs(a))==SumaCifara(abs(b))) {
		if(a<b) return true;
	}
	return false;
}
int main ()
{
	int n;
	std::cout<<"Unesite broj elemenata: ";
	std::cin>>n;
	std::vector<int> v(n);
	std::cout<<"Unesite elemente: ";
	/* for_each salje znaci svaki put element u funkciju - zato sam stavio u funkciju
	kao parametar referencu, da bi mogao unositi elemente sa tastature */
	std::for_each(v.begin(),v.end(),[](int &a)->void {
		std::cin>>a;
	});
	std::cout<<"Niz sortiran po sumi cifara glasi: ";
	std::sort(v.begin(),v.end(),Poredi);
	std::for_each(v.begin(),v.end(),[](int a)->void {
		std::cout<<a<<" ";
	});
	std::cout<<std::endl;
	int x;
	
	std::cout<<"Unesite broj koji trazite: ";
	std::cin>>x;
	/* ako nije sortiran niz kao rastuci,tj. samo sort(p1,p2) i u binary_search
	se mora navesti ona funkcija po kojoj smo sortirali, kao 4. parametar */
	bool f=std::binary_search(v.begin(),v.end(),x,Poredi); //mogu i pokazivaci umjesto iteratora
	if(f) std::cout<<"Trazeni broj nalazi se na poziciji "<<std::find(v.begin(),v.end(),x)-v.begin();
	else std::cout<<"Trazeni broj ne nalazi se u nizu!";

	return 0;
}