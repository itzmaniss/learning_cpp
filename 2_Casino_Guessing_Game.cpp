#include <iostream>
#include <random>

using namespace std;

class Game {
    public:
        void startGame () {
            generateRandomNumber();
            setDifficulty();
            takeGuesses();
        }

    private:
        int randomNumber;
        int maxAttempts;
        int difficultyLevel;

        void generateRandomNumber(){
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(1, 10);
            randomNumber = distrib(gen);
        }   

        void setDifficulty() {
            cout << "Choose difficulty level: " << endl 
            << "1. Easy (3 guesses)" << endl
            << "2. Intermediate (2 guesses)" << endl
            << "3. Hard (1 guess only!)" << endl;
            
            int choice = 0;
            cin >> choice;

            while (choice < 1 || choice > 3) {
                cout << "Invalid choice. Please enter 1, 2 or 3" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> choice;
            }
            difficultyLevel = choice;
            maxAttempts = 4 - choice;
        }

        void takeGuesses () {
            int guess;

            for (int i = 0; i < maxAttempts; i++){
                cout << "Guess the number! (Attempt " << i+1 << "/" << maxAttempts << "): " << endl;

                if (cin >> guess) {
                    if (guess == randomNumber) {
                        cout << "CONGRATULATIONS YOU HAVE GUESSED CORRECTLY ON ATTEMPT " << i + 1 << " !" << endl;
                        return;
                    } else {
                        cout << ( guess < randomNumber ? "TOO LOW!" : "TOO HIGH!") << endl;
                    }
                } else {
                    cout << "Invalid input. Please input a number from 1 to 10";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    i--;
                }
            }
            cout << "YOU LOSE! MWAHAHAHA. The number was " << randomNumber << endl;

        }
};

int main () {
    Game game;
    game.startGame();
}