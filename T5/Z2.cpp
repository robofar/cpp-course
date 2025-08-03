#include <iostream>
template <typename IterPok1, typename IterPok2>
IterPok2 RazmijeniBlokove(IterPok1 p1,IterPok1 p2,IterPok2 p3) {
	while(p1!=p2) {
		typename std::remove_reference<decltype(*p1)>::type pomocna = *p1; //ili jednostavno auto pomocna = *p1;
		*p1 = *p3;
		*p3 = pomocna;
		p1++;
		p3++;
	}
	return p3;
}
int main ()
{
	return 0;
}