#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

class Student {
private:
    int indeks; //pet cifara
    std::string godina_studija,ime_prezime,adresa,br_telefona;
    static std::string FiltriranString(std::string ip) {
        std::string novi1; //za ime i prezime
        bool razmak=true;
        int brojac_odzada=0;
        int brojac_sprijeda=0;
        for(int i=ip.length()-1;i>=0;i--) {
            if(ip.at(i)==' ') brojac_odzada++; //brojimo razmake na kraju
            else break;
        }
        for(int i=0;i<ip.length();i++) {
            if(ip.at(i)==' ') brojac_sprijeda++;
            else break;
        }
        for(int i=brojac_sprijeda;i<ip.length()-brojac_odzada;i++) {
            if(ip.at(i)!=' ') {
                novi1+=ip.at(i);
                razmak=true;
            }
            else if(razmak) {
                novi1+=' ';
                razmak=false;
            }
        }
        return novi1;
    }
public:
    Student(int ind,std::string gs,std::string i_p,std::string adr,std::string broj) {
        if(ind<10000 || ind>99999) throw std::domain_error("Neispravni parametri");
        std::vector<std::string> provjera={"1","2","3","1/B","2/B","3/B","1/M","2/M","1/D","2/D","3/D"};
        bool ispravno=false;
        for(int i=0;i<provjera.size();i++) {
            if(gs==provjera.at(i)) {
                ispravno=true;
                break;
            }
        }
        if(!ispravno) throw std::domain_error("Neispravni parametri");
        /* Provjera za broj telefona - ne treba mi petlja ovako cu sekvencijalno */
            if((broj.at(0)<'0' || broj.at(0)>'9')) throw std::domain_error("Neispravni parametri"); //ako na pocetku nije unesen broj
            ////////////////////////
            int i=0;
            while (i!=broj.length() && broj.at(i)>='0' && broj.at(i)<='9') i++;
            if(i==broj.length()) throw std::domain_error("Neispravni parametri");
            if(broj.at(i)!='/') throw std::domain_error("Neispravni parametri");
            i++;
            if(i==broj.length()) throw std::domain_error("Neispravni parametri");
            /////////////////////////
            while(i!=broj.length() && broj.at(i)>='0' && broj.at(i)<='9') i++;
            if(i==broj.length()) throw std::domain_error("Neispravni parametri");
            if(broj.at(i)!='-') throw std::domain_error("Neispravni parametri");
            i++;
            if(i==broj.length()) throw std::domain_error("Neispravni parametri");
            ////////////////////////
            while(i!=broj.length() && broj.at(i)>='0' && broj.at(i)<='9') i++;
            if(i!=broj.length()) throw std::domain_error("Neispravni parametri");
        ///////////////////////////////////////////////////
        indeks=ind;
        godina_studija=gs;
        ime_prezime=FiltriranString(i_p);
        adresa=FiltriranString(adr);
        br_telefona=broj;
    }
    int DajIndeks() const {
        return indeks;
    }
    std::string DajGodinuStudija() const {
        if(godina_studija=="1") return "1/B";
        else if(godina_studija=="2") return "2/B";
        else if(godina_studija=="3") return "3/B";
        return godina_studija; //za ostale kombinacije
    }
    std::string DajImePrezime() const {
        return ime_prezime;
    }
    std::string DajAdresu() const {
        return adresa;
    }
    std::string DajTelefon() const {
        return br_telefona;
    }
    void Ispisi() const {
        std::cout<<"Broj indeksa: "<<DajIndeks()<<std::endl;
        std::cout<<"Godina studija: "<<DajGodinuStudija()<<std::endl;
        std::cout<<"Ime i prezime: "<<DajImePrezime()<<std::endl;
        std::cout<<"Adresa: "<<DajAdresu()<<std::endl;
        std::cout<<"Telefon: "<<DajTelefon()<<std::endl;
    }
};

class Laptop {
private:
    int ev_broj;
    std::string naziv;
    std::string karakteristike;
    Student* kod_koga_je=nullptr;
public:
    Laptop(int eb,std::string n,std::string k) {
        if(eb<0) throw std::domain_error("Neispravni parametri");
        ev_broj=eb; naziv=n; karakteristike=k;
        kod_koga_je=nullptr;
    }
    int DajEvidencijskiBroj() const { return ev_broj; }
    std::string DajNaziv() const { return naziv; }
    std::string DajKarakteristike() const { return karakteristike; }
    void Zaduzi(Student& s);
    void Razduzi();
    bool DaLiJeZaduzen() const;
    Student& DajKodKogaJe() const;
    Student* DajPokKodKogaJe() const;
    void Ispisi() const;
};

void Laptop::Zaduzi(Student& s) {
    if(kod_koga_je!=nullptr) throw std::domain_error("Laptop vec zaduzen");// !kod_koga_je je za nullptr
    kod_koga_je=&s;
}
bool Laptop::DaLiJeZaduzen() const{
    if(kod_koga_je!=nullptr) return true;
    return false;
}
void Laptop::Razduzi() {
    kod_koga_je=nullptr;
}
Student& Laptop::DajKodKogaJe() const{
    if(kod_koga_je==nullptr) throw std::domain_error("Laptop nije zaduzen");
    return *kod_koga_je;
}
Student* Laptop::DajPokKodKogaJe() const{
    return kod_koga_je; //bez obzira jel zaduzen il nije
}

void Laptop::Ispisi() const {
    std::cout<<"Evidencijski broj: "<<ev_broj<<std::endl;
    std::cout<<"Naziv: "<<naziv<<std::endl;
    std::cout<<"Karakteristike: "<<karakteristike<<std::endl;
}

//////////////////////////////////////////////////////////////////
class Administracija {
private:
    std::map<int,Student*> studenti; //indeks kljucno polje
    std::map<int,Laptop*> laptopi; //ev_broj kljucno polje
public:
    void RegistrirajNovogStudenta(int ind,std::string gs,std::string ip,std::string adr,std::string broj);
    void RegistrirajNoviLaptop(int eb,std::string n,std::string k);
    Student& NadjiStudenta(int ind);
    Student NadjiStudenta(int ind) const;
    Laptop& NadjiLaptop(int eb);
    Laptop NadjiLaptop(int eb) const;
    void IzlistajStudente() const;
    void IzlistajLaptope() const;
    void ZaduziLaptop(int ind,int eb);
    int NadjiSlobodniLaptop() const;
    void RazduziLaptop(int eb);
    void PrikaziZaduzenja() const;
    ~Administracija() {
        for(auto it=studenti.begin();it!=studenti.end();it++) {
            delete it->second;
        }
        for(auto it=laptopi.begin();it!=laptopi.end();it++) {
            delete it->second;
        }
    }
};

void Administracija::RegistrirajNovogStudenta(int ind,std::string gs,std::string ip,std::string adr,std::string broj) {
        auto it=studenti.find(ind); //trazi jel postoji vec ovaj indeks
        if(it==studenti.end()) { //provjera da li ne postoji jer izraz mapa[kljucno_polje] automatski stvara novi objekt, pa moram vrsit provjeru da ovo izbjegnem(a mijenja stari ako takav postoji)
           // Student* pq=new Student(ind,gs,ip,adr,broj);
            //studenti.insert(std::pair<int,Student*>(ind,pq)); -> moze i ovako
            try {
                studenti[ind]=new Student(ind,gs,ip,adr,broj);
            }
            catch(...) {
                throw;
            }
        }
        else throw std::domain_error("Student s tim indeksom vec postoji");
}

void Administracija::RegistrirajNoviLaptop(int eb,std::string n,std::string k) {
    //auto it=laptopi.find(eb);
    if(!laptopi.count(eb)) {
        //Laptop* pq=new Laptop(eb,n,k);
        try {
            laptopi[eb]=new Laptop(eb,n,k);
        }
        catch(...) {
            throw;
        }
    }
    else throw std::domain_error("Laptop s tim evidencijskim brojem vec postoji");
}

Student& Administracija::NadjiStudenta(int ind) {
    auto it=studenti.find(ind);
    if(it==studenti.end()) throw std::domain_error("Student nije nadjen");
    return *(it->second); //vraca se svakako ako nije bacen izuzetak(it->second je sam pokazivac)
}

Student Administracija::NadjiStudenta(int ind) const {
    auto it=studenti.find(ind);
    if(it==studenti.end()) throw std::domain_error("Student nije nadjen");
    return *(it->second);
}

Laptop& Administracija::NadjiLaptop(int eb) {
    auto it=laptopi.find(eb);
    if(it==laptopi.end()) throw std::domain_error("Laptop nije nadjen");
    return *(it->second);
}

Laptop Administracija::NadjiLaptop(int eb) const {
    auto it=laptopi.find(eb);
    if(it==laptopi.end()) throw std::domain_error("Laptop nije nadjen");
    return *(it->second);
}


void Administracija::IzlistajStudente() const {
    for(auto it=studenti.begin();it!=studenti.end();it++) {
        (it->second)->Ispisi();
        std::cout<<std::endl;
    }
} 

void Administracija::IzlistajLaptope() const {
    for(auto it=laptopi.begin();it!=laptopi.end();it++) {
        (it->second)->Ispisi();
    if((it->second)->DaLiJeZaduzen()) {
        std::cout<<"Zaduzio(la): ";
        Student* daj=(it->second)->DajPokKodKogaJe();
        std::cout<<daj->DajImePrezime()<<" ("<<daj->DajIndeks()<<")";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    }
}

void Administracija::ZaduziLaptop(int ind,int eb) {
    Student& s=NadjiStudenta(ind); //baca vec izuzetak
    Laptop& l=NadjiLaptop(eb); //baca izuzetak
    if(l.DaLiJeZaduzen()) throw std::domain_error("Laptop vec zaduzen");
    /* Provjera da li je student zaduzio NEKI laptop */
    for(auto it=laptopi.begin();it!=laptopi.end();it++) {
        auto a=it->second;
        if(a->DaLiJeZaduzen() && a->DajPokKodKogaJe()->DajIndeks()==ind)
            throw std::domain_error("Student je vec zaduzio laptop");
    }
    l.Zaduzi(s);
}

int Administracija::NadjiSlobodniLaptop() const {
    int svi_zaduzeni=true;
    int broj;
    for(auto it=laptopi.begin();it!=laptopi.end();it++) {
        auto a=it->second;
        if(a->DaLiJeZaduzen()==false) {
            svi_zaduzeni=false;
            broj = a->DajEvidencijskiBroj();
            break;
        }
    } 
    if(svi_zaduzeni) throw std::domain_error("Nema slobodnih laptopa");
    return broj;
} 

void Administracija::RazduziLaptop(int eb) {
    Laptop& l=NadjiLaptop(eb); //da li je laptop nadjen ? (baca sama izuzetak)
    if(!l.DaLiJeZaduzen()) throw std::domain_error("Laptop nije zaduzen");
    l.Razduzi();
}

void Administracija::PrikaziZaduzenja() const {
    bool nema_zaduzenja=true;
    for(auto it=laptopi.begin();it!=laptopi.end();it++) {
      //  auto laptop=it->second;
        
        if((it->second)->DaLiJeZaduzen()) {
            auto laptop=it->second;
            nema_zaduzenja=false;
            Student student_kod_kojeg_je=laptop->DajKodKogaJe();
            std::cout<<"Student "<<student_kod_kojeg_je.DajImePrezime()
            <<" ("<<student_kod_kojeg_je.DajIndeks()<<") zaduzio/la laptop broj "<<
            laptop->DajEvidencijskiBroj()<<std::endl;
        }
    }
    if(nema_zaduzenja) std::cout<<"Nema zaduzenja";
}

int main ()
{
try {
    Administracija etf;
    
        Administracija faris;
        for(;;) {
            int opcija;
            std::cout<<"Odaberite opciju: "<<std::endl;
            std::cout<<"1 - Registriraj novog studenta"<<std::endl;
            std::cout<<"2 - Registriraj novi laptop"<<std::endl;
            std::cout<<"3 - Nadji studenta"<<std::endl;
            std::cout<<"4 - Nadji laptop"<<std::endl;
            std::cout<<"5 - Izlistaj studente"<<std::endl;
            std::cout<<"6 - Izlistaj laptope"<<std::endl;
            std::cout<<"7 - Zaduzi laptop"<<std::endl;
            std::cout<<"8 - Nadji slobodni laptop"<<std::endl;
            std::cout<<"9 - Razduzi laptop"<<std::endl;
            std::cout<<"10 - Prikazi zaduzenja"<<std::endl;
            std::cout<<"11 - Kraj programa"<<std::endl<<std::endl;
            std::cin>>opcija;
            if(opcija==1) {
                int ind;
                std::string gs,ip,adr,broj;
                std::cout<<"Unesite broj indeksa,godinu studija,ime i prezime,adresu i broj telefona studenta: "<<std::endl;
                std::cin>>ind;
                std::cin.ignore(1000,'\n');
                std::getline(std::cin,gs);
                std::getline(std::cin,ip);
                std::getline(std::cin,adr);
                std::getline(std::cin,broj);
                faris.RegistrirajNovogStudenta(ind,gs,ip,adr,broj);
            }
            else if(opcija==2) {
                int eb;
                std::string n,k;
                std::cout<<"Unesite evidencijski broj, naziv i karakteristike laptopa: "<<std::endl;
                std::cin>>eb;
                std::cin.ignore(1000,'\n');
                std::getline(std::cin,n);
                std::getline(std::cin,k);
                faris.RegistrirajNoviLaptop(eb,n,k);
            }
            else if(opcija==3) {
                int i;
                std::cout<<"Unesite broj indeksa studenta kojeg trazite: "<<std::endl;
                std::cin>>i;
                try {
                    faris.NadjiStudenta(i).Ispisi();
                }
                catch(std::domain_error iz) {
                    std::cout<<iz.what()<<std::endl;
                }
            }
            else if(opcija==4) {
                int e;
                std::cout<<"Unesite evidencijski broj laptopa koji trazite: "<<std::endl;
                std::cin>>e;
                try {
                    faris.NadjiLaptop(e).Ispisi();
                }
                catch(std::domain_error iz) {
                    std::cout<<iz.what()<<std::endl;
                }
            }
            else if(opcija==5) {
                std::cout<<"Studenti su: "<<std::endl;
                faris.IzlistajStudente();
            }
            else if(opcija==6) {
                std::cout<<"Laptopi su: "<<std::endl;
                faris.IzlistajLaptope();
            }
            else if(opcija==7) {
                int e,i;
                std::cout<<"Unesite indeks studenta i evidencijski broj laptopa kojeg hocete da zaduzite: "<<std::endl;
                std::cin>>i>>e;
                try {
                    faris.ZaduziLaptop(i,e);
                }
                catch(std::domain_error iz) {
                    std::cout<<iz.what()<<std::endl;
                }
            }
            else if(opcija==8) {
                std::cout<<"Prvi laptop koji nije zaduzen je(evidencijski broj): "<<std::endl;
                int x=faris.NadjiSlobodniLaptop();
                std::cout<<x<<std::endl;
            }
            else if(opcija==9) {
                int e;
                std::cout<<"Unesite evidencijski broj laptopa kojeg hocete da razduzite: "<<std::endl;
                std::cin>>e;
                try {
                    faris.RazduziLaptop(e);
                }
                catch(std::domain_error iz) {
                    std::cout<<iz.what()<<std::endl;
                }
            }
            else if(opcija==10) {
                faris.PrikaziZaduzenja();
            }
            else if(opcija==11) {
                std::cout<<"Dovidjenja!";
                break;
            }
            std::cout<<std::endl;
        }
}
catch(std::domain_error e) {
    std::cout<<e.what();
}
catch(...) {
    
}
	return 0;
}