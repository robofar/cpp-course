#include <iostream>
#include <iomanip>
#include <cmath>
double TrapeznoPravilo(double (*fun)(double), double a, double b, int n) {
	double integral;
	double suma=0;
	for(int k=1;k<n;k++) {
		suma += fun(a+ (double(b-a)/n)*k);
	}
	integral = ((double((b-a))/n) * (0.5*fun(a) + 0.5*fun(b) + suma));
	return integral;
}
int main ()
{
	int n;
	std::cout<<"Unesite broj podintervala: ";
	std::cin>>n;
	std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose:"<<std::endl;
	std::cout<<"- Za funkciju sin x na intervalu (0,pi): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo(std::sin,0,4*atan(1),n)<<std::endl;
	std::cout<<"- Za funkciju x^3 na intervalu (0,10): "<<std::fixed<<std::setprecision(2)<<TrapeznoPravilo([](double x) -> double {return x*x*x;},0,10,n)<<std::endl;
	std::cout<<"- Za funkciju 1/x na intervalu (1,2): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo([](double x)->double{return 1/x;},1,2,n)<<std::endl;
	return 0;
}