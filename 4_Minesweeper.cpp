#include <iostream>
#include <random>
#include <vector>
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_main.h>

using namespace std;

class Minesweeper {
    public:
        void startGame() {

            int x,y;

            setDifficulty();
            generateBoard();
            showPrivateBoardCLI();
            int toBeRevealed = (boardSize * boardSize) - numMines;

            while(!lost && revealed != toBeRevealed) {
                cout << revealed << " " << toBeRevealed << endl;
                showBoardCLI();
                cout << "Choose the coordinates you want to open: " << endl << "x: ";
                x = pickCoord('X');
                cout << "Y: ";
                y = pickCoord('Y');
                reveal(x, y, false);
            }

            cout << "YOU HAVE WON!! GREAT JOB!" << endl;

        }
    
    private:

        bool lost = false;
        int difficulty;
        int boardSize;
        int numMines;
        int revealed = 0;
        vector<vector<int>> privateBoard;
        vector<vector<char>> playerBoard;


        //let user set difficulty
        void setDifficulty () {
            int choice;
            int board[3] = {9, 16, 24};
            int mines[3] = {10, 40, 99};

            cout << "Choose your level of difficulty: " << endl 
                << "1. Easy (9X9)" << endl 
                << "2. Medium (16X16)" << endl
                << "3. Hard (24X24)" << endl;

            cin >> choice;

            while (choice < 1 || choice > 3) {
                cout << "Invalid choice. Please only enter 1 to 3" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cin >> choice;
            }

            difficulty = choice;
            boardSize = board[choice-1];
            numMines = mines[choice-1];
        }


        //random number generator for generating mines
        int genNum () {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(0, boardSize-1);
            return distrib(gen);
        }



        void updateBoard(const int x, const int y) {
            if ( y >= 0
            && y < boardSize
            && x >= 0
            && x < boardSize
            && privateBoard[x][y] != 9) {
                privateBoard[x][y] ++;
            }
            
        }


        void generateBoard () {

        vector <int> tempPrivate;
        vector <char> tempPlayer;

        // create empty board
        for (int i = 0; i < boardSize; i++){
            tempPrivate.push_back(0);
            tempPlayer.push_back('*');
        }

        for (int i = 0; i < boardSize; i++) {
            privateBoard.push_back(tempPrivate);
            playerBoard.push_back(tempPlayer);
        }

        
        //Generate coordinates of mines
        int count = 0;

        while (count < numMines) {
            int x = genNum();
            int y = genNum();
            if (privateBoard[x][y] != 9) {
                //update the board on mine area
                privateBoard[x][y] = 9;
                //update North
                updateBoard(x, y+1);
                //update south
                updateBoard(x, y-1);
                //update East
                updateBoard(x+1, y);
                //update West
                updateBoard(x-1, y);
                //update NorthEast
                updateBoard(x+1, y+1);
                //Update NorthWest
                updateBoard(x-1, y+1);
                //Update SouthEast
                updateBoard(x+1, y-1);
                //update SouthWest
                updateBoard(x-1, y-1);

                count ++;
            }
        }
    }   


    void reveal(const int x, const int y, bool recursed) {

        int boardValue = privateBoard[y][x];

 
        // check if already revealed
        if (playerBoard[y][x] != '*') {return;} 

        if (recursed == false && boardValue == 9) {
            cout << "YOU LOSE NOOB!!!!" << endl;
            lost = true;

        } else if (recursed == true && boardValue == 9) {
            return;

        } else if (privateBoard[y][x] != 0) {
            playerBoard[y][x] = boardValue + '0';
            revealed ++;

        } else {
            playerBoard[y][x] = boardValue + '0';
            revealed ++;

            for (int i= -1; i < 2; i++) {
                if ((y + i) < 0 || (y + i) > (boardSize - 1)){continue;}

                for (int j = -1; j < 2; j++) {
                    if ((x + j) < 0 || (x + j) > (boardSize - 1) || (x == 0 && y == 0) > boardSize - 1) {continue;}

                    reveal((x + j), (y + i), true);
                    }
                }
            }
        }
    


    void showPrivateBoardCLI(){
        for (int i = 0; i < privateBoard.size(); i++) { 
            for (int j = 0; j < privateBoard[i].size(); j++) 
                cout << privateBoard[i][j] << " "; 
                cout << endl; 
            }
    }

    void showBoardCLI () {
        for (int i = 0; i < playerBoard.size() + 1; i++) {
            if (i < 10) {cout<< 0;}
            cout << i << " ";
        }
        cout << endl;
        for (int i = 0; i < playerBoard.size(); i++) { 
            if (i < 9) {cout << 0;}
            cout << i + 1 << " ";
            for (int j = 0; j < playerBoard[i].size(); j++) {
                cout << playerBoard[i][j] << "  "; 
            }
            cout << endl; 
        } 
    }

    int pickCoord(const char y) {
        int x;
        cin >> x;
        while (x < 1 || x > boardSize) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input please enter a number between 0 and " << boardSize - 1 << "." << endl << y << ": ";
            cin >> x;
        }
        return x - 1;
    }
};
/*
int main (int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "error" << endl;
    }

    SDL_Window* window = SDL_CreateWindow("Minesweeper", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        600, 400, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    gameLogic();

    //CleanUp
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();    
}
*/
void gameLogic() {
    cout << "start" << endl;
    Minesweeper game;
    game.startGame();
}

int main() {
    Minesweeper game;
    game.startGame();
}