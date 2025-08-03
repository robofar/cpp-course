#include <iostream>
#include <set>
#include <string>

template<typename NekiTip>
std::set<NekiTip> Presjek(std::set<NekiTip> s1,std::set<NekiTip> s2) {
    std::set<NekiTip> novi;
    auto it1=s1.begin();
    while(it1!=s1.end()) {
        auto pomocni=s2.find(*it1); //da li se trenutni clan s1 nalazi u s2
        if(pomocni!=s2.end()) novi.insert(*it1); //ne moram paziti da li se ponavljaju jer svakako se ne pikaju ponovljeni u set-u
        it1++;
    }
    return novi;
}

/* Svakako ce ti se izbaciti ponavljajuci elementi haha */
template<typename NekiTip>
std::set<NekiTip> Unija(std::set<NekiTip> s1,std::set<NekiTip> s2) {
    std::set<NekiTip> novi;
    auto it1=s1.begin();
    auto it2=s2.begin();
    while(it1!=s1.end()) novi.insert(*it1++);
    while(it2!=s2.end()) novi.insert(*it2++);
    return novi;
}
int main ()
{
    std::set<std::string> s1={"Ja","sam","dosao","jucer","a","ti"};
    std::set<std::string> s2={"a","on","je","dosao","isto","jucer"};
    std::set<std::string> p=Presjek(s1,s2);
    std::set<std::string> u=Unija(s1,s2);
    std::set<std::string>::iterator a=p.begin();
    std::set<std::string>::iterator b=u.begin();
    while(a!=p.end()) std::cout<<*a++<<" ";
    std::cout<<std::endl;
    while(b!=u.end()) std::cout<<*b++<<" ";
	return 0;
}