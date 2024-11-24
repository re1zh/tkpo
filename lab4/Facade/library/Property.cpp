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
    : Property("Apartment", area, residents, yearBuilt, wearAndTear) {}

double Apartment::calculateBaseRate() const {
    return area * 5 - wearAndTear * 1.2;
}

// Townhouse
Townhouse::Townhouse(double area, int residents, int yearBuilt, double wearAndTear)
    : Property("Townhouse", area, residents, yearBuilt, wearAndTear) {}

double Townhouse::calculateBaseRate() const {
    return area * 7 - wearAndTear * 1.5;
}

// Cottage
Cottage::Cottage(double area, int residents, int yearBuilt, double wearAndTear)
    : Property("Cottage", area, residents, yearBuilt, wearAndTear) {}

double Cottage::calculateBaseRate() const {
    return area * 10 - wearAndTear * 2;
}