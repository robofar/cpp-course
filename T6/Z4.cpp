#include <iostream>
#include <stdexcept>
int **KreirajTrougao(int n) {
	if(n<=0) throw std::domain_error("Broj redova mora biti pozitivan");
	int **niz=nullptr;
	try {
		niz=new int*[n]{};
		int a=0;
		try {
			niz[0]=new int[n*n];
			niz[0][0]=1;
				for(int i=1;i<n;i++) {
					niz[i]=niz[i-1]+2*i-1;
					int a=0;
					for(int j=0;j<=(2*i)/2;j++) {
						niz[i][j]=2*i-i+1-j;
						niz[i][(2*i)-j]=2*i-i+1-j;
					}
				}
		}
		catch(std::bad_alloc) {
		//	delete[] niz[0]; svakako nije uspjelo
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
		delete[] p[0];
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