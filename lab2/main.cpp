#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class Document {
    public:
        virtual ~Document() = default;
        virtual void print() const = 0;
};

class Item {
    public:
        Item(const string& name, const double price, const int quantity)
            : name(name), price(price), quantity(quantity) {}

        string getName() const{
            return name;
        }

        double getPrice() const {
            return price;
        }

        int getQuantity() const {
            return quantity;
        }

        double totalPrice() const {
            return quantity * price;
        }
    private:
        string name;
        double price;
        int quantity;
};

class FinancialDocument : public virtual Document {
    public:
        virtual double getTotalAmount() const = 0;
        virtual void addItem(const Item& item) = 0;
    private:
        vector<Item> items;
};

class Bill : public FinancialDocument {
public:
    Bill() = default;
    explicit Bill(const vector<Item>& initialItems): items(initialItems) {}

    vector<Item> getItems() const {
        return items;
    }

    void addItem(const Item& item) override {
        items.push_back(item);
    }

    double getTotalAmount() const override {
        double total = 0.0;
        for (const Item& item : items) {
            total += item.totalPrice();
        }
        return total;
    }

    void print() const override {
        cout << "Счет: \n";
        for (const auto& item : items) {
            cout << "- " << item.getName() << " | Количество: " << item.getQuantity()
                      << " | Цена: " << fixed << setprecision(2) << item.getPrice()
                      << " | Итоговая сумма товара: " << item.totalPrice() << "\n";
        }
        cout << "Итоговая сумма: " << getTotalAmount() << "\n";
    }
private:
    vector<Item> items;
};

class Invoice : public FinancialDocument {
    public:
        Invoice() = default;
        explicit Invoice(const vector<Item>& initialItems): items(initialItems) {}

        void addItem(const Item& item) override {
            items.push_back(item);
        }

        double getTotalAmount() const override {
            double total = 0.0;
            for (const Item& item : items) {
                total += item.totalPrice();
            }
            return total;
        }

        void print() const override {
            cout << "Накладная: \n";
            for (const Item& item : items) {
                cout << "- " << item.getName() << " | Количество: " << item.getQuantity()
                          << " | Цена: " << fixed << setprecision(2) << item.getPrice()
                          << " | Итоговая сумма товара: " << item.totalPrice() << "\n";
            }
        }
    private:
        vector<Item> items;
};

class Receipt : public Document {;
public:
    Receipt() = default;
    explicit Receipt(const double amount): paidAmount(amount) {}

    void print() const override {
        cout << "Квитанция: Оплата подтверждена. Сумма к оплате: "
            << fixed << setprecision(2) << paidAmount << "\n";
    }
private:
    double paidAmount;
};

class DocumentProcessor {
public:
    static void processDocument(const Document& doc) {
        doc.print();
    }
};

void runConsoleApp() {
    DocumentProcessor processor;
    cout << "--------------------Закупка товаров--------------------" << endl;
    Bill bill;
    cout << "Новый счёт создан" << endl;

    cout << "--------------------------------------------------------" << endl;

    int numItems;
    cout << "Введите количество позиций для добавления в счет: ";
    cin  >> numItems;

    for (int i = 0; i < numItems; ++i) {
        int quantity; double price; string name;
        cout << "Введите название товара: ";
        cin.ignore();
        getline(cin, name);
        cout << "Введите количество товара: ";
        cin >> quantity;
        cout << "Введите цену за единицу товара: ";
        cin >> price;

        bill.addItem(Item(name, price, quantity));
        cout << "Товар добавлен в счёт" << endl;
    }

    cout << "--------------------------------------------------------" << endl;

    Invoice invoice(bill.getItems()) ;
    cout << "Накладная создана на основе счёта" << endl;

    cout << "--------------------------------------------------------" << endl;

    Receipt receipt(bill.getTotalAmount());
    cout << "Счёт оплачен. Квитанция создана" << endl;

    cout << "--------------------------------------------------------" << endl;

    processor.processDocument(bill);
    cout << "--------------------------------------------------------" << endl;
    processor.processDocument(invoice);
    cout << "--------------------------------------------------------" << endl;
    processor.processDocument(receipt);
    cout << "--------------------------------------------------------" << endl;
}

int main() {
    runConsoleApp();
    return 0;
}