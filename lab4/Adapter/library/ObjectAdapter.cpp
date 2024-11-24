#include "ObjectAdapter.h"

ObjectAdapter::ObjectAdapter(GasBalloon* gasBalloon) : balloon(gasBalloon) {}

double ObjectAdapter::CalculateDp(int T0, int dT) {
    double P0 = balloon->GetPressure(T0);
    double P1 = balloon->GetPressure(T0 + dT);
    return P1 - P0;
}

void ObjectAdapter::ModifMass(double dm) {
    balloon->Mass += dm;
}

string ObjectAdapter::GetData() {
    return balloon->ToString();
}