#include <iostream>
#include <cmath>

//enum Pol {Musko,Zensko};

class GradjaninBiH {
public:
    enum Pol {Musko,Zensko};
private:
    std::string ImeIPrezime;
    int DanRodjenja;
    int MjesecRodjenja;
    int GodinaRodjenja;
    int SifraRegije;
    long long int JMBG;
    GradjaninBiH::Pol p;
    GradjaninBiH* prethodni;
    static GradjaninBiH* posljednji;
    static bool ProvjeraDatuma(int dan,int mjesec,int godina) {
        int broj_dana[]={31,28,31,30,31,30,31,31,30,31,30,31};
        if(godina%4==0 && godina%100!=0 || godina%400==0) broj_dana[1]++;
        if(godina<1 || dan<1 || mjesec<1 || mjesec>12 || dan>broj_dana[mjesec-1]) return false;
        return true;
    }
    static int ProvjeraC13(long long int jmbg) {
        int a[12]={0};
        int i=11;
        while(jmbg!=0) {
            int x=jmbg%10;
            a[i]=x;
            i--;
            jmbg/=10;
        }
        int c13=11 - (7*(a[0]+a[6]) + 6*(a[1]+a[7]) + 5*(a[2]+a[8]) + 4*(a[3]+a[9]) + 3*(a[4]+a[10]) + 2*(a[5]+a[11]))%11;
        if(c13==11) c13=0;
        return c13;
    }
    static int C10C11C12(long long int jmbg) {
        jmbg/=10;
        int rez=0;
        for(int i=0;i<3;i++) {
            int x=jmbg%10;
            rez=rez+x*pow(10,i);
            jmbg/=10;
        }
        return rez;
    }
public:
    GradjaninBiH(const GradjaninBiH &g) = delete;
    GradjaninBiH& operator = (const GradjaninBiH &g) = delete;
    GradjaninBiH(std::string ime_i_prezime,long long int jmbg) {
        ImeIPrezime=ime_i_prezime;
        long long int kopija_jmbg=jmbg;
        int kontrolna=jmbg%10; jmbg/=10; //da preskocis zadnju cifru
        if(ProvjeraC13(jmbg)!=kontrolna || ProvjeraC13(jmbg)==10) throw std::logic_error("JMBG nije validan");
        int musko_zensko=jmbg%1000; jmbg/=1000;
        int sifra_regije=jmbg%100; jmbg/=100;
        int godina_rodjenja=jmbg%1000; jmbg/=1000;
        int mjesec_rodjenja=jmbg%100; jmbg/=100;
        int dan_rodjenja=jmbg;
        if(!ProvjeraDatuma(dan_rodjenja,mjesec_rodjenja,godina_rodjenja)) throw std::logic_error("JMBG nije validan");
       
        auto pok=posljednji;//treba nam pomocni da ne pomjeramo ovaj
        while(pok) {
            if(pok->JMBG==kopija_jmbg) throw std::logic_error("Vec postoji gradjanin sa istim JMBG");
            pok=pok->prethodni;
        }
        if(musko_zensko>=0 && musko_zensko<=499) p=GradjaninBiH::Pol::Musko;
        else p=GradjaninBiH::Pol::Zensko;
        SifraRegije=sifra_regije;
        /* Provjera godine rodjenja */
        if(godina_rodjenja+2000>2017) godina_rodjenja+=1000;
        else godina_rodjenja+=2000;
        GodinaRodjenja=godina_rodjenja;
        MjesecRodjenja=mjesec_rodjenja;
        DanRodjenja=dan_rodjenja; //ovo sto je ostalo od jmbg-a
        JMBG=kopija_jmbg;
        /* Uvezivanje u listu */
        prethodni=posljednji; //predhodni ce uvijek biti prosla verzija "posljednjeg" a posljednji stalno
        //pomjeramo jer je on static(zajednicki za sve). Tako dobivamo da pokazivac prvog objekta bude nullptr
        //a ostali da budu ono na sta je posljednji pokazivao prije promjene
        posljednji=this;
    }
    GradjaninBiH(std::string ime_i_prezime,int dan_rodjenja,int mjesec_rodjenja,
    int godina_rodjenja, int sifra_regije,GradjaninBiH::Pol pol) {
        if(!ProvjeraDatuma(dan_rodjenja,mjesec_rodjenja,godina_rodjenja)) throw std::logic_error("Neispravni podaci");
        if(sifra_regije<0 || sifra_regije>99) throw std::logic_error("Neispravni podaci");
        long long int jmbg;
        int godina_rodjenja_3_cifre=godina_rodjenja%1000;
        jmbg=dan_rodjenja*pow(10,11)+mjesec_rodjenja*pow(10,9)+godina_rodjenja_3_cifre*pow(10,6)+sifra_regije*pow(10,4);
        int min_musko=500;
        int min_zensko=1000;
        int histogram_m[500]={0};
        int histogram_z[1000]={0};
        auto pok=posljednji;
        while(pok!=nullptr) {
            if(pol==GradjaninBiH::Pol::Zensko) {
                if(dan_rodjenja==pok->DanRodjenja && mjesec_rodjenja==pok->MjesecRodjenja
                && godina_rodjenja==pok->GodinaRodjenja && sifra_regije==pok->SifraRegije) {
                   histogram_z[C10C11C12(pok->JMBG)]++; 
                }
            }
            if(pol==GradjaninBiH::Pol::Musko) {
                if(dan_rodjenja==pok->DanRodjenja && mjesec_rodjenja==pok->MjesecRodjenja
                && godina_rodjenja==pok->GodinaRodjenja && sifra_regije==pok->SifraRegije) {
                    histogram_m[C10C11C12(pok->JMBG)]++;
                }
            }
            pok=pok->prethodni;
        }
        for(int i=0;i<500;i++) {
            if(histogram_m[i]==0) {
                min_musko=i;
                break;
            }
        }
        for(int i=500;i<1000;i++) {
            if(histogram_z[i]==0) {
                min_zensko=i;
                break;
            }
        }
        if(pol==GradjaninBiH::Pol::Zensko) jmbg=jmbg+min_zensko*10;
        else if(pol==GradjaninBiH::Pol::Musko) jmbg=jmbg+min_musko*10;
        if(ProvjeraC13(jmbg/10)==10) throw std::logic_error("JMBG nije validan"); //(prvo provjeris c13 da ne bi djava pravio novi jmbg ako je nevalidan)
        jmbg+=ProvjeraC13(jmbg/10); //mora /10 jer uvijek saljes bez zadnje cifre
        ////////////////////////////////
        /* Provjera datuma -> ne veci od 2017 */
        if(godina_rodjenja+2000>2017) godina_rodjenja+=1000;
        else godina_rodjenja+=2000;
        ImeIPrezime=ime_i_prezime;
        DanRodjenja=dan_rodjenja;
        MjesecRodjenja=mjesec_rodjenja;
        GodinaRodjenja=godina_rodjenja;
        SifraRegije=sifra_regije;
        p=pol; //ok je - kad se dodjeljuju dva pola onda ne mora ici ono Gra::Pol variabla
        JMBG=jmbg;
        /* I ovdje pokazivaci, zavisi koji konstruktor pozovemo */
        prethodni=posljednji;
        posljednji=this;
    }
    std::string DajImeIPrezime() const {
        return ImeIPrezime;
    }
    long long int DajJMBG() const {
        return JMBG;
    }
    int DajDanRodjenja() const {
        return DanRodjenja;
    }
    int DajMjesecRodjenja() const {
        return MjesecRodjenja;
    }
    int DajGodinuRodjenja() const {
        return GodinaRodjenja;
    }
    int DajSifruRegije() const {
        return SifraRegije;
    }
    Pol DajPol() const {
        return p;
    }
    void PromijeniImeIPrezime(std::string novo_ime) {
        ImeIPrezime=novo_ime;
    }
    ~GradjaninBiH() {
        auto pok=posljednji;
        if(pok==this) { //iskljucimo ga iz liste
        // delete posljednji;
        // posljednji=nullptr;
            posljednji=prethodni;
        }
        else {
            while(pok->prethodni!=this) pok=pok->prethodni;
            // delete pok->predhodni;
            // pok->predhodni=nullptr;
            pok->prethodni=prethodni;
        }
    }
};


GradjaninBiH* GradjaninBiH::posljednji=nullptr;
int main ()
{
    int n;
    std::cout<<"Koliko gradjana zelite unijeti po JMBG? "<<std::endl;
    std::cin>>n;
    std::cin.ignore(1000,'\n');
    for(int i=0;i<n;i++) {
        std::string s;
        long long int jmbg;
        std::cout<<"Unesite ime i prezime (u istom redu): "<<std::endl;
        std::getline(std::cin,s);
        //std::cin.ignore(1000,'\n');
        std::cout<<"Unesite JMBG: "<<std::endl;
        std::cin>>jmbg;
        std::cin.ignore(1000,'\n');
        try {
        GradjaninBiH a(s,jmbg);
        std::cout<<"Unijeli ste gradjanina "<<
        a.DajImeIPrezime()<<" rodjenog "<<a.DajDanRodjenja()<<"."<<a.DajMjesecRodjenja()<<"."<<a.DajGodinuRodjenja()<<" u regiji "<<a.DajSifruRegije()<<", ";
        if(a.DajPol()==GradjaninBiH::Pol::Zensko) std::cout<<"zensko.";
        else std::cout<<"musko.";
        }
        catch(std::logic_error iz) {
            std::cout<<iz.what();
            i--;
        }
        std::cout<<std::endl;
    }
    std::cout<<"Koliko gradjana zelite unijeti po datumu rodjenja, regiji i polu?"<<std::endl;
    int m;
    std::cin>>m;
    std::cin.ignore(1000,'\n');
    for(int i=0;i<m;i++) {
        std::string s;
        int dan,mjesec,godina,sifra;
        char pol,znak1,znak2;
        std::cout<<"Unesite ime i prezime (u istom redu): "<<std::endl;
        std::getline(std::cin,s);
       // std::cin.ignore(1000,'\n');
        std::cout<<"Unesite datum rodjenja (format dd/mm/gggg): "<<std::endl;
        std::cin>>dan>>znak1>>mjesec>>znak2>>godina;
        std::cout<<"Unesite sifru regije: "<<std::endl;
        std::cin>>sifra;
        std::cout<<"Unesite M za musko, Z za zensko: "<<std::endl;
        std::cin>>pol;
        std::cin.ignore(1000,'\n');
        try {
        if(pol=='M') {
            GradjaninBiH a(s,dan,mjesec,godina,sifra,GradjaninBiH::Pol::Musko);
            std::cout<<"Unijeli ste gradjanina "<<a.DajImeIPrezime()<<" JMBG: "<<a.DajJMBG()<<".";
        }
        else {
            GradjaninBiH a(s,dan,mjesec,godina,sifra,GradjaninBiH::Pol::Zensko);
            std::cout<<"Unijeli ste gradjanina "<<a.DajImeIPrezime()<<" JMBG: "<<a.DajJMBG()<<".";
        }
        }
        catch(std::logic_error iz) {
            std::cout<<iz.what();
            i--;
        }
        std::cout<<std::endl;
    }
	return 0;
}