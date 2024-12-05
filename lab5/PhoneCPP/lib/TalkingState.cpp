#include "TalkingState.h"
#include "Phone.h"
#include <iostream>

using namespace std;

void TalkingState::Call(Phone& phone, const string& number) {
    cout << "Вы уже в разговоре." << endl;
}

void TalkingState::ReceiveCall(Phone& phone) {
    cout << "Вы не можете принять новый звонок во время разговора." << endl;
}

void TalkingState::EndCall(Phone& phone) {
    cout << "Разговор завершён." << endl;
    phone.SetBalance(phone.GetBalance() - 10.0);
    if (phone.GetBalance() <= 0) {
        cout << "Баланс отрицательный. Телефон заблокирован." << endl;
        phone.SetState(phone.GetBlockedState());
    } else {
        phone.SetState(phone.GetWaitingState());
    }
}

void TalkingState::AddBalance(Phone& phone, double amount) {
    phone.SetBalance(phone.GetBalance() + amount);
    cout << "Баланс пополнен на " << amount << ". Текущий баланс: " << phone.GetBalance() << endl;
}
