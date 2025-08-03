#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
typedef std::vector<std::vector<int>> Matrica;
typedef std::vector<int> Vektor;

Matrica KroneckerovProizvod(Vektor v1, Vektor v2) {
    int n=v1.size();
    int m=v2.size();
    Matrica a(n, Vektor(m));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            a[i][j] = v1[i]*v2[j];
        }
    }
    return a;
}

int NajvecaSirina(Matrica m) {
    int brojac=0;
    int max_cifara=0;
    if(m.size()==0) return 0;
    for(int i=0;i<m.size();i++) {
        for(int j=0;j<m[i].size();j++) {
            brojac=0;
            if(m[i][j]<0) brojac++;
            while(m[i][j]!=0) {
                brojac++;
                m[i][j]/=10;
            }
            if(brojac>max_cifara) max_cifara=brojac;
        }
    }
    return max_cifara;
}

int main ()
{
    int n,m;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>n;
    Vektor v1(n);
    std::cout<<"Unesite elemente prvog vektora: ";
    for(int i=0;i<n;i++) std::cin>>v1[i];
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>m;
    Vektor v2(m);
    std::cout<<"Unesite elemente drugog vektora: ";
    for(int i=0;i<m;i++) std::cin>>v2[i];
    std::cout<<std::endl;
    Matrica mat = KroneckerovProizvod(v1,v2);
    int sirina = NajvecaSirina(mat);
    for(int i=0;i<mat.size();i++) {
        for(int j=0;j<mat[i].size();j++) {
            std::cout<<std::right<<std::setw(sirina+1)<<mat[i][j];
        }
        std::cout<<std::endl;
    }
	return 0;
}
