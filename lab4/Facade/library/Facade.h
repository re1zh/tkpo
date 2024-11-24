#ifndef FACADE_H
#define FACADE_H

#include "Property.h"

class InsuranceFacade {
    public:
        static double calculatePremium(Property& property, int insuranceTerm);
};

#endif //FACADE_H
