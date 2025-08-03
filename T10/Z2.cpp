#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

const double pi=4*atan(1);

class Krug {
private:
	double poluprecnik;
public:
	explicit Krug(double x) { 
		Postavi(x);
	}
	void Postavi(double x) {
		if(x<=0) throw std::domain_error("Neispravan poluprecnik");
		poluprecnik=x;
	}
	double DajPoluprecnik() const {
		return poluprecnik;
	}
	double DajObim() const {
		return 2*poluprecnik*pi;
	}
	double DajPovrsinu() const {
		return poluprecnik*poluprecnik*pi;
	}
	void Skaliraj(double faktor) {
		if(faktor<=0) throw std::domain_error("Neispravan faktor skaliranja");
		poluprecnik*=faktor;
	}
	void Ispisi() const {
		std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnik()<<" O="<<DajObim()<<" P="<<DajPovrsinu();
	}
};

class Valjak {
private:
	double visina;
	Krug baza;
public:
	Valjak(double r,double h) : baza(r) /* ovo je poziv konstruktora iz klase odakle je baza */ {
		if(h<0) throw std::domain_error("Neispravna visina");
		visina=h; 
		//Postavi(r,h);
	}
	void Postavi(double r,double h) {
		baza.Postavi(r); 
		if(h<0) throw std::domain_error("Neispravna visina");
		visina=h;
	}
	Krug DajBazu() const {
		return baza;
	}
	double DajPoluprecnikBaze() const {
		return DajBazu().DajPoluprecnik(); //baza.poluprecnik, baza.DajPoluprecnik()
	}
	double DajVisinu() const {
		return visina;
	}
	double DajPovrsinu() const {
		return 2*baza.DajPovrsinu()+visina*baza.DajObim();
	}
	double DajZapreminu() const {
		return baza.DajPovrsinu()*visina;
	}
	void Skaliraj(double faktor) {
		if(faktor<=0) throw std::domain_error("Neispravan faktor skaliranja");
		baza.Skaliraj(faktor);
		visina*=faktor;
	}
	void Ispisi() const {
		std::cout<<std::fixed<<std::setprecision(5)<<"R="<<DajPoluprecnikBaze()<<" H="<<DajVisinu()<<" P="<<DajPovrsinu()<<" V="<<DajZapreminu();
	}
};

int main ()
{
	Krug k1(5);
	k1.Ispisi();
	std::cout<<std::endl;
	k1.Postavi(5);
	std::cout<<std::endl;
	std::cout<<" "<<k1.DajPoluprecnik()<<" "<<k1.DajObim()<<k1.DajPovrsinu()<<" ";
	std::cout<<std::endl;
	k1.Skaliraj(4);
	k1.Ispisi();
	std::cout<<std::endl;
	Valjak v1(2,3);
	v1.Ispisi();
	std::cout<<std::endl;
	std::cout<<v1.DajPoluprecnikBaze()<<" "<<v1.DajVisinu()<<" "<<v1.DajPovrsinu()<<" "<<v1.DajZapreminu();
	std::cout<<std::endl;
	Krug b1=v1.DajBazu(); //jer DajBazu vraca objekat tipa class Krug
	b1.Ispisi();
	return 0;
}