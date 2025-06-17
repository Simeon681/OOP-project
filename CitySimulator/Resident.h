#pragma once
#include "ResidentValues.h"	

enum class Profession {
	TEACHER,
	DEVELOPER,
	MINER,
	UNEMPLOYED
};

class Resident {
public:
	Resident(const std::string& name, Profession profession, uint8_t happiness, unsigned money, uint8_t life, uint16_t salary, uint16_t rent);
	virtual ~Resident() noexcept = default;

	const std::string& getName() const;
	uint16_t getSalary() const;
	uint16_t getRent() const;
	virtual std::string getJob() const = 0;
	//virtual Profession stringToProfession(const std::string& proffesion) const = 0;

	void dailyRoutine(bool isFirstDay, uint16_t rent);
	virtual void monthlyLife() = 0;
	void monthlyRoutine();

	void saveValues();

	virtual Resident* clone() const = 0;

	friend std::istream& operator>>(std::istream& is, Resident& resident);
	friend std::ostream& operator<<(std::ostream& os, const Resident& resident);
protected:
	std::string name;
	Profession profession;
	ResidentValues currentValues;
	std::vector<ResidentValues> residentHistory;
	uint16_t salary;
	uint16_t rent;
};

