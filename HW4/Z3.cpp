#include <iostream>
#include <tuple> //tuple je pair sa n parametara
#include <utility>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

int obrisano=0;
class Datum {
private:
    int dan,mjesec,godina;
    static bool ProvjeraDatuma(int dan,int mjesec,int godina) {
        int dani[]={31,28,31,30,31,30,31,31,30,31,30,31};
        if(godina%4==0 && godina%100!=0 || godina%400==0) dani[1]++;
        if(godina<1 || mjesec<1 || dan<1 || mjesec>12 || dan>dani[mjesec-1]) return false;
        return true;
    }
public:
    Datum(int dan,int mjesec,int godina) {
        Postavi(dan,mjesec,godina);
    }
    void Postavi(int dan,int mjesec,int godina) {
        if(!ProvjeraDatuma(dan,mjesec,godina)) throw std::domain_error("Neispravan datum");
        Datum::dan=dan; Datum::mjesec=mjesec; Datum::godina=godina;
    }
    std::tuple<int,int,int> Ocitaj() const {
        return {dan,mjesec,godina}; 
    }
    void Ispisi() const {
        //if(dan<10) std::cout<<"0";
        std::cout<<dan<<"/";
       // if(mjesec<10) std::cout<<"0";
        std::cout<<mjesec<<"/"<<godina;
    }
    friend class Pregled;
};

class Vrijeme {
private:
    int sati,minute;
    static bool ProvjeraVremena(int h,int m) {
        if(h<0 || h>23 || m<0 || m>59) return false; //IZMJENA(1) - stavio sam <1 padala 5 AT, sad stavio <0 pa cemo vidjet - OPET PADALA 5 (POSLAO SAM IZMJENU 2)
        return true;
    }
public:
    Vrijeme(int sati,int minute) {
        Postavi(sati,minute);
    }
    void Postavi(int sati,int minute) {
        if(!ProvjeraVremena(sati,minute)) throw std::domain_error("Neispravno vrijeme");
        Vrijeme::sati=sati; Vrijeme::minute=minute;
    }
    std::pair<int,int> Ocitaj() const {
        return {sati,minute};
    }
    void Ispisi() const {
        if(sati<10) std::cout<<"0";
        std::cout<<sati<<":";
        if(minute<10) std::cout<<"0";
        std::cout<<minute;
    }
    friend class Pregled;
};

class Pregled {
private:
    std::string ImePacijenta; //pacijenta
    int DanPregleda,MjesecPregleda,GodinaPregleda; //za pregled
    int SatPregleda,MinutaPregleda;
public:
    Pregled(const std::string &ime_pacijenta,const Datum &datum_pregleda,const Vrijeme &vrijeme_pregleda) {
     /* Ovdje ti provjera ne treba jer se svakako pozivaju konstruktori gore u parametrima */
        ImePacijenta=ime_pacijenta;
        DanPregleda=std::get<0>(datum_pregleda.Ocitaj());
        MjesecPregleda=std::get<1>(datum_pregleda.Ocitaj());
        GodinaPregleda=std::get<2>(datum_pregleda.Ocitaj());
        SatPregleda=vrijeme_pregleda.Ocitaj().first;
        MinutaPregleda=vrijeme_pregleda.Ocitaj().second;
    }
    Pregled(const std::string &ime_pacijenta,int dan_pregleda,int mjesec_pregleda,int godina_pregleda,
    int sati_pregleda,int minute_pregleda) {
        if(!Datum::ProvjeraDatuma(dan_pregleda,mjesec_pregleda,godina_pregleda)) throw std::domain_error("Neispravan datum");
        if(!Vrijeme::ProvjeraVremena(sati_pregleda,minute_pregleda)) throw std::domain_error("Neispravno vrijeme");
        ImePacijenta=ime_pacijenta;
        DanPregleda=dan_pregleda;
        MjesecPregleda=mjesec_pregleda;
        GodinaPregleda=godina_pregleda;
        SatPregleda=sati_pregleda;
        MinutaPregleda=minute_pregleda;
    }
    void PromijeniPacijenta(const std::string &ime_pacijenta) {
        ImePacijenta=ime_pacijenta;
    }
    void PromijeniDatum(const Datum &novi_datum) {
        DanPregleda=std::get<0>(novi_datum.Ocitaj());
        MjesecPregleda=std::get<1>(novi_datum.Ocitaj());
        GodinaPregleda=std::get<2>(novi_datum.Ocitaj()); //IZMJENA(2) - slucajno napisao SatPregleda umjesto GodinaPregleda - POSLANO
    }
    void PromijeniVrijeme(const Vrijeme &novo_vrijeme) {
        SatPregleda=novo_vrijeme.Ocitaj().first;
        MinutaPregleda=novo_vrijeme.Ocitaj().second;
    }
    void PomjeriDanUnaprijed();
    void PomjeriDanUnazad();
    std::string DajImePacijenta() const {
        return ImePacijenta;
    }
    Datum DajDatumPregleda() const {
        Datum vrati(DanPregleda,MjesecPregleda,GodinaPregleda);
        return vrati;
    }
    Vrijeme DajVrijemePregleda() const {
        Vrijeme vrati(SatPregleda,MinutaPregleda);
        return vrati;
    }
    /* Kad definisem static funkciju izvan klase, tamo mi ne treba ponovo rijec static */
    static bool DolaziPrije(const Pregled &p1,const Pregled &p2);
    void Ispisi() const {
        Datum d(DanPregleda,MjesecPregleda,GodinaPregleda);
        Vrijeme v(SatPregleda,MinutaPregleda);
        std::cout<<std::left<<std::setw(30)<<ImePacijenta;
        d.Ispisi();
        std::cout<<" ";
        v.Ispisi();
        std::cout<<std::endl;
    }
};

void Pregled::PomjeriDanUnaprijed() {
    int dani[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(GodinaPregleda%4==0 && GodinaPregleda%100!=0 || GodinaPregleda%400==0) dani[1]++;
    DanPregleda+=1;
    if(DanPregleda>dani[MjesecPregleda-1]) {
        MjesecPregleda+=1;
        DanPregleda=1;
    }
    if(MjesecPregleda>12) { //izvrsice se ako je bio 31.12 pa se dan pomjerio za 1
        GodinaPregleda+=1;
        MjesecPregleda=1;
    } 
}

void Pregled::PomjeriDanUnazad() {
    int dani[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if(GodinaPregleda%4==0 && GodinaPregleda%100!=0 || GodinaPregleda%400==0) dani[1]++;
    DanPregleda-=1;
    if(DanPregleda<=0) {
        MjesecPregleda-=1; //prvo vratis mjesec zbog ovog ispod
        if(MjesecPregleda<=0) {
            MjesecPregleda=12;
            GodinaPregleda-=1;
        }
        DanPregleda=dani[MjesecPregleda-1];
    }
}

bool Pregled::DolaziPrije(const Pregled &p1,const Pregled &p2) {
    /* Krenucu redom od godine prema danu */
    /* Sve su ifovi jer odma vracam */
    if(p1.GodinaPregleda<p2.GodinaPregleda) return true;
    if(p1.GodinaPregleda>p2.GodinaPregleda) return false;
    if(p1.MjesecPregleda<p2.MjesecPregleda) return true;
    if(p1.MjesecPregleda>p2.MjesecPregleda) return false;
    if(p1.DanPregleda<p2.DanPregleda) return true;
    if(p1.DanPregleda>p2.DanPregleda) return false;
    if(p1.SatPregleda<p2.SatPregleda) return true;
    if(p1.SatPregleda>p2.SatPregleda) return false;
    if(p1.MinutaPregleda<p2.MinutaPregleda) return true;
    //if(p1.MinutaPregleda>=p2.MinutaPregleda) return false; //jednako jer je to zadnji slucaj(moglo je i else ovdje al ovako preglednije)
    return false; //ovaj false znaci ovaj komentarisani if(jer fja ocekuje neki podrazuminevani zavrsetak)
}

class Pregledi {
private:
    const int max_pregleda;
    int broj_pregleda;
    Pregled** p=nullptr;
    static bool JD(const Datum &d1,const Datum &d2) {
        auto x=d1.Ocitaj();
        auto y=d2.Ocitaj();
        if(std::get<0>(x)==std::get<0>(y) && std::get<1>(x)==std::get<1>(y) && std::get<2>(x)==std::get<2>(y)) return true;
        return false;
    }
    static bool JV(const Vrijeme &v1,const Vrijeme &v2) {
        if(v1.Ocitaj().first==v2.Ocitaj().first && v1.Ocitaj().second==v2.Ocitaj().second) return true;
        return false;
    }
public:
    explicit Pregledi(int max_broj_pregleda) : max_pregleda(max_broj_pregleda),broj_pregleda(0),
    p(new Pregled*[max_pregleda]{}) {}
    Pregledi(std::initializer_list<Pregled> spisak_pregleda) : max_pregleda(spisak_pregleda.size()), broj_pregleda(spisak_pregleda.size()) {
        try {
        p=new Pregled*[broj_pregleda]{};
        int i=0;
        try {
        for(auto it=spisak_pregleda.begin();it!=spisak_pregleda.end();it++) {
            p[i]=new Pregled(*it);
            i++;
        }
        }
        catch(...) {
            for(int i=0;i<broj_pregleda;i++) delete p[i];
            delete[] p;
            throw;
        }
        }
        catch(...) {
            throw;
        }
    }
    ~Pregledi() {
        for(int i=0;i<broj_pregleda;i++) delete p[i];
        delete[] p;
    }
    Pregledi(const Pregledi &pregledi) : max_pregleda(pregledi.max_pregleda),broj_pregleda(pregledi.broj_pregleda) {
        
        try {
            p=new Pregled*[max_pregleda]{};
        try {
            for(int i=0;i<broj_pregleda;i++) {
                p[i]=new Pregled(*pregledi.p[i]);
            }
        }
        catch(...) { //jer se nece ovdje pozvat destruktor
            for(int i=0;i<broj_pregleda;i++) delete p[i];
            delete[] p;
            throw;
        }
    }
    catch(...) {
        throw;
    }
    }
    Pregledi(Pregledi &&pregledi) : max_pregleda(pregledi.max_pregleda),broj_pregleda(pregledi.broj_pregleda) {
        p=pregledi.p;
        pregledi.p=nullptr;
        pregledi.broj_pregleda=0; //zbog for petlje u destruktoru
        // pregledi.max_pregleda=0;
    }
    Pregledi& operator = (const Pregledi &pregledi) {
        //if(max_pregleda!=pregledi.max_pregleda) baci izuzetak ko dole
    if(&pregledi!=this) {
        if(broj_pregleda<pregledi.broj_pregleda) {
            try {
                for(int i=broj_pregleda;i<pregledi.broj_pregleda;i++) {
                    p[i]=new Pregled(*pregledi.p[i]);
                }
            }
            catch(...) {
                for(int i=broj_pregleda;i<pregledi.broj_pregleda;i++) {
                    delete p[i];
                    p[i]=nullptr;
                }
                throw;
            }
        }
        else {
            for(int i=pregledi.broj_pregleda;i<broj_pregleda;i++) {
                delete p[i];
                p[i]=nullptr; //ako ne stavis nullptr onaj ce ti biti viseci pokazivac(mozda ovo nije nuzno ali bar da nemas visece pokazivace)
            }
        }
        broj_pregleda=pregledi.broj_pregleda;
        for(int i=0;i<broj_pregleda;i++) *p[i]=*pregledi.p[i];
    }    
    return *this;
    }
    Pregledi& operator = (Pregledi &&pregledi) { //ili preko one non-swap metode al eto moze i ovo
      // if(max_pregleda!=pregledi.max_pregleda) throw std::logic_error("Nesaglasni kapaciteti pregleda");
        std::swap(broj_pregleda,pregledi.broj_pregleda);
        std::swap(p,pregledi.p);
        return *this;
    }
    void RegistrirajPregled(const std::string &ime_pacijenta,const Datum &datum_pregleda,const Vrijeme &vrijeme_pregleda);
    void RegistrirajPregled(const std::string &ime_pacijenta,int dan_pregleda,int mjesec_pregleda,int godina_pregleda,
    int sati_pregleda,int minute_pregleda);
    void RegistrirajPregled(Pregled *pregled);
    int DajBrojPregleda() const {
        return broj_pregleda;
    }
    int DajBrojPregledaNaDatum(const Datum &datum) const;
    Pregled &DajNajranijiPregled();
    Pregled DajNajranijiPregled() const;
    void IsprazniKolekciju();
    void ObrisiNajranijiPregled();
    void ObrisiPregledePacijenta(const std::string &ime_pacijenta);
    void IspisiPregledeNaDatum(const Datum &datum) const;
    void IspisiSvePreglede() const;
};

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta,const Datum &dan_pregleda,const Vrijeme &vrijeme_pregleda) {
    if(broj_pregleda>=max_pregleda) throw std::range_error("Dostignut maksimalni broj pregleda");
    try {
        p[broj_pregleda]=new Pregled(ime_pacijenta,dan_pregleda,vrijeme_pregleda);
        broj_pregleda++;
    }
    catch(...) {
        throw;
    }
}

void Pregledi::RegistrirajPregled(const std::string &ime_pacijenta,int dan_pregleda,int mjesec_pregleda,int godina_pregleda,
int sati_pregleda,int minute_pregleda) {
    if(broj_pregleda>=max_pregleda) throw std::range_error("Dostignut maksimalni broj pregleda");
    try {
        p[broj_pregleda]=new Pregled(ime_pacijenta,dan_pregleda,mjesec_pregleda,godina_pregleda,sati_pregleda,minute_pregleda);
        broj_pregleda++;
    }
    catch(...) {
        throw;
    }
}

void Pregledi::RegistrirajPregled(Pregled* pregled) {
    if(broj_pregleda>=max_pregleda) {
        delete pregled;
        throw std::range_error("Dostignut maksimalni broj pregleda");
    }
    p[broj_pregleda]=pregled;
    broj_pregleda++;
    pregled=nullptr;
}

int Pregledi::DajBrojPregledaNaDatum(const Datum &datum) const { //mora i ovdje ici const
    int x = std::count_if(p,p+broj_pregleda,[datum](Pregled* pregled)->bool {
        Datum pomocna=pregled->DajDatumPregleda();
        if(JD(datum,pomocna)) return true;
        return false;
    });
    return x;
}

Pregled& Pregledi::DajNajranijiPregled() {
    if(DajBrojPregleda()==0) throw std::domain_error("Nema registriranih pregleda");
    auto najmanji=std::min_element(p,p+broj_pregleda,[](Pregled *p1,Pregled *p2)->bool {
        return Pregled::DolaziPrije(*p1,*p2);
    }); 
    return **najmanji; //jer je najmanji ustvari iterator na najmanji element niza p(a to je iterator na pokazivac)
}

Pregled Pregledi::DajNajranijiPregled() const {
    if(DajBrojPregleda()==0) throw std::domain_error("Nema registriranih pregleda");
    auto najmanji=std::min_element(p,p+broj_pregleda,[](Pregled *p1,Pregled *p2)->bool {
        return Pregled::DolaziPrije(*p1,*p2);
    });
    return **najmanji; 
}

void Pregledi::IsprazniKolekciju() {
    for(int i=0;i<broj_pregleda;i++) {
        delete p[i];
        p[i]=nullptr;
    }
    //delete[] p; -> ne treba delete ovaj(jer samo deletas objekte na koje pokazuju pokazivaci al ne i D.A. niz pokazivaca)
    //p=nullptr;
    broj_pregleda=0;
}

void Pregledi::ObrisiNajranijiPregled() {
    if(broj_pregleda==0) throw std::range_error("Prazna kolekcija");
    Pregled najraniji=DajNajranijiPregled(); //poziva se metoda sa referencom
    for(int i=0;i<broj_pregleda;i++) {
        if(JD(najraniji.DajDatumPregleda(),p[i]->DajDatumPregleda())
        && JV(najraniji.DajVrijemePregleda(),p[i]->DajVrijemePregleda())
        && najraniji.DajImePacijenta()==p[i]->DajImePacijenta()) {
            delete p[i];
            for(int j=i;j<broj_pregleda-1;j++) p[j]=p[j+1]; //klasicno izbacivanje(da nam i ne bi osto u sred niza)
            p[broj_pregleda-1]=nullptr; //iako sam broj pregleda dole smanjio,za svaki slucaj cu stavit na nullptr 
            broj_pregleda--; 
            break;
        }
    }
}

void Pregledi::ObrisiPregledePacijenta(const std::string &ime_pacijenta) {
    obrisano=0; //stavicu da se stalo resetuje ovo
    for(int i=0;i<broj_pregleda;i++) {
        if(ime_pacijenta==p[i]->DajImePacijenta()) {
            delete p[i];
            for(int j=i;j<broj_pregleda-1;j++) p[j]=p[j+1];
            p[broj_pregleda-1]=nullptr;
            broj_pregleda--;
            obrisano++;
            i--; //pogledaj da nema jos nekog pregleda za tog pacijenta
        }
    }
}

void Pregledi::IspisiPregledeNaDatum(const Datum &datum) const {
    std::vector<Pregled*> a;
    for(int i=0;i<broj_pregleda;i++) {
        if(JD(p[i]->DajDatumPregleda(),datum)) a.push_back(p[i]);
    }
    std::sort(a.begin(),a.end(),[](Pregled* q1,Pregled* q2)->bool {
        return Pregled::DolaziPrije(*q1,*q2);
    });
    for(int i=0;i<a.size();i++) {
        a.at(i)->Ispisi();
    }
}

void Pregledi::IspisiSvePreglede() const {
    std::vector<Pregled*> a;
    for(int i=0;i<broj_pregleda;i++) a.push_back(p[i]);
    std::sort(a.begin(),a.end(),[](Pregled* q1,Pregled* q2)->bool {
        return Pregled::DolaziPrije(*q1,*q2);
    });
    for(int i=0;i<a.size();i++) a[i]->Ispisi();
}

int main ()
{
try {
    
    int n;
    std::cout<<"Unesite maksimalan broj pregleda: ";
    std::cin>>n;
    Pregledi a(n);
    for(int i=0;i<n;i++) {
        std::cout<<"Unesite ime novog pacijenta ili 'kraj' za zavrsetak unosa: ";
        std::string s;
        std::cin>>s;
        if(s=="kraj") break; //broj_pregleda je sad npr 2 ili 3(npr)
        std::cout<<"Unesite dan mjesec i godinu pregleda: ";
        int dan,mjesec,godina;
        std::cin>>dan>>mjesec>>godina;
        std::cout<<"Unesite sate i minute pregleda: ";
        int sati,minute;
        std::cin>>sati>>minute;
        a.RegistrirajPregled(s,dan,mjesec,godina,sati,minute);
    }
    std::cout<<"Trenutno su registrovani sljedeci pregledi"<<std::endl;
    a.IspisiSvePreglede();
    std::cout<<std::endl;
    std::cin.ignore(1000,'\n');
    for(;;) {
        int opcija;
        std::cout<<"Odaberite jednu od sljedecih opcija"<<std::endl;
        std::cout<<"1 - Broj pregleda na datum"<<std::endl;
        std::cout<<"2 - Najraniji pregled"<<std::endl;
        std::cout<<"3 - Obrisi pregled pacijenta"<<std::endl;
        std::cout<<"4 - Obrisi najraniji pregled"<<std::endl;
        std::cout<<"5 - Ispisi sve pregleda na datum"<<std::endl;
        std::cout<<"6 - Ispisi sve preglede"<<std::endl;
        std::cout<<"7 - Kraj programa"<<std::endl;
        std::cin>>opcija;
        if(opcija==1) {
            int dan,mjesec,godina;
            std::cout<<"Unesite dan mjesec i godinu : ";
            std::cin>>dan>>mjesec>>godina;
            Datum d(dan,mjesec,godina);
            std::cout<<"Broj pregleda na datum "<<dan<<" "<<mjesec<<" "<<godina<<" je: "<<a.DajBrojPregledaNaDatum(d);
        }
        else if(opcija==2) {
            std::cout<<"Najraniji pregled je:"<<std::endl;
            a.DajNajranijiPregled().Ispisi();
        }
        else if(opcija==3) {
            std::string s;
            std::cout<<"Unesite ime pacijenta: ";
            std::cin>>s;
            a.ObrisiPregledePacijenta(s);
            std::cout<<"Uspjesno obrisano "<<obrisano<<" pregleda";
        }
        else if(opcija==4) {
            a.ObrisiNajranijiPregled();
            std::cout<<"Najraniji pregled uspjesno obrisan";
        }
        else if(opcija==5) {
            int dan,mjesec,godina;
            std::cout<<"Unesite dan mjesec i godinu : ";
            std::cin>>dan>>mjesec>>godina;
            std::cout<<"Pregledi na datum "<<dan<<" "<<mjesec<<" "<<godina<<" su:"<<std::endl;
            Datum d(dan,mjesec,godina);
            a.IspisiPregledeNaDatum(d);
        }
        else if(opcija==6) {
            a.IspisiSvePreglede();
        }
        else if(opcija==7) break;
        std::cout<<std::endl;
        std::cout<<std::endl;
    } 
}
catch(std::domain_error iz) {
    std::cout<<iz.what();
}
catch(std::range_error iz) {
    std::cout<<iz.what();
}
catch(...) {
    
}
	return 0;
}