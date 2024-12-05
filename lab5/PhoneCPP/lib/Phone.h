#ifndef PHONE_H
#define PHONE_H

#include <string>

using namespace std;

class PhoneState;
class WaitingState;
class CallingState;
class TalkingState;
class BlockedState;

class Phone {
public:
    Phone(const std::string& number, double balance, int callProbability);
    ~Phone();

    void SetState(PhoneState* state);
    PhoneState* GetWaitingState() const;
    PhoneState* GetCallingState() const;
    PhoneState* GetTalkingState() const;
    PhoneState* GetBlockedState() const;

    void Call(const string& number);
    void ReceiveCall();
    void EndCall();
    void AddBalance(double amount);
    double GetBalance() const;
    string GetNumber() const;
    void SetBalance(double newBalance);
    void CheckForIncomingCall();
private:
    PhoneState* waitingState;
    PhoneState* callingState;
    PhoneState* talkingState;
    PhoneState* blockedState;

    PhoneState* currentState;
    double balance;
    string number;
    int callProbability;
};

#endif //PHONE_H
