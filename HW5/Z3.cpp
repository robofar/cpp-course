#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>
#include <stdexcept>
#include <fstream>

/* DajKopiju su mi smart pointers zbog dole vektora pametnih pokazivaca */
class Spremnik {
protected:
    double tezina;
    std::string naziv;
public:
    virtual ~Spremnik() {}
    Spremnik(double t,std::string n) : tezina(t),naziv(n) {}
    double DajTezinu() const { return tezina; }
    /* ove metode u nasljedjenim klasama mogu biti override a i ne moraju */
    virtual double DajUkupnuTezinu() const = 0; //apstraktna metoda
    virtual void Ispisi() const = 0; //apstraktna metoda
    virtual std::shared_ptr<Spremnik> DajKopiju() const = 0;
};

class Sanduk : public Spremnik {  //cvrsti predmeti
private:
    std::vector<double> tezine_predmeta;
public:
    Sanduk(double t,std::string np,std::vector<double> tp) : Spremnik(t,np),tezine_predmeta(tp) {}
    double DajUkupnuTezinu() const override {
        double ukupno=tezina;
        std::for_each(tezine_predmeta.begin(),tezine_predmeta.end(),[&ukupno](double x) {
            ukupno+=x;
        });
        return ukupno;
    }
    std::shared_ptr<Spremnik> DajKopiju() const override {
        return std::make_shared<Sanduk>(*this);
    }
    void Ispisi() const override {
        std::cout<<"Vrsta spremnika: Sanduk"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv<<std::endl;
        std::cout<<"Tezine predmeta: ";
        for(int i=0;i<tezine_predmeta.size();i++) {
            std::cout<<tezine_predmeta.at(i)<<" ";
        }
        std::cout<<"(kg)"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
    }
};

class Vreca : public Spremnik {   //praskaste materije
private:
    double tezina_materije;
public:
    Vreca(double t,std::string nm,double tm) : Spremnik(t,nm), tezina_materije(tm) {}
    double DajUkupnuTezinu() const override { return tezina+tezina_materije; }
    std::shared_ptr<Spremnik> DajKopiju() const override {
        return std::make_shared<Vreca>(*this);
    }
    void Ispisi() const override {
        std::cout<<"Vrsta spremnika: Vreca"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
        std::cout<<"Tezina pohranjene materije: "<<DajUkupnuTezinu()-DajTezinu()<<" (kg)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
    }
};

class Bure : public Spremnik {    //tecnosti
private:
    double gustina;
    double zapremina_tecnosti;
public:
    Bure(double t,std::string nt,double g,double zt) : Spremnik(t,nt),gustina(g),zapremina_tecnosti(zt) {}
    std::shared_ptr<Spremnik> DajKopiju() const override {
        return std::make_shared<Bure>(*this);
    }
    double DajUkupnuTezinu() const override {
        double x((gustina*zapremina_tecnosti)/1000);
        double ukupno(x+tezina);
        return ukupno;
    }
    void Ispisi() const override {
        std::cout<<"Vrsta spremnika: Bure"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" (kg)"<<std::endl;
        std::cout<<"Specificna tezina tecnosti: "<<gustina<<" (kg/m^3)"<<std::endl;
        std::cout<<"Zapremina tecnosti: "<<zapremina_tecnosti<<" (l)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
    }
};

class Skladiste {
private:
    std::vector<std::shared_ptr<Spremnik>> v;
public:
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
    Spremnik* DodajSanduk(double t,std::string np,std::vector<double> tp) {
        Sanduk san(t,np,tp);
        v.push_back(san.DajKopiju()); //ili v.push_back(std::make_shared<Sanduk>(t,np,tp);
        return v[v.size()-1].get(); //ovo size - 1 jer pushbekom dodamo na kraj ; .get() moram ga pretvorit u glupi pokazivac
    }
    Spremnik* DodajVrecu(double t,std::string nm,double tm) {
        Vreca vre(t,nm,tm);
        v.push_back(vre.DajKopiju());
        return v[v.size()-1].get();
    }
    Spremnik* DodajBure(double t,std::string nt,double g,double zt) {
        Bure bur(t,nt,g,zt);
        v.push_back(bur.DajKopiju());
        return v.at(v.size()-1).get();
    }
    Spremnik* DodajSpremnik(Spremnik* novi,bool q) {
        if(q) {
            v.push_back(std::shared_ptr<Spremnik>(novi)); //konverzija u pametni pokazivac
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
            if(v.at(i).get() == brisi) {
                for(int j=i;j<v.size()-1;j++) {
                    v.at(j)=v.at(j+1);
                }
                v.resize(v.size()-1);
            }
        }
    }
    Spremnik& DajNajlaksi() const {
        if(v.size()==0) throw std::range_error("Skladiste je prazno");
        double najmanji=v.at(0)->DajTezinu();
        int indeks = 0;
        for(int i=1;i<v.size();i++) {
            if(v.at(i)->DajTezinu()<najmanji) {
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
            if(v.at(i)->DajTezinu()>najveci) {
                najveci=v.at(i)->DajTezinu();
                indeks=i;
            }
        }
        return *v.at(indeks);
    }
    int BrojPreteskih(double a) const {
        int brojac=0;
        for(int i=0;i<v.size();i++) {
            if(v.at(i)->DajUkupnuTezinu()>a) brojac++;
        }
        return brojac;
    }
    void IzlistajSkladiste() const {
        std::vector<std::shared_ptr<Spremnik>> novi=v;
        std::sort(novi.begin(),novi.end(),[](std::shared_ptr<Spremnik> a,std::shared_ptr<Spremnik> b)->bool {
           return a->DajUkupnuTezinu()>b->DajUkupnuTezinu();
        });
        for(int i=0;i<novi.size();i++) {
            novi[i]->Ispisi();
        }
        novi.resize(0);
    }
       
    void UcitajIzDatoteke(std::string ime_datoteke) {
        bool visak=false;
        std::ifstream ulazni_tok(ime_datoteke);
        if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
        if(v.size()!=0) v.resize(0);
        while(ulazni_tok && !ulazni_tok.eof()) { //ako je sve uredu on ce biti u ispravnom stanju, ali tad i na kraju ce biti u ispravnom stanju
        //te ce se petlja jos jednom izvrsiti i onda ce doci u neispravno stanje (iako je sve uredu bilo). zato ide jos da bude razlicito od eof-a 
            std::string prvi;
            std::string naziv;
            ulazni_tok >> prvi;
            ulazni_tok.seekg(1,std::ios::cur); //pomjerim kurzor da preskocim razmak da se ne peglam sa tim (posto getline cita i razmake, tj. sve do \n)
            std::getline(ulazni_tok,naziv);
            if(prvi=="S") {
                int broj_predmeta;
                double tezina_sanduka;
                std::vector<double> tezine_predmeta;
                ulazni_tok>>tezina_sanduka>>broj_predmeta;
                for(int i=0;i<broj_predmeta;i++) {
                    int x;
                    ulazni_tok>>x;
                    if(!ulazni_tok) break; //moram brejkat ovdje da se dole tok ne bi oporavio
                    tezine_predmeta.push_back(x);
                }
                if(!ulazni_tok) break; //jos jednom brejkam jer sam gore brejko prvu petlju
                int provjera;
                ulazni_tok>>provjera;
                if(ulazni_tok) {
                    visak=true;
                    break;
                }
                else {
                    ulazni_tok.clear();
                }
                DodajSanduk(tezina_sanduka,naziv,tezine_predmeta);
            }
            else if(prvi=="V") {
                double tezina_vrece;
                int tezina_materije;
                ulazni_tok>>tezina_vrece>>tezina_materije;
                DodajVrecu(tezina_vrece,naziv,tezina_materije);
            }
            else if(prvi=="B") {
                double tezina_bureta,gustina,zapremina;
                ulazni_tok>>tezina_bureta>>gustina>>zapremina;
                DodajBure(tezina_bureta,naziv,gustina,zapremina);
            }
        }
        if(!ulazni_tok || visak) { //ako nije kraj datoteke a izasli smo iz petlje (ili !ulazni_tok.eof())
            if(ulazni_tok.bad()) throw std::logic_error("Problemi pri citanju datoteke"); //ostecena
            else throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
        ulazni_tok.clear();
        ulazni_tok.close();
    }
    
    
}; 



int main () {
    try {
        Skladiste ETF;
        ETF.UcitajIzDatoteke("ROBA.TXT");
        ETF.IzlistajSkladiste();
    }
    catch(std::logic_error iz) {
        std::cout<<iz.what();
    }
	return 0;
}




