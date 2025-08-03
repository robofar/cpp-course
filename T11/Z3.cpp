#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <cstring>

class Tim {
	char ime_tima[20];
	int broj_odigranih,broj_pobjeda,broj_nerijesenih,broj_poraza;
	int broj_datih,broj_primljenih;
	int broj_poena;
public:
	Tim(const char ime[]) : broj_odigranih(0),broj_pobjeda(0),broj_nerijesenih(0),
	broj_poraza(0),broj_datih(0),broj_primljenih(0),broj_poena(0) {
		if(std::strlen(ime)>19) throw std::range_error("Predugacko ime tima");
		std::strcpy(ime_tima,ime);
	}
	void ObradiUtakmicu(int broj_datih,int broj_primljenih) {
		if(broj_datih<0 || broj_primljenih<0) throw std::range_error("Neispravan broj golova");
		Tim::broj_datih+=broj_datih;
		Tim::broj_primljenih+=broj_primljenih;
		broj_odigranih++;
		if(broj_datih==broj_primljenih) {
			broj_nerijesenih++;
			broj_poena++;
		}
		else if(broj_datih>broj_primljenih) {
			broj_pobjeda++;
			broj_poena+=3;
		}
		else if(broj_datih<broj_primljenih) broj_poraza++;
	}
	const char *DajImeTima() const {
		return ime_tima;
	}
	int DajBrojPoena() const {
		return broj_poena;	
	}
	int DajGolRazliku() const {
		return broj_datih-broj_primljenih;
	}
	void IspisiPodatke() const {
		std::cout<<std::left<<std::setw(20)<<DajImeTima()<<std::right<<std::setw(4)<<std::setw(4)<<broj_odigranih<<std::setw(4)<<broj_pobjeda<<std::setw(4)<<broj_nerijesenih
		<<std::setw(4)<<broj_poraza<<std::setw(4)<<broj_datih<<std::setw(4)<<broj_primljenih<<std::setw(4)<<DajBrojPoena()<<std::endl;
	}
};
int main ()
{
	Tim a("Zeljeznicar");
	Tim b("Sarajevo");
	Tim c("Barselona");
	a.ObradiUtakmicu(3,1);
	b.ObradiUtakmicu(3,2);
	c.ObradiUtakmicu(1,4);
	a.IspisiPodatke();
	std::cout<<std::endl;
	b.IspisiPodatke();
	std::cout<<std::endl;
	c.IspisiPodatke();
	std::cout<<std::endl;
	
	return 0;
}