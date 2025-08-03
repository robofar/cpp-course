#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <vector>

//using std::shared_ptr<Tim> Pametni;
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

/* Nova klasa */
class Liga {
	std::vector<std::shared_ptr<Tim>> timovi;
public:
/* Problem je sto radi i bez ovog obicnog konstruktora(jer valjda vektor ima svoj konstruktor podrazumijevani)
(a radi i sa ovom mojom implementacijom konstruktora) pa zbog toga ne znam je li ona dobra ... */
	explicit Liga() { //OBICNI KONSTRUKTOR
		timovi.resize(0);
	}
	/* Kad se {} dodjeljuje tada je automatski max_br_timova i broj_timova jedno te isto */
	explicit Liga(std::initializer_list<Tim> lista_timova) {
		int i=0;
		timovi.resize(lista_timova.size()); //automatski su na nullptr
		for(auto it=lista_timova.begin();it!=lista_timova.end();it++) {
			timovi[i]=std::make_shared<Tim>(*it); //ili sam mogao sa push_back al eto(tako sam dole uradio)
			i++;
		}
	}
	//destruktor nam uopce ne treba(pogledaj predavanje kad se opisuje vezano za koristenje vektora kao ovdje)
	Liga(const Liga &l) : timovi(l.timovi.size()) {
		for(int i=0;i<timovi.size();i++) {
			timovi[i]=std::make_shared<Tim>(*l.timovi[i]);
		}
	}
	/* Pomjerajui konstruktor i pomjerajuci operator dodjele JE VEOMA LAKO NAPISATI,
	SOBZIROM DA VEKTOR PODRZAVA move SEMANTIKU */
	Liga(Liga &&l) : timovi(std::move(l.timovi)) {} //prazno tijelo konstuktora
	
	Liga &operator = (const Liga &l) { //done
		timovi.resize(l.timovi.size());
		for(int i=0;i<timovi.size();i++)
			timovi[i]=std::make_shared<Tim>(*l.timovi[i]);
		return *this;
	}
	Liga &operator = (Liga &&l) {
		timovi=std::move(l.timovi);
		return *this;
	}
	void DodajNoviTim(const char ime_tima[]) {
		if(std::strlen(ime_tima)>19) throw std::range_error("Predugacko ime tima");
	//	if(broj_timova==max_br_timova) throw std::range_error("Liga popunjena");
		for(int i=0;i<timovi.size();i++) {
			if(!std::strcmp(timovi[i]->DajImeTima(),ime_tima)) throw std::logic_error("Tim vec postoji");
		}
		timovi.push_back(std::make_shared<Tim>(ime_tima));
	}
	void RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2);
	void IspisiTabelu() {
		std::sort(timovi.begin(),timovi.end(),[](std::shared_ptr<Tim> t1,std::shared_ptr<Tim> t2)->bool {
			if(t1->DajBrojPoena() > t2->DajBrojPoena()) return true;
			else if(t1->DajBrojPoena() < t2->DajBrojPoena()) return false;
			else if(t1->DajGolRazliku() > t2->DajGolRazliku()) return true;
			else if(t1->DajGolRazliku() < t2->DajGolRazliku()) return false;
			else if(std::strcmp(t1->DajImeTima(),t2->DajImeTima())<0) return true;
			return false;
		});
		for(int i=0;i<timovi.size();i++) timovi[i]->IspisiPodatke();
	}
};

void Liga::RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2) {
	if(rezultat_1<0 || rezultat_2<0) throw std::range_error("Neispravan broj golova");
	bool a1=false;
	bool a2=false;
	int indeks1;
	int indeks2;
	for(int i=0;i<timovi.size();i++) {
		if(!std::strcmp(timovi[i]->DajImeTima(),tim1)) {
			indeks1=i;
			a1=true;
			if(a2) break;
		}
		if(!std::strcmp(timovi[i]->DajImeTima(),tim2)) {
			indeks2=i;
			a2=true;
			if(a1) break;
		}
	}
	if(!a1 || !a2) throw std::logic_error("Tim nije nadjen");
	timovi[indeks1]->ObradiUtakmicu(rezultat_1,rezultat_2);
	timovi[indeks2]->ObradiUtakmicu(rezultat_2,rezultat_1);
}
int main ()
{
	Liga BHT;
	BHT.DodajNoviTim("Borac");
	BHT.DodajNoviTim("Celik");
	BHT.DodajNoviTim("Jedinstvo");
	BHT.DodajNoviTim("Sarajevo");
	BHT.DodajNoviTim("Zeljeznicar");
	BHT.DodajNoviTim("Zrinjski");
	for(;;) {
		BHT.IspisiTabelu();
		char prvi[20],drugi[20];
		std::cout<<"Unesite ime prvog tima (ENTER za kraj): ";
		std::cin.getline(prvi,sizeof(prvi));
		if(std::strlen(prvi)==0) break;
		std::cout<<"Unesite ime drugog tima: ";
		std::cin.getline(drugi,sizeof(drugi));
		int p,d;
		std::cout<<"Unesite broj postignutih golova za oba tima: ";
		std::cin>>p>>d;
		std::cin.ignore(1000,'\n');
		BHT.RegistrirajUtakmicu(prvi,drugi,p,d);
	}
}

// z5