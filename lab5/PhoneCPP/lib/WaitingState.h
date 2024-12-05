#ifndef WAITINGSTATE_H
#define WAITINGSTATE_H

#include "PhoneState.h"

class WaitingState : public PhoneState {
public:
    void Call(Phone& phone, const string& number) override;
    void ReceiveCall(Phone& phone) override;
    void EndCall(Phone& phone) override;
    void AddBalance(Phone& phone, double amount) override;
};

#endif //WAITINGSTATE_H
