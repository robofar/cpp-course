#include <iostream>

int main ()
{
	char recenica[1000];
	std::cout<<"Unesite recenicu: ";
	std::cin.getline(recenica,sizeof recenica);
	std::cout<<"Recenica bez prve rijeci glasi: ";
	char *p=recenica;
	while(*p!='\0' && *p==' ') p++;
	while(*p!='\0' && *p!=' ') p++;
	while(*p!='\0' && *p==' ') p++;
	std::cout<<p<<std::endl;
	return 0;
}

