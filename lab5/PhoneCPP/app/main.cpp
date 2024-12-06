#include "Phone.h"
#include <iostream>
#include <ctime>

using namespace std;

void showCommands() {
    cout << "\nСписок команд" << endl;
    cout << "1. Совершить звонок" << endl;
    cout << "2. Завершить звонок" << endl;
    cout << "3. Пополнить баланс" << endl;
    cout << "4. Проверить входящие вызовы" << endl;
    cout << "5. Уменьшить баланс (симулировать списание)" << endl;
    cout << "6. Показать текущий баланс" << endl;
    cout << "0. Выйти" << endl;
    cout << "Выберите действие: ";
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    string phoneNum;
    double phoneBalance;
    int callProbability;

    cout << "Введите ваш номер телефона (+#-###-###-##-##): "; cin >> phoneNum;
    cout << "Введите первоначальный баланс: "; cin >> phoneBalance;
    cout << "Введите вероятность того, что вам позвонят (1 - 100): "; cin >> callProbability;

    Phone phone(phoneNum, phoneBalance * 1.0, callProbability);

    int choice = -1;

    cout << "Добро пожаловать! Ваш номер телефона: " << phone.GetNumber() << endl;

    while (choice != 0) {
        showCommands();
        cout << endl;
        cin >> choice;

        switch (choice) {
            case 1: {
                string number;
                cout << "Введите номер для звонка: "; cin >> number;
                phone.Call(number);
                break;
            }
            case 2: {
                phone.EndCall();
                break;
            }
            case 3: {
                double amount;
                cout << "Введите сумму пополнения: "; cin >> amount;
                if
                phone.AddBalance(amount);
                break;
            }
            case 4: {
                phone.CheckForIncomingCall();
                break;
            }
            case 5: {
                double decreaseSum;
                cout << "Введите сумму списания: "; cin >> decreaseSum;
                phone.AddBalance(-decreaseSum);
                break;
            }
            case 6: {
                cout << "Текущий баланс: " << phone.GetBalance() << endl;
                break;
            }
            case 0: {
                cout << "Выход из программы." << endl;
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте еще раз." << endl;
                break;
            }
        }
    }

    return 0;
}
