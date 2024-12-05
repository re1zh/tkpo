#ifndef TALKINGSTATE_H
#define TALKINGSTATE_H

#include "PhoneState.h"

class TalkingState : public PhoneState {
public:
    void Call(Phone& phone, const string& number) override;
    void ReceiveCall(Phone& phone) override;
    void EndCall(Phone& phone) override;
    void AddBalance(Phone& phone, double amount) override;
};

#endif //TALKINGSTATE_H
