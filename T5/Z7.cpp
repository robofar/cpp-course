#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename IterPok>
auto SumaBloka(IterPok p1, IterPok p2) -> decltype(*p1 + *p1) {
	if(p2-p1==0) throw std::range_error("Blok je prazan");
	//ovo ispod je ruznije iako bi radilo, al eto ljepse je sa auto
	//kad vec moramo dodijeliti pocetnu vrijednost sumi
	//typename std::remove_reference<decltype(*p1)>::type suma=*p1;
	auto suma=(*p1); 
	p1++;
	/* ovdje moze i ne mora referenca - za ovaj decltype*/
	std::for_each(p1,p2,[&suma](typename std::remove_reference<decltype(*p1)>::type a)->void {
		suma+=a;
	});
	return suma;
}
int main ()
{
	return 0;
}

