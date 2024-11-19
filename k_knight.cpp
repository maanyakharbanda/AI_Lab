#include <iostream>
#include <vector>

using namespace std;

// Function to mark all positions that a knight at (i, j) can attack
void attack(vector<vector<int>>& board, int i, int j, int rows, int cols) {
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for (int d = 0; d < 8; ++d) {
        int nx = i + dx[d]; // nx and ny are the attacking positions.
        int ny = j + dy[d];
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
            board[nx][ny] = 2;  // Mark as under attack
        }
    }
}

// Function to place a knight on the board and mark attack positions
vector<vector<int>> place(const vector<vector<int>>& board, int i, int j, int rows, int cols) {
    vector<vector<int>> new_board = board;
    new_board[i][j] = 1;  // Place knight
    attack(new_board, i, j, rows, cols);  // Mark positions attacked by this knight
    return new_board;
}

// Check if a knight can be placed at (i, j) without being attacked
bool canPlace(const vector<vector<int>>& board, int i, int j, int rows, int cols) {
    return board[i][j] == 0;
}

// Function to display the board
void display(const vector<vector<int>>& board, int rows, int cols) {
    cout << "Board configuration:\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << (board[i][j] == 1 ? "K " : (board[i][j] == 2 ? "a " : ". "));
        }
        cout << endl;
    }
    cout << endl;
}

// Main solution function using backtracking
void kn(vector<vector<int>>& board, int k, int start_i, int start_j, int rows, int cols) {
    if (k == 0) {
        display(board, rows, cols);
        return;
    }

    for (int i = start_i; i < rows; ++i) {
        for (int j = (i == start_i ? start_j : 0); j < cols; ++j) {
            if (canPlace(board, i, j, rows, cols)) {
                // Allocate a new board with the knight placed
                vector<vector<int>> new_board = place(board, i, j, rows, cols);
                kn(new_board, k - 1, i, j, rows, cols);  // Recursive call
            }
        }
        start_j = 0;  // Reset column start for the next row
    }
}

int main() {
    int rows, cols, knights;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;
    cout << "Enter the number of knights: ";
    cin >> knights;

    vector<vector<int>> board(rows, vector<int>(cols, 0));  // Initialize board with 0
    kn(board, knights, 0, 0, rows, cols);  // Start placing knights from (0, 0)

    return 0;
}
