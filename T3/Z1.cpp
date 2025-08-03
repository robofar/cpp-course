#include <iostream>
#include <vector>
#include <cmath>
std::vector<int> IzdvojiElemente(std::vector<int> v,bool q) {
    std::vector<int> a;
    if(q==true) {
        for(int i : v) {
            int pomocna=i;
            int suma=0;
            while(i!=0) {
                int n=i%10;
                suma+=n;
                i/=10;
            }
            if(suma%2==0) a.push_back(pomocna);
        }
    }
    if(q==false) {
        for(int i : v) {
            int pomocna=i;
            int suma=0;
            while(i!=0) {
                int n=i%10;
                suma+=abs(n);
                i/=10;
            }
            if(suma%2==1) a.push_back(pomocna);
        }
    }
    return a;
}
int main ()
{
    int n;
    std::cout<<"Koliko zelite unijeti elemenata: ";
    std::cin>>n;
    if(n<=0) {
        std::cout<<"Broj elemenata mora biti veci od 0!";
        return 0;
    }
    std::vector<int> v(n);
    std::cout<<"Unesite elemente: ";
    for(int i=0;i<n;i++) {
        std::cin>>v.at(i);
    }
    std::vector<int> novi=IzdvojiElemente(v,true);
    for(int i : novi) {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
    std::vector<int> novi1=IzdvojiElemente(v,false);
    for(int i : novi1) {
        std::cout<<i<<" ";
    }
    
	return 0;
}
