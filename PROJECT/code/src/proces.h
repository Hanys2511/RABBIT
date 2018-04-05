#pragma once

#include <memory>
#include <iostream>

class proces {
public:
	proces(int Rpi_, int Ppi_, int Qpi_):
		Rpi(Rpi_),
		Ppi(Ppi_),
		Qpi(Qpi_)
	{}

	proces(proces* other)
	{
		this->Rpi = other->Rpi;
		this->Ppi = other->Ppi;
		this->Qpi = other->Qpi;
		this->Cpi = other->Cpi;
	}

	int Rpi;
	int Ppi;
	int Qpi;
	int Cpi;
};
