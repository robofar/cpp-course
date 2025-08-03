#include <iostream>
#include <stdexcept>

class Sat {
private:
    int sekunde;
public:
    static bool DaLiJeIspravno(int h,int m,int s) { //DONE
        if(h<0 || h>23 || m<0 || m>59 || s<0 || s>59) return false;
        return true;
    }
    void Postavi(int h,int m,int s) { //DONE
        if(!DaLiJeIspravno(h,m,s)) throw std::domain_error("Neispravno vrijeme");
        int rez=h*3600 + m*60 + s;
        sekunde=rez;
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
        sekunde=h*3600+m*60+s; //valjda fja ostane ista samo se sad ukupne sekunde mjenjaju
    }
    Sat &PomjeriZa(int s) { //DONE
        sekunde+=s;
            int h=sekunde/3600;
            int m=(sekunde/60)%60;
            int sek=(sekunde%60);
            PostaviNormalizirano(h,m,sek); //poziva se nad objektom nad kojim je pozvana ova Pomjeri fja
        return *this;
    }
    Sat &Sljedeci() { //DONE
        return PomjeriZa(1);
    }
    Sat &Prethodni() { //DONE
        return PomjeriZa(-1);
    }
    int DajSate() const {
        return sekunde/3600;
    }
    int DajMinute() const {
        return ((sekunde/60)%60);
    }
    int DajSekunde() const {
        return sekunde%60;
    }
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
int BrojSekundiIzmedju(const Sat &v1,const Sat &v2) { //DONE
    return v1.sekunde-v2.sekunde;
}

int Sat::Razmak(const Sat &v1,const Sat &v2) { //DONE
    return v1.sekunde-v2.sekunde;
}

int main ()
{
	return 0;
}