#include <iostream>
#include <deque>
#include <cmath>
std::deque<int> IzdvojiElemente(std::deque<int> v,bool q) {
    std::deque<int> a;
    if(q==true) {
        for(int i = (v.size() - 1);i>=0; i--) {
            int pomocna=v[i];
            int suma=0;
            while(v[i]!=0) {
                int n=v[i]%10;
                suma+=abs(n);
                v[i]/=10;
            }
            if(suma%2==0) a.push_front(pomocna);
        }
    }
    if(q==false) {
        for(int i = (v.size() - 1);i>=0; i--) {
            int pomocna=v[i];
            int suma=0;
            while(v[i]!=0) {
                int n=v[i]%10;
                suma+=abs(n);
                v[i]/=10;
            }
            if(suma%2==1) a.push_front(pomocna);
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
    std::deque<int> v(n);
    std::cout<<"Unesite elemente: ";
    for(int i=0;i<n;i++) {
        std::cin>>v.at(i);
    }
    std::deque<int> novi=IzdvojiElemente(v,true);
    if(novi.size()!=0) {
    for(int i=0; i<novi.size();i++) {
        if(i==novi.size()-1) std::cout<<novi.at(i);
        else std::cout<<novi.at(i)<<",";
    }
    }
    std::cout<<std::endl;
    
    std::deque<int> novi1=IzdvojiElemente(v,false);
    
    if(novi1.size()!=0) {
    for(int i=0; i<novi1.size();i++) {
        if(i==novi1.size()-1) std::cout<<novi1.at(i);
        else std::cout<<novi1.at(i)<<",";
    }
    }
    
	return 0;
}