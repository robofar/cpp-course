#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

typedef std::vector<std::vector<int>> Matrica;

int NajvecaSirina(Matrica m) {
	int brojac=0;
	int max=0;
	int minus=0;
	if(m.size()==0) return 0;
	for(int i=0;i<m.size();i++) {
		for(int j=0;j<m.at(0).size();j++) {
			brojac=0;
			minus=0;
			if(m.at(i).at(j)<0) minus=1;
			while(m.at(i).at(j)!=0) {
				brojac++;
				m.at(i).at(j)/=10;
			}
			if((brojac+minus)>max) max=brojac+minus;
		}
	}
	return max;
}
Matrica KroneckerovProizvod(Matrica A, Matrica B) {
	int formaA=1,formaB=1;
	if(A.size()==0 || B.size()==0) return {};
	for(int i=1;i<A.size();i++) {
		if(A.at(0).size() != A.at(i).size()) {
			formaA=0;
			break;
		}
	}
	for(int i=1;i<B.size();i++) {
		if(B.at(0).size() != B.at(i).size()) {
			formaB=0;
			break;
		}
	}
	if(formaA==0 && formaB==0) throw std::domain_error("Parametri nemaju formu matrice");
	else if(formaA==0) throw std::domain_error("Prvi parametar nema formu matrice");
	else if(formaB==0) throw std::domain_error("Drugi parametar nema formu matrice");
	
	int n=A.size();
	int p=B.size();
	int a=n*p;
	int m=A.at(0).size();
	int q=B.at(0).size();
	int b=m*q;
	int sirina,visina; //jer ispisujemo proizvod svakog elementa matA sa cijelom matB
	visina=0; 
	Matrica C(a,std::vector<int> (b));
	for(int i=0;i<n;i++) {
		sirina=0; //resetujemo sirinu svaki put na 0 kad predjemo u novi red
		for(int j=0;j<m;j++) {
			for(int k=0;k<p;k++) {
				for(int l=0;l<q;l++) {
					C.at(k+visina).at(l+sirina) = A.at(i).at(j) * B.at(k).at(l);
				}
			}
			sirina += q; //za svaku kolonu matriceA se pomjerimo sirina mjesta dalje da bi to ispisali u C
		}
		visina += p; //za svaki red matriceA se pomjerimo visina mjesta dole da bi ispisali to u C
	}
	return C;
}

int main ()
{
	Matrica C;
	int m,n;
	std::cout<<"Unesite dimenzije prve matrice:"<<std::endl;
	std::cin>>m>>n;
	Matrica A(m,std::vector<int>(n));
	std::cout<<"Unesite elemente prve matrice:"<<std::endl;
	for(int i=0;i<m;i++) {
		for(int j=0;j<n;j++) {
			std::cin>>A.at(i).at(j);
		}
	}
	int p,q;
	std::cout<<"Unesite dimenzije druge matrice:"<<std::endl;
	std::cin>>p>>q;
	Matrica B(p,std::vector<int>(q));
	std::cout<<"Unesite elemente druge matrice:"<<std::endl;
	for(int i=0;i<p;i++) {
		for(int j=0;j<q;j++) {
			std::cin>>B.at(i).at(j);
		}
	}
	try {
		C=KroneckerovProizvod(A,B);
	}
	catch(std::domain_error izuzetak) {
		std::cout<<izuzetak.what()<<std::endl;
	}
	int duzina = NajvecaSirina(C);
	std::cout<<"Njihov Kroneckerov proizvod glasi:"<<std::endl;
	for(int i=0;i<C.size();i++) {
		for(int j=0;j<C.at(0).size();j++) {
			std::cout<<std::setw(duzina+1)<<std::right<<C.at(i).at(j);
		}
		std::cout<<std::endl;
	}

	return 0;
	
}