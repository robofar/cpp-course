#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <deque>

template<typename NekiTip>
auto KreirajDinamickuKopiju2D(NekiTip mat) -> typename std::remove_reference<decltype(mat[0][0])>::type**{
	typename std::remove_reference<decltype(mat[0][0])>::type** matrica=nullptr;
	int n=mat.size();
	int broj_elemenata=0;
	try {
		matrica=new typename std::remove_reference<decltype(mat[0][0])>::type*[n]{};
		try {
			for(int i=0;i<n;i++) {
				broj_elemenata+=mat.at(i).size();
			}
			matrica[0]=new typename std::remove_reference<decltype(mat[0][0])>::type[broj_elemenata];
			for(int i=1;i<mat.size();i++) {
				matrica[i]=matrica[i-1]+mat.at(i-1).size(); //mora .at(i-1); bio sam stavio .at(i) al ugl mozes skontat sto
			}
			
			for(int i=0;i<mat.size();i++) {
				for(int j=0;j<mat.at(i).size();j++) {
					matrica[i][j]=mat[i][j];
				}
			}
			}
		catch(std::bad_alloc) {
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
		delete[] mat2[0];
		delete[] mat2;
	}
	catch(...) {
		std::cout<<"Nedovoljno memorije";
	}
	return 0;
}