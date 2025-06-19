#pragma once
#include "Building.h"

class City {
public:
	City(unsigned n, unsigned m);

	void addBuilding(unsigned x, unsigned y, const Building& building);

	void info() const;
	void info(std::ostream& os, unsigned x, unsigned y) const;
	void info(unsigned x, unsigned y, std::string name) const;

	friend std::istream& operator>>(std::istream& is, City& city);
	friend std::ostream& operator<<(std::ostream& os, const City& city);
private:
	unsigned n;
	unsigned m;
	std::vector<std::vector<Building>> buildings;
};

 