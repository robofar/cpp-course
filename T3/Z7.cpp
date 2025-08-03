#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

typedef std::vector<std::vector<int>> Matrica;

int NajvecaSirina(Matrica m) {
    int brojac=0;
    int max_cifara=0;
    if(m.size()==0) return 0;
    for(int i=0;i<m.size();i++) {
        for(int j=0;j<m[i].size();j++) {
            brojac=0;
            while(m[i][j]!=0) {
                brojac++;
                m[i][j]/=10;
            }
            if(brojac>max_cifara) max_cifara=brojac;
        }
    }
    return max_cifara;
}

Matrica PascalovTrougao(int n) {
    Matrica p; // prazna matrica
    if(n==0) return p;
    if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");
    p.resize(n);
    
    for(int i=0;i<n;i++) p.at(i).resize(i+1);
    
    for(int i=0;i<n;i++) {
        p.at(i).at(0)=1;
        p.at(i).at(i)=1;
    }
    
    for(int i=2;i<n;i++) {
        for(int j=1;j<p.at(i).size()-1;j++) {
            p.at(i).at(j) = p.at(i-1).at(j) + p.at(i-1).at(j-1);
        }
    }
    return p;
}
int main ()
{
	int n;
	std::cout<<"Unesite broj redova: ";
	std::cin>>n;
	std::cout<<std::endl;
	Matrica mat=PascalovTrougao(n);
	int sirina=NajvecaSirina(mat);
	
	for(int i=0;i<mat.size();i++) {
	    for(int j=0;j<mat[i].size();j++) {
	        std::cout<<std::right<<std::setw(sirina+1)<<mat[i][j];
	    }
	    std::cout<<std::endl;
	}
	return 0;
}
