#include <iostream>
#include <cmath>

int Cifre(long long int n,int &c_min, int &c_max) {
    int brojac=0;
    c_min=abs(n%10);
    c_max=abs(n%10);
    if(n==0) return 1;
    while(n!=0) {
        int x=abs(n%10);
        if(x<c_min) c_min=x;
        if(x>c_max) c_max=x;
        brojac++;
        n/=10;
    }
    return brojac;
}

int main ()
{
    long long int n;
    std::cout<<"Unesite broj: ";
    std::cin>>n;
    int a,b,x;
    x=Cifre(n,a,b);
    std::cout<<"Broj "<<n<<" ima "<<x<<" cifara, najveca je "<<b<<" a najmanja "<<a<<".";
    return 0;
}