#include "Generator.h"

void Generator::generateCity(City& city)
{
	unsigned height = city.getHeight();
	unsigned width = city.getWidth();
	unsigned numberOfBuildings = 1 + rand() % (height + width);
    for (unsigned i = 0; i < numberOfBuildings; ++i) {
        Building building = buildingFactory(generateBuildingType(), 1 + rand() % 100);
        city.addBuilding(rand() % height, rand() % width, building);
	}

    for (unsigned i = 0; i < height; ++i) {
        for (unsigned j = 0; j < width; ++j) {
            if (city.hasBuilding(i, j)) {
                city.getBuilding(i, j).setRent(i, j, height, width);
            }
        }
	}

	std::cout << city.getDate().getStartDateString() << std::endl;   
}

Profession Generator::generateProfession() { return static_cast<Profession>(rand() % 4); }
BuildingType Generator::generateBuildingType() { return static_cast<BuildingType>(rand() % 3); }
std::string Generator::generateName() { return names[rand() % names.size()]; }

ResidentValues Generator::generateResidentValues()
{
    return ResidentValues(1 + rand() % 100, 100 + rand() % 901, 1 + rand() % 100);
}

std::unique_ptr<Resident> Generator::residentFactory(const std::string& name, Profession profession, const ResidentValues& values)
{
    switch (profession) {
        case Profession::TEACHER: 
            return std::make_unique<Teacher>(name, profession, values.getHappiness(), values.getMoney(), values.getLife(), 1200 + rand() % 101);
        case Profession::DEVELOPER: 
            return std::make_unique<Developer>(name, profession, values.getHappiness(), values.getMoney(), values.getLife(), 1200 + rand() % 101);
        case Profession::MINER: 
            return std::make_unique<Miner>(name, profession, values.getHappiness(), values.getMoney(), values.getLife(), 1200 + rand() % 101);
        case Profession::UNEMPLOYED: 
            return std::make_unique<Unemployed>(name, profession, values.getHappiness(), values.getMoney(), values.getLife(), 1200 + rand() % 101);
        default: 
            throw std::logic_error("Unknown job type");
    }
}

Building Generator::buildingFactory(BuildingType type, unsigned capacity)
{
	Building building(type, capacity);

	unsigned residentsCount = 1 + rand() % capacity;
    for (unsigned i = 0; i < residentsCount; ++i) {
        std::unique_ptr<Resident> resident = residentFactory(generateName(), generateProfession(), generateResidentValues());
        building.addResident(std::move(resident));
	}
}
