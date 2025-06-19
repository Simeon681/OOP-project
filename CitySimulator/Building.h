#pragma once
#include "Resident.h"

enum class BuildingType {
	MODERN,
	PANEL,
	DORMITORY
};

class Building
{
public:
	Building() = default;
	Building(BuildingType type, unsigned x, unsigned y, unsigned capacity);

	std::string getType() const;
	unsigned getCapacity() const;
	unsigned getX() const;
	unsigned getY() const;
	const std::vector<std::unique_ptr<Resident>>& getResidents() const;

	void setType(const std::string& type);
	void setBaseRent();
	void setRent(unsigned width, unsigned height);

	bool addResident(std::unique_ptr<Resident> resident);
	bool removeResident(const std::string& name);

	friend std::istream& operator>>(std::istream& is, Building& building);
	friend std::ostream& operator<<(std::ostream& os, const Building& building);
private:
	BuildingType type;
	unsigned x;
	unsigned y;
	unsigned capacity;
	uint16_t rent;
	std::vector<std::unique_ptr<Resident>> residents;
};

