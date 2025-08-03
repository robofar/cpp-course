#include <iostream>
#include <cmath>

class Vektor3d {
private:
    double koordinate[3];
    mutable int brojac=0; //ovim mutable naznacimo da iako je privatan moze se mijenjati
public:
    void Postavi(double a,double b,double c) {
        koordinate[0]=a; koordinate[1]=b; koordinate[2]=c;
    }
    void Ocitaj(double &a,double &b,double &c) const {
        a=koordinate[0]; b=koordinate[1]; c=koordinate[2];
    }
    void PostaviX(double a) {koordinate[0]=a;}
    void PostaviY(double b) {koordinate[1]=b;}
    void PostaviZ(double c) {koordinate[2]=c;}
    double DajX() const {return koordinate[0];}
    double DajY() const {return koordinate[1];}
    double DajZ() const {return koordinate[2];}
    double DajDuzinu() const { return std::sqrt(koordinate[0]*koordinate[0] + koordinate[1]*koordinate[1] + koordinate[2]*koordinate[2]); }
    Vektor3d& PomnoziSaSkalarom(double s) {
        koordinate[0]*=s;
        koordinate[1]*=s;
        koordinate[2]*=s;
        return *this;
    }
    Vektor3d& SaberiSa(const Vektor3d &v) {
        koordinate[0]+=v.koordinate[0];
        koordinate[1]+=v.koordinate[1];
        koordinate[2]+=v.koordinate[2];
        return *this;
    }
    int DajBrojIspisa() const { 
        return brojac;
    }
    void Ispisi() const {
        brojac++;
        std::cout<<"{"<<koordinate[0]<<","<<koordinate[1]<<","<<koordinate[2]<<"}";
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1,const Vektor3d &v2); //prototip
};

Vektor3d ZbirVektora(const Vektor3d &v1,const Vektor3d &v2) {
    Vektor3d v3;
    v3.koordinate[0]=v1.koordinate[0]+v2.koordinate[0];
    v3.koordinate[1]=v1.koordinate[1]+v2.koordinate[1];
    v3.koordinate[2]=v1.koordinate[2]+v2.koordinate[2];
    return v3;
}


int main ()
{
    Vektor3d v,v1;
    v1.Postavi(7,7,7);
    v.Postavi(2,2,2);
    v.Ispisi();
    std::cout<<std::endl;
    v.PostaviX(3);
    v.PostaviY(4);
    v.PostaviZ(5);
    v.Ispisi();
    double a,b,c;
    v.Ocitaj(a,b,c);
    double x=v.DajDuzinu();
    std::cout<<x<<std::endl;
    v.PomnoziSaSkalarom(4);
    v.Ispisi();
    std::cout<<std::endl;
    v.SaberiSa(v1).Ispisi();
    std::cout<<std::endl;
    Vektor3d rez=ZbirVektora(v,v1);
    rez.Ispisi();
    v1.Ispisi(); v1.Ispisi();
    std::cout << "Objekat v1 je ispisan " << v.DajBrojIspisa() << "puta, a objekat v2 " << v1.DajBrojIspisa() << "puta"<< std::endl;
	return 0;
}