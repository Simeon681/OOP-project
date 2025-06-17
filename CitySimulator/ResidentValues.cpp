#include "ResidentValues.h"

ResidentValues::ResidentValues() 
    : happiness(rand() % 101),
    money(0),
    life(rand() % 101)
{}

ResidentValues::ResidentValues(uint8_t happiness, unsigned money, uint8_t life)
    : happiness(happiness), money(money), life(life) {}

uint8_t ResidentValues::getHappiness() const { return happiness; }
unsigned ResidentValues::getMoney() const { return money; }
uint8_t ResidentValues::getLife() const { return life; }
const std::vector<std::string>& ResidentValues::getHistory() const { return history; }

void ResidentValues::setHappiness(uint8_t happiness) { this->happiness = happiness; }
void ResidentValues::setMoney(unsigned money) { this->money = money; }
void ResidentValues::setLife(uint8_t life) { this->life = life; }
void ResidentValues::addHistory(const std::string& history) { this->history.push_back(history); }

std::ostream& operator<<(std::ostream& os, const ResidentValues& values)
{
    os << static_cast<int>(values.happiness) << ' ' << values.money << ' ' 
        << static_cast<int>(values.life) << ' ' << values.history.size() << std::endl;

    for (unsigned i = 0; i < values.history.size(); i++) {
        os << values.history.at(i) << std::endl;
    }

    return os;
}

std::istream& operator>>(std::istream& is, ResidentValues& values)
{
    unsigned historySize;
    is >> values.happiness >> values.money >> values.life >> historySize;
    
    for (unsigned i = 0; i < historySize; i++) {
        std::string line;
        std::getline(is, line);
        values.history.push_back(line);
    }

    return is;
}
