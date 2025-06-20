#pragma once
#include "Teacher.h"
#include "Developer.h"
#include "Miner.h"
#include "Unemployed.h"
#include "City.h"


const std::vector<std::string> names = {
	"Simeon", "Ivan", "Maria", "Petar", "Viktoria" "Georgi", "Elena", "Stoyan", "Nikolay", "Dimitar"
};

class Generator
{
public:
	void generateCity(City& city);
	std::unique_ptr<Resident> residentFactory(const std::string& name, Profession profession, const ResidentValues& values);
private:
	Profession generateProfession();
	BuildingType generateBuildingType();
	std::string generateName();
	ResidentValues generateResidentValues();
	Building buildingFactory(BuildingType type, unsigned capacity);
};

