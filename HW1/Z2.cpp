#include <iostream>
#include <vector>
#include <stdexcept>
#include <complex>

typedef std::vector<std::vector<int>> Matrica;

std::complex<double> VrhMatrice(Matrica mat,int n, int m) {
	std::complex<double> z; //ima pocetne vrijednosti (0,0)
	int max;
	/* Baci izuzetke */
	for(int i=0;i<mat.size();i++) {
		if(mat.at(0).size() != mat.at(i).size()) throw std::domain_error("Nekorektna matrica");
		if(mat.at(i).size()==0) throw std::domain_error("Nekorektna matrica");
	}
	if(mat.size()==0) throw std::domain_error("Nekorektna matrica");
	if(n>=mat.size() || n<0 || m>=mat.at(0).size() || m<0) throw std::range_error("Nekorektna pocetna pozicija");
	/* Sad idemo sa radom */
	int nema=1;
	int maxi=n,maxj=m;
	max=mat.at(maxi).at(maxj);
	for(;;) {
		nema=1;
		if(n-1>=0 && mat.at(n-1).at(m)>max) {
			maxi=n-1;
			maxj=m;
			max=mat.at(maxi).at(maxj);
			nema=0;
		}
		if(n-1>=0 && m+1<mat.at(0).size() && mat.at(n-1).at(m+1)>max) {
			maxi=n-1;
			maxj=m+1;
			max=mat.at(maxi).at(maxj);
			nema=0;
		}
		if(m+1<mat.at(0).size() && mat.at(n).at(m+1)>max) {
			maxi=n;
			maxj=m+1;
			max=mat.at(maxi).at(maxj);
			nema=0;
		}
		if(n+1<mat.size() && m+1<mat.at(0).size() && mat.at(n+1).at(m+1)>max) {
			maxi=n+1;
			maxj=m+1;
			max=mat.at(maxi).at(maxj);
			nema=0;
		}
		if(n+1<mat.size() && mat.at(n+1).at(m)>max) {
			maxi=n+1;
			maxj=m;
			max=mat.at(maxi).at(maxj);
			nema=0;
		}
		if(n+1<mat.size() && m-1>=0 && mat.at(n+1).at(m-1)>max) {
			maxi=n+1;
			maxj=m-1;
			max=mat.at(maxi).at(maxj);
			nema=0;
		}
		if(m-1>=0 && mat.at(n).at(m-1)>max) {
			maxi=n;
			maxj=m-1;
			max=mat.at(maxi).at(maxj);
			nema=0;
		}
		if(n-1>=0 && m-1>=0 && mat.at(n-1).at(m-1)>max) {
			maxi=n-1;
			maxj=m-1;
			max=mat.at(maxi).at(maxj);
			nema=0;
		}
		n=maxi;
		m=maxj;
		if(nema==1) break;
		//max=mat.at(maxi).at(maxj);
	}
	/* Sada su ti n i m pozicije, a max je najveca vrijednost */
	z.real(maxi);
	z.imag(maxj);
	return z;
}

int main ()
{
	int n,m;
	std::cout<<"Unesite broj redova i kolona matrice: "<<std::endl;
	std::cin>>n>>m;
	Matrica M(n,std::vector<int>(m));
	std::cout<<"Unesite elemente matrice: "<<std::endl;
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			std::cin>>M.at(i).at(j);
		}
	}
	int a,b;
	std::cout<<"Unesite poziciju odakle zapocinje pretraga: "<<std::endl;
	std::cin>>a>>b;
	std::complex<double> z;
	/* Pozovi u try-catch bloku */
	try {
		z=VrhMatrice(M,a,b);
		std::cout<<"Nadjen je vrh matrice na poziciji "<<z.real()<<" "<<z.imag()<<std::endl;
		std::cout<<"Njegova vrijednost je "<<M.at(z.real()).at(z.imag());
	}
	catch(std::domain_error izuzetak) {
		std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
	}
	catch(std::range_error izuzetak) {
		std::cout<<"Greska: "<<izuzetak.what()<<std::endl;
	}
	return 0;
}