#include <iostream>
#include <vector>
#include <string>

template <typename NekiTip>
NekiTip Presjek(const NekiTip &v1, const NekiTip &v2) {
    NekiTip novi;
    for(int i=0;i<v1.size();i++) {
        for(int j=0;j<v2.size();j++) {
            if(v1.at(i) == v2.at(j)) {
                novi.push_back(v1.at(i));
                break;
            }
        }
    }
    
    /* Filtrirajmo sad niz novi */
    for(int i=0;i<novi.size();i++) {
        for(int j=i+1;j<novi.size();j++) {
            if(novi.at(i)==novi.at(j)) {
                for(int k=j;k<novi.size()-1;k++) {
                    novi.at(k)=novi.at(k+1);
                }
                j--;
                novi.resize(novi.size()-1);
            }
        }
    }
 return novi;
}

int main ()
{
    std::cout<<"Test za realne brojeve..."<<std::endl;
    int n;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>n;
    std::vector<int> v1;
    std::cout<<"Unesite elemente prvog vektora: ";
    for(int i=0;i<n;i++) {
        int broj;
        std::cin>>broj;
        v1.push_back(broj);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    int m;
    std::cin>>m;
    std::cout<<"Unesite elemente drugog vektora: ";
    std::vector<int> v2;
    for(int i=0;i<m;i++) {
        int broj;
        std::cin>>broj;
        v2.push_back(broj);
    }
    
    std::vector<int> r1=Presjek(v1,v2);
    std::cout<<"Zajednicki elementi su: ";
    for(int i=0;i<r1.size();i++) {
        std::cout<<r1.at(i)<<" ";
    }
    
    std::cout<<"\n\n";
    
    std::cout<<"Test za stringove..."<<std::endl;
    int a,b;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>a;
    std::cin.ignore(1000,'\n');
    std::vector<std::string> s1;
    std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
    for(int i=0;i<a;i++) {
        std::string s;
        std::getline(std::cin,s);
        s1.push_back(s);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>b;
    std::cin.ignore(1000,'\n');
    std::vector<std::string> s2;
    std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
    for(int i=0;i<b;i++) {
        std::string s;
        std::getline(std::cin,s);
        s2.push_back(s);
    }
    std::vector<std::string> r2=Presjek(s1,s2);
    std::cout<<"Zajednicki elementi su: \n";
    for(int i=0;i<r2.size();i++) {
        std::cout<<r2.at(i)<<"\n";
    }
    
	return 0;
}