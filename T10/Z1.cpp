#include <iostream>
#include <stdexcept>

class StedniRacun {
private:
	double stanje_racuna;
public:
	StedniRacun() { stanje_racuna=0; }
	StedniRacun(double x) { 
		if(x<0) throw std::logic_error("Nedozvoljeno pocetno stanje");
		stanje_racuna=x; 
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
};
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