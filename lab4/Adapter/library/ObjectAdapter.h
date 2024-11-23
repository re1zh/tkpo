#ifndef OBJECTADAPTER_H
#define OBJECTADAPTER_H

#include "Adapter.h"
#include "GasBalloon.h"

using namespace std;

class ObjectAdapter : public Adapter {
    public:
        ObjectAdapter(GasBalloon* gasBalloon);
        double CalculateDp(int T0, int dT) override;
        void ModifMass(double dm) override;
        string GetData() override;
    private:
        GasBalloon* balloon;
};

#endif //OBJECTADAPTER_H
