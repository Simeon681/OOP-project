#pragma once
#include "Building.h"
#include "MyDate.h"

class City {
public:
	City(unsigned n, unsigned m);

	unsigned getHeight() const;
	unsigned getWidth() const;
	const Building& getBuilding(unsigned x, unsigned y) const;
	Building& getBuilding(unsigned x, unsigned y);
	const MyDate& getDate() const;
	const std::vector<std::vector<Building>>& getBuildings() const;

	void addBuilding(unsigned x, unsigned y, Building& building);
	bool hasBuilding(unsigned x, unsigned y) const;
	

	void info() const;
	void info(std::ostream& os, unsigned x, unsigned y) const;
	void info(unsigned x, unsigned y, std::string name) const;

	void cityStepBack(int n);
	unsigned cityStepForward(int n);

	friend std::istream& operator>>(std::istream& is, City& city);
	friend std::ostream& operator<<(std::ostream& os, const City& city);
private:
	unsigned n;
	unsigned m;
	std::vector<std::vector<Building>> buildings;
	MyDate date;
};

 