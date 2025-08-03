#include <iostream>
#include <vector>

bool DaLiJeProst(int n) {
    bool jeste=true;
    for(int i=2;i<n;i++) {
        if(n%i==0) {
            jeste=false;
            break;
        }
    }
    return jeste;
}

void RastavaBroja(double broj, int &prvi, int &drugi) {
    if(broj<=0) throw std::domain_error("Broj koji se rastavlja mora biti prirodan");
    int n=broj; //sluzi za provjeru da li je npr unesen realan broj(u nastavku cu raditi sa n jer je cijeli broj)
    if(n!=broj) throw std::domain_error("Broj koji se rastavlja mora biti prirodan");
    std::vector<int> v;
    int i=2;
    /* Smjesti proste faktore u vektor */
    while(n>1) {
        if(DaLiJeProst(i)) {
            while(n%i==0) {
                v.push_back(i);
                n/=i;
                if(n==1) break;
            }
            i++;
        }
        else i++;
    }
    /* One sa parnim brojem ponavljanja smjesti u jedan vektor,
       one sa neparnim u drugi vektor */
    int brojac=0;
    int prosti_faktor;
    std::vector<int> a; //vektor za prvi
    std::vector<int> b;// vektor za drugi
    for(int i=0;i<v.size();i++) {
        brojac=0;
        prosti_faktor=v.at(i);
        while(i<v.size() && v.at(i)==prosti_faktor) {
            brojac++;
            i++;
        }
        i--; //zbog onog zadnjeg gore i++ da se ne bi 2 puta pomjerilo
        if(brojac%2==1) {
            a.push_back(prosti_faktor);
            for(int j=0;j<brojac/2;j++) b.push_back(prosti_faktor);
        }
        else {
            for(int j=0;j<brojac/2;j++) b.push_back(prosti_faktor);
        }
    }
    /* U prvi smjestimo ove iz vektora a, u drugi ove iz vektora b */
    int proizvod_a=1;
    int proizvod_b=1;
    for(int i=0;i<a.size();i++) proizvod_a*=a.at(i);
    for(int i=0;i<b.size();i++) proizvod_b*=b.at(i);
    prvi=proizvod_a;
    drugi=proizvod_b;
}
int main ()
{
    double n;
    std::cout<<"Unesite prirodan broj ";
    std::cin>>n;
    std::cout<<std::endl;
    int prvi=0,drugi=0;
    try{
        RastavaBroja(n,prvi,drugi);
        std::cout<<prvi<<" "<<drugi;
    }
    catch(std::domain_error izuzetak) {
        std::cout<<"Izuzetak: "<<izuzetak.what()<<"!";
    }
	return 0;
}