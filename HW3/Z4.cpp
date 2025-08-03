#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <list>
#include <stdexcept>

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> imena,int timovi) {
    if(timovi<1 || timovi>imena.size()) throw std::logic_error("Razvrstavanje nemoguce");
    std::list<std::string> lista;
    for(int i=0;i<imena.size();i++) lista.push_back(imena.at(i));
    std::vector<std::set<std::string>> rez(timovi);
    int broj_imena=imena.size();
    int tim_sa_vise=broj_imena%timovi;
    int tim_sa_manje=timovi-tim_sa_vise;
    int broj_sa_vise=broj_imena/timovi + 1;
    int broj_sa_manje=broj_imena/timovi;
    
    auto it=lista.begin();
    int broj_imena_po_timu=broj_sa_vise;
    for(int i=0;i<timovi;i++) {
        if(i<tim_sa_vise) broj_imena_po_timu=broj_sa_vise;
        else broj_imena_po_timu=broj_sa_manje;
        for(int j=0;j<broj_imena_po_timu;j++) {
            std::string pomocni=*it;
            rez.at(i).insert(pomocni);
            it=lista.erase(it);
            it--;
            for(int k=0;k<pomocni.length();k++) {
                if((pomocni.at(k)>='a' && pomocni.at(k)<='z') || (pomocni.at(k)>='A' && pomocni.at(k)<='Z') || (pomocni.at(k)>='0' && pomocni.at(k)<='9')) {
                    it++;
                    if(it==lista.end()) it=lista.begin();
                }
            }
        }
    }
    return rez;
}
int main ()
{
    try {
        int n;
        std::vector<std::string> djeca;
        std::cout<<"Unesite broj djece: ";
        std::cin>>n;
        std::cin.ignore(1000,'\n');
        std::cout<<"Unesite imena djece: "<<std::endl;
        for(int i=0;i<n;i++) {
            std::string s;
            std::getline(std::cin,s);
            djeca.push_back(s);
        }
        int timovi;
        std::cout<<"Unesite broj timova: ";
        std::cin>>timovi;
        std::vector<std::set<std::string>> rezultat=Razvrstavanje(djeca,timovi);
        for(int i=0;i<timovi;i++) {
            std::cout<<"Tim "<<i+1<<": ";
            int x=rezultat.at(i).size();
            auto it=rezultat.at(i).begin();
            for(int j=0;j<x;j++) {
                if(j==x-1) std::cout<<*it;
                else std::cout<<*it<<", ";
                it++;
            }
            std::cout<<std::endl;
        }
    }
    catch(std::logic_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what();
    }
	return 0;
}