#include "WaitingState.h"
#include "Phone.h"
#include <iostream>

using namespace std;

void WaitingState::Call(Phone& phone, const string& number) {
    if (phone.GetBalance() > 0) {
        cout << "Набираем номер " << number << "..." << endl;
        phone.SetState(phone.GetCallingState());
    } else {
        cout << "Баланс недостаточен для звонка." << endl;
        phone.SetState(phone.GetBlockedState());
    }
}

void WaitingState::ReceiveCall(Phone& phone) {
    cout << "Входящий звонок..." << endl;
    phone.SetState(phone.GetTalkingState());
}

void WaitingState::EndCall(Phone& phone) {
    cout << "Вы не в разговоре." << endl;
}

void WaitingState::AddBalance(Phone& phone, double amount) {
    phone.SetBalance(phone.GetBalance() + amount);
    cout << "Баланс пополнен на " << amount << ". Текущий баланс: " << phone.GetBalance() << endl;
}