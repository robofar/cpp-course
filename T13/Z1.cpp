#include <iostream>
#include <cmath>
#include <stdexcept>
#include <memory>
#include <vector>
#include <iomanip>

const double eps=10e-8;

class Lik {
public:
	virtual ~Lik() {}
	virtual void IspisiSpecificnosti() const = 0;
	virtual double DajObim() const = 0;
	virtual double DajPovrsinu() const = 0;
	void Ispisi() const {
		IspisiSpecificnosti();
		std::cout<<"Obim: "<<DajObim()<<" Povrsina: "<<DajPovrsinu()<<std::endl;
	}
};

class Krug : public Lik {
private:
	double r;
	static constexpr double pi=3.1415926;
public:
	Krug(double poluprecnik) {
		if(poluprecnik<=0) throw std::domain_error("Neispravni parametri");
		r=poluprecnik;
	}
	double DajObim() const override {
		return 2*r*pi;
	}
	double DajPovrsinu() const override {
		return r*r*pi;
	}
	void IspisiSpecificnosti() const{
		std::cout<<"Krug poluprecnika "<<r<<std::endl;
	}
};

class Pravougaonik : public Lik {
private:
	double a,b;
public:
	Pravougaonik(double x,double y) : a(x),b(y) {
		if(x<=0 || y<=0) throw std::domain_error("Neispravni parametri");	
	}
	double DajObim() const override {
		return 2*a+2*b;
	}
	double DajPovrsinu() const override {
		return a*b;
	}
	void IspisiSpecificnosti() const {
		std::cout<<"Pravougaonik sa stranicama duzine "<<a<<" i "<<b<<std::endl;
	}
};

class Trougao : public Lik {
private:
	double a,b,c;
public:
	Trougao(double x,double y,double z) : a(x),b(y),c(z) {
		if(x<=0 || y<=0 || z<=0) throw std::domain_error("Neispravni parametri");
		double max,q,w;
		if(x>=y && x>=z) {
			max=x;
			q=y; w=z;
		}
		else if(y>=x && y>=z) {
			max=y;
			q=x; w=z;
		}
		else if(z>=x && z>=y) {
			max=z;
			q=x; w=y;
		}
		if(q*w<=max) throw std::domain_error("Neispravni parametri");
		//a=x; b=y; c=z;
	}
	double DajObim() const override {
		return a+b+c;
	}
	double DajPovrsinu() const override {
		double s=(a+b+c)/2;
		return sqrt(s*(s-a)*(s-b)*(s-c));
	}
	void IspisiSpecificnosti() const {
		std::cout<<"Trougao sa stranicama duzine "<<a<<", "<<b<<" i "<<c<<std::endl;
	}
};

int main ()
{
	int n;
	std::cout<<"Koliko zelite likova: ";
	std::cin>>n;
	std::vector<std::shared_ptr<Lik>> v(n);
//	std::string s;
	for(int i=0;i<n;i++) {
		std::cout<<"Lik "<<i+1<<": ";
		char prvo_slovo;
		std::cin>>prvo_slovo;
		if(prvo_slovo=='K') {
			double r;
			std::cin>>r;
			if(!std::cin || std::cin.peek()!='\n') {
				std::cin.clear();
				std::cin.ignore(1000,'\n');
				std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
				i--;
				continue;
			}
			try {
				v.at(i)=std::make_shared<Krug>(r);
			}
			catch(...) {
				std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
				i--;
			} 
		}
		else if(prvo_slovo=='P') {
			double a,b;
			char znak;
			std::cin>>a>>znak>>b;
			if(!std::cin || std::cin.peek()!='\n') {
				std::cin.clear();
				std::cin.ignore(1000,'\n');
				std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
				i--;
				continue;
			}
		//	if(znak!=',') throw std::domain_error("Pogresni podaci, ponovite unos!");
			try {
				v.at(i)=std::make_shared<Pravougaonik>(a,b);
			}
			catch(...) {
				std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
				i--;
			}
		}
		else if(prvo_slovo=='T') {
			double a,b,c;
			char znak1,znak2;
			std::cin>>a>>znak1>>b>>znak2>>c;
			if(!std::cin || std::cin.peek()!='\n') {
				std::cin.clear();
				std::cin.ignore(1000,'\n');
				std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
				i--;
				continue;
			}
		//	if(znak1!=',' || znak2!=',') throw std::domain_error("Pogresni podaci, ponovite unos!");
			try {
				v.at(i)=std::make_shared<Trougao>(a,b,c);
			}
			catch(...) {
				std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
				i--;
			}
		}
		else {
			std::cin.clear();
			std::cin.ignore(1000,'\n');
			std::cout<<"Pogresni podaci, ponovite unos!"<<std::endl;
			i--;
		}
	}
	std::cout<<std::endl;
	for(int i=0;i<n;i++) {
		v[i]->Ispisi();
	}
	return 0;
}