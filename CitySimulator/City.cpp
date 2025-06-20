#include "City.h"

City::City(unsigned n, unsigned m) 
	: n(n), 
	m(m),
	date()
{}

unsigned City::getHeight() const { return n; }
unsigned City::getWidth() const { return m; }

const Building& City::getBuilding(unsigned x, unsigned y) const {
	if (x >= n || y >= m) {
		throw std::out_of_range("Invalid building coordinates");
	}
	return const_cast<Building&>(buildings[x][y]);
}

Building& City::getBuilding(unsigned x, unsigned y) {
	if (x >= n || y >= m) {
		throw std::out_of_range("Invalid building coordinates");
	}
	return const_cast<Building&>(buildings[x][y]);
}

const std::vector<std::vector<Building>>& City::getBuildings() const { return buildings; }
const MyDate& City::getDate() const { return date; }

void City::addBuilding(unsigned x, unsigned y, Building & building)
{
	if (x >= n || y >= m) {
		throw std::out_of_range("Invalid building coordinates");
	}

	if (building.getCapacity() == buildings.size()) {
		throw std::invalid_argument("Building capacity is reached");
	}

	if (hasBuilding(x, y)) {
		throw std::invalid_argument("Space already occupied by another building");
	}

	buildings[x][y] = std::move(building);;
}

bool City::hasBuilding(unsigned x, unsigned y) const
{
	return x < n && y < m && buildings[x][y].getCapacity() > 0;
}

void City::info() const
{
	std::cout << *this;
}

void City::info(std::ostream& os, unsigned x, unsigned y) const
{
	if (hasBuilding(x, y)) {
		std::cout << "No building at (" << x << ", " << y << ")!";
	} else {
		os << buildings[x][y];
	}
}

void City::info(unsigned x, unsigned y, std::string name) const
{	
	bool found = false;
	if (hasBuilding(x, y)) {
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

void City::cityStepBack(int n)
{
	n *= -1;
	for (unsigned i = 0; i < n; ++i) {
		for (unsigned x = 0; x < n; ++x) {
			for (unsigned y = 0; y < m; ++y) {
				if (hasBuilding(x, y)) {
					buildings[x][y].stepBackBuilding();
				}
			}
		}
		date.step(-1);
	}
}

unsigned City::cityStepForward(int n)
{
	unsigned dead = 0;
	for (unsigned i = 0; i < n; ++i) {
		for (unsigned x = 0; x < n; ++x) {
			for (unsigned y = 0; y < m; ++y) {
				if (hasBuilding(x, y)) {
					dead += buildings[x][y].stepForwardBuilding(date.isFirstDay(), date.isLastDay());
				}
			}
		}
		date.step(1);
	}

	return dead;
}

std::istream& operator>>(std::istream& is, City& city)
{
	unsigned numberOfBuildings;
	is >> city.n >> city.m >> numberOfBuildings;

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
