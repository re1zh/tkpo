#include "Facade.h"

double InsuranceFacade::calculatePremium(Property& property, int insuranceTerm) {
    double baseRate = 0.0;
    if (property.getType() == "Apartment") {
        baseRate = 5.0;
    } else if (property.getType() == "Townhouse") {
        baseRate = 6.0;
    } else if (property.getType() == "Cottage") {
        baseRate = 8.0;
    }

    double termCoefficient = insuranceTerm * 1.0;
    double ageCoefficient = (2024 - property.getYearBuilt() > 30) ? 1.3 : 1.0;
    double residentsCoefficient = (property.getResidents() > 3) ? 1.1 : 1.0;

    double premium = baseRate * property.getArea() * termCoefficient * ageCoefficient * residentsCoefficient;

    return std::max(premium, 1000.0);
}