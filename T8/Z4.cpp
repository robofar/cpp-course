#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iterator>
std::string ZamijeniPremaRjecniku(std::string s,std::map<std::string, std::string> mapa) {
    std::string novi=std::string();
    std::string pomocna;
    for(int i=0;i<s.size();i++) {
        if(s.at(i)==' ') {
                novi+=s.at(i);
                pomocna=std::string();
        }
        else {
            while(i<s.size() && s.at(i)!=' ') {
                pomocna+=s.at(i);
                i++;
            }
            i--; //vratimo se jednom da se ne bi opet gore povecalo
            auto it=mapa.find(pomocna);
            if(it!=mapa.end()) novi+=it->second;
            else novi+=pomocna;
        }
    }
    return novi;
}

int main() {
std::string s="kako da ne";
std::map<std::string, std::string> moj_rjecnik{ {"jabuka", "apple"},{"da", "yes"}, {"kako", "how"}, {"ne", "no"}, {"majmun", "monkey"}};
std::string novi=ZamijeniPremaRjecniku(s,moj_rjecnik);
std::cout<<novi;
return 0;
}