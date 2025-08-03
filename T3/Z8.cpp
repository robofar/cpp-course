#include <iostream>
#include <string>
std::string IzdvojiRijec(std::string s,int n) {
    if(n<1) throw std::range_error("IZUZETAK: Pogresan redni broj rijeci!");
    std::string rijec; //stringovima ne moramo odma davati duzinu
    int brojac=0;
    int a=1;
    for(int i=0;i<s.length();i++) {
        if(a==1 && s.at(i)==' ') {
            while(s.at(i)==' ') i++; //preskace razmake prije prve rijeci
        }
        a=0;
        if(s.at(i)!=' ') {
            brojac++;
            if(brojac==n) {
                while(i!=s.length() && s.at(i)!=' ') { //mora prvo ovaj uslov i!= jer da se ne bi izvrsilo s.at(i) i pristupili nevalidnom mjestu
                    rijec.push_back(s.at(i));
                    i++;
                }
                return rijec;
            }
            while(s.at(i)!=' ') i++;
            i--;
        }
    }
    if(n>brojac) throw std::range_error("IZUZETAK: Pogresan redni broj rijeci!");
    
    return rijec;
}
int main ()
{
    int n;
    std::cout<<"Unesite redni broj rijeci: ";
    std::cin>>n;
    std::cin.ignore(10000,'\n');
    std::string s;
    std::cout<<"Unesite recenicu: ";
    std::getline(std::cin,s);
    
    try {
        std::string rijec = IzdvojiRijec(s,n);
        std::cout<<"Rijec na poziciji "<<n<<" je "<<rijec;
    }
    catch(std::range_error izuzetak) {
        std::cout<<izuzetak.what()<<std::endl;
    }
	return 0;
}


/* URADJEN ZADATAK NA LJEPSI NACIN

Mogao si char po char smjestati u string tj rijec i onda kad formiras rijec nju ubacis u neki vektor stringova, i onda
samo iz funkcije vratis odredjenu rijec po redu

#include <iostream>
#include <string>
std::string NadjiRijec(std::string s,int n) {
    int broj=0;
    int slova=0;
    int znak=0;
    for(int i=0;i<s.length();i++) {
        if(s.at(i)!=' ') {
            znak=1;
            slova++;
        }
        else if(znak) {
            znak=0;
            broj++;
            if(broj==n) return s.substr(i-slova,slova);
            slova=0;
        }
        /* Ovo mora ako nema razmaka iza zadnje rijeci */
    /*    if(i==s.length()-1 && znak) {
                broj++; 
                if(broj==n) return s.substr(i-slova+1,slova); //sve je ovo zbog toga ako nema razmaka iza zadnje rijeci
        }
    }
    return s; //OVAJ RETURN JE OVJDE NAKO, SOBZIROM DA TREBA BACIT IZUZETAK AKO NEMA RIJECI
} */
