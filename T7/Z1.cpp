#include <iostream>
#include <cstring>
bool Veci(const char* a,const char* b) {
	return (std::strcmp(a,b)>0);
}
int main ()
{
	int n;
	std::cout<<"Koliko zelite recenica: ";
	std::cin>>n;
	std::cin.ignore(10000,'\n');
	std::cout<<"Unesite recenice: "<<std::endl;
	char** p=nullptr;
	try {
		p=new char*[n]{};
		try {
			for(int i=0;i<n;i++) {
				char recenica[1000];
				std::cin.getline(recenica,sizeof recenica);
				p[i]=new char[std::strlen(recenica)+1];
				std::strcpy(p[i],recenica);
			}
			for(int i=0;i<n;i++) {
				for(int j=i+1;j<n;j++) {
					if(Veci(p[i],p[j])) {
						char* pomocni=p[i];
						p[i]=p[j];
						p[j]=pomocni;
					}
				}
			}
		std::cout<<"Sortirane recenice: "<<std::endl;
		for(int i=0;i<n;i++) std::cout<<p[i]<<std::endl;
		for(int i=0;i<n;i++) delete[] p[i];
		delete[] p;
		}
		catch(std::bad_alloc) {
			for(int i=0;i<n;i++) delete[] p[i];
			delete[] p;
			throw;
		}
	}
	catch(std::bad_alloc) {
		std::cout<<"Problemi s memorijom!";
	}
	
	
	return 0;
}