#include <iostream>
#include <stdexcept>
#include <iomanip>

class Sat {
private:
    int sat,minuta,sekunda;
public:
    Sat() : sat(0),minuta(0),sekunda(0) {}
    Sat(int a,int b,int c) {
        PostaviNormalizirano(a,b,c);
    }
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
    Sat& operator ++() {
        sekunda+=1;
        PostaviNormalizirano(sat,minuta,sekunda);
    }
    Sat& operator --() {
        sekunda-=1;
        PostaviNormalizirano(sat,minuta,sekunda);
    }
    Sat operator ++(int) {
        Sat pomocna(*this); //automatski kopirajuci konstruktor
        sekunda+=1;
        PostaviNormalizirano(sat,minuta,sekunda);
        return pomocna;
    }
    Sat operator --(int) {
        Sat pomocna(*this);
        sekunda-=1;
        PostaviNormalizirano(sat,minuta,sekunda);
        return pomocna;
    }
    Sat& operator +=(int broj) {
        sekunda+=broj;
        PostaviNormalizirano(sat,minuta,sekunda);
        return *this;
    }
    Sat& operator -=(int broj) {
        /* Probaj izvesti preko += */
        broj=-broj;
        /* Ovo pod komentarom je drugi nacin(tj ne preko +=, al to je ponavljanje procesa) */
        //sekunda-=broj;
        //PostaviNormalizirano(sat,minuta,sekunda);
       // return *this;
       return *this+=broj; // ovo je uradjeno preko operatora +=
    }
    friend int operator -(const Sat &v1,const Sat &v2); //za razliku sekundi
    int DajSate() const {
        return sat;
    }
    int DajMinute() const {
        return minuta;
    }
    int DajSekunde() const {
        return sekunda;
    }
    friend Sat operator +(const Sat &s,int broj) {
        //PROBAJ SUTRA IZVESTI PREKO += 
        Sat pomocna(s);
        pomocna.sekunda+=broj;
        pomocna.PostaviNormalizirano(pomocna.sat,pomocna.minuta,pomocna.sekunda);
        return pomocna;
    }
   friend Sat operator -(const Sat &s,int broj) {
        Sat pomocna(s);
        pomocna.sekunda-=broj;
        pomocna.PostaviNormalizirano(pomocna.sat,pomocna.minuta,pomocna.sekunda);
        return pomocna;
    }
    friend std::ostream &operator <<(std::ostream &tok,const Sat &s) {
        return tok<<std::setw(2)<<std::setfill('0')<<s.sat<<":"<<std::setw(2)<<
        std::setfill('0')<<s.minuta<<":"<<std::setw(2)<<std::setfill('0')<<s.sekunda;
    }
};
int operator -(const Sat &v1,const Sat &v2) {
    int rez=0;
    int s1=0,s2=0;
    s1=v1.sat*3600+v1.minuta*60+v1.sekunda;
    s2=v2.sat*3600+v2.minuta*60+v2.sekunda;
    rez=s1-s2;
    return rez;
}

int main() {
    Sat a(13,15,2);
    Sat b(12,12,8);
    std::cout<<a.DajMinute()<<" "<<a.DajSekunde()<<" "<<a.DajSate()<<std::endl;
    std::cout<<a<<" "<<b<<" "<<std::endl;
    std::cout<<a-b<<std::endl;
    std::cout<<a+5<<std::endl;
    std::cout<<b-5<<std::endl;
    a--;
    b++;
    std::cout<<a<<std::endl;
    std::cout<<b<<std::endl;
  Sat s1(11, 4, 39);
  std::cout << s1 << std::endl;
  s1 += 25000;
  std::cout << s1 << std::endl;
  s1 -= 25000;
  std::cout << s1 << std::endl;
    return 0;
}


