#include "BlockedState.h"
#include "Phone.h"
#include <iostream>

using namespace std;

void BlockedState::Call(Phone& phone, const string& number) {
    cout << "Телефон заблокирован. Пополните баланс." << endl;
}

void BlockedState::ReceiveCall(Phone& phone) {
    cout << "Телефон заблокирован. Вы не можете принимать звонки." << endl;
}

void BlockedState::EndCall(Phone& phone) {
    cout << "Вы не в разговоре." << endl;
}

void BlockedState::AddBalance(Phone& phone, double amount) {
    phone.SetBalance(phone.GetBalance() + amount);
    cout << "Баланс пополнен на " << amount << ". Текущий баланс: " << phone.GetBalance() << endl;
    if (phone.GetBalance() > 0) {
        phone.SetState(phone.GetWaitingState());
    }
}