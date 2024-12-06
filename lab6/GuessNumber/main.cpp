#include <iostream>

using namespace std;

class GuessNumberModel {
    public:
        GuessNumberModel() {
            reset();
        }
        void reset() {
            secretNumber = generateRandomNumber(1, 100);
            attempts = 0;
        }
        int getSecretNumber() const {
            return secretNumber;
        }
        int getAttempts() const {
            return attempts;
        }
        void incrementAttempts() {
            attempts++;
        }
    private:
        int secretNumber;
        int attempts;

        int generateRandomNumber(int min, int max) {
            return rand() % (max - min) + min;
        }
};

class GuessNumberView {
    public:
        void displayWelcomeMessage() {
            cout << "Я загадал число от 1 до 100. Угадай его" << endl;
        }
        void displayPrompt() {
            cout << "Введите число: ";
        }
        void displayHint(const string& hint) {
            cout << hint << endl;
        }
        void displayWinMessage(int attempts) {
            cout << "Победа! Количество попыток: " << attempts << endl;
        }
        void displayError(const string& errorMessage) {
            cout << "Ошибка: " << errorMessage << endl;
        }
};

class GuessNumberController {
    public:
        GuessNumberController(GuessNumberModel& model, GuessNumberView& view)
            : model(model), view(view) {}
    
        void startGame() {
            model.reset();
            view.displayWelcomeMessage();

            int guess;
            while (true) {
                view.displayPrompt();
                if (!(cin >> guess)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    view.displayError("Введите только число!");
                    continue;
                }

                model.incrementAttempts();

                if (guess < model.getSecretNumber()) {
                    view.displayHint("Слишком малое число!");
                } else if (guess > model.getSecretNumber()) {
                    view.displayHint("Слишком большое число!");
                } else {
                    view.displayWinMessage(model.getAttempts());
                    break;
                }
            }
        }
    private:
        GuessNumberModel& model;
        GuessNumberView& view;
};

int main() {
    GuessNumberModel model;
    GuessNumberView view;
    GuessNumberController controller(model, view);

    controller.startGame();

    return 0;
}