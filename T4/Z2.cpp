#include <iostream>
#include <string>
#include <utility>
void IzvrniString(std::string &s) {
    for(int i=0;i<s.length()/2;i++) std::swap(s.at(i),s.at(s.length()-1-i));
}

int main ()
{
    std::string s;
    std::cout<<"Unesi string: ";
    std::getline(std::cin,s);
    IzvrniString(s);
    std::cout<<"Izvrnuti string je: "<<s;
	return 0;
}