#include <iostream>
#include <cmath>
#include <iomanip>

class Ugao {
private:
    double rad;
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
        rad=radijani;
    }
    void Postavi(int stepeni,int minute,int sekunde) {
        double radijani=(pi/180)*(stepeni+double(minute)/60+double(sekunde)/3600);
        Postavi(radijani); //pozovem prvu funkciju da mi reducira radijane, da ne moram isto pisat opet
    }
    double DajRadijane() const {
        return rad;
    }
    void OcitajKlasicneJedinice(int &stepeni,int &minute,int &sekunde) {
        stepeni=DajSekunde();
        minute=DajMinute();
        sekunde=DajSekunde();
    }
    int DajStepene() const {
        return rad*180/pi;
    }
    int DajMinute() const {
        return (rad*180/pi - int(rad*180/pi))*60;
    }
    int DajSekunde() const {
        double minute_realne = (rad*180/pi - int(rad*180/pi))*60;
        return (minute_realne-int(minute_realne))*60 + 0.000000001; //moras dodat ovo jer npr broj neki broj je u realnom zapisu predstavljen nekad malo veci nekad malo manji, a int to uvijek odsjece
    }
    void Ispisi() const {
        std::cout<<std::fixed<<std::setprecision(5)<<DajRadijane();
    }
    void IspisiKlasicno() const {
        std::cout<<DajStepene()<<"deg "<<DajMinute()<<"min "<<DajSekunde()<<"sec";
    }
    Ugao& SaberiSa(const Ugao &u) {
        rad+=u.rad;
        Postavi(rad); //jer ga treba reducirat opet
        return *this;
    }
    Ugao& PomnoziSa(double x) {
        rad*=x;
        Postavi(rad);
        return *this;
    }
    friend Ugao ZbirUglova(const Ugao &u1,const Ugao &u2);
    friend Ugao ProduktUglaSaBrojem(const Ugao &u,double x);
};

Ugao ZbirUglova(const Ugao &u1,const Ugao &u2) {
    Ugao novi;
    novi.rad=u1.rad+u2.rad;
    novi.Postavi(novi.rad); //da se radijani ljepse postave
    return novi;
}

Ugao ProduktUglaSaBrojem(const Ugao &u,double x) {
    Ugao novi=u;
    novi.rad*=x;
    novi.Postavi(novi.rad);
    return novi; //u.rad*x; -> radice ako postoji konstruktor SA JEDNIM PARAMETROM koji prima double npr jer oni sluze za automatsku konverziju
    //ali konstruktor ne smije biti explicit
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