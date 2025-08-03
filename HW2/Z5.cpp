#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <deque>
#include <iomanip>

template<typename NekiTip>
bool ZaSve(NekiTip p1,NekiTip p2,bool (*fun)(typename std::remove_reference<decltype(*p1)>::type)) {
    if(p1==p2) return true; //sad je true a bilo ja false(padala 2)
    while(p1!=p2) {
        if(!fun(*p1)) return false;
        p1++;
    }
    return true;
}

template<typename NekiTip>
bool MakarJedan(NekiTip p1,NekiTip p2,bool (*fun)(typename std::remove_reference<decltype(*p1)>::type)) {
    if(p1==p2) return false; 
    while(p1!=p2) {
        if(fun(*p1)) return true;
        p1++;
    }
    return false;
}

template<typename NekiTip>
auto Akumuliraj(NekiTip p1,NekiTip p2, typename std::remove_reference<decltype(*p1)>::type (*fun)(typename std::remove_reference<decltype(*p1)>::type a,typename std::remove_reference<decltype(*p1)>::type b),typename std::remove_reference<decltype(*p1)>::type a=0) -> typename std::remove_reference<decltype(*p1)>::type{
    if(p1==p2) return a;
    typename std::remove_reference<decltype(*p1)>::type x=fun(a,*p1);
    typename std::remove_reference<decltype(*p1)>::type rezultat;
    p1++;
   while(p1!=p2) {
        x=fun(x,*p1);
        p1++;
    }
    rezultat=x;
    return rezultat; 
}
int main ()
{
    /* --------------------------------------------------- */
    std::cout<<"Unesite string: ";
    std::string s;
    std::getline(std::cin,s);
    bool a=ZaSve(s.begin(),s.end(),[](char x)->bool {
        //if(x==' ') return true;
        if((x>='A' && x<='Z') ||(x>='a' && x<='z') || (x>='0' && x<='9')) return true;
        return false;
    });
    if(a) std::cout<<"Uneseni string sadrzi samo slova i cifre";
    else std::cout<<"Uneseni string sadrzi i druge znakove osim slova i cifara";
    std::cout<<std::endl;
    /* ---------------------------------------------------- */
    long long int niz[10];
    std::cout<<"Unesite niz od 10 brojeva: ";
    /* Unos - mora preko for_each i onda ide referenca */
    std::for_each(niz,niz+10,[](long long int &x) {
        std::cin>>x;
    });
    bool b=MakarJedan(niz,niz+10,[](long long int x)->bool {
        if(x==0) return false; // 0/0 undefined
        long long int suma=0;
        long long int kopija=x;
        while(kopija!=0) {
            int n=kopija%10;
            suma+=n;
            kopija/=10;
        }
        if(x%suma==0) return true;
        return false;
    });
    if(b) std::cout<<"U nizu ima brojeva djeljivih sa sumom svojih cifara";
    else std::cout<<"U nizu nema brojeva djeljivih sa sumom svojih cifara";
    std::cout<<std::endl;
    /* ---------------------------------------------------------------- */
    std::deque<long double> d(10);
    std::cout<<"Unesite dek od 10 elemenata: ";
    std::for_each(d.begin(),d.end(),[](long double &x){
        std::cin>>x;
    });
    std::cout<<std::endl;
    long double suma=Akumuliraj(d.begin(),d.end(),[](long double x,long double y)->long double {
                return x+y;
    });
    long double proizvod=Akumuliraj(d.begin(),d.end(),[](long double x,long double y)->long double {
                return x*y;
    },1);
    long double najmanji_element=Akumuliraj(d.begin(),d.end(),[](long double x,long double y)->long double {
        if(x<y) return x;
        return y;
    },20);
    long double najveci_element=Akumuliraj(d.begin(),d.end(),[](long double x,long double y)->long double {
        if(x>y) return x;
        return y;
    });
    std::cout<<"Suma deka: "<<suma<<std::endl;
    std::cout<<"Produkt deka: "<<proizvod<<std::endl;
    std::cout<<"Najveci elemenat deka: "<<najveci_element<<std::endl;
    std::cout<<"Najmanji elemenat deka: "<<najmanji_element<<std::endl;
   
    return 0;
}