#include <iostream>
#include <vector>

using namespace std;

const int BLANK = 2;
const int X = 3; // User
const int O = 5; // AI

// Function to check for possible winning move
int posswin(vector<int>& board, int player) {
    int winPatterns[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};
    
    for (auto& pattern : winPatterns) {
        int product = board[pattern[0]] * board[pattern[1]] * board[pattern[2]];
        if (product == player * player * BLANK) {
            for (int i = 0; i < 3; ++i) {
                if (board[pattern[i]] == BLANK)
                    return pattern[i];
            }
        }
    }
    return 0; // No possible win
}

// Function to make a move
void go(vector<int>& board, int turn, int n) {
    if (turn % 2 == 1) {
        board[n] = X; // Player X's turn (User)
    } else {
        board[n] = O; // Player O's turn (AI)
    }
}

// Function to find a move if center is blank or choose another position
int make2(vector<int>& board) {
    if (board[5] == BLANK)
        return 5; // Center square
    int corners[] = {1, 3, 7, 9};
    for (int corner : corners) {
        if (board[corner] == BLANK)
            return corner;
    }
    return 2; // Default
}

// Function to check if the board is full
bool isFull(const vector<int>& board) {
    for (int i = 1; i <= 9; ++i) {
        if (board[i] == BLANK)
            return false;
    }
    return true;
}

// Function to check for a win
bool checkWin(vector<int>& board, int player) {
    int winPatterns[8][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};
    
    for (auto& pattern : winPatterns) {
        int product = board[pattern[0]] * board[pattern[1]] * board[pattern[2]];
        if (product == player * player * player) {
            return true;
        }
    }
    return false;
}

// Function to get user's move
int getPlayerMove(const vector<int>& board) {
    int move;
    while (true) {
        cin >> move;
        if (move >= 1 && move <= 9 && board[move] == BLANK) {
            return move;
        } else {
            cout << "Invalid move! Try again: ";
        }
    }
}

// Function to print the board
void printBoard(const vector<int>& board) {
    for (int i = 1; i <= 9; i++) {
        if (board[i] == X)
            cout << " X ";
        else if (board[i] == O)
            cout << " O ";
        else
            cout << " " << i << " "; // Display available positions
        if (i % 3 == 0) cout << endl;
    }
    cout << endl;
}


// Main algorithm for the Tic-Tac-Toe game
int main() {
    vector<int> board(10, BLANK); // Board initialized with 2 (blank) values
    int turn = 1; // Start with the first turn
    bool gameOver = false;

    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "You are 'X' and the computer is 'O'." << endl;

    while (turn <= 9 && !isFull(board) && !gameOver) {
        printBoard(board);
        if (turn % 2 == 1) { // User's turn (odd turns)
            cout << "Your turn! Choose a position (1-9): ";
            int move = getPlayerMove(board);
            go(board, turn, move);
            if (checkWin(board, X)) {
                printBoard(board);
                cout << "Congratulations, you won!" << endl;
                gameOver = true;
            }
        } else { // AI's turn (even turns)
            cout << "AI is making its move..." << endl;

            if (turn == 2) {
                if (board[5] == BLANK)
                    go(board, turn, 5); // Go(5)
                else
                    go(board, turn, 1); // Go(1)
            } else if (turn == 3) {
                if (board[9] == BLANK)
                    go(board, turn, 9); // Go(9)
                else
                    go(board, turn, 3); // Go(3)
            } else {
                int move = posswin(board, O); // Check if AI can win
                if (move != 0)
                    go(board, turn, move); // Go(posswin(O))
                else {
                    move = posswin(board, X); // Block user's winning move
                    if (move != 0)
                        go(board, turn, move); // Go(posswin(X))
                    else
                        go(board, turn, make2(board)); // Go(Make2)
                }
            }

            if (checkWin(board, O)) {
                printBoard(board);
                cout << "AI won this time!" << endl;
                gameOver = true;
            }
        }

        turn++;
    }

    if (!gameOver && isFull(board)) {
        printBoard(board);
        cout << "It's a tie!" << endl;
    }

    return 0;
}