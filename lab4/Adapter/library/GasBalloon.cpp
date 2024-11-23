#include "GasBalloon.h"
#include <sstream>

using namespace std;

GasBalloon::GasBalloon(double volume, double mass, double molar)
    : Volume(volume), Mass(mass), Molar(molar) {};

double GasBalloon::GetPressure(int T) const {
    const double R = 8.31;
    double n = Mass / Molar;
    return (n * R * T) / Volume;
}
double  GasBalloon::AmountOfMatter() const {
    return Mass / Molar;
}

string GasBalloon::ToString() const {
    ostringstream oss;
    oss << "Объем: " << Volume << " м^3, "
        << "Масса: " << Mass << " кг, "
        << "Молярная масса: " << Molar << " кг/моль" << endl;
    return oss.str();
}
