#pragma once

#include "proces.h"

#include <iostream>
#include <memory>
#include <vector>

class permutacja
{
public:
	permutacja() = default;

	permutacja(const permutacja& other)
	{
		std::cout<<"kopy"<<std::endl;
//		memcpy ( this->procesy, other.procesy, other.procesy.size() );
		std::copy(other.procesy.begin(), other.procesy.end(),
					  std::back_inserter(this->procesy));
		this->Cmax = other.Cmax;
		this->a = other.a;
		this-> b = other.b;
		this-> c = other.c;
		this->n = other.n;
	}
	permutacja& operator=(const permutacja& other) = delete;
	permutacja(permutacja&& other) = delete;
	permutacja& operator=(permutacja&& other) = delete;

	void blok_a_b()
	{
		int aktualnyMax=0;
		for (int i=n-1; i >-1; i--) {														//przejrzyj listeZadan. jezeli moment rozpoczecia realizacji+r+q = Cmax,
			if (procesy[i]->Cpi+procesy[i]->Ppi+procesy[i]->Qpi > aktualnyMax) {		//to mamy zadanie, ktore konczy caly proces
				b=i;
				aktualnyMax=procesy[i]->Cpi+procesy[i]->Ppi+procesy[i]->Qpi;
			}
		}
		int suma_p = 0;
		for (int i = 0; i <= b; i++) {
			suma_p += procesy[i]->Ppi;
		}
		a=0;
		while ((a<n) && (aktualnyMax-procesy[b]->Qpi != procesy[a]->Rpi+suma_p) ){
			suma_p=suma_p-procesy[a]->Ppi;
			a++;
		}
		std::cout << "A: " << a << "B " << b << std::endl;
	}

	int znajdz_zadanie_interferencyjne()
	{
		bool znaleziono { false };

		for(int i=b-1; i>=a; i--) {
			if (procesy[i]->Qpi < procesy[b]->Qpi) {
				znaleziono=true;
				c=i;
				std::cout<< "c "<< c <<std::endl;
				break;
			}
		}
		if (znaleziono==true)
			return 1;
		else
			return 0;
	}

	int wyznacz_pprim()
	{
		int pprim=0;

		for (int i=c+1; i<=b; i++) {
			pprim+=procesy[i]->Ppi;
		}

		return pprim;
	}

	int wyznacz_rprim()
	{
		int rprim=procesy[c+1]->Rpi;

		for (int i=c+1; i<=b; i++) {
			if (procesy[i]->Rpi < rprim)
				rprim=procesy[i]->Rpi;
		}

		return rprim;
	}

	int wyznacz_qprim()
	{
		int qprim=procesy[c+1]->Qpi;

		for (int i=c+1; i<=b; i++) {
			if (procesy[i]->Qpi<qprim)
				qprim=procesy[i]->Qpi;
		}
		return qprim;
	}

	std::vector<std::shared_ptr<proces>> procesy;
	int Cmax;
	int a;
	int b;
	int c;
	int n;
};
