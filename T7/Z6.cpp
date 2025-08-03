#include <iostream>
#include <list>
#include <iterator>

template<typename NekiTip>
std::list<NekiTip> SortirajListu(std::list<NekiTip> &l) {
	std::list<NekiTip> nova;
	auto it1=l.begin(); //zasto ne moze std::list<NekiTip>::iterator????
	while(it1!=l.end()) {
		NekiTip x;
		x=*it1;
		it1++;
		auto it2=nova.begin();
		while(it2!=nova.end() && *it2<x) it2++; //kao u predavanju
		nova.insert(it2,x);
	}
	l=nova; //zbog AT-ova
	return nova;
}
int main ()
{
	int n;
	std::cout<<"Koliko ima elemenata: ";
	std::cin>>n;
	std::list<int> l;
	std::cout<<"Unesite elemente: ";
	for(int i=0;i<n;i++) {
		int x;
		std::cin>>x;
		l.push_back(x);
	}
	std::list<int> nova=SortirajListu(l);
	std::list<int>::iterator q=nova.begin();
	std::cout<<"Sortirana lista: ";
	while(q!=nova.end()) std::cout<<*q++<<" ";
	return 0;
}