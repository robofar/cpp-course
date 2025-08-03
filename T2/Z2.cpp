#include <iostream>
#include <vector>

bool TestPerioda(std::vector<double> v, int p) {
    if(v.size()==1 || p>=v.size()) return false;
    for(int i=0;i<v.size()-p;i++) { 
        if(v.at(i)!=v.at(i+p)) return false;
    }
    return true;
}

int OdrediOsnovniPeriod(std::vector<double> v) {
    for(int i=1;i<v.size();i++) {
        if(TestPerioda(v,i)) return i;
    }
    return 0;
}

int main () {
    std::vector<double> v;
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    double x;
    for(;;) {
        std::cin>>x;
        if(x==0) break;
        v.push_back(x);
    }
    if(OdrediOsnovniPeriod(v)) std::cout<<"Slijed je periodican sa osnovnim periodom "<<OdrediOsnovniPeriod(v)<<".";
    else  std::cout<<"Slijed nije periodican!";
	return 0;
}
