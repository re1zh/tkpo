#ifndef GASBALLOON_H
#define GASBALLOON_H

#include <string>

using namespace std;

class GasBalloon {
    public:
        double Volume;
        double Mass;
        double Molar;

        GasBalloon(double volume, double mass, double molar);
        double GetPressure(int T) const;
        double AmountOfMatter() const;
        string ToString() const;
};

#endif //GASBALLOON_H
