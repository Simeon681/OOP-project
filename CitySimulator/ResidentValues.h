#pragma once
#include <iostream>
#include <vector>
#include <string>

class ResidentValues {
public:
	ResidentValues();
	ResidentValues(uint8_t happiness, unsigned money, uint8_t life);

	uint8_t getHappiness() const;
	unsigned getMoney() const;
	uint8_t getLife() const;
	const std::vector<std::string>& getHistory() const;

	void setHappiness(uint8_t happiness);
	void setMoney(unsigned money);
	void setLife(uint8_t life);
	void addHistory(const std::string& history);

	friend std::ostream& operator<<(std::ostream& os, const ResidentValues& values);
	friend std::istream& operator>>(std::istream& is, ResidentValues& values);
private:
	uint8_t happiness;
	unsigned money;
	uint8_t life;
	std::vector<std::string> history;
};
