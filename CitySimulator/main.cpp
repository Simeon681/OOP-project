#include "City.h"
#include "Generator.h"
#include <fstream>

int main() {
	Generator generator;
    City* city = nullptr;
    std::string command;

    do {
        std::cout << ">> "; 
        std::cin >> command;

        if (command == "generate") {
            unsigned n, m;
            std::cin >> n >> m;
            delete city;
            city = new City(n, m);
			generator.generateCity(*city);
        }
        else if (command == "add") {
            unsigned x, y;
            std::string name, job;
            int happiness, money, life;

            std::cin >> x >> y >> name >> job >> happiness >> money >> life;

            if (!city) {
				throw std::runtime_error("No city created yet!");
            }
            else {
                std::unique_ptr<Resident> citizen = generator.residentFactory(name, Resident::stringToProfession(job), { happiness, money, life });
				bool success = city->getBuilding(x, y).addResident(std::move(citizen));
                std::cout << (success ? "Added." : "Failed to add") << std::endl;
            }

        }
        else if (command == "remove") {
            unsigned x, y;
            std::string name;
            std::cin >> x >> y >> name;

            if (!city) {
                throw std::runtime_error("No city created yet!");
            }
            else {
				bool removed = city->getBuilding(x, y).removeResident(name);
                std::cout << (removed ? "Removed." : "Failed to remove") << std::endl;
            }

        }
        else if (command == "step") {
            int n = 1;
            if (std::cin.peek() != '\n') {
                std::cin >> n;
            }

            if (!city) {
                throw std::runtime_error("No city created yet!");
            }
            else {
                if (n > 0) {
					city->cityStepForward(n);
				}
                else if (n < 0) {
					city->cityStepBack(-n);
                }
                else {
                    throw std::runtime_error("No city created yet!");
				}
            }   

        }
        else if (command == "info") {
            if (!city) {
                throw std::runtime_error("No city created yet!");
            }

            unsigned x, y;
            std::string name;

            if (std::cin.peek() != '\n') {
                std::cin >> x >> y;

                if (std::cin.peek() != '\n') {
                    std::cin >> name;

					city->info(x, y, name);
                }
                else {
					city->info(std::cout, x, y);
                }
            }
            else {
                city->info();
            }
        }
        else if (command == "save") {
            std::string filename;
            std::cin >> filename;

            if (!city) {
                throw std::runtime_error("No city created yet!");
            }
            else {
                std::ofstream ofs(filename);
                if (!ofs.is_open()) {
                    ofs << *city;
                }
                else {
					throw std::runtime_error("Failed to open file for saving!");
                }
            }

        }
        else if (command == "load") {
            std::string filename;
            std::cin >> filename;
            std::ifstream ifs(filename);
            if (!ifs.is_open()) {
				throw std::runtime_error("Failed to open file for loading!");
            }
            else {
                delete city;
                ifs >> *city;;
            }

        }
        else {
			throw std::runtime_error("Unknown command: " + command);
        }
    } while (true);

    delete city;
    return 0;
}
