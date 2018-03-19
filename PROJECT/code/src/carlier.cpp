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
			Cmax = std::max(Cmax, G.top()->Qpi + t); //Cmax=t^+qpi (chyba, ze wieksze jest Cmax stare)
			optymalna.procesy.push_back(result);
			G.pop(); //usuwa z gotowych
		}
	}
	optymalna.Cmax = Cmax;
}

int prmtS(const permutacja optymalna)
{
	std::cout<<"prmtS"<<std::endl;
	for (auto it: optymalna.procesy)
	{
		std::cout<< it->Rpi << " " << it->Ppi << " " << it->Qpi << std::endl;
	}
	std::cout<<"prmtS ed"<<std::endl;
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
//	int UB = 1, LB = 1;
	permutacja obecna;
	wczytaj_z_pliku(carlierr, obecna);
//	schrage(obecna);
//	std::cout<<obecna.n<<std::endl;
	carlier(obecna);

	return obecna.Cmax;
}

void carlier(permutacja& obecna)
{
	schrage(obecna);
	std::cout<<obecna.n<<std::endl;
	obecna.blok_a_b();
	std::cout<<"jest a b"<<std::endl;
	if (obecna.znajdz_zadanie_interferencyjne())
	{
		std::cout<<"jest c"<<std::endl;
		int rprim = obecna.wyznacz_rprim();
		int pprim = obecna.wyznacz_pprim();
		int qprim = obecna.wyznacz_qprim();
		std::shared_ptr<proces> rc = obecna.procesy[obecna.c];
		int stare_rpi = rc->Rpi;
		std::cout<<"carlier"<<std::endl;
		for (auto it: obecna.procesy)
		{
			std::cout<< it->Rpi << " " << it->Ppi << " " << it->Qpi << std::endl;
		}
		std::cout<<"carlier ed"<<std::endl;
		std::cout<<"RPi "<<rc->Rpi<<std::endl;
		std::cout<<"PPi "<<obecna.procesy[obecna.b]->Ppi<<std::endl;
		std::cout<<"QPi "<<obecna.procesy[obecna.b]->Qpi<<std::endl;
		std::cout<<"CPi "<<obecna.procesy[obecna.b]->Cpi<<std::endl;
		std::cout<<"Rprim "<<rprim<<std::endl;
		std::cout<<"Pprim "<<pprim<<std::endl;
		rc->Rpi = std::max(rc->Rpi, rprim + pprim);
		int LB { prmtS(obecna) };
		if (LB < obecna.Cmax)
		{
			std::cout<<"r!!!!!!"<<obecna.Cmax<<std::endl;
			carlier(obecna);
		}
		rc->Rpi = stare_rpi;

		std::shared_ptr<proces> qc = obecna.procesy[obecna.c];
		int stare_qpi = qc->Qpi;
		qc->Qpi = std::max(qc->Qpi, qprim + pprim);
		LB = prmtS(obecna);
		if (LB < obecna.Cmax)
		{
			std::cout<<"q!!!!!!"<<obecna.Cmax<<std::endl;
			carlier(obecna);
		}
		qc->Qpi = stare_qpi;
	}
}
