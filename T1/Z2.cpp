#include <iostream>
#include <cmath>

int main ()
{
    double a,b,c;
    
    std::cout<<"Unesite tri broja: ";
    std::cin>> a >> b >> c;
    
    //PROVJERA
    if(a<0 || b<0 || c<0 || a+b<=c || a+c<=b || b+c<=a) 
    std::cout<<"Ne postoji trougao cije su duzine stranica "<<a<<", "<<b<<" i "<<c<<"!"<<std::endl;
    
    else {
    //OBIM
    double O;
    O=a+b+c;
    
    std::cout<<"Obim trougla sa duzinama stranica "<<a<<", "<<b<<" i "<<c<<" iznosi "<<O<<"."<<std::endl;
    
    //POVRSINA
    double s;
    s=(a+b+c)/2;
    double P;
    P=std::sqrt(s*(s-a)*(s-b)*(s-c));
    
    std::cout<<"Njegova povrsina iznosi "<<P<<"."<<std::endl;
    
    //NAJMANJI UGAO
    const double PI = 4*atan(1); //define u C -> CONST tip ime u C++
    double alfa,beta,gama;
    
    alfa = acos((c*c+b*b-a*a)/(2*b*c));
    beta = acos((a*a+c*c-b*b)/(2*a*c));
    gama = acos((a*a+b*b-c*c)/(2*a*b));
    
    double minimalni{0};
    
    if(alfa<=beta && alfa<=gama) minimalni=alfa; 
    else if(beta<=alfa && beta<=gama) minimalni=beta; 
    else if(gama<=alfa && gama<=beta) minimalni=gama;
    
    double temp{(180*minimalni)/PI}; // 1 radijan ima 180/PI stepeni, tj. 180/PI * ugao(u radijanima) = taj ugao u stepenima = temp; ovo je inicijalizacija i ovo je nepraa konstanta
    
    double stepeni = int(temp);
    double minute = int((temp-stepeni)*3600)/60;
    double sekunde = int((temp-stepeni)*3600)%60;
    
    std::cout<<"Njegov najmanji ugao ima "<< stepeni <<" stepeni, "<< minute <<" minuta i "<< sekunde <<" sekundi."<<std::endl;
    
    }
  
    
    return 0;

}
