#include <iostream>
#include <limits>
enum class Smjer{Nalijevo,Nadesno};
enum class Pravci{Sjever,Istok,Jug,Zapad};
enum class KodoviGresaka{PogresnaKomanda,NedostajeParametar,SuvisanParametar,NeispravanParametar};
enum class Komande{Aktiviraj,Deaktiviraj,Nalijevo,Nadesno,Idi,Kraj};

bool aktivan=true;
int maks=std::numeric_limits<int>::max();
int min=std::numeric_limits<int>::min();
void AktivirajRobota() {
    aktivan=true;
}

void DeaktivirajRobota() {
    aktivan=false;
}

void IspisiPoziciju(int x,int y,Pravci orjentacija) {
    if(aktivan) std::cout<<"Robot je trenutno aktivan, ";
    else if(!aktivan) std::cout<<"Robot je trenutno neaktivan, ";
    std::cout<<"nalazi se na poziciji ("<<x<<","<<y<<") i gleda na ";
    if(orjentacija==Pravci::Sjever) std::cout<<"sjever."<<std::endl;
    else if(orjentacija==Pravci::Istok) std::cout<<"istok."<<std::endl;
    else if(orjentacija==Pravci::Jug) std::cout<<"jug."<<std::endl;
    else if(orjentacija==Pravci::Zapad) std::cout<<"zapad."<<std::endl;
}

void Rotiraj(Pravci &orjentacija,Smjer na_koju_stranu) {
    if(na_koju_stranu == Smjer::Nadesno) {
        if(orjentacija==Pravci::Sjever) orjentacija=Pravci::Istok;
        else if(orjentacija==Pravci::Istok) orjentacija=Pravci::Jug;
        else if(orjentacija==Pravci::Jug) orjentacija=Pravci::Zapad;
        else if(orjentacija==Pravci::Zapad) orjentacija=Pravci::Sjever;
    }
    else if(na_koju_stranu == Smjer::Nalijevo) {
        if(orjentacija==Pravci::Sjever) orjentacija=Pravci::Zapad;
        else if(orjentacija==Pravci::Zapad) orjentacija=Pravci::Jug;
        else if(orjentacija==Pravci::Jug) orjentacija=Pravci::Istok;
        else if(orjentacija==Pravci::Istok) orjentacija=Pravci::Sjever;
    }
}

void PrijaviGresku(KodoviGresaka kod_greske) {
    if(kod_greske==KodoviGresaka::PogresnaKomanda) std::cout<<"Nerazumljiva komanda!"<<std::endl;
    else if(kod_greske==KodoviGresaka::NedostajeParametar) std::cout<<"Komanda trazi parametar koji nije naveden!"<<std::endl;
    else if(kod_greske==KodoviGresaka::NeispravanParametar) std::cout<<"Parametar komande nije ispravan!"<<std::endl;
    else if(kod_greske==KodoviGresaka::SuvisanParametar) std::cout<<"Zadan je suvisan parametar nakon komande!"<<std::endl;
}

void Idi(int &x,int &y,Pravci orjentacija,int korak) {
    if(orjentacija==Pravci::Sjever) {
        if((static_cast<long int>(y) + static_cast<long int>(korak)) >= maks) y=maks; //korak pozitivan
        else if((static_cast<long int>(y) + static_cast<long int>(korak)) <= min) y=min; //korak negativan
        else y=y+korak;
    }
    else if(orjentacija==Pravci::Jug) {
        if((static_cast<long int>(y) - static_cast<long int>(korak)) <= min) y=min; //korak pozitivan
        else if((static_cast<long int>(y) - static_cast<long int>(korak)) >=maks) y=maks; //korak negativan
        else y=y-korak;
    }
    if(orjentacija==Pravci::Istok) {
        if((static_cast<long int>(x) + static_cast<long int>(korak)) >= maks) x=maks; //korak pozitivan
        else if((static_cast<long int>(x) + static_cast<long int>(korak)) <= min) x=min; //korak negativan
        else x=x+korak;
    }
    if(orjentacija==Pravci::Zapad) {
        if((static_cast<long int>(x) - static_cast<long int>(korak)) <= min) x=min;//korak pozitivan
        else if((static_cast<long int>(x) - static_cast<long int>(korak)) >= maks) x=maks; //korak negativan
        else x=x-korak;
    }
}

void IzvrsiKomandu(Komande komanda,int parametar,int &x,int &y,Pravci &orjentacija) {
    if(komanda==Komande::Aktiviraj) AktivirajRobota();
    else if(komanda==Komande::Deaktiviraj) DeaktivirajRobota();
    else if(aktivan && komanda==Komande::Nalijevo) Rotiraj(orjentacija,Smjer::Nalijevo);
    else if(aktivan && komanda==Komande::Nadesno) Rotiraj(orjentacija,Smjer::Nadesno);
    else if(aktivan && komanda==Komande::Idi) Idi(x,y,orjentacija,parametar);
    else if(aktivan && komanda==Komande::Kraj) return; //"osim ako je zadan Kraj, tad funkcija ne radi nista"
}

bool UnosKomande(Komande &komanda,int &parametar,KodoviGresaka &kod_greske) {
    std::cout<<"Unesi komandu: ";
    char unos;
    unos=std::cin.get();
    /* Preskoci sve razmake */
    while(unos==' ' || unos=='\t') {
        unos=std::cin.get();
    }
    /* Unutar svakog ovog provjeravaj jos slucajeve ako ima neki znak iza vamo tamo da mozes gresku ispisat */
    if(unos=='A' && std::cin.peek()=='-') {
        unos=std::cin.get(); //uzeo minus
        if(std::cin.peek()=='\n') komanda=Komande::Deaktiviraj;
        else if(std::cin.peek()==' ' || std::cin.peek()=='\t') { //mora peek, jer ako unesemo A-, on ce trazit jos jedan, zato unos ide tek ispod
            unos=std::cin.get();
            while(unos==' ' || unos=='\t') {
                unos=std::cin.get();
            }
            if(unos!='\n') {
                kod_greske=KodoviGresaka::SuvisanParametar;
                std::cin.ignore(100,'\n');
                return false;
            }
            else komanda=Komande::Deaktiviraj;
        }
        else if(std::cin.peek() !=' ' && std::cin.peek()!='\t' && std::cin.peek()!='\n') {
            unos=std::cin.get();
            kod_greske=KodoviGresaka::SuvisanParametar;
            std::cin.ignore(100,'\n');
            return false;
        }
        //inace je dobar unos
        else komanda=Komande::Deaktiviraj; //ne treba al eto
        if(unos!='\n') std::cin.ignore(100,'\n');
        return true;
    }
    else if(unos=='A' && std::cin.peek()=='+') {
        unos=std::cin.get(); //uzmemo +
        if(std::cin.peek()=='\n') komanda=Komande::Aktiviraj;
        else if(std::cin.peek()==' ' || std::cin.peek()=='\t') {
            unos=std::cin.get();
            while(unos==' ' || unos=='\t') {
                unos=std::cin.get();
            }
            if(unos!='\n') {
                kod_greske=KodoviGresaka::SuvisanParametar;
                std::cin.ignore(100,'\n');
                return false;
            }
            else komanda=Komande::Aktiviraj;
        }
        else if(std::cin.peek()!=' ' && std::cin.peek()!='\t' && std::cin.peek()!='\n') {
            unos=std::cin.get();
            kod_greske=KodoviGresaka::SuvisanParametar;
            std::cin.ignore(100,'\n');
            return false;
        }
        else komanda=Komande::Aktiviraj;
        if(unos!='\n') std::cin.ignore(100,'\n');
        return true;
    }
    else if(unos=='L') {
        if(std::cin.peek()!='\n') { //ako nije razmak, znaci da je \n  (jer inace ne bi ni usli u ovaj gornji if)
            unos=std::cin.get();
            while(unos==' ' || unos=='\t') { //prodjemo sve razmake izmedju A i moguceg -(jer smiju izmedju bit razmaci)
                unos=std::cin.get();
            }
            if(unos!='\n') {
                kod_greske=KodoviGresaka::SuvisanParametar;//los unos(znaci mora biti \n, jer nema sta drugo)(sad ces pozivati prijavi_gresku i slati odredjen parametar)
                std::cin.ignore(100,'\n');
                return false;
            }
            else komanda=Komande::Nalijevo;
        }
        else komanda=Komande::Nalijevo;//ako nije razmak, onda je \n a to je okej
        if(unos!='\n') std::cin.ignore(100,'\n');
        return true;
    }
    else if(unos=='D') {
         if(std::cin.peek()!='\n') { //ako nije razmak, znaci da je \n  (jer inace ne bi ni usli u ovaj gornji if)
            unos=std::cin.get();
            while(unos==' ' || unos=='\t') { //prodjemo sve razmake izmedju A i moguceg -(jer smiju izmedju bit razmaci)
                unos=std::cin.get();
            }
            if(unos!='\n') {
                kod_greske=KodoviGresaka::SuvisanParametar;//los unos(znaci mora biti \n, jer nema sta drugo)(sad ces pozivati prijavi_gresku i slati odredjen parametar)
                std::cin.ignore(100,'\n');
                return false;
            }
            else komanda=Komande::Nadesno;
         }
        else komanda=Komande::Nadesno;
        if(unos!='\n') std::cin.ignore(100,'\n');
        return true;
    }
    /* Pustim ga da udje u ovaj if samo ako je prvi I, nevezano za poslije da bi mogo lakse greske ispisat */
    else if(unos=='I') {
        if(std::cin.peek()=='\n') { //npr ako je uneseno I\n onda nedostaje parametar
            kod_greske=KodoviGresaka::NedostajeParametar;
            std::cin.ignore(100,'\n');
            return false;
        }
        else if(std::cin.peek()==' ' || std::cin.peek()=='\t') {
            unos=std::cin.get(); //pokupi taj razmak
            while((unos==' ' || unos=='\t') && (std::cin.peek()==' ' || std::cin.peek()=='\t')) { //moro sam peek-at zbog cin-a(kad budem smjesto broj preko cina)
                unos=std::cin.get(); //unos je razmak, a kad se prekine petlja on ce biti i dalje razmak, samo znamo da poslije toga je nesto sto nije razmak
            } 
            if(!(std::cin.peek()>='0' && std::cin.peek()<='9') && std::cin.peek()!='-') {
                if(std::cin.peek()=='\n') kod_greske=KodoviGresaka::NedostajeParametar;
                else kod_greske=KodoviGresaka::NeispravanParametar;//los unos(jer poslije razmaka mora biti neki broj)
                std::cin.ignore(100,'\n'); //ovdje moze ignore jer i ako je \n nije izdvojen, jer smo samo peekali
                return false;
            }
            else {//uzmi taj broj
                int predznak=1;
                if(std::cin.peek()=='-') {
                    predznak=-1;
                    unos=std::cin.get(); //uzmemo taj minus
                    if(!(std::cin.peek()>='0' && std::cin.peek()<='9')) {
                        kod_greske=KodoviGresaka::NeispravanParametar;
                        std::cin.ignore(100,'\n');
                        return false;
                    }
                }  
                long int broj=0;
                std::cin>>broj;
                if(predznak==1 && broj>=maks) broj=maks;
                else if(predznak==-1 && (broj*(-1))<=min) broj=min;
                unos=std::cin.get();
                if(unos!=' ' && unos!='\t' && unos!='\n') {
                    kod_greske=KodoviGresaka::NeispravanParametar;//los unos
                    std::cin.ignore(100,'\n');
                    return false;
                }
                else if(unos==' ' || unos=='\t') {
                    while(unos==' ' || unos=='\t') {
                        unos=std::cin.get();
                    }
                    if(unos!='\n') {
                        kod_greske=KodoviGresaka::NeispravanParametar;//los unos
                        std::cin.ignore(100,'\n');
                        return false;
                    }
                    else { //onda je \n, a posto je on vec izdvojen onda nam ne treba ovaj ignore(PRAVICE GRESKU)
                        komanda=Komande::Idi;
                        parametar=(broj*predznak);
                        return true;
                    }
                }
                else { //onda je \n
                    komanda=Komande::Idi; //ako nije ovo gore onda je \n a to je okej
                    parametar=(broj*predznak);
                    return true;
                }
            }
        }
        else if((std::cin.peek()>='0' && std::cin.peek()<='9') || std::cin.peek()=='-') {  //mora biti cifra, jer inace ne bi ni usli u ovaj glavni if
            int predznak=1;
            if(std::cin.peek()=='-') {
                predznak=-1;
                unos=std::cin.get(); //uzmemo taj minus
                if(!(std::cin.peek()>='0' && std::cin.peek()<='9')) {
                    kod_greske=KodoviGresaka::NeispravanParametar;
                    std::cin.ignore(100,'\n');
                    return false;
                }
            }  
            long int broj=0;
            std::cin>>broj;
            if(predznak==1 && broj>=maks) broj=maks;
            if(predznak==-1 && (broj*(-1))<=min) broj=min;
            
            unos=std::cin.get(); //pokupimo BJELINU jer je cin nije izdvojio
            if(unos!=' ' && unos!='\t' && unos!='\n') {
                kod_greske=KodoviGresaka::NeispravanParametar;//los unos
                std::cin.ignore(100,'\n');
                return false;
            }
            else if(unos==' ' || unos=='\t') {
                while(unos==' ' || unos=='\t') {
                    unos=std::cin.get();
                }
                if(unos!='\n') {
                    kod_greske=KodoviGresaka::NeispravanParametar;//los unos
                    std::cin.ignore(100,'\n');
                    return false;
                }
                else {
                    komanda=Komande::Idi;
                    parametar=(broj*predznak);
                    return true;
                }
            }
            else if(unos=='\n') { //onda je \n
                komanda=Komande::Idi;
                parametar=(broj*predznak);
                return true;
            }
        }
        else {
            kod_greske=KodoviGresaka::NeispravanParametar;
            std::cin.ignore(100,'\n');
            return false;
        }
        return true;
    }
    else if(unos=='K') {
         if(std::cin.peek()!='\n') { //ako nije razmak, znaci da je \n  (jer inace ne bi ni usli u ovaj gornji if)
            unos=std::cin.get();
            while(unos==' ' || unos=='\t') { //prodjemo sve razmake izmedju A i moguceg -(jer smiju izmedju bit razmaci)
                unos=std::cin.get();
            }
            if(unos!='\n') {
                kod_greske=KodoviGresaka::SuvisanParametar;//los unos(znaci mora biti \n, jer nema sta drugo)(sad ces pozivati prijavi_gresku i slati odredjen parametar)
                std::cin.ignore(100,'\n');
                return false;
            }
            else komanda=Komande::Kraj;
         }
        else komanda=Komande::Kraj;
        if(unos!='\n') std::cin.ignore(100,'\n');// NE SMIJEMO KUPITI ZBOG \N
        return true;
    }
    else kod_greske=KodoviGresaka::PogresnaKomanda;
    if(unos!='\n') std::cin.ignore(1000,'\n');
    return false; //ovaj ide false jer ako nijedan nije true bio znaci nista nije bilo ispravno uneseno pa mora false ovdje
}

int main() {
    int x=0;
    int y=0;
    Komande komanda;
    int parametar;
    KodoviGresaka kod_greske;
    Pravci orjentacija=Pravci::Sjever;
    IspisiPoziciju(x,y,orjentacija);
    for(;;) {
        bool unos=UnosKomande(komanda,parametar,kod_greske);
        if(unos) {
            IzvrsiKomandu(komanda,parametar,x,y,orjentacija);
            if(komanda==Komande::Kraj) {
                std::cout<<"Dovidjenja!";
                break;
            }
            IspisiPoziciju(x,y,orjentacija);
        }
        else {
            PrijaviGresku(kod_greske);
        }
    }
return 0;
}

