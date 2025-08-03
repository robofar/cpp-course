#include <iostream>
#include <vector>
#include <string>

bool Simetricna(std::string s) {
	if(s.size()<=1) return false;
	/* Sve pretvori u mala slova, sobzirom da smo poslali kopiju */
	for(int i=0;i<s.size();i++) {
		if(s.at(i)>='A' && s.at(i)<='Z') s.at(i) += 32;
	}
	/* Simetricnost */
	for(int i=0;i<(s.size()/2);i++) {
		if(s.at(i) != s.at(s.size()-1-i)) return false;
	}
	return true;
}

std::vector<std::string> NadjiSimetricneRijeci(std::string s) {
	std::vector<std::string> v;
	std::string pomocni;
	for(int i=0;i<s.length();i++) {
		/* Uslov ce se ispuniti samo kada je char slovo ili broj, za ostalo samo prolazimo kroz petlju */
			if((s.at(i)>='1' && s.at(i)<='9') || (s.at(i)>='A' && s.at(i)<='Z') || (s.at(i)>='a' && s.at(i)<='z')) {
				pomocni.push_back(s.at(i));
				/* Ovaj prvi uslov je ako je zadnja rijec u recenici palindrom a iza nje nema vise nicega u stringu */
				if(i+1==s.length() || (!((s.at(i+1)>='1' && s.at(i+1)<='9') || (s.at(i+1)>='A' && s.at(i+1)<='Z') || (s.at(i+1)>='a' && s.at(i+1)<='z')))) {
					bool a=Simetricna(pomocni);
					if(a) v.push_back(pomocni);
					pomocni.resize(0);
				}
			}
	}
	return v;
}

int main ()
{
	std::string s;
	std::cout<<"Unesite recenicu:"<<std::endl;
	std::getline(std::cin,s);
	std::vector<std::string> rez=NadjiSimetricneRijeci(s);
	if(rez.size()==0) std::cout<<"Recenica ne sadrzi simetricne rijeci!";
	else {
		std::cout<<"Simetricne rijeci unutar recenice su:"<<std::endl;
		for(int i=0;i<rez.size();i++) {
			std::cout<<rez.at(i)<<std::endl;
		}
	}
	return 0;
}