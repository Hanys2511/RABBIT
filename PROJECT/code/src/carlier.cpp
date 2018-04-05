#include "carlier.h"
#include "proces.h"
#include "permutacja.h"

#include <memory>
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>


void wczytaj_z_pliku(int schrag, permutacja& optymalna)
{
	int n = -1;
	std::fstream plik;
	std::string nazwa_pliku { "bin/SCHRAGE" };
	nazwa_pliku += std::to_string(schrag);
	nazwa_pliku += ".DAT";
	plik.open(nazwa_pliku, std::ios::in);
	if (plik.good()) {
		plik >> n;
		int dane1, dane2, dane3;
		for (int i=0; i < n; ++i) {
			plik >> dane1;
			plik >> dane2;
			plik >> dane3;
			optymalna.procesy.push_back(std::make_shared<proces>(dane1, dane2, dane3));
		}
		plik.close();
	} else {
		std::cout << "Nie ma takiego Jacka" << std::endl;
	}
	optymalna.n = n;
}

void schrage(permutacja& optymalna)
{
	int t = 1, Cmax = 1;
	int cmax;
	int pozycja = 0;
	auto cmp = []( const std::shared_ptr<proces>& left, const std::shared_ptr<proces>& right) { return (left->Rpi > right->Rpi); };
	std::priority_queue<std::shared_ptr<proces>, std::vector<std::shared_ptr<proces>>, decltype(cmp)> N(cmp);
	for (auto it: optymalna.procesy) {
		N.push(it);
	}
	optymalna.procesy.clear();
	auto cmp2 = []( const std::shared_ptr<proces>& left, const std::shared_ptr<proces>& right) { return (left->Qpi < right->Qpi); };
	std::priority_queue<std::shared_ptr<proces>, std::vector<std::shared_ptr<proces>>, decltype(cmp2)> G(cmp2);
	std::shared_ptr<proces> result;
	while (!G.empty() || !N.empty()) {
		if(!N.empty()) {
			result = N.top();
			while(!N.empty() && result->Rpi <= t) {
				G.push(result);
				N.pop(); //jak znajdzie to usun ten proces z nieuszeregowanych
				if(!N.empty()) {
					result = N.top();
				}
			}
		}
		if (G.empty() && !N.empty()) { //jezeli nic nie znalazł a w nieuszeregowanych są jeszcze jakies procesy
			t = N.top()->Rpi;  // to t = pierwszy.RPi
		} else {
			result = G.top();
			result->Cpi = t;
			t = t + G.top()->Ppi; //t=stary t+ppi
			cmax = G.top()->Qpi + t;
			if (cmax >= Cmax) {
				Cmax = cmax; //Cmax=t^+qpi (chyba, ze wieksze jest Cmax stare)
				optymalna.b = pozycja;
			}
			optymalna.procesy.push_back(result);
			G.pop(); //usuwa z gotowych
			pozycja++;
		}
	}
	optymalna.Cmax = Cmax;
}

int prmtS(const permutacja optymalna)
{
	int t = 1, Cmax = 1;
	auto cmp = []( const std::shared_ptr<proces>& left, const std::shared_ptr<proces>& right) { return (left->Rpi > right->Rpi); };
	std::priority_queue<std::shared_ptr<proces>, std::vector<std::shared_ptr<proces>>, decltype(cmp)> N(cmp);
	for (auto it: optymalna.procesy) {
		N.push(std::make_shared<proces>(it.get()));
	}
	auto cmp2 = []( const std::shared_ptr<proces>& left, const std::shared_ptr<proces>& right) { return (left->Qpi < right->Qpi); };
	std::priority_queue<std::shared_ptr<proces>, std::vector<std::shared_ptr<proces>>, decltype(cmp2)> G(cmp2);
	std::shared_ptr<proces> result;
	std::shared_ptr<proces> aktualne;
	while (!G.empty() || !N.empty()) {
		if(!N.empty()) {
			result = N.top();
			while(!N.empty() && result->Rpi <= t) {
				G.push(result);
				N.pop(); //jak znajdzie to usun ten proces z nieuszeregowanych
				if (aktualne) {
					if (aktualne->Qpi < (G.top()->Qpi)) {
						aktualne->Ppi = t - G.top()->Rpi;
						t = G.top()->Rpi;
						if (aktualne->Ppi > 0) {
							G.push(aktualne);
						}
					}
				}
				if(!N.empty()) {
					result = N.top();;
				}
			}
		}
		if (G.empty() && !N.empty()) { //jezeli nic nie znalazł a w nieuszeregowanych są jeszcze jakies procesy
			t = N.top()->Rpi;  // to t = pierwszy.RPi
		} else {
			aktualne = G.top();
			t = t + G.top()->Ppi; //t=stary t+ppi
			Cmax = std::max(Cmax, G.top()->Qpi + t); //Cmax=t^+qpi (chyba, ze wieksze jest Cmax stare)
			G.pop(); //usuwa z gotowych
		}
	}
	return Cmax;
}

int start(int carlierr)
{
	permutacja obecna;
	wczytaj_z_pliku(carlierr, obecna);
	carlier(obecna);
	return obecna.Cmax;
}

void carlier(permutacja& obecna)
{
	schrage(obecna);
	obecna.wyznacz_a();
	if (obecna.znajdz_zadanie_interferencyjne())
	{
		int rprim = obecna.wyznacz_rprim();
		int pprim = obecna.wyznacz_pprim();
		int qprim = obecna.wyznacz_qprim();
		std::shared_ptr<proces> stary = obecna.procesy[obecna.c];

		int stare_rpi = stary->Rpi;
		stary->Rpi = std::max(stary->Rpi, rprim + pprim);
		int LB { prmtS(obecna) };
		if (LB < obecna.Cmax)
		{
			carlier(obecna);
		}
		stary->Rpi = stare_rpi;

		int stare_qpi = stary->Qpi;
		stary->Qpi = std::max(stary->Qpi, qprim + pprim);
		LB = prmtS(obecna);
		if (LB < obecna.Cmax)
		{
			carlier(obecna);
		}
		stary->Qpi = stare_qpi;
	}
}
