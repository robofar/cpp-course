#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <algorithm>
#include <stdexcept>

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
    virtual Spremnik* DajKopiju() const = 0;
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
    Spremnik* DajKopiju() const override {
        return new Sanduk(*this);
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
    Spremnik* DajKopiju() const override {
        return new Vreca(*this);
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
    Spremnik* DajKopiju() const override {
        return new Bure(*this);
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


/* Surogatska klasa */
class PolimorfniSpremnik {
    Spremnik* p_spremnik;
    void Test() const {
        if(p_spremnik==nullptr) throw std::logic_error("Nespecificiran spremnik");
    }
public:
    PolimorfniSpremnik() : p_spremnik(nullptr) {}
    ~PolimorfniSpremnik() {
        delete p_spremnik;
    } 
    PolimorfniSpremnik(const Spremnik &s) : p_spremnik(s.DajKopiju()) {}
    PolimorfniSpremnik(const PolimorfniSpremnik &ps) {
        if(ps.p_spremnik==nullptr) p_spremnik=nullptr;
        else p_spremnik=ps.p_spremnik->DajKopiju();
    }
    PolimorfniSpremnik(PolimorfniSpremnik &&ps) {
        p_spremnik=ps.p_spremnik;
        ps.p_spremnik=nullptr;
    }
    PolimorfniSpremnik& operator = (const PolimorfniSpremnik &ps) {
        Spremnik* pomocni=nullptr; //u slucaju da ne uspije dodjela
        if(ps.p_spremnik==nullptr) pomocni=nullptr;
        else pomocni=ps.p_spremnik->DajKopiju();
        
        delete p_spremnik;
        p_spremnik=pomocni;
        pomocni=nullptr;
        
        return *this;
    }
    PolimorfniSpremnik& operator = (PolimorfniSpremnik &&ps) {
        p_spremnik=ps.p_spremnik; // ili std::swap(p_spremnik,ps.p_spremnik);
        ps.p_spremnik=nullptr;
        return *this;
    }
    double DajTezinu() const { Test(); return p_spremnik->DajTezinu(); }
    double DajUkupnuTezinu() const { Test(); return p_spremnik->DajUkupnuTezinu(); }
    void Ispisi() const { Test(); p_spremnik->Ispisi(); }
//    std::shared_ptr<Spremnik> DajKopiju() { return p_spremnik->DajKopiju(); }
};
int main ()
{
    try {
        PolimorfniSpremnik s1(Bure(5,"Benzin",930,70));
        PolimorfniSpremnik s2,s3;
        s2=Sanduk(5,"Koferi",{4.3,3.2,7.6,4.3});
        s3=Vreca(0.5,"Riba",26.4);
        std::cout<<s1.DajTezinu()<<" "<<s2.DajTezinu()<<" "<<s3.DajUkupnuTezinu()<<" "<<s1.DajUkupnuTezinu();
        std::cout<<std::endl;
        s1.Ispisi();
        std::cout<<std::endl;
        s2.Ispisi();
        std::cout<<std::endl;
        s3.Ispisi();
    }
    catch(std::logic_error le) {
        std::cout<<le.what();
    }
	return 0;
}