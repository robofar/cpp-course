#include <iostream>
#include <fstream>
#include <string>

void IzvrniDatoteku(std::string ime) {
    std::fstream tok(ime,std::ios::in | std::ios::binary);
    if(!tok) throw std::logic_error("Datoteka ne postoji");
    tok.close();
    tok.open(ime,std::ios::in | std::ios::out | std::ios::binary);
    tok.seekg(0,std::ios::end);
    unsigned int velicina= tok.tellg()/sizeof(double);
    for(int i=0;i<velicina/2;i++) {
        double x;
        tok.seekg(i*sizeof(double),std::ios::beg);
        tok.read(reinterpret_cast<char*>(&x),sizeof(double));
        double y;
        tok.seekg((velicina-i-1)*sizeof(double),std::ios::beg);
        tok.read(reinterpret_cast<char*>(&y),sizeof(double));
        double temp=x;
        tok.seekp(i*sizeof(double),std::ios::beg);
        tok.write(reinterpret_cast<char*>(&y),sizeof(double));
        tok.seekp((velicina-i-1)*sizeof(double),std::ios::beg);
        tok.write(reinterpret_cast<char*>(&temp),sizeof(double));
    }
} 
int main ()
{
	return 0;
}