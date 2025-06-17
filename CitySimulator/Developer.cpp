#include "Developer.h"

Developer::Developer(const std::string name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary, uint16_t rent)
	: Resident(name, profession, happiness, money, life, salary, rent)
{}

std::string Developer::getJob() const { return "Developer"; }

void Developer::monthlyLife()
{
	currentValues.setHappiness(std::max(0, currentValues.getHappiness() - 1));
	currentValues.addHistory("Happiness: " + std::to_string(currentValues.getHappiness()));
}

Developer* Developer::clone() const { return new Developer(*this); }
