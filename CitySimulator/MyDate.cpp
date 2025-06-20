#include "MyDate.h"
#include <stdexcept>

MyDate::MyDate() {
    std::time_t t = std::time(nullptr);
    startDate = *std::localtime(&t);
    currentDate = startDate;
}

void MyDate::step(int n) {
    if (daysPassed + n < 0) {
        throw std::out_of_range("Cannot go before the start date.");
    }

    daysPassed += n;
    currentDate.tm_mday += n;
    std::mktime(&currentDate);
}

int MyDate::getDay() const { return currentDate.tm_mday; }
bool MyDate::isFirstDay() const { return currentDate.tm_mday == 1; }

std::string MyDate::getStartDateString() const {
    char buffer[10 + 1];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &startDate);
    return std::string(buffer);
}

unsigned MyDate::getDaysPassed() const
{
    return daysPassed;
}

bool MyDate::isLastDay() const {
    std::tm next = currentDate;
    next.tm_mday += 1;
    std::mktime(&next);

    return next.tm_mon != currentDate.tm_mon;
}
