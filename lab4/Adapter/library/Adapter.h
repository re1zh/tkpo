#ifndef ADAPTER_H
#define ADAPTER_H

#include <string>

using namespace std;

class Adapter {
    public:
        virtual double CalculateDp(int T0, int dT) = 0;
        virtual void ModifMass(double dm) = 0;
        virtual string GetData() = 0;
        virtual ~Adapter() = default;
};

#endif //ADAPTER_H
