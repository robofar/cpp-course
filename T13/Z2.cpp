#include <iostream>
#include <string>

class ApstraktniStudent {
private:
	std::string ime,prezime;
	int indeks,polozenih;
	double prosjek;
public:
	virtual ~ApstraktniStudent() {} //destruktor treba uvijek biti virual
	ApstraktniStudent(std::string i,std::string p,int ind) : ime(i),prezime(p),indeks(ind),polozenih(0),prosjek(5) {}
	std::string DajIme() const { return ime; }
	std::string DajPrezime() const { return prezime; }
	int DajBrojIndeksa() const { return indeks; }
	int DajBrojPolozenih() const { return polozenih; }
	double DajProsjek() const { return prosjek; }
	void RegistrirajIspit(int ocjena) {
		if(ocjena<5 || ocjena>10) throw std::domain_error("Neispravna ocjena");
		if(ocjena!=5) {
			double zbir_ocjena=prosjek*polozenih;
			polozenih++;
			zbir_ocjena+=ocjena;
			prosjek=zbir_ocjena/polozenih;
		}
	}
	void PonistiOcjene() {
		polozenih=0;
		prosjek=5;
	}
	virtual void IspisiPodatke() const = 0;
	virtual ApstraktniStudent* DajKopiju() const = 0;
};

class StudentBachelor : public ApstraktniStudent {
public:
	StudentBachelor(std::string i,std::string p,int ind) : ApstraktniStudent(i,p,ind) {} // KONSTRUKTORI SE NIKADA NE NASLJEDJUJU (iako je isti moramo ga ponovo definirati i samo pozvaati ovaj iz bazne klase)
	void IspisiPodatke() const override {
		std::cout<<"Student bachelor studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl;
		std::cout<<"ima prosjek "<<DajProsjek()<<"."<<std::endl;
	}
	ApstraktniStudent* DajKopiju() const override {
		return new StudentBachelor(*this);
	}
};

class StudentMaster : public ApstraktniStudent {
private:
	int godina_diplomiranja;
public:
	StudentMaster(std::string i,std::string p,int ind,int gd) : ApstraktniStudent(i,p,ind),godina_diplomiranja(gd) {}
	void IspisiPodatke() const override {
		std::cout<<"Student master studija "<<DajIme()<<" "<<DajPrezime()<<", sa brojem indeksa "<<DajBrojIndeksa()<<","<<std::endl;
		std::cout<<"zavrsio bachelor studij godine "<<godina_diplomiranja<<",ima prosjek "<<DajProsjek()<<"."<<std::endl;
	}
	ApstraktniStudent* DajKopiju() const override {
		return new StudentMaster(*this);
	}
};

int main ()
{
	StudentBachelor x("Faris","Hajdarpasic",18230);
	StudentMaster y("Edin","Dzeko",18400,1997);
	x.RegistrirajIspit(9);
	x.RegistrirajIspit(8);
	y.RegistrirajIspit(6);
	y.RegistrirajIspit(10);
	std::cout<<x.DajIme()<<x.DajPrezime()<<x.DajProsjek()<<x.DajBrojPolozenih()<<x.DajBrojIndeksa()<<std::endl;
	x.PonistiOcjene();
	std::cout<<x.DajProsjek();
	x.IspisiPodatke();
	y.IspisiPodatke();
	ApstraktniStudent* k1=x.DajKopiju();
	std::cout<<"Kopija su : "<<std::endl;
	k1->IspisiPodatke();
	delete k1;
	k1=y.DajKopiju(); // POLIMORFIZAM
	k1->IspisiPodatke();
	delete k1;
	return 0;
}