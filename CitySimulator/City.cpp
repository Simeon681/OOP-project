#include "City.h"

City::City(unsigned n, unsigned m) 
	: n(n), 
	m(m),
	buildings(n, std::vector<Building>(m))
{}

void City::addBuilding(unsigned x, unsigned y, const Building & building)
{
	if (buildings[x][y].getCapacity() != 0) {
		throw std::invalid_argument("Space already occupied by another building");
	}

	buildings[x][y] = building;
}

void City::info() const
{
	std::cout << *this;
}

void City::info(std::ostream& os, unsigned x, unsigned y) const
{
	if (buildings[x][y].getCapacity() == 0) {
		std::cout << "No building at (" << x << ", " << y << ")!";
	} else {
		os << buildings[x][y];
	}
}

void City::info(unsigned x, unsigned y, std::string name) const
{	
	bool found = false;
	if (buildings[x][y].getCapacity() == 0) {
		std::cout << "No building at (" << x << ", " << y << ")!";
	}
	else {
		unsigned size = buildings[x][y].getResidents().size();
		for (unsigned i = 0; i < size; i++) {
			if (buildings[x][y].getResidents()[i].get()->getName() == name) {
				std::cout << buildings[x][y].getResidents()[i];
				found = true;
			}
		}
	}

	if (!found) {
		std::cout << "No resident with name " << name << " at (" << x << ", " << y << ")!";
	}
}

std::istream& operator>>(std::istream& is, City& city)
{
	unsigned numberOfBuildings;
	return is >> city.n >> city.m >> numberOfBuildings;

	if (numberOfBuildings != city.n * city.m) {
		throw std::invalid_argument("Invalid number of buildings");
	}

	for (unsigned i = 0; i < numberOfBuildings; i++) {
		Building building;
		unsigned x, y;
		is >> x >> y;
		is >> building;
		city.addBuilding(x, y, building);
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const City& city)
{
	os << city.n << " " << city.m << std::endl;
	for (unsigned i = 0; i < city.n; i++) {
		for (unsigned j = 0; j < city.m; j++) {
			city.info(os, i, j);
		}
	}

	return os;
}
