#include <iostream>
#include <string>
#include <map>
#include <set>

std::string vrati(std::string s) { //u mala pretvori
    std::string q=s;
    for(int i=0;i<s.size();i++) q.at(i)=std::tolower(s.at(i));
    return q;
}

std::map<std::string,std::set<int>> KreirajIndeksPojmova(std::string a) {
    std::map<std::string,std::set<int>> rez;
    std::string pomocni=std::string();
    std::set<int> skup;
    std::string s=vrati(a);
    for(int i=0;i<s.length();i++) {
        if((s.at(i)<'a' || s.at(i)>'z') && (s.at(i)<'0' || s.at(i)>'9')) continue;
        else {
            int pozicija=i;
            while((s.at(i)>='a' && s.at(i)<='z') || (s.at(i)>='0' && s.at(i)<='9')) {
                pomocni+=s.at(i);
                i++;
                if(i==s.length()) break;
            }
            skup.insert(pozicija); //prva pozicija
            bool nalazi_se;
            for(int j=i;j<s.length();j++) {
                nalazi_se=true;
                pozicija=j;
                
                for(int k=0;k<pomocni.length();k++) {
                    /* Podstring za slova ispred */
                    if(k==0 && j-1>=0 && ((s.at(j-1)>='a' && s.at(j-1)<='z') || (s.at(j-1)>='0' && s.at(j-1)<='9'))) {
                       nalazi_se=false;
                       break;
                    }
                    if(s.at(j)!=pomocni.at(k)) {
                        nalazi_se=false;
                        break;
                    }
                    j++; //moram ga rucno pomjerat
                    if(j==s.length() && k==pomocni.length()-1) {
                        nalazi_se=true;
                        break;
                    }
                    if(j==s.length() && k!=pomocni.length()-1) {
                        nalazi_se=false;
                        break;
                    }
                    /* Podstring za slova iza */
                    if(k==pomocni.length()-1) {
                        if((s.at(j)<'a' || s.at(j)>'z') && (s.at(j)<'0' || s.at(j)>'9')){
                            nalazi_se=true;; //provjera za podstring. npr abcdef i abc OVO NE MOZE jer je abc podstring, pa provjerim znak iza c koji bi trebao bit razmak il slicno
                            break;
                        }
                        else nalazi_se=false;
                    }
                }
                if(nalazi_se) skup.insert(pozicija);
            }
            /* posto su mi sad done set i pomocni string ubaci ih u mapu */
            rez.insert(std::make_pair(pomocni,skup)); 
            pomocni=std::string(); 
            skup={}; //resetujem skup
        }
    }
    return rez;
}

std::set<int> PretraziIndeksPojmova(std::string s,std::map<std::string,std::set<int>> mapa) {
    s=vrati(s);
    auto it=mapa.find(s);
    if(it==mapa.end()) throw std::logic_error("Pojam nije nadjen");
    std::set<int> q=it->second;
    return q;
}

void IspisiIndeksPojmova(std::map<std::string,std::set<int>> mapa) {
    for(auto it=mapa.begin();it!=mapa.end();it++) {
        std::cout<<it->first<<": ";
        std::set<int> q=it->second;
        auto it1=q.begin();
        int x=q.size();
        for(int i=0;i<x;i++) {
            if(i==x-1) std::cout<<*it1;
            else std::cout<<*it1<<",";
            it1++;
        }
        std::cout<<std::endl;
    }
}

int main ()
{
    std::string s;
    std::cout<<"Unesite tekst: ";
    std::getline(std::cin,s);
    std::map<std::string, std::set<int>> mapa=KreirajIndeksPojmova(s);
    IspisiIndeksPojmova(mapa);
   for(;;) {
       std::string s;
       std::cout<<"Unesite rijec: ";
       std::cin>>s;
       if(s==".") break;
       try {
            std::set<int> indeksi=PretraziIndeksPojmova(s,mapa);
            for(auto it1=indeksi.begin();it1!=indeksi.end();it1++) std::cout<<*it1<<" ";
       }
       catch(std::logic_error) {
           std::cout<<"Unesena rijec nije nadjena!";
       }
       std::cout<<std::endl;
   }
	return 0;
}


/* mogo si prvo ubacit sve rijeci preko mapa[rijec] - nebitno jel se ponavljaju
onda preko for(auto it=mapa.begin ...) if(it->first==rijec) it->second.insert(i);
gdje ti je ova rijec u ovom ifu rijec koju uzimas iz recenice. Ovako bi bilo lakse */