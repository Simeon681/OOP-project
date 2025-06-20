#include "Building.h"

Building::Building(BuildingType type, unsigned capacity) 
	: type(type),
    capacity(capacity)
{
	setBaseRent();
}

std::string Building::getType() const
{
    switch (type) {
        case BuildingType::MODERN: return "Modern";
        case BuildingType::PANEL: return "Panel";
        case BuildingType::DORMITORY: return "Dormitory";
        default: throw std::logic_error("Unknown type of building!");
    }
}

void Building::setType(const std::string& type)
{
    if (type == "Modern") {
        this->type = BuildingType::MODERN;
    }
    else if (type == "Panel") {
        this->type = BuildingType::PANEL;
    }
    else if (type == "Dormitory") {
       this->type = BuildingType::DORMITORY;
    }
    else {
        throw std::logic_error("Unknown type of building!");
    }
}

void Building::setBaseRent()
{
    switch (type) {
        case BuildingType::MODERN: rent = 1000; break;
        case BuildingType::PANEL: rent = 500; break;
        case BuildingType::DORMITORY: rent = 40; break;
        default: throw std::logic_error("Unknown type of building!");
    }
}

void Building::setRent(unsigned x, unsigned y, unsigned width, unsigned height) // do it more abstract
{
    double centerX = width / 2.0;
	double centerY = height / 2.0;

    double distance = std::sqrt(std::pow(x - centerX, 2) + std::pow(y - centerY, 2));

    double minDistance = std::min(static_cast<double>(width), static_cast<double>(height)) / 8.0;
    if (distance <= minDistance) {
        rent *= 2.5; 
	} 
    if (distance > minDistance * 6.0) {
        rent *= 0.8;
    }
}

unsigned Building::getCapacity() const { return capacity; }
const std::vector<std::unique_ptr<Resident>>& Building::getResidents() const { return residents; }

bool Building::addResident(std::unique_ptr<Resident> resident)
{
	if (capacity < residents.size()) {
		residents.push_back(std::move(resident));

		return true;
	}
	return false;
}

bool Building::removeResident(const std::string& name)  
{  
    unsigned size = residents.size();  
    for (unsigned i = 0; i < size; i++) {  
        if (residents[i]->getName() == name) {
            residents.erase(residents.begin() + i);

            return true;  
        }  
    }  
    return false;  
}

void Building::stepBackBuilding()
{
    for (unsigned i = 0; i < capacity; i++) {
        if (residents[i]->stepBack() == 0) {
			residents.erase(residents.begin() + i);
        }
	}
}

unsigned Building::stepForwardBuilding(bool isFirstDay, bool isLastDay)
{
	unsigned dead = 0;
    for (unsigned i = 0; i < capacity; i++) {
        residents[i]->dailyRoutine(isFirstDay, isLastDay, rent);
        if (residents[i].get()->isDead()) {
            dead++;
			residents.erase(residents.begin() + i);
        }
    }

    return dead;
}

std::istream& operator>>(std::istream& is, Building& building)
{
    std::string type;
    unsigned size;
    is >> type;
    
	building.setType(type);
	is >> building.capacity >> size;
    
 //   for (unsigned i = 0; i < size; i++) {
 //       //std::unique_ptr<Resident> resident = std::make_unique<Resident>();
 //       is >> *resident;
 //       building.addResident(std::move(resident));
	//}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Building& building)
{
    os << building.getType() << ' ' << building.capacity << ' ' << building.residents.size() << std::endl;
    
    unsigned size = building.residents.size();
    for (unsigned i = 0; i < size; i++) {
		os << *building.residents[i];
    }
    
    return os;
}
