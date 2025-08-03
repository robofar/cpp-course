#include <iostream>
#include <functional>

std::function<int(int)>IteriranaFunkcija(std::function<int(int)> f, int n) {
	return [f,n](int x) {
		int rezultat=f(x);
		for(int i=0;i<n-1;i++) rezultat=f(rezultat);
		return rezultat;
	};
}

int f(int x) {
	return x+5;
}

int main ()
{
	auto g=IteriranaFunkcija(f,7);
	std::cout<<g(5)<<std::endl;
	std::cout<<IteriranaFunkcija(f,8)(3);
	return 0;
}