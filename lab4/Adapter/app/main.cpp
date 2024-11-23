#include <iostream>
#include "ObjectAdapter.h"
#include "GasBalloon.h"

using namespace std;

int main() {
    GasBalloon* balloon = new GasBalloon(1.0, 2.0, 0.028);
    Adapter* adapter = new ObjectAdapter(balloon);
    cout << "Изначальные данные: " << adapter->GetData() << endl;

    double dP = adapter->CalculateDp(300, 50);
    cout << "Изменение давления (dP): " << dP << " Pa" << endl;

    adapter->ModifMass(0.5);
    cout << "Данные после изменения: " << adapter->GetData() << endl;

    delete adapter;
    delete balloon;

    return 0;
}