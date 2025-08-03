#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <cstring>
#include <iomanip>
#include <algorithm>

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
	int broj_timova;
	const int max_br_timova;
	Tim** timovi=nullptr;
public:
	explicit Liga(int velicina_lige) : max_br_timova(velicina_lige){ //OBICNI KONSTRUKTOR
		broj_timova=0;
		timovi=new Tim*[max_br_timova]{}; //na nullptr ih stavljamo
	}
	/* Kad se {} dodjeljuje tada je automatski max_br_timova i broj_timova jedno te isto */
	explicit Liga(std::initializer_list<Tim> lista_timova) : max_br_timova(lista_timova.size()) {
		broj_timova=lista_timova.size();
		timovi=new Tim*[lista_timova.size()]{};
		int i=0;
		for(auto it=lista_timova.begin();it!=lista_timova.end();it++) {
			timovi[i]=new Tim(*it);
			i++;
		}
	}
	~Liga() {
		for(int i=0;i<broj_timova;i++) delete timovi[i];
		delete[] timovi;
	}
	Liga(const Liga &l) : max_br_timova(l.max_br_timova) {
		if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
		broj_timova=l.broj_timova;
		timovi=new Tim*[broj_timova]{};
		try {
			for(int i=0;i<broj_timova;i++) {
				timovi[i]=new Tim(*l.timovi[i]);
			}
		}
		catch(...) {
			for(int i=0;i<broj_timova;i++) delete timovi[i];
			delete[] timovi;
			throw;
		}
	}
	Liga(Liga &&l) : max_br_timova(l.max_br_timova) {
		if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
		broj_timova=l.broj_timova;
		timovi=l.timovi;
		l.timovi=nullptr;
		l.broj_timova=0; //da se ne brisu elementi kod poziva destruktora
	}
	Liga &operator = (const Liga &l) {
		if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
		if(l.broj_timova>broj_timova) {
			try {
				for(int i=broj_timova;i<l.broj_timova;i++) timovi[i]=new Tim(*l.timovi[i]);
			}
			catch(...) {
				for(int i=broj_timova;i<l.broj_timova;i++) {
					delete timovi[i];
					timovi[i]=nullptr;
				}
			//delete[] timovi; -> ne treba
			throw;
			}
		}
		else {
			for(int i=l.broj_timova;i<broj_timova;i++) {
				delete timovi[i];
				timovi[i]=nullptr;
			}
		}
		broj_timova=l.broj_timova; //promjenimo ga sada (gore smo preduzeli mjere ako je ovaj novi ima vise ili manje timova)
		for(int i=0;i<broj_timova;i++) *timovi[i]=*l.timovi[i];
		return *this;
	}
	Liga &operator = (Liga &&l) {
		if(max_br_timova!=l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
		std::swap(broj_timova,l.broj_timova);
		std::swap(timovi,l.timovi);
		return *this;
	}
	void DodajNoviTim(const char ime_tima[]) {
		if(std::strlen(ime_tima)>19) throw std::range_error("Predugacko ime tima");
		if(broj_timova==max_br_timova) throw std::range_error("Liga popunjena");
		for(int i=0;i<broj_timova;i++) {
			if(!std::strcmp(timovi[i]->DajImeTima(),ime_tima)) throw std::logic_error("Tim vec postoji");
		}
		timovi[broj_timova]=new Tim(ime_tima);
		broj_timova++;
	}
	void RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2);
	void IspisiTabelu() {
		std::sort(timovi,timovi+broj_timova,[](Tim *t1,Tim *t2)->bool {
			if(t1->DajBrojPoena() > t2->DajBrojPoena()) return true;
			else if(t1->DajBrojPoena() < t2->DajBrojPoena()) return false;
			else if(t1->DajGolRazliku() > t2->DajGolRazliku()) return true;
			else if(t1->DajGolRazliku() < t2->DajGolRazliku()) return false;
			else if(std::strcmp(t1->DajImeTima(),t2->DajImeTima())<0) return true;
			return false;
		});
		for(int i=0;i<broj_timova;i++) timovi[i]->IspisiPodatke();
	}
};

void Liga::RegistrirajUtakmicu(const char tim1[],const char tim2[],int rezultat_1,int rezultat_2) {
	if(rezultat_1<0 || rezultat_2<0) throw std::range_error("Neispravan broj golova");
	bool a1=false;
	bool a2=false;
	int indeks1;
	int indeks2;
	for(int i=0;i<broj_timova;i++) {
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
	Liga BHT(6);
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

//z4