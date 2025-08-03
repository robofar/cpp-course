#include <iostream>
#include <stdexcept>
int **KreirajTrougao(int n) {
	if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
	int **niz=nullptr;
	try {
		niz=new int*[n]{};
		int a=0;
		try {
			for(int i=1;i<2*n;i+=2) {
				niz[a]=new int[i];
				a++;
				int q=a-1;
				for(int k=a;k>0;k--) {
					niz[q][a-k]=k;
					niz[q][a-1+k-1]=k;
				}
			}
		}
		catch(std::bad_alloc) {
			for(int i=0;i<n;i++) delete[] niz[i];
			delete[] niz;
			throw;
		}
	}
	catch(std::bad_alloc) {
		throw;
	}
	return niz;
}
#include <iostream>
int main ()
{
	int n;
	std::cout<<"Koliko zelite redova: ";
	std::cin>>n;
	int **p=nullptr;
	try {
		p=KreirajTrougao(n);
		for(int i=0;i<n;i++) {
			for(int j=0;j<=2*i;j++) {
				std::cout<<p[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
		for(int i=0;i<n;i++) delete[] p[i];
		delete[] p;
	}
	catch(std::domain_error izuzetak) {
		std::cout<<"Izuzetak: "<<izuzetak.what();
	}
	catch(std::bad_alloc izuzetak) {
		std::cout<<"Izuzetak: Nedovoljno memorije!";
	}
	return 0;
}