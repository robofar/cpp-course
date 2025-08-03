#include <iostream>
#include <vector>
#include <string>
#include <list>

template<typename Tip>
struct Cvor{
    Tip elemenat;
    Cvor* veza;
};

template<typename TipElemenata>
Cvor<TipElemenata>* KreirajPovezanuListu(TipElemenata zavrsni) {
    Cvor<TipElemenata>* pocetak=nullptr;
    Cvor<TipElemenata>* predhodni=nullptr;
    for(;;) {
        TipElemenata unos;
        std::cin>>unos;
        if(unos==zavrsni) break;
        Cvor<TipElemenata>* novi=new Cvor<TipElemenata>{unos,nullptr};
        if(!pocetak) pocetak=novi;
        else predhodni->veza=novi;
        predhodni=novi;
    }
    return pocetak;
}

template<typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata>* pocetak) {
    if(!pocetak) return 0;
    int brojac=0;
    for(Cvor<TipElemenata>* x=pocetak; x!=nullptr; x=x->veza) brojac++;
    return brojac;
}

template<typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata>* pocetak) {
    TipElemenata suma=TipElemenata(); /* ili TipElemenata suma{} */
    for(auto x=pocetak;x!=nullptr;x=x->veza) suma+=x->elemenat;
    return suma;
}

template<typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata>* pocetak,TipElemenata prag) {
    if(pocetak==nullptr) return 0;
    int brojac=0;
    for(auto x=pocetak;x!=nullptr;x=x->veza) {
        if(x->elemenat > prag) brojac++;
    }
    return brojac;
}

template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata>* pocetak) {
    while(pocetak!=nullptr) {
        auto sljedeci=pocetak->veza;
        delete pocetak;
        pocetak=sljedeci;
    }
}

int main() {
    double x=0;
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    auto pocetak = KreirajPovezanuListu(x);
    int broj = BrojElemenata(pocetak);
    double suma=SumaElemenata(pocetak);
    double as=suma/broj;
    int vecih_od=BrojVecihOd(pocetak,as);
    std::cout<<"U slijedu ima "<<vecih_od<<" brojeva vecih od njihove aritmeticke sredine";
    UnistiListu(pocetak);
    return 0;
}