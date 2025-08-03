#include <iostream>
#include <cmath>
#include <iomanip>

class Ugao {
private:
    int deg,min,sec;
    static constexpr double pi=4*atan(1); 
public:
    Ugao(double radijani=0) { //podrzava automatsku konverziju realnih brojeva u objeke tipa klase
        Postavi(radijani);
    }
    explicit Ugao(int stepeni,int minute,int sekunde) { //ne treba podrzavati automatsku konverziju
        Postavi(stepeni,minute,sekunde);
    }
    void Postavi(double radijani) {
        if(radijani<0) {
            while(radijani<0) radijani+=2*pi;
        }
        if(radijani>=2*pi) {
            while(radijani>=2*pi) radijani-=2*pi;
        }
        double a,b,c;//deg min sek (treba mi pomocne za double)
        a=radijani*180/pi;
        b=(a-int(a))*60;
        c=(b-int(b))*60 + 0.0000000001;
        deg=a; min=b; sec=c;
    }
    void Postavi(int stepeni,int minute,int sekunde) {
       double radijani=(pi/180)*(stepeni+double(minute)/60+double(sekunde)/3600);
       Postavi(radijani); //pozovem prvu funkciju da mi reducira radijane, da ne moram isto pisat opet
    }
    double DajRadijane() const {
        double radijani=(pi/180)*(deg+double(min)/60+double(sec)/3600);
        return radijani;
    }
    void OcitajKlasicneJedinice(int &stepeni,int &minute,int &sekunde) {
        stepeni=DajSekunde();
        minute=DajMinute();
        sekunde=DajSekunde();
    }
    int DajStepene() const {
        return deg;
    }
    int DajMinute() const {
        return min;
    }
    int DajSekunde() const {
    	return sec;
    }
    void Ispisi() const {
        std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane();
    }
    void IspisiKlasicno() const {
        std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";
    }
    Ugao& SaberiSa(const Ugao &u) {
        deg+=u.deg;
        min+=u.min;
        sec+=u.sec;
        Postavi(deg,min,sec); //jer ga treba reducirat opet
        return *this;
    }
    Ugao& PomnoziSa(double x) {
        deg*=x;
        min*=x;
        sec*=x;
        Postavi(deg,min,sec);
        return *this;
    }
    friend Ugao ZbirUglova(const Ugao &u1,const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u,double x);
};

Ugao ZbirUglova(const Ugao &u1,const Ugao &u2) {
    Ugao novi;
    novi.deg=u1.deg+u2.deg;
    novi.min=u1.min+u2.min;
    novi.sec=u1.sec+u2.sec;
    /* ne moze novi={...,....,....} jer je ovaj konstruktor sa 3 parametra
    eksplicitan te ne dozvoljava automatske pretvorbe npr ove inicijalizacione
    liste u objekt tipa ove klase */
    novi.Postavi(novi.deg,novi.min,novi.sec); //da se radijani ljepse postave
    return novi;
}

Ugao ProduktUglaSaBrojem(const Ugao &u,double x) {
    Ugao novi=u;
    novi.deg=novi.deg*x;
    novi.min=novi.min*x;
    novi.sec=novi.sec*x;
    novi.Postavi(novi.deg,novi.min,novi.sec);
    return novi;
}

int main ()
{
    Ugao u1(5);
    u1.Ispisi();
    std::cout<<std::endl;
    u1.Postavi(220);
    u1.Ispisi();
    std::cout<<std::endl;
    u1.IspisiKlasicno();
    std::cout<<std::endl;
    u1.Postavi(100,32,32);
    u1.Ispisi();
    std::cout<<std::endl;
    u1=Ugao(120,13,17); //ne bi moglo u1={120,13,17};
    u1.Ispisi();
    std::cout<<std::endl;
    u1.IspisiKlasicno();
    std::cout<<std::endl;
    u1.SaberiSa(5).Ispisi(); //ova 5 se automatski predtava u KLASU(da je obicna referenca bila ne bi moglo)
    std::cout<<std::endl;
    u1.PomnoziSa(2).Ispisi(); //isto za 2
    std::cout<<std::endl;
    ZbirUglova(u1,20).Ispisi();
    std::cout<<std::endl;
    ProduktUglaSaBrojem(u1,2).Ispisi();
	return 0;
}