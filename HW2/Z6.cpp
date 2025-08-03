#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <new>

std::string SvaVelika(std::string s) {
    for(int i=0;i<s.length();i++) {
        s.at(i)=toupper(s.at(i));
    }
    return s;
}

bool KriterijSortiranja(std::string s1, std::string s2) {
    int duzina1=s1.length();
    int duzina2=s2.length();
    if(duzina1<duzina2) return true;
    else if(duzina1==duzina2) {
        if(SvaVelika(s1)<SvaVelika(s2)) return true;
    }
    return false;
}

bool PretraziBinarno(std::string *p,int velicina, std::string s) {
    return std::binary_search(p,p+velicina,s,KriterijSortiranja);
}

void SortirajPoDuzini(std::string *p,int velicina) {
    std::sort(p,p+velicina,KriterijSortiranja);
}

int main ()
{
    long long int n;
    std::cout<<"Unesite broj rijeci: ";
    std::cin>>n;
    std::string *p=nullptr;
    try {
        p=new std::string[n];
        std::cout<<"Unesite rijeci: ";
        for(int i=0;i<n;i++) {
            std::cin>>p[i];
        }
        std::cout<<"Sortirane rijeci: ";
        SortirajPoDuzini(p,n);
        for(int i=0;i<n;i++) std::cout<<p[i]<<" ";
        std::cout<<std::endl;
        std::cout<<"Unesite rijec za pretragu: ";
        std::string nova;
        std::cin>>nova;
        bool a = PretraziBinarno(p,n,nova);
        if(a) std::cout<<"Rijec '"<<nova<<"' se nalazi u nizu.";
        else std::cout<<"Rijec '"<<nova<<"' se ne nalazi u nizu.";
        delete[] p;
    }
    catch(...) {
        std::cout<<"Nedovoljno memorije!";
    }
	return 0;
}