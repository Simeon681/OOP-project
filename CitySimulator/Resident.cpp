#include "Resident.h"

Resident::Resident(const std::string& name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary, uint16_t rent)
	: name(name),
	profession(profession),
	currentValues(happiness, money, life),
	salary(salary),
	rent(rent) 
{
	residentHistory.push_back(currentValues);
}

void Resident::dailyRoutine(bool isFirstDay, uint16_t rent) {
	currentValues.addHistory("Getting up.");
	if (isFirstDay) {
		if (currentValues.getMoney() - rent < 0) {
			currentValues.setMoney(0);
		}
		else {
			currentValues.setMoney(currentValues.getMoney() - rent);
		}
		currentValues.addHistory(" Paid rent: -" + std::to_string(rent) + "lv");
	}

	// const value
	if (currentValues.getMoney() - 50 < 0) {
		currentValues.setMoney(0);
	}
	else {
		currentValues.setMoney(currentValues.getMoney() - 50);
	}
	currentValues.addHistory(" Food: -50lv. Sleep.");
	residentHistory.push_back(currentValues);
}

void Resident::monthlyRoutine()
{
	currentValues.setMoney(currentValues.getMoney() + salary);
	currentValues.addHistory(" Received salary as " + getJob() + " : +" + std::to_string(salary));
	monthlyLife();
}

void Resident::saveValues() { residentHistory.push_back(currentValues); }

const std::string& Resident::getName() const { return name; }
uint16_t Resident::getSalary() const { return salary; }
uint16_t Resident::getRent() const { return rent; }

std::istream& operator>>(std::istream& is, Resident& resident)
{
	std::string job;
	std::getline(is, resident.name);
	std::getline(is, job);
	//resident.profession = resident.stringToProfession(job);
	is >> resident.currentValues;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Resident& resident)
{
	return os << resident.name << std::endl << resident.getJob() << std::endl << resident.currentValues;
}
