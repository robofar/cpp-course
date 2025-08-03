#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <stdexcept>
struct  Dijete {
    std::string ime;
    Dijete* sljedeci;
};

std::vector<std::set<std::string>> Razvrstavanje(std::vector<std::string> imena,int timovi) {
    if(timovi<1 || timovi>imena.size()) throw std::logic_error("Razvrstavanje nemoguce");
    Dijete* pocetak=nullptr;
    Dijete* predhodni;
    /* Po zavrsetku ove petlje zadnja dodjela predhodni ce biti takva da je 
    predhodni->sljedeci NULLPTR, te njega iza petlje stavi da pokazuje na pocetak ponovo */
    for(int i=0;i<imena.size();i++) {
        Dijete* novi=new Dijete{imena.at(i),nullptr};
        if(!pocetak) pocetak=novi;
        else predhodni->sljedeci=novi;
        predhodni=novi;
    }
    predhodni->sljedeci=pocetak; //sad ovaj zadnji sljedeci(tj veza) nije nullptr nego pokazuje na pocetnu strukturu
    
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
         //   std::cout<<pomocni<<std::endl;
             /* izbacivanje iz povezanih cvorova */
            predhodni->sljedeci=pocetak->sljedeci; //pok sljedeci iz predhodnog sad pokazuje na onaj cvor na koji pokazuje sljedeci od onog kojeg trebamo izbacit -> tj. na sljedeci svor :D
            pocetak->sljedeci=nullptr; //prvo moram sljedeci unutar cvora kojeg izbacujem stavit na nullptr, jer ako izbrisem taj cvoj onda ovom sljedeci necu nikad moc pristupit - kruzno dereferenciranje
            if(pocetak==predhodni) {
                delete pocetak;
                break;
            }
            else {
            delete pocetak;
            /* Kad ostane zadnji element na njega pokazuju i pocetak i predhodni tako da kad
            obrisemo pocetak obrisali smo i predhodni ALI mu pristupim dole u for-u i tu je GRESKA
            tako da ovaj dole for izvravaj samo kad ima vise od jednog cvora tj 2+ */
            pocetak=predhodni->sljedeci; //pocetak ponovo vracamo da pokazuje na sljedeci element
           bool pikaj_trenutni=true;
            for(int k=0;k<pomocni.length();k++) {
                if(((pomocni.at(k)>='a' && pomocni.at(k)<='z') || (pomocni.at(k)>='A' && pomocni.at(k)<='Z') || (pomocni.at(k)>='0' && pomocni.at(k)<='9')) && pikaj_trenutni) pikaj_trenutni=false;
                else if((pomocni.at(k)>='a' && pomocni.at(k)<='z') || (pomocni.at(k)>='A' && pomocni.at(k)<='Z') || (pomocni.at(k)>='0' && pomocni.at(k)<='9')) {
                    /* MORAM POMJERAT I POCETAK I PREDHODNI (pocetak je onaj kojim hodam iako se zove pocetak :P) */
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