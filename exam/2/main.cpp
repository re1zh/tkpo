// Едисеев Олег Владимирович 221-329

// Интерфейс PrintStrategy определяет общий метод print(), который должен быть реализован каждой конкретной стратегией (моделью принтера).
// Три стратегии (LaserPrint, InkPrint, MatrixPrint) реализуют данный интерфейс.
// Контекст Printer:
//      Хранит стратегию печати в виде указателя printStrategy.
//      Предоставляет метод setPrintStrategy(...), чтобы менять стратегию.

#include <iostream>
#include <string>

using namespace std;

// Общий интерфейс (стратегия печати)
class PrintStrategy {
    public:
        virtual ~PrintStrategy() = default;
        virtual void print(const string& text) = 0;
};

// Три конкретные стратегии (разные модели принтеров)

// Лазерный принтер
class LaserPrint : public PrintStrategy {
    public:
        void print(const string& text) override {
            cout << "[Laser Printer] Печать текста лазером: " << text << endl;
        }
};

// Струйный принтер
class InkPrint : public PrintStrategy {
    public:
        void print(const string& text) override {
            cout << "[Ink Printer] Печать текста струйным методом: " << text << endl;
        }
};

// Матричный принтер
class MatrixPrint : public PrintStrategy {
    public:
        void print(const string& text) override {
            cout << "[Matrix Printer] Печать текста матричным методом: " << text << endl;
        }
};

// 3. Класс Printer (контекст), который хранит стратегию печати без умных указателей
class Printer {
    public:
        // Конструктор без стратегии
        Printer() : printStrategy(nullptr) {}

        // Конструктор с установкой стратегии
        explicit Printer(PrintStrategy* strategy) : printStrategy(strategy) {}

        // Деструктор
        ~Printer() {
            delete printStrategy;
        }

        // Метод для установки или смены стратегии
        void setPrintStrategy(PrintStrategy* strategy) {
            delete printStrategy;
            printStrategy = strategy;
        }

        // Метод «печатать»
        void printDocument(const string& text) {
            if (printStrategy) {
                printStrategy->print(text);
            } else {
                cout << "Стратегия печати не установлена!\n";
            }
        }
    private:
        PrintStrategy* printStrategy;
};

int main() {
    // Создаём объект «Принтер» без заданной стратегии
    Printer myPrinter;

    // Устанавливаем стратегию: Лазерная печать
    myPrinter.setPrintStrategy(new LaserPrint());
    myPrinter.printDocument("Hello World! (laser)");

    // Меняем стратегию: Струйная печать
    myPrinter.setPrintStrategy(new InkPrint());
    myPrinter.printDocument("Hello World! (ink)");

    // Меняем стратегию: Матричная печать
    myPrinter.setPrintStrategy(new MatrixPrint());
    myPrinter.printDocument("Hello World! (matrix)");

    return 0;
}
