#include <iostream>
#include <string>
#include <random>

using namespace std;

int main() {
    // Random number Generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution <> distrib(0, 2);

    const string rps[3] = {"rock", "paper", "scissors"};
    int playerChoice;
    int computerChoice = distrib(gen);
    int diff;

    //Get Player Input
    cout << "choose your pick! (just type the number!)" << endl;
    cout << "1. Rock" << endl;
    cout << "2. Paper" << endl;
    cout << "3. Scissors" <<endl;
    cin >> playerChoice;

    while (playerChoice < 1 || playerChoice > 3) {
        cout << "Invalid choice. Please enter 1, 2, or 3: ";
        cin >> playerChoice;
    }

    playerChoice--;
    cout << "checking PC then CC " << playerChoice << computerChoice << " " << (playerChoice-computerChoice) << " " << ((playerChoice-computerChoice) % 3) << endl;

    cout << "You picked: " << (rps[playerChoice]) << endl;
    cout << "Computer Picked: " << (rps[computerChoice]) << endl;
    
    //Win Condition Logic

    diff = playerChoice - computerChoice;
    if (diff < 0) {
        diff += 3;
    }

    cout << (diff == 0 ? "Its a TIE!":
    diff == 1 ? "YOU WON!!!!":
    "you lost :(") << endl;

    return 0;
}

