#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stdexcept>
#include <new>
#include <memory>

struct  Dijete {
    std::string ime;
    std::shared_ptr<Dijete> sljedeci;
};

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> imena,int timovi) {
    if(timovi<1 || timovi>imena.size()) throw std::logic_error("Razvrstavanje nemoguce");
    std::shared_ptr<Dijete> pocetak=nullptr;
    std::shared_ptr<Dijete> predhodni;
    for(int i=0;i<imena.size();i++) {
        /* mora ici ovako : std::make_shared<Dijete>(Dijete{imena.at(i),nullptr});
        jer je tip na sta pokazuje pametni Dijete
        ALI mora opet u zagradama ici Dijete jer se MORA NAVESTI ZA STA SE KORISTE viticaste zagrade
        pri inicijalizaciji - tj kazes da je za strukturu dijete */
        std::shared_ptr<Dijete> novi=std::make_shared<Dijete>(Dijete{imena.at(i),nullptr});
        if(!pocetak) pocetak=novi;
        else predhodni->sljedeci=novi;
        predhodni=novi;
    }
    predhodni->sljedeci=pocetak; 
    
    std::vector<std::set<std::string>> rez(timovi);
    int broj_imena=imena.size();
    int tim_sa_vise=broj_imena%timovi;
    int tim_sa_manje=timovi-tim_sa_vise;
    int broj_sa_vise=broj_imena/timovi+1;
    int broj_sa_manje=broj_imena/timovi;
    
    int broj_imena_po_timu=broj_sa_vise;
    for(int i=0;i<timovi;i++) {
        if(i<tim_sa_vise) broj_imena_po_timu=broj_sa_vise;
        else broj_imena_po_timu=broj_sa_manje;
        for(int j=0;j<broj_imena_po_timu;j++) {
            std::string pomocni=pocetak->ime;
            rez.at(i).insert(pomocni);
            predhodni->sljedeci=pocetak->sljedeci; 
            pocetak->sljedeci=nullptr; 
            if(pocetak==predhodni) {
                /* Kad ova dva pokazuju na isti, ukupno tri pokazuju na taj zadnji pa ih moram prekinuti da bi se i zadnji obrisao kad brojac padne na 0 */
                pocetak->sljedeci=nullptr;
                pocetak=nullptr;
                predhodni=nullptr;
                break;
            }
            else {
           pocetak=predhodni->sljedeci; // OVO JE GLAVNA STVAR
           //KAD OVAJ PREUSMJERIM NA DRUGI OBJEKAT, BROJAC IZA STAROG OBJEKTA POSTAJE 0 I ON SE SAM UNISITI
           bool pikaj_trenutni=true;
            for(int k=0;k<pomocni.length();k++) {
                if(((pomocni.at(k)>='a' && pomocni.at(k)<='z') || (pomocni.at(k)>='A' && pomocni.at(k)<='Z') || (pomocni.at(k)>='0' && pomocni.at(k)<='9')) && pikaj_trenutni) pikaj_trenutni=false;
                else if((pomocni.at(k)>='a' && pomocni.at(k)<='z') || (pomocni.at(k)>='A' && pomocni.at(k)<='Z') || (pomocni.at(k)>='0' && pomocni.at(k)<='9')) {
                    pocetak=pocetak->sljedeci;
                    predhodni=predhodni->sljedeci;
                }
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