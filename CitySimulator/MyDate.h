#pragma once
#include <ctime>
#include <string>
#pragma warning(disable:4996)

class MyDate {
public:
    MyDate();

    void step(int n);
    int getDay() const;
    std::string getStartDateString() const;
	unsigned getDaysPassed() const;
    bool isFirstDay() const;
    bool isLastDay() const;
private:
    std::tm startDate{};
    std::tm currentDate{};
    unsigned daysPassed = 0;
};
