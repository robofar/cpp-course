#include <type_traits>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <new>
#include <string>
#include <fstream>
#include <vector>

template <typename TipEl>
class Matrica
{
	int br_redova, br_kolona;
	TipEl **elementi;
	char ime_matrice;
	static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
	static void DealocirajMemoriju(TipEl **elementi, int br_redova);
	void KopirajElemente(TipEl **elementi);
public:
	Matrica(int br_redova, int br_kolona, char ime = 0);
	Matrica(const Matrica &m);
	Matrica(Matrica &&m);
	~Matrica()
	{
		DealocirajMemoriju(elementi, br_redova);
	}
	Matrica &operator =(const Matrica &m);
	Matrica &operator =(Matrica &&m);
	/* SAMO ZA FRIEND FUNKCIJE OPET TREBA DEKLARISATI TEMPLATE - DRUGO IME PARAMETARA TEMPLATE-A OFC!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	/* ZA OPERATORE KOJI SU PUBLIC METHOD NE TREBA !!!!!!!!!!!!!!!!!!!! */
	/* OPERATORI *//////////////////////////////////////////////////////////////////////////////
	/* Friend funkcije - one koje 'nemaju smisla' da se definisu nad objektom, nego nad neka dva objekta */
	template<typename Tip>
	friend Matrica<Tip> operator *(const Matrica<Tip> &m1,const Matrica<Tip> &m2); //friend
	template<typename Tip>
	friend Matrica<Tip> operator *(const Matrica<Tip> &m1,int d); //friend
	template<typename Tip>
	friend Matrica<Tip> operator *(int d,const Matrica<Tip> &m); //friend
	template<typename Tip>
	friend Matrica<Tip> operator -(const Matrica<Tip> &m1,const Matrica<Tip> &m2);
	template<typename Tip>
	friend Matrica<Tip> operator +(const Matrica<Tip> &m1,const Matrica<Tip> &m2);
	template<typename Tip>
	friend Matrica<Tip> operator -(Matrica<Tip> m); //npr m=-m;
	// >> i << ne smiju biti funkcije clanice
	template<typename Tip>
	friend std::ostream& operator <<(std::ostream &tok,const Matrica<Tip> &m);
	template<typename Tip>
	friend std::istream& operator >>(std::istream &tok,Matrica<Tip> &m);
	/////////////////////////////////////////////////////////////////////////////////////
	/* Funkcije clanice - one operacije koje imaju smisla da se definisu nad nekim objektom */
	Matrica& operator +=(const Matrica &m);
	Matrica& operator -=(Matrica m); 
	Matrica& operator *=(const Matrica &m);
	Matrica& operator *=(TipEl d); // 
	operator std::string() const;
	TipEl* operator [](int indeks) const {
		return elementi[indeks];
	}
	TipEl* operator[](int indeks) {
		return elementi[indeks];
	}
	TipEl& operator()(int i,int j) const {
		if(i<1 || j<1 || i>br_redova || j>br_kolona) throw std::range_error("Neispravan indeks");	
		return elementi[i-1][j-1];
	}
	TipEl& operator()(int i,int j) {
		if(i<1 || j<1 || i>br_redova || j>br_kolona) throw std::range_error("Neispravan indeks");
		return elementi[i-1][j-1];
	}
	void SacuvajUTekstualnuDatoteku(std::string d);
	void SacuvajUBinarnuDatoteku(std::string d);
	void ObnoviIzTekstualneDatoteke(std::string d);
	void ObnoviIzBinarneDatoteke(std::string d);
	Matrica(std::string ime_datoteke,bool odakle) {
	    elementi=nullptr;
	    br_redova=0;
	    if(!odakle) ObnoviIzTekstualneDatoteke(ime_datoteke);
	    else ObnoviIzBinarneDatoteke(ime_datoteke);
	}
};

template <typename TipEl>
void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(std::string d) {
    std::ofstream izlazni_tok(d);
    for(int i=0;i<br_redova;i++) {
        for(int j=0;j<br_kolona;j++) {
            if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
            if(j!=br_kolona-1) izlazni_tok << elementi[i][j] << ",";
            else izlazni_tok << elementi[i][j];
        }
        izlazni_tok<<std::endl; //ovo je ko flush (taman usput dodje i novi red i praznjenje spreminka)
    }
    if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
}

template <typename TipEl>
void Matrica<TipEl>::ObnoviIzTekstualneDatoteke(std::string d) {
	std::ifstream ulazni_tok(d);
	if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
    int red=0,kol=0;
    char razdvojeno='.';
    while(razdvojeno!='\n') {
    	TipEl pom;
    	kol++;
    	ulazni_tok>>pom;
    	razdvojeno=ulazni_tok.get();
    	if(razdvojeno!=',' && razdvojeno!='\n') {
    		throw std::logic_error("Datoteka sadrzi besmislene podatke");
    	}
    	if(!ulazni_tok && !ulazni_tok.eof()) {
    		throw std::logic_error("Datoteka sadrzi besmislene podatke");
    	}
    }
    red++;
    while(ulazni_tok && !ulazni_tok.eof()) {
    	char a;
    	TipEl pom;
    	for(int j=0;j<kol-1;j++) {
    		ulazni_tok>>pom>>a;
    		if(a!=',') {
    			throw std::logic_error("Datoteka sadrzi besmislene podatke");
    		}
    		/* Ako je tok dosao u neispravno stanje samo zato sto je kraj datoteke - nista ne radi */
    		if(!ulazni_tok && !ulazni_tok.eof()) {
    			throw std::logic_error("Datoteka sadrzi besmislene podatke");
    		}
    	}
    	/* Provjera za zadnji elementi - mora biti \n iza zadnjeg - ako nije to znaci da u ovoj koloni ima vise elemenata */
    	ulazni_tok>>pom;
    	a=ulazni_tok.get(); //mora get jer >> ce preskocit \n (preskace sve bjeline)
    	if(!ulazni_tok) { //dosli do kraja -> pokusaj citanja iza kraja dovodi tok u neispravno stanje
    		ulazni_tok.clear();
    		red++;
    		break;
    	}
    	if(a!='\n' && !ulazni_tok.eof()) {
    		throw std::logic_error("Datoteka sadrzi besmislene podatke");
    	}
    	if(!ulazni_tok && !ulazni_tok.eof()) {
    		throw std::logic_error("Datoteka sadrzi besmislene podatke");
    	}
    	if(ulazni_tok.eof()) ulazni_tok.clear();
    	red++; 
    }
    /* Sada sam izbrojao broj redova i kolona - kreiraj matricu */
    /* Prvo izbrisi staru - ne na pocetku nego sada kad znamo da se u fajlu nalaze normalne stvari */
    if(elementi!=nullptr) {
    	DealocirajMemoriju(elementi,br_redova);
    }
    ulazni_tok.seekg(0,std::ios::beg);
    br_redova=red;
    br_kolona=kol;
    elementi=new TipEl*[red]{};
    for(int i=0;i<red;i++) {
    	elementi[i]=new TipEl[kol]{};
    }
    /* Posto si izvrsio sve provjere, pa znas da ima toliko redova i toliko kolona */
	for(int i=0;i<red;i++) {
		char y;
		TipEl x;
		for(int j=0;j<kol;j++) {
			ulazni_tok>>x;
			y=ulazni_tok.get(); //da ne cita zadnji element iza datoteke (jer zadni red zadji elment je samo broj, nema \n)
			if(!ulazni_tok) ulazni_tok.clear();
			elementi[i][j]=x;
		}
	}
}

template <typename TipEl>
void Matrica<TipEl>::SacuvajUBinarnuDatoteku(std::string d) {
    std::ofstream izlazni_tok(d,std::ios::binary);
   izlazni_tok.write(reinterpret_cast<char*>(this),sizeof *this);
   for(int i=0;i<br_redova;i++) {
   		for(int j=0;j<br_kolona;j++) {
   			izlazni_tok.write(reinterpret_cast<char*>(&elementi[i][j]),sizeof(TipEl));
   		}
   }
    if(!izlazni_tok) throw std::logic_error("Problemi sa upisom u datoteku");
} 

template <typename TipEl>
void Matrica<TipEl>::ObnoviIzBinarneDatoteke(std::string d) {
    std::ifstream ulazni_tok(d,std::ios::binary);
    if(!ulazni_tok) throw std::logic_error("Trazena datoteka ne postoji");
    Matrica<TipEl> kopija(*this); //ako nesta ne uspije
    DealocirajMemoriju(elementi,br_redova);
    ulazni_tok.read(reinterpret_cast<char*>(this),sizeof *this);
    elementi=new TipEl*[br_redova]{};
    for(int i=0;i<br_redova;i++) {
    	elementi[i]=new TipEl[br_kolona];
    	for(int j=0;j<br_kolona;j++) {
    		ulazni_tok.read(reinterpret_cast<char*>(&elementi[i][j]),sizeof(TipEl));
    	}
    }
    if(!ulazni_tok) {
    	*this=kopija;
    	DealocirajMemoriju(kopija.elementi,kopija.br_redova);
    	kopija.br_redova=0;
    	kopija.br_kolona=0;
    }
} 



template <typename TipEl>
TipEl ** Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona)
{
	TipEl **elementi = new TipEl*[br_redova] {};
	try {
		for(int i = 0; i < br_redova; i++) elementi[i] = new TipEl[br_kolona];
	} catch(...) {
		DealocirajMemoriju(elementi, br_redova);
		throw;
	}
	return elementi;
}
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova)
{
	for(int i = 0; i < br_redova; i++) delete[] elementi[i];
	delete[] elementi;
}
template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime) :
	br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
	elementi(AlocirajMemoriju(br_redova, br_kolona)) {}
template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi)
{
	for(int i = 0; i < br_redova; i++)
		for(int j = 0; j < br_kolona; j++)
			Matrica::elementi[i][j] = elementi[i][j];
}
template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), ime_matrice(m.ime_matrice),
	elementi(AlocirajMemoriju(m.br_redova, m.br_kolona))
{
	KopirajElemente(m.elementi);
}
template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m) : br_redova(m.br_redova),
	br_kolona(m.br_kolona), elementi(m.elementi), ime_matrice(m.ime_matrice)
{
	m.br_redova = 0;
	m.elementi = nullptr;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(const Matrica<TipEl> &m)
{
	if(br_redova < m.br_redova || br_kolona < m.br_kolona) {
		TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
		DealocirajMemoriju(elementi, br_redova);
		elementi = novi_prostor;
	} else if(br_redova > m.br_redova)
		for(int i = m.br_redova; i < br_redova; i++) delete elementi[i];
	br_redova = m.br_redova;
	br_kolona = m.br_kolona;
	ime_matrice = m.ime_matrice;
	KopirajElemente(m.elementi);
	return *this;
}



/* O P E R A T O R I */
template<typename TipEl>
Matrica<TipEl>::operator std::string() const {
	std::string s;
	s+='{';
	for(int i=0;i<br_redova;i++) {
		s+='{';
		for(int j=0;j<br_kolona;j++) {
			s+=std::to_string(int(elementi[i][j])); //mora ovo int(...) jer je TipEl double pa ce bit umjesto 1 -> 1.000000
			if(j!=br_kolona-1) s+=',';
		}
		if(i!=br_redova-1) s+="},";
		else s+="}";
	}
	s+='}';
	
	return s;
}
template<typename TipEl>
std::ostream& operator <<(std::ostream& tok,const Matrica<TipEl> &m) {
	int x=tok.width(); //daje sirinu
	for(int i=0;i<m.br_redova;i++) {
		for(int j=0;j<m.br_kolona;j++) {
			tok<<std::setw(x)<<m.elementi[i][j];
		}
		tok<<std::endl;
	}
	return tok;
}

template<typename TipEl>
std::istream& operator >>(std::istream& tok,Matrica<TipEl> &m) {
	for(int i=0;i<m.br_redova;i++) {
		for(int j=0;j<m.br_kolona;j++) {
			std::cout<<m.ime_matrice<<"("<<i+1<<","<<j+1<<") = ";
			tok>>m.elementi[i][j];
		}
	}
	return tok;
}
template<typename TipEl>
Matrica<TipEl> operator *(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2) {	// DONE
	if(m1.br_kolona!=m2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
	Matrica<TipEl> rez(m1.br_redova,m2.br_kolona);
	for(int i=0;i<m1.br_redova;i++) {
		for(int j=0;j<m2.br_kolona;j++) {
			rez.elementi[i][j]=0;
			for(int k=0;k<m1.br_kolona;k++) rez.elementi[i][j] += m1.elementi[i][k]*m2.elementi[k][j];
		}
	}
	return rez;
}

template<typename TipEl>
Matrica<TipEl> operator *(const Matrica<TipEl> &m1,int d) {  //DONE
	Matrica<TipEl> rez=m1;
	for(int i=0;i<m1.br_redova;i++) {
		for(int j=0;j<m1.br_kolona;j++) rez.elementi[i][j]=m1.elementi[i][j]*d;
	}
	return rez;
}

template<typename TipEl> //DONE
Matrica<TipEl> operator *(int d,const Matrica<TipEl> &m1) { 
	return m1*d; 
}

/* Minus moze preko plusa -> jedna matrica obicna kopija, definisem minus koji mjenja samo sve za *(-1) i pozovem m1+m2 */
template<typename TipEl>
Matrica<TipEl> operator -(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2) { //done
	if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<TipEl> rez(m1.br_redova,m1.br_kolona);
	for(int i=0;i<m1.br_redova;i++) {
		for(int j=0;j<m1.br_kolona;j++) {
			rez.elementi[i][j]=m1.elementi[i][j]-m2.elementi[i][j];
		}
	}
	return rez;
}

template<typename TipEl>
Matrica<TipEl> operator +(const Matrica<TipEl> &m1,const Matrica<TipEl> &m2) {
	if(m1.br_redova!=m2.br_redova || m1.br_kolona!=m2.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
	Matrica<TipEl> rez(m1.br_redova,m1.br_kolona);
	for(int i=0;i<m1.br_redova;i++) {
		for(int j=0;j<m1.br_kolona;j++) {
			rez.elementi[i][j]=m1.elementi[i][j]+m2.elementi[i][j];
		}
	}
	return rez;
}

template<typename TipEl>
Matrica<TipEl> operator -(Matrica<TipEl> m) {
	for(int i=0;i<m.br_redova;i++) {
		for(int j=0;j<m.br_kolona;j++) m.elementi[i][j]*=-1;
	}
	return m;
}

template<typename TipEl>
Matrica<TipEl>& Matrica<TipEl>::operator +=(const Matrica<TipEl> &m) {
	if(br_redova!=m.br_redova || br_kolona!=m.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
	for(int i=0;i<br_redova;i++) {
		for(int j=0;j<br_kolona;j++) elementi[i][j]+=m.elementi[i][j];
	}
	return *this;
}

template<typename TipEl>
Matrica<TipEl>& Matrica<TipEl>::operator -=(Matrica<TipEl> m) {
	if(br_redova!=m.br_redova || br_kolona!=m.br_kolona) throw std::domain_error("Matrice nemaju jednake dimenzije!");
	m=-m;
	*this+=m;
	return *this;
} 

template<typename TipEl>
Matrica<TipEl>& Matrica<TipEl>::operator *=(const Matrica<TipEl> &m) {
	if(br_kolona!=m.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
	Matrica<TipEl> a(br_redova,m.br_kolona);
	for(int i=0;i<br_redova;i++) {
		for(int j=0;j<m.br_kolona;j++) {
			a.elementi[i][j]=0;
			for(int k=0;k<br_kolona;k++) a.elementi[i][j] += elementi[i][k]*m.elementi[k][j]; 
		}
	}
	*this=a;
	return *this;
}

template<typename TipEl>
Matrica<TipEl>& Matrica<TipEl>::operator *=(TipEl d) {
	for(int i=0;i<br_redova;i++) {
		for(int j=0;j<br_kolona;j++) elementi[i][j]*=d;
	}
	return *this;
}

/* K R A J			O P E R A T O R A */



template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator =(Matrica<TipEl> &&m)
{
	std::swap(br_redova, m.br_redova);
	std::swap(br_kolona, m.br_kolona);
	std::swap(ime_matrice, m.ime_matrice);
	std::swap(elementi, m.elementi);
	return *this;
}



int main ()
{
try {
	Matrica<int> m0{3,3};
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			m0[i][j]=i+j;
	m0.SacuvajUBinarnuDatoteku("prva.DAT");
	Matrica<int> m1("prva.DAT",true);
	std::cout<<std::setw(6)<<m1;
}
catch(std::logic_error x) {
	std::cout<<"Izuzetak: "<<x.what();
	std::cout<<std::endl;
}
std::cout<<std::endl;

try {
	Matrica<double> m1("druga.TXT",false);
	std::cout<<std::setw(6)<<m1;
	std::cout<<std::endl;
}
catch(std::logic_error x) {
	std::cout<<"Izuzetak: "<<x.what();
	std::cout<<std::endl;
}
	return 0;
}