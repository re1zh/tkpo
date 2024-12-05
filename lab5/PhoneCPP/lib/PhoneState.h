#ifndef PHONESTATE_H
#define PHONESTATE_H

#include <string>

using namespace std;

class Phone;

class PhoneState {
public:
    virtual void Call(Phone& phone, const string& number) = 0;
    virtual void ReceiveCall(Phone& phone) = 0;
    virtual void EndCall(Phone& phone) = 0;
    virtual void AddBalance(Phone& phone, double amount) = 0;
    virtual ~PhoneState() = default;
};

#endif //PHONESTATE_H
