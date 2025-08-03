#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iterator>

class Berza {
    std::vector<int> v;
    int min,max;
public:
    explicit Berza(int high) {
        if(high<0) throw std::range_error("Ilegalne granicne cijene");
        min=0;
        max=high;
    }
    Berza(int low,int high) {
        if(low<0 || high<0) throw std::range_error("Ilegalne granicne cijene");
        min=low; max=high;
    }
    void RegistrirajCijenu(int cijena);
    int DajBrojRegistriranihCijena() const { return v.size(); }
    void BrisiSve();
    int DajMinimalnuCijenu() const;
    int DajMaksimalnuCijenu() const;
    int DajBrojCijenaVecihOd(int x) const;
    void Ispisi() const;
    /* Operatori - funkcije clanice */
    int operator [](int indeks) const;
    Berza& operator ++(); //++a
    Berza operator ++(int); //a++
    Berza& operator --(); //--a
    Berza operator --(int); //a--
    bool operator !() const;
    Berza operator -() const;
    Berza& operator +=(const Berza &q);
    Berza& operator -=(const Berza &q);
    Berza& operator +=(int x);
    Berza& operator -=(int x);
    /* Operatori - friend funkcija */
    friend Berza operator +(Berza a,Berza b);
    friend Berza operator +(Berza a,int x);
    friend Berza operator +(int x,Berza a);
    friend Berza operator -(Berza a,Berza b);
    friend Berza operator -(Berza a,int x);
    friend Berza operator -(int x,Berza a);
    friend bool operator ==(const Berza &a,const Berza &b);
    friend bool operator !=(const Berza &a,const Berza &b);
};

void Berza::RegistrirajCijenu(int cijena) {
    if(cijena<min || cijena>max) throw std::range_error("Ilegalna cijena");
    v.push_back(cijena);
}
void Berza::BrisiSve() {
    v.resize(0);
}
int Berza::DajMinimalnuCijenu() const {
    if(v.size()==0) throw std::range_error("Nema registriranih cijena");
    auto it=std::min_element(v.begin(),v.end());
    return *it;
}
int Berza::DajMaksimalnuCijenu() const {
    if(v.size()==0) throw std::range_error("Nema registriranih cijena");
    auto it=std::max_element(v.begin(),v.end());
    return *it;
}
int Berza::DajBrojCijenaVecihOd(int x) const {
    if(v.size()==0) throw std::range_error("Nema registriranih cijena");
    int broj=std::count_if(v.begin(),v.end(),std::bind(std::greater<int>(),std::placeholders::_1,x));
    return broj;
}
void Berza::Ispisi() const {
    std::vector<double> pomocna;
    for(int i=0;i<v.size();i++) {
        pomocna.push_back(v.at(i));
    }
    std::sort(pomocna.begin(),pomocna.end(),std::greater<double>());
    std::ostream_iterator<double> ekran_direktno(std::cout<<std::fixed<<std::setprecision(2),"\n"); //ovako je u cpp-reference (nije mi bas logicno ovo al eto)
    std::transform(pomocna.begin(),pomocna.end(),ekran_direktno,std::bind(std::divides<double>(),std::placeholders::_1,100.00));
}
int Berza::operator [](int indeks) const {
    if(indeks<1 || indeks>v.size()) throw std::range_error("Neispravan indeks");
    return v.at(indeks-1);
}
Berza& Berza::operator ++() {   //verzija ++a
/* Ne mozes placeholder sabirati sa 100 pa moras oduzet max sa 100 */
    if(std::count_if(v.begin(),v.end(),std::bind(std::greater<int>(),std::placeholders::_1,max-100))) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    std::transform(v.begin(),v.end(),v.begin(),std::bind(std::plus<int>(),std::placeholders::_1,100));
    return *this;
}
Berza Berza::operator ++(int) { //a++
    if(std::count_if(v.begin(),v.end(),std::bind(std::greater<int>(),std::placeholders::_1,max-100))) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    Berza pomocna=*this;
    std::transform(v.begin(),v.end(),v.begin(),std::bind(std::plus<int>(),std::placeholders::_1,100));
    return pomocna;
}
Berza& Berza::operator --() {
    if(std::count_if(v.begin(),v.end(),std::bind(std::less<int>(),std::placeholders::_1,min+100))) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    std::transform(v.begin(),v.end(),v.begin(),std::bind(std::minus<int>(),std::placeholders::_1,100));
    return *this;
}
Berza Berza::operator --(int) {
    if(std::count_if(v.begin(),v.end(),std::bind(std::less<int>(),std::placeholders::_1,min+100))) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    Berza pomocna=*this;
    std::transform(v.begin(),v.end(),v.begin(),std::bind(std::minus<int>(),std::placeholders::_1,100));
    return pomocna;
}
bool Berza::operator !() const {
    if(v.size()==0) return true;
    else return false;
}
Berza Berza::operator -() const {
    Berza pomocni=*this; //jer trebas vratiti samo izmjenjeni, orginalni ne trebas mijenjati
    int x=max+min;
    std::transform(v.begin(),v.end(),pomocni.v.begin(),std::bind(std::minus<int>(),x,std::placeholders::_1));
    return pomocni;
}
//friend
Berza operator +(Berza a,Berza b) {
    if(a.v.size()!=b.v.size() || a.max!=b.max || a.min!=b.min) throw std::domain_error("Nesaglasni operandi"); //mozda ovo ne treba ?
    std::transform(a.v.begin(),a.v.end(),b.v.begin(),a.v.begin(),std::plus<int>());
    int provjera=std::count_if(a.v.begin(),a.v.end(),std::bind(std::greater<int>(),std::placeholders::_1,a.max));
    int provjera2=std::count_if(a.v.begin(),a.v.end(),std::bind(std::less<int>(),std::placeholders::_1,a.min));
    if(provjera>0 || provjera2>0) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return a;
}
Berza operator +(Berza a,int x) {
    int provjera=std::count_if(a.v.begin(),a.v.end(),std::bind(std::greater<int>(),std::placeholders::_1,a.max-x)); 
    int provjera2=std::count_if(a.v.begin(),a.v.end(),std::bind(std::less<int>(),std::placeholders::_1,a.min+x));
    if(provjera>0 || provjera2>0) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    std::transform(a.v.begin(),a.v.end(),a.v.begin(),std::bind(std::plus<int>(),std::placeholders::_1,x));
    return a;
}
Berza operator +(int x,Berza a) {
    return a+x;
}
Berza operator -(Berza a,Berza b) {
    if(a.v.size()!=b.v.size() || a.max!=b.max || a.min!=b.min) throw std::domain_error("Nesaglasni operandi");
    std::transform(a.v.begin(),a.v.end(),b.v.begin(),a.v.begin(),std::minus<int>());
    int provjera=std::count_if(a.v.begin(),a.v.end(),std::bind(std::less<int>(),std::placeholders::_1,a.min));
    int provjera2=std::count_if(a.v.begin(),a.v.end(),std::bind(std::greater<int>(),std::placeholders::_1,a.max));
    if(provjera>0 || provjera2>0) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return a;
}
Berza operator -(Berza a,int x) {
    std::transform(a.v.begin(),a.v.end(),a.v.begin(),std::bind(std::minus<int>(),std::placeholders::_1,x));
    int provjera=std::count_if(a.v.begin(),a.v.end(),std::bind(std::less<int>(),std::placeholders::_1,a.min));
    int provjera2=std::count_if(a.v.begin(),a.v.end(),std::bind(std::greater<int>(),std::placeholders::_1,a.max));
    if(provjera>0 || provjera2>0) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return a;
}
Berza operator -(int x,Berza a) {
    std::transform(a.v.begin(),a.v.end(),a.v.begin(),std::bind(std::minus<int>(),x,std::placeholders::_1));
    int provjera=std::count_if(a.v.begin(),a.v.end(),std::bind(std::less<int>(),std::placeholders::_1,a.min));
    int provjera2=std::count_if(a.v.begin(),a.v.end(),std::bind(std::greater<int>(),std::placeholders::_1,a.max));
    if(provjera>0 || provjera2>0) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return a;
}
Berza& Berza::operator +=(const Berza &q) {
    //std::transform(v.begin(),v.end(),q.begin(),v.begin(),std::plus<int>());
    *this = *this+q;
    return *this;
}
Berza& Berza::operator -=(const Berza &q) {
    return *this=*this-q;
    return *this;
}
Berza& Berza::operator +=(int x) {
    *this=*this+x;
    return *this;
}
Berza& Berza::operator -=(int x) {
    *this=*this-x;
    return *this;
}
bool operator ==(const Berza &a,const Berza &b) {
    return (a.v.size()==b.v.size() && std::equal(a.v.begin(),a.v.end(),b.v.begin()) );
}
bool operator !=(const Berza &a,const Berza &b) {
    return !(a==b);
}

int main ()
{
    try {
        Berza a(50,5000);
        Berza b(50,5000);
        a.RegistrirajCijenu(780);
        a.RegistrirajCijenu(1000);
        a.RegistrirajCijenu(1420);
        b.RegistrirajCijenu(1230);
        b.RegistrirajCijenu(1200);
        b.RegistrirajCijenu(870);
        std::cout<<b.DajMaksimalnuCijenu()<<" "<<b.DajMinimalnuCijenu()<<" "<<b.DajBrojCijenaVecihOd(900)<<" "<<b.DajBrojRegistriranihCijena();
        std::cout<<std::endl;
        std::cout<<a[1]<<" "<<a[2]<<" "<<a[3];
        std::cout<<std::endl;
        b.Ispisi();
        std::cout<<std::endl;
        a++;
        a.Ispisi();
        std::cout<<std::endl;
        a++;
        a.Ispisi();
        std::cout<<std::endl;
        b--;
        b.Ispisi();
        std::cout<<std::endl;
        Berza c=a+b;
        c.Ispisi();
        std::cout<<std::endl;
        c+=b;
        c.Ispisi();
    }
    catch(std::range_error iz) {
        std::cout<<iz.what();
    }
    catch(std::domain_error iz) {
        std::cout<<iz.what();
    }
	return 0;
}