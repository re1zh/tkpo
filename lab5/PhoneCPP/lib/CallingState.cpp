#include "CallingState.h"
#include "Phone.h"
#include <iostream>

using namespace std;

void CallingState::Call(Phone &phone, const string &number) {
    cout << "Вы уже пытаетесь позвонить." << endl;
}

void CallingState::ReceiveCall(Phone &phone) {
    cout << "Вы не можете принять звонок во время набора." << endl;
}

void CallingState::EndCall(Phone &phone) {
    cout << "Звонок завершён." << endl;
    phone.SetBalance(phone.GetBalance() - 10.0);
    if (phone.GetBalance() <= 0) {
        cout << "Баланс отрицательный. Телефон заблокирован." << endl;
        phone.SetState(phone.GetBlockedState());
    } else {
        phone.SetState(phone.GetWaitingState());
    }
}

void CallingState::AddBalance(Phone &phone, double amount) {
    cout << "Невозможно пополнить баланс во время звонка." << endl;
}
