#pragma once
#include "Resident.h"

class Unemployed : public Resident
{
public:
	Unemployed(const std::string name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary);

	std::string getJob() const override;

	void monthlyLife() override;

	Unemployed* clone() const override;
};
