#include <iostream>
#include "Facade.h"

using namespace std;

int main()
{
    Apartment apt(50, 2, 2010, 10);
    Townhouse th(120, 4, 2000, 20);
    Cottage ct(200, 5, 1990, 30);

    int insuranceTerm = 5;

    cout << "Расчёт страхового взноса: " << endl;
    cout << apt.getType() << ": " << InsuranceFacade::calculatePremium(apt, insuranceTerm) << " руб." << endl;
    cout << th.getType() << ": " << InsuranceFacade::calculatePremium(th, insuranceTerm) << " руб." << endl;
    cout << ct.getType() << ": " << InsuranceFacade::calculatePremium(ct, insuranceTerm) << " руб." << endl;
    
    return 0;
}
