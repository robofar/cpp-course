#include <iostream>
#include <cmath>

class Vektor3d {
private:
    double x,y,z;
public:
    void Postavi(double a,double b,double c) {
        x=a; y=b; z=c;
    }
    void Ocitaj(double &a,double &b,double &c) const {
        a=x; b=y; c=z;
    }
    void PostaviX(double a) {x=a;}
    void PostaviY(double b) {y=b;}
    void PostaviZ(double c) {z=c;}
    double DajX() const {return x;}
    double DajY() const {return y;}
    double DajZ() const {return z;}
    double DajDuzinu() const { return std::sqrt(x*x + y*y + z*z); }
    Vektor3d& PomnoziSaSkalarom(double s) {
        x*=s;
        y*=s;
        z*=s;
        return *this;
    }
    Vektor3d& SaberiSa(const Vektor3d &v) {
        x+=v.x;
        y+=v.y;
        z+=v.z;
        return *this;
    }
    void Ispisi() const { //treba bit const 
        std::cout<<"{"<<x<<","<<y<<","<<z<<"}";
    }
    friend Vektor3d ZbirVektora(const Vektor3d &v1,const Vektor3d &v2); //prototip
};

Vektor3d ZbirVektora(const Vektor3d &v1,const Vektor3d &v2) {
    Vektor3d v3;
    v3.x=v1.x+v2.x;
    v3.y=v1.y+v2.y;
    v3.z=v1.z+v2.z;
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
	return 0;
}