#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <stdexcept>
#include <vector>

template <typename TipElemenata>
class DatotecniKontejner {
private:
    std::fstream tok;
public:
    DatotecniKontejner(const std::string &ime_datoteke) {
        tok.open(ime_datoteke,std::ios::in | std::ios::binary); //citanje -> provjera da li postoji
        if(!tok) { //datoteka ne postoji -> sad je napravi tako sto ces je otvoriti u modu za pisanje
            tok.clear(); //oporavljam tok
            tok.open(ime_datoteke,std::ios::out | std::ios::binary);   // napravis datoteku
            if(!tok) throw std::logic_error("Problemi prilikom otvaranja ili kreiranja datoteke");
            tok.close();
            tok.open(ime_datoteke, std::ios::out | std::ios::in | std::ios::binary); //sad kad je imas napravljenu otvoris je da radi u oba moda
        }
        else {
            tok.close(); //tok se prvo mora zatvoriti prije sljedeceg otvaranja
            tok.open(ime_datoteke,std::ios::out | std::ios::in | std::ios::binary);
        }
    }
    void DodajNoviElement(const TipElemenata &element) {
        TipElemenata pomocni=element;
        tok.seekp(0,std::ios::end);
        tok.write(reinterpret_cast<char*>(&pomocni),sizeof pomocni); //pise se na kraj datoteke zbog ios::app
        if(!tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
        tok.flush(); //praznjenje toka iako buffer nije pun kad mi hocemo
    }
    int DajBrojElemenata() {
        tok.seekg(0,std::ios::end);
        int broj = tok.tellg()/sizeof(TipElemenata);
        return broj;
    } 
    TipElemenata DajElement(int pozicija) {
        int broj_elemenata=DajBrojElemenata();
        if(pozicija<0) throw std::range_error("Neispravna pozicija");
        if(pozicija >= broj_elemenata) throw std::range_error("Neispravna pozicija");
        TipElemenata pomocni;
        tok.seekg(pozicija*sizeof(TipElemenata),std::ios::beg);
        tok.read(reinterpret_cast<char*>(&pomocni),sizeof pomocni);
        if(!tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
        return pomocni;
    }
    void IzmijeniElement(int pozicija,const TipElemenata &element) {
        tok.seekg(0,std::ios::end);
        int broj_elemenata=tok.tellg()/sizeof(TipElemenata);
        if(pozicija<0 || pozicija>=broj_elemenata) throw std::range_error("Neispravna pozicija");
        tok.seekp(pozicija*sizeof(TipElemenata));
        tok.write(reinterpret_cast<const char*>(&element),sizeof element);
        if(!tok) throw std::logic_error("Problemi prilikom pristupa datoteci");
        tok.flush(); 
    } 
    void Sortiraj(std::function<bool(const TipElemenata &,const TipElemenata &)> kriterij=std::less<TipElemenata>()) {
        for(int i=0;i<DajBrojElemenata();i++) {
            int q=i;
            for(int j=i+1;j<DajBrojElemenata();j++) {
                if(kriterij(DajElement(j),DajElement(q))) q=j;
            }
            TipElemenata p=DajElement(i);
            IzmijeniElement(i,DajElement(q));
            IzmijeniElement(q,p);
        }
    }
    
};
int main ()
{
try {
    DatotecniKontejner<double> dat("nova.DAT");
    std::vector<double> v{1.2,6.5,12.6,5,9.8,11.2};
    std::cout<<"Vektor je: ";
    std::cout<<std::endl;
    for(int i=0;i<v.size();i++) std::cout<<v.at(i)<<", ";
    std::cout<<std::endl;
    for(int i=0;i<v.size();i++) {
        dat.DodajNoviElement(v[i]);
    }
    std::cout<<"Datoteka ima: "<<dat.DajBrojElemenata()<<" elemenata";
    std::cout<<std::endl;
    std::cout<<"Prvi i treci element su: ";
    std::cout<<std::endl;
    std::cout<<dat.DajElement(0)<<" i "<<dat.DajElement(2);
    std::cout<<std::endl;
    std::cout<<"Sada cemo izmijeniti ova dva elementa, i ispisati ih: ";
    dat.IzmijeniElement(0,54.3);
    dat.IzmijeniElement(2,76.4);
    std::cout<<std::endl;
    std::cout<<dat.DajElement(0)<<" i "<<dat.DajElement(2);
    std::cout<<std::endl;
    std::cout<<"Sortirani sadrzaj je: ";
    std::cout<<std::endl;
    dat.Sortiraj();
    for(int i=0;i<v.size();i++) std::cout<<dat.DajElement(i)<<", ";
}
catch(std::logic_error iz) {
    std::cout<<iz.what();
}
catch(std::range_error iz) {
    std::cout<<iz.what();
}
    
	return 0;
}