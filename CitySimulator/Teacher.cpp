#include "Teacher.h"

Teacher::Teacher(const std::string name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary)
    : Resident(name, profession, happiness, money, life, salary)
{}

std::string Teacher::getJob() const { return "Teacher"; }

void Teacher::monthlyLife()
{
    currentValues.setHappiness(std::min(currentValues.getHappiness() + 1, 100));
    currentValues.addHistory("Happiness: " + std::to_string(currentValues.getHappiness()));
}

Teacher* Teacher::clone() const { return new Teacher(*this); }
