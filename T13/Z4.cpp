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

/* Surogatska klasa Student */
class Student {
	ApstraktniStudent* p_student; //ovaj surogat je ustvari pokazivac na neki objekt izveden iz bazne klase
public:
	/* Osnovni konstruktor */
	Student() : p_student(nullptr) {}
	/* Destruktor */
	~Student() {
		delete p_student;
	}
	/* Konstruktor sa jednim parametrom - da se objektu tipa Student mogu dodijeliti svi objekti izvedenih klasa iz bazne klase ApstraktniStudent */
	Student(const ApstraktniStudent &s) : p_student(s.DajKopiju()) {}
	/* Kopirajuci konstruktor */
	Student(const Student &s) {
		if(s.p_student==nullptr) p_student=nullptr;
		else p_student=s.p_student->DajKopiju();
	}
	/* Pomjerajuci konstruktor */
	Student(Student &&s) {
		p_student=s.p_student;
		s.p_student=nullptr;
	}
	/* Kopirajuci operator dodjele */
	Student& operator = (const Student &s) {
		ApstraktniStudent* pomocni=nullptr;
		if(s.p_student==nullptr) pomocni=nullptr;
		else pomocni=s.p_student->DajKopiju();
		
		delete p_student;
		p_student=pomocni;
		
		return *this;
	}
	/* Pomjerajuci operator dodjele */
	Student& operator = (Student &&s) {
		std::swap(p_student,s.p_student);
		return *this;
	}
	/* Surogat mora implementirati (ponovo) sve metode koje podrzavaju i tipovi koje oponasa */
	int DajBrojIndeksa() const { return p_student->DajBrojIndeksa(); }
	std::string DajIme() const { return p_student->DajIme(); }
	std::string DajPrezime() const { return p_student->DajPrezime(); }
	int DajBrojPolozenih() const { return p_student->DajBrojPolozenih(); }
	double DajProsjek() const { return p_student->DajProsjek(); }
	void RegistrirajIspit(int x) {
		p_student->RegistrirajIspit(x);
	}
	void PonistiOcjene() {
		p_student->PonistiOcjene();
	}
	void IspisiPodatke() {
		p_student->IspisiPodatke();
	}
	ApstraktniStudent* DajKopiju() const {
		return p_student->DajKopiju();
	}
};
int main ()
{
	Student a,b,c;
	StudentBachelor x("Faris","Hajdarpasic",18230);
	StudentBachelor y("Edin","Dzeko",18510);
	StudentMaster z("Nindja","Kornjaca",18543,1992);
	a=x;
	b=y;
	c=z;
	a.IspisiPodatke();
	std::cout<<std::endl;
	b.IspisiPodatke();
	std::cout<<std::endl;
	c.IspisiPodatke();
	std::cout<<std::endl;
	a.RegistrirajIspit(10);
	a.RegistrirajIspit(9);
	a.RegistrirajIspit(8);
	b.RegistrirajIspit(7);
	b.RegistrirajIspit(8);
	b.RegistrirajIspit(6);
	c.RegistrirajIspit(9);
	c.RegistrirajIspit(6);
	c.RegistrirajIspit(6);
	std::cout<<a.DajIme()<<" "<<a.DajPrezime()<<" "<<a.DajBrojIndeksa()<<" "<<a.DajBrojPolozenih()<<" "<<a.DajProsjek();
	std::cout<<std::endl;
	std::cout<<"Sad dodjele i to: ";
	std::cout<<std::endl;
	b=a;
	c=a; //c je  Mastera a sad pokazuje na Bachelora
	std::cout<<"Provjera po prosjeku da je sve isto: ";
	std::cout<<std::endl;
	std::cout<<a.DajProsjek()<<" "<<b.DajProsjek()<<" "<<c.DajProsjek();
	std::cout<<std::endl;
	std::cout<<"b je bachelor: ";
	std::cout<<std::endl;
	b.IspisiPodatke();
	std::cout<<std::endl;
	std::cout<<"b je master: ";
	b=z;
	std::cout<<std::endl;
	b.IspisiPodatke();
	return 0;
}