#include <iostream>
#include <stdexcept>

class StedniRacun {
private:
	double stanje_racuna;
	static int kreiranih; //moraju biti static jer su ove 2 varijable ovise samo od poziva, nebitno nad kojim objektom su pozvane
	static int aktivnih; //da se ne bi pravio svaki primjerak za svaki objekt posebno
public:
	StedniRacun() { 
		stanje_racuna=0; 
		kreiranih++;
		aktivnih++;
	}
	StedniRacun(const StedniRacun &s1) { //kopirajuci konstruktor(pravimo svoju verziju da se ne pozove podrazumijevani kopirajuci konstruktor)
		stanje_racuna=s1.stanje_racuna;
		kreiranih++;
		aktivnih++;
	}
	StedniRacun(double x) { 
		if(x<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
		stanje_racuna=x;
		kreiranih++;
		aktivnih++;
	}
	~StedniRacun() { //automatski se poziva da unisti objekat(posto nas objekat nije duzio nikakve dodatne resurse ne treba nikakav delete u tijelu desturktora)
		aktivnih--;
	}
	void Ulozi(double x) {
		if(stanje_racuna+x<0) throw std::logic_error("Transakcija odbijena"); //provjera ovako da se ne bi mijenjao sam iznos pa tek onda bacio izuzetak
		stanje_racuna+=x;
	}
	void Podigni (double x) { //mutator
		if(x>stanje_racuna) throw std::logic_error("Transakcija odbijena");
		stanje_racuna-=x;
	}
	double DajStanje() const { //const sluzi da se neki privatni atribut ne moze mjenjat unutar te metode
		return stanje_racuna;
	}
	void ObracunajKamatu(double kamata) { 
		if(kamata<0) throw std::logic_error("Nedozvoljena kamatna stopa");
		double uvecanje=stanje_racuna*(kamata/100);
		stanje_racuna+=uvecanje;
	}
	static int DajBrojKreiranih() { //static funkcije ne mogu biti const !
		return kreiranih;
	}
	static int DajBrojAktivnih() { //staticke su - jer ne treba da znaju nad kim se pozivaju
		return aktivnih;
	}
};
int StedniRacun::kreiranih=0; //definisu se izvan klase
int StedniRacun::aktivnih=0;
int main ()
{
	StedniRacun prvi;
	std::cout<<prvi.DajStanje();
	std::cout<<std::endl;
	StedniRacun drugi(3);
	std::cout<<drugi.DajStanje();
	std::cout<<std::endl;
	drugi.Ulozi(1000);
	std::cout<<drugi.DajStanje();
	std::cout<<std::endl;
	drugi.Podigni(50);
	std::cout<<drugi.DajStanje();
	std::cout<<std::endl;
	drugi.ObracunajKamatu(20);
	std::cout<<drugi.DajStanje();
	std::cout<<std::endl;
	const StedniRacun proba(500);
	std::cout<<proba.DajStanje();
	return 0;
}