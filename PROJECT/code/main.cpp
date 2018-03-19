#include "src/carlier.h"

#include <iostream>

int main()
{
	int schrag = 1;
	std::cout << "Który Schrage?:" << std::endl;
	std::cin >> schrag;
	std::cout << "Wynik: " << start(schrag) << std::endl;
	return 1;
}
