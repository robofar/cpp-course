#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>

std::string IzvrniBezRazmaka(std::string s) {
	std::string novi;
	/* Obrnuti iteratori i umetaci(inserteri) */
	std::remove_copy(s.rbegin(),s.rend(),std::back_inserter(novi),' '); 
	return novi;
}
int main ()
{
	std::cout<<IzvrniBezRazmaka("Danas je lijep dan!");
	return 0;
}