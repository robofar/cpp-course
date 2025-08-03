#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>

int main () {
	int n;
	std::cout<<"Koliko zelite elemenata: ";
	std::cin>>n;
	std::vector<double> v(n);
	std::cout<<"Unesite elemente: ";
	for(int i=0;i<n;i++) std::cin>>v.at(i);
	std::transform(v.begin(),v.end(),v.begin(),std::bind(std::divides<double>(),1,std::placeholders::_1));
	std::cout<<"Transformirani elementi: ";
	for(int i=0;i<n;i++) std::cout<<v.at(i)<<" ";
	return 0;
}