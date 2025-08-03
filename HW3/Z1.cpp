#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <utility>
#include <algorithm>

const double epsilon=0.0000000001;
std::function<double(double)> BaricentricnaInterpolacija(std::vector<std::pair<double,double>> cvorovi,int d) {
    if(d<0 || d>=cvorovi.size()) throw std::domain_error("Nedozvoljen red");
    for(int i=0;i<cvorovi.size();i++) {
        double z=cvorovi.at(i).first;
        for(int j=i+1;j<cvorovi.size();j++) {
            if(cvorovi.at(j).first==z) throw std::domain_error("Neispravni cvorovi");
        }
    }
     std::sort(cvorovi.begin(),cvorovi.end(),[](std::pair<double,double> p1,std::pair<double,double> p2) -> bool {
            return p1.first<p2.first;
     });
      int n=cvorovi.size();
      std::vector<double> tezinski(n);
      for(int i=0;i<n;i++) {
          double xi=cvorovi.at(i).first;
          double proizvod=1;
          /////////////////////////
          int donja,gornja;
          if(0>i-d) donja=0; //umjesto 1 u formuli ide 0, jer indeksacije pocinje od 0
          else donja=i-d;
          if(i>n-1-d) gornja=n-1-d; //umjesto n u formuli ide n-1 zbog idenksacije
          else gornja=i;
          ////////////////////////////////
          for(int k=donja;k<=gornja;k++) { //ide ukljucivo ko u formuli
              proizvod=1;
              int predznak=pow(-1,k-1);
              for(int j=k;j<=k+d;j++) { //ide ukljucivo ko u formuli
                  double xj=cvorovi.at(j).first;
                  if(i!=j) proizvod=(proizvod/(xi-xj));
              }
              tezinski.at(i)=tezinski.at(i)+(predznak*proizvod);
          }
        }
        return[cvorovi,tezinski,n](double x) {
        double rez;
        double brojnik=0;
        double nazivnik=0;
        double pomocna;
        for(int i=0;i<n;i++) {
            double xi=cvorovi.at(i).first;
            double yi=cvorovi.at(i).second;
            double wi=tezinski.at(i);
            if(x==xi) return yi;
            pomocna=(wi/(x-xi));
            brojnik=brojnik+pomocna*yi;
            nazivnik=nazivnik+pomocna;
        }
        rez=brojnik/nazivnik;
        return rez;
    };
}

std::function<double(double)> BaricentricnaInterpolacija(std::function<double(double)> f,double xmin,double xmax,double deltax,int d) {
    if(xmin>xmax || deltax<=0) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double,double>> cvorovi;
    for(double a=xmin;a<=xmax+epsilon;a+=deltax) {
        double xi,yi;
        xi=a;
        yi=f(xi);
        cvorovi.push_back(std::make_pair(xi,yi));
    }
    auto rez=BaricentricnaInterpolacija(cvorovi,d);
    return rez;
}
int main ()
{
try {
    int opcija;
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin>>opcija;
    if(opcija==1) {
        int broj_cvorova;
        std::cout<<"Unesite broj cvorova: ";
        std::cin>>broj_cvorova;
        std::vector<std::pair<double,double>> cvorovi;
        std::cout<<"Unesite cvorove kao parove x y: ";
        for(int i=0;i<broj_cvorova;i++) {
            double x,y;
            std::cin>>x;
            std::cin>>y;
            cvorovi.push_back(std::make_pair(x,y));
        }
        int d; //red
        std::cout<<"Unesite red interpolacije: ";
        std::cin>>d;
        std::function<double(double)> funkcija=BaricentricnaInterpolacija(cvorovi,d);
        for(;;) {
            double argument;
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>argument;
            if(!std::cin) return 0;
            std::cout<<"f("<<argument<<") = "<<funkcija(argument)<<std::endl;
        }
    }
    else if(opcija==2) {
        double xmin,xmax,deltax;
        std::cout<<"Unesite krajeve intervala i korak: ";
        std::cin>>xmin;
        std::cin>>xmax;
        std::cin>>deltax;
        int d;
        std::cout<<"Unesite red interpolacije: ";
        std::cin>>d;
        auto f=BaricentricnaInterpolacija([](double x) -> double {
            return x*x+std::sin(x);
        },xmin,xmax,deltax,d);
        for(;;) {
            double argument;
            std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
            std::cin>>argument;
            if(!std::cin) return 0;
            std::cout<<"f("<<argument<<") = "<<argument*argument+std::sin(argument)<<" fapprox("<<argument<<") = "<<f(argument);
            std::cout<<std::endl;
        }
    }
}
catch(std::domain_error izuzetak) {
    std::cout<<izuzetak.what();
}
	return 0;
}