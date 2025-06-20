#pragma once
#include "Resident.h"

class Teacher : public Resident
{
public:
	Teacher(const std::string name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary);
	
	std::string getJob() const override;

	void monthlyLife() override;

	Teacher* clone() const override;
};

