#include "Resident.h"

Resident::Resident(const std::string& name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary)
	: name(name),
	profession(profession),
	currentValues(happiness, money, life),
	salary(salary)
{
	residentHistory.push_back(currentValues);
}

void Resident::dailyRoutine(bool isFirstDay, bool isLastDay, uint16_t rent) {
	if (isLastDay) {
		monthlyRoutine();
	}

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

bool Resident::stepBack()
{
	if (residentHistory.size() > 1) {
		residentHistory.pop_back();
		currentValues = residentHistory.back();
		return true;
	}

	return false;
}

bool Resident::isDead() const
{
	return currentValues.getHappiness() == 0 &&
		currentValues.getMoney() == 0 &&
		currentValues.getLife() == 0;
}

const std::string& Resident::getName() const { return name; }
uint16_t Resident::getSalary() const { return salary; }

Profession Resident::stringToProfession(const std::string& profession)
{
	if (profession == "Teacher") return Profession::TEACHER;
	else if (profession == "Developer") return Profession::DEVELOPER;
	else if (profession == "Miner") return Profession::MINER;
	else if (profession == "Unemployed") return Profession::UNEMPLOYED;
	else {
		throw std::invalid_argument("Unknown profession!");
	}
}

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
