#include "Unemployed.h"

Unemployed::Unemployed(const std::string name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary)
    : Resident(name, profession, happiness, money, life, salary)
{}

std::string Unemployed::getJob() const { return std::string(); }

void Unemployed::monthlyLife()
{
    currentValues.setLife(std::max(0, currentValues.getLife() - 1));
    currentValues.addHistory("Life: " + std::to_string(currentValues.getHappiness()));
}

Unemployed* Unemployed::clone() const { return new Unemployed(*this); }
