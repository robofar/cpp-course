#include <iostream>
#include <vector>
#include <stdexcept>
struct Vrijeme {
    int sati;
    int minute;
    int sekunde;
};
void TestirajVrijeme(Vrijeme v1) { //stavljaj const & inace al eto
    if((v1.sati<0 || v1.sati>23) || (v1.minute<0 || v1.minute>59)|| (v1.sekunde<0 || v1.sekunde>59)) throw std::domain_error("Neispravno vrijeme");
}

void IspisiVrijeme(Vrijeme v) {
    TestirajVrijeme(v);
    if(v.sati<10) std::cout<<"0";
    std::cout<<v.sati<<":";
    if(v.minute<10) std::cout<<"0";
    std::cout<<v.minute<<":";
    if(v.sekunde<10) std::cout<<"0";
    std::cout<<v.sekunde<<std::endl;
   // std::cout<<v.sati<<":"<<v.minute<<":"<<v.sekunde;
}

Vrijeme SaberiVrijeme(Vrijeme v1,Vrijeme v2) {
    TestirajVrijeme(v1);
    TestirajVrijeme(v2);
    Vrijeme novo;
    int pomocna_minute=0;
    int pomocna_sati=0;
    novo.sekunde=v1.sekunde+v2.sekunde;
    if(novo.sekunde>=60) {
            novo.sekunde=novo.sekunde-60;
            pomocna_minute=1; //povecaj minute za 1
    }
    novo.minute=v1.minute+v2.minute+pomocna_minute;
    if(novo.minute>=60) {
        novo.minute=novo.minute-60;
        pomocna_sati=1;
    }
    novo.sati=v1.sati+v2.sati+pomocna_sati;
    if(novo.sati>=24) {
        novo.sati=novo.sati-24;
    }
    return novo;
}

int main() {
    try{
        Vrijeme v1,v2;
        std::cout<<"Unesite prvo vrijeme (h m s): ";
        std::cin>>v1.sati>>v1.minute>>v1.sekunde;
        TestirajVrijeme(v1);
        std::cout<<"Unesite drugo vrijeme (h m s): ";
        std::cin>>v2.sati>>v2.minute>>v2.sekunde;
        TestirajVrijeme(v2);
        std::cout<<"Prvo vrijeme: ";
        IspisiVrijeme(v1);
        std::cout<<"Drugo vrijeme: ";
        IspisiVrijeme(v2);
        Vrijeme rez=SaberiVrijeme(v1,v2);
        std::cout<<"Zbir vremena: ";
        IspisiVrijeme(rez);
    }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    return 0;
}
