#include "Facade.h"

double InsuranceFacade::calculatePremium(Property& property, int insuranceTerm) {
    double termCoefficient = insuranceTerm * 1.0;
    double ageCoefficient = 2024 - property.getYearBuilt() > 30 ? 1.3 : 1.0;
    double residentsCoefficient = property.getResidents() > 3 ? 1.1 : 1.0;

    double premium = property.calculateBaseRate() * property.getArea() * termCoefficient * ageCoefficient * residentsCoefficient;

    return std::max(premium, 1000.0);
}