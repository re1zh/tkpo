#include "Property.h"

// Property
Property::Property(string type, double area, int residents, int yearBuilt, double wearAndTear)
    : type(type), area(area), residents(residents), yearBuilt(yearBuilt), wearAndTear(wearAndTear) {}

string Property::getType() const {
    return type;
}

int Property::getYearBuilt() const {
    return yearBuilt;
}

int Property::getResidents() const {
    return residents;
}

double Property::getArea() const {
    return area;
}

// Apartment
Apartment::Apartment(double area, int residents, int yearBuilt, double wearAndTear)
    : Property("Аппартаменты", area, residents, yearBuilt, wearAndTear) {}

double Apartment::calculateBaseRate() const {
    return 5 * (1 - wearAndTear / 100);
}

// Townhouse
Townhouse::Townhouse(double area, int residents, int yearBuilt, double wearAndTear)
    : Property("Таун-хаус", area, residents, yearBuilt, wearAndTear) {}

double Townhouse::calculateBaseRate() const {
    return 7 * (1 - wearAndTear / 100);
}

// Cottage
Cottage::Cottage(double area, int residents, int yearBuilt, double wearAndTear)
    : Property("Коттедж", area, residents, yearBuilt, wearAndTear) {}

double Cottage::calculateBaseRate() const {
    return 9 * (1 - wearAndTear / 100);
}