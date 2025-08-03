#include <iostream>

enum Dani {Ponedjeljak,Utorak,Srrijeda,Cetvrtak,Petak,Subota,Nedjelja};

std::ostream& operator <<(std::ostream &tok,const Dani &d) {
	if(d==0) tok<<"Ponedjeljak";
	else if(d==1) tok<<"Utorak";
	else if(d==2) tok<<"Srijeda";
	else if(d==3) tok<<"Cetvrtak";
	else if(d==4) tok<<"Petak";
	else if(d==5) tok<<"Subota";
	else if(d==6) tok<<"Nedjelja";
	return tok;
}

Dani& operator ++(Dani &d) { //++d
	d=Dani((int(d)+1)%7);
	return d;
}

Dani operator ++(Dani &d,int) { //d++
	auto pomocna=d;
	++d; //poziva se ova gore
	return pomocna;
}

int main ()
{
	for(Dani i=Ponedjeljak;i<=Nedjelja;i++) {
		std::cout<<i<<" ";
		if(i==Nedjelja) break;
	}
	return 0;
}