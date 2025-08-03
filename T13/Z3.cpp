#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

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

class Fakultet {
private:
	std::vector<ApstraktniStudent*> v;
public:
	Fakultet() = default;
	~Fakultet() {
		for(int i=0;i<v.size();i++) delete v.at(i);
	}
	Fakultet(const Fakultet &f) {
		v.resize(f.v.size());
		for(int i=0;i<v.size();i++) v.at(i)=f.v.at(i)->DajKopiju();
	}
	Fakultet(Fakultet &&f) {
	//	v=f.v;
	//	f.v.resize(0);  //da ne bi destruktor brisao ovo jer bi obrisao i sam vektor jer se dodjeljuje pa je isti sadrzaj
	std::swap(v,f.v); //a moze i ovo gore
	}
	Fakultet& operator = (const Fakultet &f) {
		if(&f!=this) {
			for(int i=0;i<v.size();i++) {
				delete v.at(i);
				v.at(i)=nullptr;
			} 
			v.resize(f.v.size());
			for(int i=0;i<v.size();i++) {
				v.at(i)=f.v.at(i)->DajKopiju();
			}
		}
		return *this;
	}
/*	Fakultet& operator = (Fakultet &&f) {
		for(int i=0;i<v.size();i++) {
			delete v.at(i);
			v.at(i)=nullptr;
		}
		v=std::move(f.v); //mora zbog autotesta ? (msm ne moze swap)
		return *this;
	} */
	Fakultet& operator = (Fakultet &&f) {
		std::swap(v,f.v); //v je sad vektor od f, a f.v od *this, pa dole zato v resizam a ne f.v
		/* Moras deletat stari sadrzaj jer je vektor pokazivaca */
		for(int i=0;i<f.v.size();i++) {
			delete f.v.at(i);
		}
		f.v.resize(0);
		return *this;
	} 
	void UpisiStudenta(std::string i,std::string p,int ind);
	void UpisiStudenta(std::string i,std::string p,int ind,int gd);
	void ObrisiStudenta(int ind);
	void IspisiSveStudente() const;
	ApstraktniStudent& operator [](int ind) {
		for(int i=0;i<v.size();i++) {
			if(v.at(i)->DajBrojIndeksa()==ind) {
				return *v.at(i);
			}
		}
		throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
	}
	ApstraktniStudent& operator [](int ind) const {
		for(int i=0;i<v.size();i++) {
			if(v.at(i)->DajBrojIndeksa()==ind) {
				return *v.at(i);
			}
		}
		throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
	}
};

void Fakultet::UpisiStudenta(std::string i,std::string p,int ind) {
	for(int i=0;i<v.size();i++) {
		if(v.at(i)->DajBrojIndeksa()==ind) throw std::logic_error("Student sa zadanim brojem indeksa vec postoji");
	}
	try {
		v.resize(v.size()+1);
		v.at(v.size()-1) = new StudentBachelor(i,p,ind); //posto znam da je bachelor
	}
	catch(...) {
		throw;
	}
}

void Fakultet::UpisiStudenta(std::string i,std::string p,int ind,int gd) {
	for(int i=0;i<v.size();i++) {
		if(v.at(i)->DajBrojIndeksa()==ind) throw std::logic_error("Student sa zadanim brojem indekksa vec postoji");
	}
	try {
		v.resize(v.size()+1);
		v.at(v.size()-1) = new StudentMaster(i,p,ind,gd);
	}
	catch(...) {
		throw;
	}
}

void Fakultet::ObrisiStudenta(int ind) {
	bool postoji=false;
	for(int i=0;i<v.size();i++) {
		if(v.at(i)->DajBrojIndeksa()==ind) {
			postoji=true;
			break;
		}
	}
	if(!postoji) throw std::logic_error("Student sa zadanim brojem indeksa ne postoji");
	for(int i=0;i<v.size();i++) {
		if(v.at(i)->DajBrojIndeksa()==ind) {
			delete v.at(i);
			v.at(i)=nullptr;
			v.erase(v.begin()+i);
		}
	}
}

void Fakultet::IspisiSveStudente() const{
	std::vector<ApstraktniStudent*> q=v; //treba mi pomocni jer ova metoda mora biti inspektor pa ne smijem sortirati orginalni vektor
	std::sort(q.begin(),q.end(),[](ApstraktniStudent* a,ApstraktniStudent* b)->bool {
		if(a->DajProsjek()>b->DajProsjek()) return true;
		else if(a->DajProsjek()==b->DajProsjek()) {
			return a->DajBrojIndeksa()<b->DajBrojIndeksa();
		}
		return false;
	});
	for(int i=0;i<q.size();i++) q.at(i)->IspisiPodatke();
} 

int main ()
{
	Fakultet r;
	r.UpisiStudenta("Ibrahim","Sehic",10000,1987);
	r.UpisiStudenta("Toni","Sunjic",11000);
	r.UpisiStudenta("Ervin","Zukanovic",10500);
	r.UpisiStudenta("Ermin","Bicakcic",18555);
	r.UpisiStudenta("Seo","Kolasinac",18539,1999);
	r.UpisiStudenta("Miralem","Pjanic",88554);
	r.UpisiStudenta("Edin","Dzeko",18432,1996);
	r.UpisiStudenta("Mensur","Mujdza",18521);
	r.IspisiSveStudente();
	std::cout<<std::endl;
	r.ObrisiStudenta(10500);
	r.ObrisiStudenta(18539);
	r.IspisiSveStudente();
	std::cout<<std::endl;
	//////////////////////////////
	r[10000].IspisiPodatke();
	std::cout<<std::endl;
	r[18432].IspisiPodatke();
	std::cout<<std::endl;
	///////////////////////////////
	//r[10000]=r[18432]; -> dodijeio bi sei br indeksa pa bi pri ispisu ovaj indeks bio nevalidan
	Fakultet etf(r);
	etf.IspisiSveStudente();
	return 0;
}