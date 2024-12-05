#include "Phone.h"
#include "PhoneState.h"
#include "WaitingState.h"
#include "CallingState.h"
#include "TalkingState.h"
#include "BlockedState.h"
#include <iostream>
#include <random>

using namespace std;

Phone::Phone(const string& number, double balance, int callProbability)
    : balance(balance), number(number), callProbability(callProbability) {
    waitingState = new WaitingState();
    callingState = new CallingState();
    talkingState = new TalkingState();
    blockedState = new BlockedState();

    currentState = (balance > 0) ? waitingState : blockedState;
}

Phone::~Phone() {
    delete waitingState;
    delete callingState;
    delete talkingState;
    delete blockedState;
}

void Phone::SetState(PhoneState* state) {
    currentState = state;
}

PhoneState* Phone::GetWaitingState() const {
    return waitingState;
}

PhoneState* Phone::GetCallingState() const {
    return callingState;
}

PhoneState* Phone::GetTalkingState() const {
    return talkingState;
}

PhoneState* Phone::GetBlockedState() const {
    return blockedState;
}

void Phone::Call(const string& number) {
    currentState->Call(*this, number);
}

void Phone::ReceiveCall() {
    currentState->ReceiveCall(*this);
}

void Phone::EndCall() {
    currentState->EndCall(*this);
}

void Phone::AddBalance(double amount) {
    currentState->AddBalance(*this, amount);
}

double Phone::GetBalance() const {
    return balance;
}

string Phone::GetNumber() const {
    return number;
}

void Phone::SetBalance(double newBalance) {
    balance = newBalance;
}

void Phone::CheckForIncomingCall() {
    if (currentState == waitingState && rand() % 100 + 1 <= callProbability) {
        ReceiveCall();
        EndCall();
    } else {
        cout << "Входящего звонка нет." << endl;
    }
}
