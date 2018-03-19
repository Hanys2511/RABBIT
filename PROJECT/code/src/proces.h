#pragma once

#include <memory>

class proces {
public:
	proces(int Rpi_, int Ppi_, int Qpi_);
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
