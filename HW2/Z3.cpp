#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <deque>
template<typename Tip1, typename Tip2, typename Tip3>
Tip3 SimetricnaRazlikaBlokova(Tip1 p1,Tip1 p2,Tip2 p3,Tip2 p4,Tip3 p5) {
    int velicina=0; //mora biti najlokalnija u funkciji
    Tip3 pocetak=p5;
    Tip3 kraj=p5;
    Tip1 pocetak1=p1; //kopija za pregledavanje prvog niza u odnosu na drugi
    /* Kako program radi:
    1) Krecem se kroz prvi niz, uzimam element po element, i onda svaki put trebam
       svaki element iz niza 1 provjeriti sa citavim nizom 2
       Zato mi trebaju kopije pokazivaca na niz2,
       i kopije pokazivaca na niz1(jer ce mi u drugom slucaju trebati niz1 opet, pa da se ne pomjeram sa orginalnim pokazivacem)
    2)Krecem se kroz drugi niz, uzimam element po element, i onda svaki put trebam
       svaki element iz niza2 provjeriti sa citavim nizom1
       Sad mi NE trebaju kopije na niz2 jer me briga kad zavrsim sa njim,
       ali mi trebaju kopije za niz1 */
    /*--------------------------------*/
    while(p1!=p2) {
        bool nalazi_se=false;
        Tip2 a=p3;
        Tip2 b=p4;
        /* Provjera da li se element iz niza1 nalazi u nizu 2 */
        while(a!=b) {
            if(*p1==*a) {
                nalazi_se=true;
                break;
            }
            a++;
        }
        /* Ne nalazi se */
        if(!nalazi_se) {
            Tip3 pomocni=pocetak;
            /* Ako se ovaj element vec nalazi u nizu p5 nemoj ga upisivati u niz */
            bool ponavlja_se=false;
            while(pomocni!=kraj+velicina) {
                if(*p1==*pomocni) {
                    ponavlja_se=true;
                    break;
                }
                pomocni++;
            }
            if(!ponavlja_se) {
                *p5=*p1;
                p5++;
                velicina++;
            }
        }
        p1++;
    }
    /*--------------ISTI PROCES samo provjera niza2 u odnosnu na niz1---------------*/
    p1=pocetak1;
    
    while(p3!=p4) {
        bool nalazi_se=false;
        Tip1 a=p1;
        Tip1 b=p2;
        while(a!=b) {
            if(*p3==*a) {
                nalazi_se=true;
                break;
            }
            a++;
        }
        if(!nalazi_se) {
            Tip3 pomocni=pocetak;
            bool ponavlja_se=false;
            while(pomocni!=kraj+velicina) {
                if(*p3==*pomocni) {
                    ponavlja_se=true;
                    break;
                }
                pomocni++;
            }
            if(!ponavlja_se) {
                *p5=*p3;
                p5++;
                velicina++;
            }
        }
        p3++;
    }
    /*-----------------------------*/
    return pocetak+velicina;
}

int main ()
{
    int n,m;
    int niz[100];
    std::deque<int> d;
    std::cout<<"Unesite broj elemenata niza ";
    std::cin>>n;
    std::cout<<std::endl;
    std::cout<<"Unesite elemente niza ";
    for(int i=0;i<n;i++) {
        std::cin>>niz[i];
    }
    std::cout<<std::endl;
    std::cout<<"Unesite broj elemenata deka ";
    std::cin>>m;
    std::cout<<std::endl;
    std::cout<<"Unesite elemente deka ";
    for(int i=0;i<m;i++) {
        int broj;
        std::cin>>broj;
        d.push_back(broj);
    }
    std::cout<<std::endl;
	int niz3[100]={0};
	int *pocetak3=niz3;
	int *kraj3=SimetricnaRazlikaBlokova(niz,niz+n,d.begin(),d.end(),pocetak3);
	if(kraj3-pocetak3==0) std::cout<<"Blokovi nemaju simetricnu razliku";
	else {
    	std::cout<<"Simetricna razlika blokova je: ";
    	while(pocetak3!=kraj3) {
    	    std::cout<<*pocetak3<<" ";
    	    pocetak3++;
    	}
	}
	return 0;
}