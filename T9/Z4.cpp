#include <iostream>
#include <stdexcept>

class Sat {
private:
    int sat,minuta,sekunda;
public:
    static bool DaLiJeIspravno(int h,int m,int s) {
        if(h<0 || h>23 || m<0 || m>59 || s<0 || s>59) return false;
        return true;
    }
    void Postavi(int h,int m,int s) {
        if(!DaLiJeIspravno(h,m,s)) throw std::domain_error("Neispravno vrijeme");
        sat=h; minuta=m; sekunda=s;
    }
    void PostaviNormalizirano(int h,int m,int s) {
        int dodatne_minute=0;
        int dodatni_sati=0;
        int oduzmi_minute=0;
        int oduzmi_sate=0;
        /* Obradi negativno vrijeme */
        if(s<0) {
            s*=-1;
            oduzmi_minute=s/60+1;
            s=60-s%60;
        }
        m=m-oduzmi_minute;
        if(m<0) {
            m*=-1;
            oduzmi_sate=m/60+1;
            m=60-m%60;
        }
        h=h-oduzmi_sate;
        if(h<0) {
            h*=-1;
            h=24-h%24;
        }
        /* Sad radi sa normalnim vremenom - ako je bilo negativno prepravio si ga */
        if(s>59) {
            dodatne_minute=s/60;
            s=s%60;
        }
        m=m+dodatne_minute;
        if(m>59) {
            dodatni_sati=m/60;
            m=m%60;
        }
        h=h+dodatni_sati;
        if(h>23) {
            h=h%24;
        }
        sat=h;
        minuta=m;
        sekunda=s;
    }
    Sat &PomjeriZa(int s) {
            sekunda+=s;
            PostaviNormalizirano(sat,minuta,sekunda);
        return *this;
    }
    Sat &Sljedeci() {
        return PomjeriZa(1);
    }
    Sat &Prethodni() {
        return PomjeriZa(-1);
    }
    int DajSate() const {
        return sat;
    }
    int DajMinute() const {
        return minuta;
    }
    int DajSekunde() const {
        return sekunda;
    }
    /* ispisi sam mogao stavit samo sat,minuta,sekunda umjesto ovih Daj
    al ovo je bolje ladi lakse prepravke funkcije u zadatku 5
    inace se sve funkcije trebaju medjusobno sto vise oslanjat jedna na drugu */
    void Ispisi() const {
        if(DajSate()<10) std::cout<<"0";
        std::cout<<DajSate()<<":";
        if(DajMinute()<10) std::cout<<"0";
        std::cout<<DajMinute()<<":";
        if(DajSekunde()<10) std::cout<<"0";
        std::cout<<DajSekunde();
    }
    friend int BrojSekundiIzmedju(const Sat &v1, const Sat &v2);
    static int Razmak(const Sat &v1, const Sat &v2); //obje ove cu definisati izvan klase
};

int BrojSekundiIzmedju(const Sat &v1,const Sat &v2) {
    int s1=0,s2=0;
    s1=v1.sat*3600+v1.minuta*60+v1.sekunda;
    s2=v2.sat*3600+v2.minuta*60+v2.sekunda;
    int rez=s1-s2;
    return rez;
}
/* kod ove funkcije - posto je ona funckija clanica moram navesti uvijek za
koju klasu je vezana pomocu ovog Sat:: */
int Sat::Razmak(const Sat &v1,const Sat &v2) {
    int s1=0,s2=0;
    s1=v1.sat*3600+v1.minuta*60+v1.sekunda;
    s2=v2.sat*3600+v2.minuta*60+v2.sekunda;
    int rez=s1-s2;
    return rez;
}

int main ()
{
    Sat s1;
    Sat s2;
    if(Sat::DaLiJeIspravno(43,12,33)) std::cout<<"Jeste";
    else std::cout<<"Nije";
    std::cout<<std::endl;
    s1.Postavi(11,43,12);
    s2.Postavi(11,33,33);
    std::cout<<std::endl;
    s1.PostaviNormalizirano(0,0,-87);
    s1.Ispisi();
    std::cout<<std::endl;
    s1.PomjeriZa(37).Ispisi();
    std::cout<<std::endl;
    s1.PomjeriZa(-37).Ispisi();
    std::cout<<std::endl;
    s1.Sljedeci().Ispisi();
    std::cout<<std::endl;
    std::cout<<Sat::Razmak(s1,s2)<<" "<<BrojSekundiIzmedju(s1,s2);
	return 0;
}