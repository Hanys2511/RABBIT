#pragma once

#include "permutacja.h"

#include <iostream>
#include <memory>

void wczytaj_z_pliku(int schrag, permutacja& optymalna);
void schrage(permutacja& obecna);
int start(int n);
int prmtS(const permutacja optymalna);
void carlier(permutacja& obecna);
