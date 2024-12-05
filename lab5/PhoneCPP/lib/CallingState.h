#ifndef CALLINGSTATE_H
#define CALLINGSTATE_H

#include "PhoneState.h"

class CallingState : public PhoneState {
public:
    void Call(Phone& phone, const string& number) override;
    void ReceiveCall(Phone& phone) override;
    void EndCall(Phone& phone) override;
    void AddBalance(Phone& phone, double amount) override;
};

#endif //CALLINGSTATE_H
