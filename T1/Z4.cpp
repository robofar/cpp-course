#include <iostream>
#include <cmath>
int main ()
{
    double n;
    int a; //za provjeru realnog broja
    int suma=0;
    for(;;) {
        suma=0;
        std::cout << "Unesite prirodan broj ili 0 za kraj: ";
        std::cin>>n; 
        a=n; 
        // Pogresan unos
        if(!(std::cin)) {
            std::cout<<"Niste unijeli prirodan broj!"<<std::endl;
            std::cin.clear();   //oporavak toka
            std::cin.ignore(10000,'\n'); //brisanje svega iz spremnika jer je los unos
        }
        //  Da li je unesen realan broj - ne treba nam oporavak toka i brisanje 
        else if(a<n || n<0) std::cout<<"Niste unijeli prirodan broj!\n";
        else if (a==0) break;
        else {
        for(int i=1;i<a;i++) {
            if(a%i==0) suma+=i;
        }
        
        if(suma<a) std::cout<<"Broj "<<a<<" je manjkav!"<<std::endl;
        else if(suma>a) std::cout<<"Broj "<<a<<" je obilan!"<<std::endl;
        else std::cout<<"Broj "<<a<<" je savrsen!"<<std::endl;
        }
    }
    std::cout<<"Dovidjenja!";
	return 0;
}