#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <deque>
template<typename NekiTip>
auto KreirajDinamickuKopiju2D(NekiTip mat) -> typename std::remove_reference<decltype(mat[0][0])>::type**{
	typename std::remove_reference<decltype(mat[0][0])>::type** matrica=nullptr;
	int n=mat.size();
	try {
		matrica=new typename std::remove_reference<decltype(mat[0][0])>::type*[n]{};
		try {
			for(int i=0;i<mat.size();i++) {
				int m=mat.at(i).size();
				matrica[i]=new typename std::remove_reference<decltype(mat[0][0])>::type[m];
				for(int j=0;j<m;j++) {
					matrica[i][j] = mat.at(i).at(j);
				}
			}
		}
		catch(std::bad_alloc) {
			for(int i=0;i<n;i++) {
				delete[] matrica[i];
			}
			delete[] matrica;
			throw;
		}
	}
	catch(std::bad_alloc) {
		throw;
	}
	return matrica;
}
int main ()
{
	int n;
	std::cout<<"Unesite broj redova kvadratne matrice: ";
	std::cin>>n;
	/* mora i vektor u try jer i on je dinamicki alociran tako da i on moze bacit izuzetak */
	try {
		std::vector<std::vector<int>> mat(n,std::vector<int>(n));
		std::cout<<"Unesite elemente matrice: ";
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				std::cin>>mat[i][j];
			}
		}
	
		auto mat2=KreirajDinamickuKopiju2D(mat);
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				std::cout<<mat2[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
		for(int i=0;i<n;i++) delete[] mat2[i];
		delete[] mat2;
	}
	catch(...) {
		std::cout<<"Nedovoljno memorije";
	}
	return 0;
}