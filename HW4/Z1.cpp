#include <iostream>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>
#include <tuple>
#include <utility>

typedef  std::pair<double,double> Tacka;
const double pi=4*atan(1);
const double eps=10e-10;
/* MOZDA UVEDI NEKI EPSILON */
class Trougao {
    Tacka T1,T2,T3;
    static double UdaljenostIzmedjuDvijeTacke(const Tacka &t1,const Tacka &t2) {
        double rezultat;
        rezultat=std::sqrt((t2.first-t1.first)*(t2.first-t1.first)+(t2.second-t1.second)*(t2.second-t1.second));
        return rezultat;
    }
    //reko profesor dodatne funkcije u private
    static double Pomocna(const Tacka &t1,const Tacka &t2,const Tacka &t3) { //mora biti static(jer se ne poziva nad nicim pa zato) -> a friend nije jer friend se koriste samo izvan klase lol
        double rezultat;
        rezultat=t1.first*(t2.second-t3.second)-t2.first*(t1.second-t3.second)+t3.first*(t1.second-t2.second);
        return rezultat;
    }
    Tacka RacunajSkaliranje(const Tacka &t1,const Tacka &t2,double faktor) {
        Tacka rez;
        rez.first=(t2.first+faktor*(t1.first-t2.first));
        rez.second=(t2.second+faktor*(t1.second-t2.second));
        return rez;
    }
    Tacka RacunajRotaciju(const Tacka &t1,const Tacka &t2,double ugao) {
        Tacka rez;
        rez.first=(t2.first+(t1.first-t2.first)*cos(ugao) - (t1.second-t2.second)*sin(ugao));
        rez.second=(t2.second+(t1.first-t2.first)*sin(ugao) + (t1.second-t2.second)*cos(ugao));
        return rez;
    }
public:
    Trougao(const Tacka &t1,const Tacka &t2,const Tacka &t3) {
        Postavi(t1,t2,t3);
    }
    void Postavi(const Tacka &t1,const Tacka &t2,const Tacka &t3) { //jos ovo razmotri
        if(Orijentacija(t1,t2,t3)==0) throw std::domain_error("Nekorektne pozicije tjemena"); //kolinearne -> leze na istom pravcu
        T1=t1; T2=t2; T3=t3;
    }
    void Postavi(int indeks,const Tacka &t) { //treba paziti da li dodjeljivanjem nastaju KOLINEARNE TACKE prije samo dodjele u svakom ifu
        if(indeks==1) Postavi(t,T2,T3);
        else if(indeks==2) Postavi(T1,t,T3);
        else if(indeks==3) Postavi(T1,T2,t);
        else throw std::range_error("Nekorektan indeks");
    }
    static int Orijentacija(const Tacka &t1,const Tacka &t2,const Tacka &t3) {
        double rezultat;
        rezultat=Pomocna(t1,t2,t3);
        if(rezultat>0) return 1; //Orijentacija pozitivna
        if(rezultat<0) return -1;
        if(rezultat==0) return 0;
    }
    Tacka DajTjeme(int indeks) const {
        if(indeks==1) return T1;
        else if(indeks==2) return T2;
        else if(indeks==3) return T3;
        else throw std::range_error("Nekorektan indeks");
    }
    double DajStranicu(int indeks) const { //mogao sam napraviti pom. fju al nema veze -> pravio sam za ostale
        if(indeks==1) return (sqrt((T2.first-T3.first)*(T2.first-T3.first) + (T2.second-T3.second)*(T2.second-T3.second)));
        else if(indeks==2) return (sqrt((T1.first-T3.first)*(T1.first-T3.first) + (T1.second-T3.second)*(T1.second-T3.second)));
        else if(indeks==3) return (sqrt((T2.first-T1.first)*(T2.first-T1.first) + (T2.second-T1.second)*(T2.second-T1.second)));
        else throw std::range_error("Nekorektan indeks");
    }
    double DajUgao(int indeks) const {
        double ugao1=acos((DajStranicu(2)*DajStranicu(2)+DajStranicu(3)*DajStranicu(3)-DajStranicu(1)*DajStranicu(1))/(2*DajStranicu(2)*DajStranicu(3)));
        double ugao2=acos((DajStranicu(1)*DajStranicu(1)+DajStranicu(3)*DajStranicu(3)-DajStranicu(2)*DajStranicu(2))/(2*DajStranicu(1)*DajStranicu(3)));
        double ugao3=acos((DajStranicu(1)*DajStranicu(1)+DajStranicu(2)*DajStranicu(2)-DajStranicu(3)*DajStranicu(3))/(2*DajStranicu(1)*DajStranicu(2)));
        if(indeks==1) return (ugao1);
        else if(indeks==2) return (ugao2);
        else if(indeks==3) return (ugao3);
        else throw std::range_error("Nekorektan indeks");
    }
    Tacka DajCentar() const {
        Tacka Centar;
        Centar.first=(T1.first+T2.first+T3.first)/3;
        Centar.second=(T1.second+T2.second+T3.second)/3;
        return Centar;
    }
    double DajObim() const {
        return (DajStranicu(1)+DajStranicu(2)+DajStranicu(3));
    }
    friend double Pomocna(const Tacka &t1,const Tacka &t2,const Tacka &t3);
    double DajPovrsinu() const {
        double povrsina;
        povrsina=0.5*fabs(Pomocna(T1,T2,T3));
        return povrsina;
    }
    bool DaLiJePozitivnoOrijentiran() const {
        if(Orijentacija(T1,T2,T3)>0) return true;
        return false;
    }
    bool DaLiJeUnutra(const Tacka &t) const {
        /* Ako je glavna Orijentacija negativna,sve ostale moraju biti negativne da tacka bude unutra */
        if(Orijentacija(T1,T2,T3)<0) { //<= 0 je false, >0 je true
            if(Orijentacija(T1,T2,t)<=0 && Orijentacija(T2,T3,t)<=0 && Orijentacija(T3,T1,t)<=0) return true;
           // if(Orijentacija(T1,T2,t)==0 || Orijentacija(T2,T3,t)==0 || Orijentacija(T3,T1,t)==0) return true;
        }
        /* Ako je glavna orjenatacija pozitivna, sve ostale moraju biti pozivitvne da tacak bude unutra */
        else if(Orijentacija(T1,T2,T3)>0) {
            if(Orijentacija(T1,T2,t)>=0 && Orijentacija(T2,T3,t)>=0 && Orijentacija(T3,T1,t)>=0) return true;
         //   if(Orijentacija(T1,T2,t)==0 || Orijentacija(T2,T3,t)==0 || Orijentacija(T3,T1,t)==0) return true;
        }
        return false;
    }
    void Ispisi() const {
        std::cout<<"(("<<T1.first<<","<<T1.second<<"),("<<T2.first<<","<<T2.second<<"),("<<T3.first<<","<<T3.second<<"))";
    }
    void Transliraj(double delta_x,double delta_y) {
        T1.first+=delta_x; T2.first+=delta_x; T3.first+=delta_x;
        T1.second+=delta_y; T2.second+=delta_y; T3.second+=delta_y;
    }
    void Centriraj(const Tacka &t) {
        double po_x=t.first-DajCentar().first;
        double po_y=t.second-DajCentar().second;
        Transliraj(po_x,po_y);
    }
    void Rotiraj(const Tacka &t,double ugao) {
        T1=RacunajRotaciju(T1,t,ugao);
        T2=RacunajRotaciju(T2,t,ugao);
        T3=RacunajRotaciju(T3,t,ugao);
    }
    void Skaliraj(const Tacka &t,double faktor) {
        if(faktor==0) throw std::domain_error("Nekorektan faktor skaliranja");
        T1=RacunajSkaliranje(T1,t,faktor);
        T2=RacunajSkaliranje(T2,t,faktor);
        T3=RacunajSkaliranje(T3,t,faktor);
    }
    void Rotiraj(double ugao) {
        Rotiraj(DajCentar(),ugao);
    }
    void Skaliraj(double faktor) {
        Skaliraj(DajCentar(),faktor);
    }
    friend bool DaLiSuIdenticni(const Trougao &t1,const Trougao &t2);
    friend bool DaLiSuPodudarni(const Trougao &t1,const Trougao &t2);
    friend bool DaLiSuSlicni(const Trougao &t1,const Trougao &t2);
};

/* Friend funkcije iz zadatka */
/* Ova radi funkcija */
bool DaLiSuIdenticni(const Trougao &t1,const Trougao &t2) {
    if(t1.T1==t2.T1) {
        if(t1.T2==t2.T2) {
            if(t1.T3==t2.T3) return true;
        }
        else if(t1.T2==t2.T3) {
            if(t1.T3==t2.T2) return true;
        }
    }
    else if(t1.T1==t2.T2) {
        if(t1.T2==t2.T1) {
            if(t1.T3==t2.T3) return true;
        }
        else if(t1.T2==t2.T3) {
            if(t1.T3==t2.T1) return true;
        }
    }
    else if(t1.T1==t2.T3) {
        if(t1.T2==t2.T1) {
            if(t1.T3==t2.T2) return true;
        }
        else if(t1.T2==t2.T2) {
            if(t1.T3==t2.T1) return true;
        }
    }
    return false;
}

bool DaLiSuPodudarni(const Trougao &t1,const Trougao &t2) {
    std::vector<std::tuple<double,double,Tacka>> a,b;
    int brojac1=0,brojac2=0;
    a.push_back(std::make_tuple(t1.DajUgao(1),t1.DajStranicu(1),t1.T1));
    a.push_back(std::make_tuple(t1.DajUgao(2),t1.DajStranicu(2),t1.T2));
    a.push_back(std::make_tuple(t1.DajUgao(3),t1.DajStranicu(3),t1.T3));
    b.push_back(std::make_tuple(t2.DajUgao(1),t2.DajStranicu(1),t2.T1));
    b.push_back(std::make_tuple(t2.DajUgao(2),t2.DajStranicu(2),t2.T2));
    b.push_back(std::make_tuple(t2.DajUgao(3),t2.DajStranicu(3),t2.T3));
    std::sort(a.begin(),a.end(),[](std::tuple<double,double,Tacka> x,std::tuple<double,double,Tacka> y)-> bool {
        return std::get<0>(x)<std::get<0>(y);
    });
    std::sort(b.begin(),b.end(),[](std::tuple<double,double,Tacka> x,std::tuple<double,double,Tacka> y)->bool {
        return std::get<0>(x)<std::get<0>(y);
    });
    for(int i=0;i<3;i++) {
        if(fabs(std::get<0>(a.at(i)) - std::get<0>(b.at(i))) < eps) brojac1++;
        if(fabs(std::get<1>(a.at(i)) - std::get<1>(b.at(i))) < eps) brojac2++;
    }
    if(brojac1==3 && brojac2==3) {
        if(Trougao::Orijentacija(std::get<2>(a.at(0)),std::get<2>(a.at(1)),std::get<2>(a.at(2)))==Trougao::Orijentacija(std::get<2>(b.at(0)),std::get<2>(b.at(1)),std::get<2>(b.at(2)))) return true;
    }
    return false;
}

bool DaLiSuSlicni(const Trougao &t1,const Trougao &t2) {
    std::vector<std::tuple<double,double,Tacka>> a,b;
    int brojac1=0,brojac2=0;
    a.push_back(std::make_tuple(t1.DajUgao(1),t1.DajStranicu(1),t1.T1));
    a.push_back(std::make_tuple(t1.DajUgao(2),t1.DajStranicu(2),t1.T2));
    a.push_back(std::make_tuple(t1.DajUgao(3),t1.DajStranicu(3),t1.T3));
    b.push_back(std::make_tuple(t2.DajUgao(1),t2.DajStranicu(1),t2.T1));
    b.push_back(std::make_tuple(t2.DajUgao(2),t2.DajStranicu(2),t2.T2));
    b.push_back(std::make_tuple(t2.DajUgao(3),t2.DajStranicu(3),t2.T3));
    std::sort(a.begin(),a.end(),[](std::tuple<double,double,Tacka> x,std::tuple<double,double,Tacka> y)->bool {
        return (std::get<0>(x)<std::get<0>(y));
    });
    std::sort(b.begin(),b.end(),[](std::tuple<double,double,Tacka> x,std::tuple<double,double,Tacka> y)->bool {
        return (std::get<0>(x)<std::get<0>(y));
    });
    double odnos=(std::get<1>(a.at(0)) / std::get<1>(b.at(0))); //uzmes prve dvije stranice jer je svakako sortirano sve
    for(int i=0;i<3;i++) {
        if(fabs(std::get<0>(a.at(i)) - std::get<0>(b.at(i)))<eps) brojac1++;
        if( fabs((std::get<1>(a.at(i)) / std::get<1>(b.at(i))) - odnos)<eps ) brojac2++;
    }
    if(brojac1==3 && brojac2==3) {
        if(Trougao::Orijentacija(std::get<2>(a.at(0)),std::get<2>(a.at(1)),std::get<2>(a.at(2)))==Trougao::Orijentacija(std::get<2>(b.at(0)),std::get<2>(b.at(1)),std::get<2>(b.at(2)))) return true;
    }
    return false;
}

int main ()
{  
    
    try {
    int n,f1=0,f2=0,f3=0;
    std::cout<<"Koliko zelite kreirati trouglova: ";
    std::cin>>n;
    std::vector<std::shared_ptr<Trougao>> v(n);
    for(int i=0;i<n;i++) {
        std::cout<<"Unesite podatke za "<<i+1<<". trougao (x1 y1 x2 y2 x3 y3): ";
        int x1,y1,x2,y2,x3,y3;
        std::cin>>x1>>y1>>x2>>y2>>x3>>y3;
        try {
            Trougao t1(Tacka{x1,y1},Tacka{x2,y2},Tacka{x3,y3});
            v[i]=std::make_shared<Trougao>(t1);
        }
        catch(std::domain_error e) {
            std::cout<<e.what()<<", ponovite unos!"<<std::endl;
            i--;
        }
    }
    
    std::cout<<"Unesite vektor translacije (dx dy): ";
    double delta_x,delta_y;
    std::cin>>delta_x>>delta_y;
    std::cout<<"Unesite ugao rotacije: ";
    double faktor,ugao;
    std::cin>>ugao;
    std::cout<<"Unesite faktor skaliranja: ";
    std::cin>>faktor;
    std::cout<<"Trouglovi nakon obavljenih transformacija: "<<std::endl;
    std::transform(v.begin(),v.end(),v.begin(),[delta_x,delta_y,ugao,faktor](std::shared_ptr<Trougao> p) {
        p->Transliraj(delta_x,delta_y);
        p->Rotiraj(p->DajCentar(),ugao);
        p->Skaliraj(p->DajTjeme(1),faktor);
        return p;
    });
    std::sort(v.begin(),v.end(),[](std::shared_ptr<Trougao> t1,std::shared_ptr<Trougao> t2) {
        return(t1->DajPovrsinu()<t2->DajPovrsinu());
    });
    std::for_each(v.begin(),v.end(),[](std::shared_ptr<Trougao> t1) {
        t1->Ispisi();
        std::cout<<std::endl;
    });
    std::cout<<"Trougao sa najmanjim obimom: ";
    (*std::min_element(v.begin(),v.end(),[](std::shared_ptr<Trougao> t1,std::shared_ptr<Trougao> t2)->bool {
        return t1->DajObim() < t2->DajObim();
    }))->Ispisi(); 
    std::cout<<std::endl;
    for(int i=0;i<v.size();i++) {
        for(int j=i+1;j<v.size();j++) {
            if(DaLiSuIdenticni(*v.at(i),*v.at(j)) && !f1) f1++;
            if(DaLiSuPodudarni(*v.at(i),*v.at(j)) && !f2) f2++;
            if(DaLiSuSlicni(*v.at(i),*v.at(j)) && !f3) f3++;
            if(f1 && f2 && f3) break;
        }
        if(f1 && f2 && f3) break;
    }
    if(f1==0) std::cout<<"Nema identicnih trouglova!"<<std::endl;
    else {
   std::cout<<"Parovi identicnih trouglova: "<<std::endl;
   for(int i=0;i<v.size();i++) {
       for(int j=i+1;j<v.size();j++) {
           if(DaLiSuIdenticni(*v.at(i),*v.at(j) ) )  {
               v.at(i)->Ispisi();
               std::cout<<" i ";
               v.at(j)->Ispisi();
               std::cout<<std::endl;
           }
       }
   }
    }
    if(f2==0) std::cout<<"Nema podudarnih trouglova!"<<std::endl;
    else {
   //std::cout<<std::endl;
   std::cout<<"Parovi podudarnih trouglova: "<<std::endl;
   for(int i=0;i<v.size();i++) {
       for(int j=i+1;j<v.size();j++) {
           if(DaLiSuPodudarni(*v.at(i),*v.at(j))) {
               v.at(i)->Ispisi();
               std::cout<<" i ";
               v.at(j)->Ispisi();
               std::cout<<std::endl;
           }
       }
   }
    }
    if(f3==0) std::cout<<"Nema slicnih trouglova!"<<std::endl;
    else {
   std::cout<<"Parovi slicnih trouglova: "<<std::endl;
   for(int i=0;i<v.size();i++) {
       for(int j=i+1;j<v.size();j++) {
           if(DaLiSuSlicni(*v.at(i),*v.at(j))) {
               v.at(i)->Ispisi();
               std::cout<<" i ";
               v.at(j)->Ispisi();
               std::cout<<std::endl;
           }
       }
   }
    }
    }
catch(std::domain_error e) {
    std::cout<<e.what();
}
catch(std::range_error e) {
    std::cout<<e.what();
}
catch(...) {
    
}
	return 0;
}