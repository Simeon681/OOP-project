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
	Building(BuildingType type, unsigned capacity);
	Building(const Building&) = delete;
	Building& operator=(const Building&) = delete;
	Building(Building&&) = default;
	Building& operator=(Building&&) = default;

	std::string getType() const;
	unsigned getCapacity() const;
	const std::vector<std::unique_ptr<Resident>>& getResidents() const;

	void setType(const std::string& type);
	void setBaseRent();
	void setRent(unsigned x, unsigned y, unsigned width, unsigned height);

	bool addResident(std::unique_ptr<Resident> resident);
	bool removeResident(const std::string& name);

	void stepBackBuilding();
	unsigned stepForwardBuilding(bool isFirstDay, bool isLastDay);

	friend std::istream& operator>>(std::istream& is, Building& building);
	friend std::ostream& operator<<(std::ostream& os, const Building& building);
private:
	BuildingType type;
	unsigned capacity;
	uint16_t rent;
	std::vector<std::unique_ptr<Resident>> residents;
};

