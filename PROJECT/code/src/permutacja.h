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
		std::copy(other.procesy.begin(), other.procesy.end(),
					  std::back_inserter(this->procesy));
		this->Cmax = other.Cmax;
		this->a = other.a;
		this->b = other.b;
		this->c = other.c;
		this->n = other.n;
	}
	permutacja& operator=(const permutacja& other) = delete;
	permutacja(permutacja&& other) = delete;
	permutacja& operator=(permutacja&& other) = delete;

	void wyznacz_a()
	{
		int suma_p = 0;
		for (int i = 0; i <= b; i++) {
			suma_p += procesy[i]->Ppi;
		}
		a=0;
		while ((a<b) && (Cmax-procesy[b]->Qpi != procesy[a]->Rpi+suma_p) ){
			suma_p=suma_p-procesy[a]->Ppi;
			a++;
		}
	}

	int znajdz_zadanie_interferencyjne()
	{
		bool znaleziono { false };

		for(int i=b-1; i>=a; i--) {
			if (procesy[i]->Qpi < procesy[b]->Qpi) {
				znaleziono=true;
				c=i;
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
