#ifndef BLOCKEDSTATE_H
#define BLOCKEDSTATE_H

#include "PhoneState.h"

class BlockedState : public PhoneState {
public:
    void Call(Phone& phone, const string& number) override;
    void ReceiveCall(Phone& phone) override;
    void EndCall(Phone& phone) override;
    void AddBalance(Phone& phone, double amount) override;
};

#endif //BLOCKEDSTATE_H
