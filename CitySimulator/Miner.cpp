#include "Miner.h"

Miner::Miner(const std::string name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary, uint16_t rent)
    : Resident(name, profession, happiness, money, life, salary, rent)
{}

std::string Miner::getJob() const { return "Miner"; }

void Miner::monthlyLife()
{
    currentValues.setLife(std::max(0, currentValues.getLife() - 1));
    currentValues.addHistory("Life: " + std::to_string(currentValues.getLife()));
}

Miner* Miner::clone() const { return new Miner(*this); }
