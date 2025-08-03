#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cctype>
std::string SvaVelika(std::string s) {
    for(int i=0;i<s.length();i++) {
        s.at(i)=toupper(s.at(i));
    }
    return s;
}

void IzdvojiKrajnjeRijeci(std::vector<std::string> vs,std::string &p,std::string &z) {
    if(vs.size()==0) {
        p="";
        z="";
        return;
    }
    p=vs.at(0);
    z=vs.at(0);
    for(int i=1;i<vs.size();i++) {
        if(SvaVelika(vs.at(i)) > SvaVelika(z)) z=vs.at(i);
        if(SvaVelika(vs.at(i)) < SvaVelika(p)) p=vs.at(i);
    }
}
void IzbaciDuplikateDuplikata(std::vector<std::string> &vs) {
    for(int i=0;i<vs.size();i++) {
        for(int j=i+1;j<vs.size();j++) {
            if(vs.at(i)==vs.at(j)) {
                for(int k=j;k<vs.size()-1;k++) {
                    vs.at(k)=vs.at(k+1);
                }
                j--;
                vs.resize(vs.size()-1);
            }
        }
    }
}
void ZadrziDuplikate(std::vector<std::string> &vs) {
    std::vector<std::string> q; //sadrzi sve dupllikate
    for(int i=0;i<vs.size();i++) {
        for(int j=i+1;j<vs.size();j++) {
            if(vs.at(i)==vs.at(j)) {
                q.push_back(vs.at(i));
                break;
            }
        }
    }
    vs=q;
    IzbaciDuplikateDuplikata(vs);
}

int main ()
{
    int n;
    std::cout<<"Koliko zelite unijeti rijeci: ";
    std::cin>>n;
    std::cin.ignore(1000,'\n');
    std::vector<std::string> v;
    std::cout<<"Unesite rijeci: ";
    for(int i=0;i<n;i++) {
        std::string s;
        std::cin>>s;
        v.push_back(s);
    }
    
    std::string prva;
    std::string posljednja;
    
    IzdvojiKrajnjeRijeci(v, prva, posljednja);
    ZadrziDuplikate(v); 
    
    std::cout<<std::endl;
    std::cout<<"Prva rijec po abecednom poretku je: "<<prva;
    std::cout<<std::endl;
    std::cout<<"Posljednja rijec po abecednom poretku je: "<<posljednja;
    std::cout<<std::endl;
    
    std::cout<<"Rijeci koje se ponavljaju su: ";
    for(int i=0;i<v.size();i++) {
        if(i==v.size()-1) std::cout<<v.at(i);
        else std::cout<<v.at(i)<<" ";
    }
	return 0;
}