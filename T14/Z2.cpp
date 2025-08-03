#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include <fstream>
#include <cstring>

class Spremnik {
protected:
    double tezina;
    char naziv[1000]; ///////////////////
public:
    virtual ~Spremnik() {}
    Spremnik(double t,const char* n) : tezina(t) {
        std::strcpy(naziv,n);
    }
    double DajTezinu() const { return tezina; }
    virtual double DajUkupnuTezinu() const =0;
    virtual void Ispisi() const=0;
    virtual std::shared_ptr<Spremnik> DajKopiju() const =0;
};

class Sanduk: public Spremnik {
private:
    int broj_predmeta;
    double tezine_predmeta;
public:
    Sanduk(double t,const char np[],int bp,double tp) : Spremnik(t,np),broj_predmeta(bp),tezine_predmeta(tp) {}
    double DajUkupnuTezinu() const override {
        double ukupno=tezina;
        for(int i=0;i<broj_predmeta;i++) ukupno+=tezine_predmeta;
        return ukupno;
    }
    std::shared_ptr<Spremnik> DajKopiju() const override {
        return std::make_shared<Sanduk>(*this);
    }
    void Ispisi() const override {
        std::cout<<"Vrsta spremnika: Sanduk"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
};

class Bure : public Spremnik {
private:
    double tezina_tecnosti;
public:
    Bure(double t,const char nt[],double tt) : Spremnik(t,nt),tezina_tecnosti(tt) {}
    std::shared_ptr<Spremnik> DajKopiju() const override {
        return std::make_shared<Bure>(*this);
    }
    double DajUkupnuTezinu() const override {
        double ukupno(tezina+tezina_tecnosti);
        return ukupno;
    }
    void Ispisi() const override {
        std::cout<<"Vrsta spremnika: Bure"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
};

class Skladiste {
private:
    std::vector<std::shared_ptr<Spremnik>> v;
public:
    explicit Skladiste(int broj) : v(broj) {}
    Skladiste() : v(0) {}
    Skladiste(const Skladiste &s) {
        v.resize(s.v.size());
        try {
            for(int i=0;i<s.v.size();i++) {
                v[i]=s.v[i]->DajKopiju();
            }
        }
        catch(...) {
            v.resize(0);
            throw;
        }
    }
    Skladiste(Skladiste &&s) : v(std::move(s.v)) {}
    Skladiste& operator = (Skladiste &&s) {
        v=std::move(s.v);
        return *this;
    }
    Skladiste& operator = (const Skladiste &s) {
        if(this==&s) return *this;
        std::vector<std::shared_ptr<Spremnik>> pomocni;
        pomocni.resize(s.v.size());
        try {
            for(int i=0;i<pomocni.size();i++) {
                pomocni[i]=s.v[i]->DajKopiju();
            }
        }
        catch(...) {
            pomocni.resize(0);
            throw;
        }
        v=pomocni;
        pomocni.resize(0);
        return *this;
    }
    Spremnik* DodajSanduk(double t,const char np[],int bp,double tp) {
        Sanduk san(t,np,bp,tp);
        v.push_back(san.DajKopiju());
        return v[v.size()-1].get();
    }
    Spremnik* DodajBure(double t,const char nt[],double tt) {
        Bure bur(t,nt,tt);
        v.push_back(bur.DajKopiju());
        return v.at(v.size()-1).get();
    }
    Spremnik* DodajSpremnik(Spremnik* novi,bool q) {
        if(q) {
            v.push_back(std::shared_ptr<Spremnik>(novi));
            novi=nullptr;
        }
        else {
            std::shared_ptr<Spremnik> kopija=novi->DajKopiju();
            v.push_back(kopija);
            kopija=nullptr;
            novi=nullptr;
        }
        return v.at(v.size()-1).get();
    }
    void BrisiSpremnik(Spremnik* brisi) {
        for(int i=0;i<v.size();i++) {
            if(v.at(i).get()==brisi) {
                for(int j=i;j<v.size()-1;j++) {
                    v.at(j)=v.at(j+1);
                }
                v.resize(v.size()-1);
            }
        }
    }
    Spremnik& DajjNajlaksi() const {
        if(v.size()==0) throw std::range_error("Skladiste je prazno");
        double najmanji=v.at(0)->DajTezinu();
        int indeks=0;
        for(int i=1;i<v.size();i++) {
            if(v.at(i)->DajTezinu() < najmanji) {
                najmanji=v.at(i)->DajTezinu();
                indeks=i;
            }
        }
        return *v.at(indeks);
    }
    Spremnik& DajNajtezi() const {
        if(v.size()==0) throw std::range_error("Skladiste je prazno");
        double najveci=v.at(0)->DajTezinu();
        int indeks=0;
        for(int i=1;i<v.size();i++) {
            if(v.at(i)->DajTezinu() > najveci) {
                najveci=v.at(i)->DajTezinu();
                indeks=i;
            }
        }
        return *v.at(indeks);
    }
    int BrojPreteskih(double a) const {
        int brojac=0;
        for(int i=0;i<v.size();i++) {
            if(v.at(i)->DajUkupnuTezinu() > a) brojac++;
        }
        return brojac;
    }
    void IzlistajSkladiste() const {
        std::vector<std::shared_ptr<Spremnik>> novi=v;
        std::sort(novi.begin(),novi.end(),[](std::shared_ptr<Spremnik> a,std::shared_ptr<Spremnik> b)->bool {
            return a->DajUkupnuTezinu() > b->DajUkupnuTezinu();
        });
        for(int i=0;i<novi.size();i++) {
            novi[i]->Ispisi();
        }
        novi.resize(0);
    }
    void UcitajIzDatoteke(std::string ime_datoteke) {
        std::ifstream ulazni_tok(ime_datoteke);
        if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
        if(v.size()!=0) v.resize(0);
        while(ulazni_tok && !ulazni_tok.eof()) {
            std::string prvi;
            char naziv[1000];
            ulazni_tok >> prvi;
            ulazni_tok.seekg(1,std::ios::cur);
            ulazni_tok.getline(naziv,sizeof naziv);
            if(prvi=="S") {
                int broj_predmeta;
                double tezina_sanduka;
                double tezina_svakog;
                ulazni_tok>>tezina_sanduka>>broj_predmeta>>tezina_svakog;
                DodajSanduk(tezina_sanduka,naziv,broj_predmeta,tezina_svakog);
            }
            else if(prvi=="B") {
                double tezina_bureta,tezina_tec;
                ulazni_tok>>tezina_bureta>>tezina_tec;
                DodajBure(tezina_bureta,naziv,tezina_tec);
            }
        }
        if(!ulazni_tok) {
            if(ulazni_tok.bad()) throw std::logic_error("Problemi pri citanju datoteke");
            else throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
        ulazni_tok.clear();
        ulazni_tok.close();
    }
 };
 
int main () {
    Skladiste ETF;
    try {
        ETF.UcitajIzDatoteke("ROBA.TXT");
        ETF.IzlistajSkladiste();
    }
    catch(std::logic_error iz) {
        std::cout<<iz.what();
    }
    catch(std::range_error iz) {
        std::cout<<iz.what();
    }
	return 0;
}