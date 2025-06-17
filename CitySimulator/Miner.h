#pragma once
#include "Resident.h"

class Miner : public Resident
{
public:
	Miner(const std::string name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary, uint16_t rent);

	std::string getJob() const override;

	void monthlyLife() override;

	Miner* clone() const override;
};

