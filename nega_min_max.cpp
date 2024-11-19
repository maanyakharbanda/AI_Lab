#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const int MAX_SCORE = 10;
const int MIN_SCORE = -10;
const int SIZE = 3; // Tic-Tac-Toe board size

// Function to evaluate board with specific scores for different configurations
int evaluate_board(const vector<vector<int>>& board) {
    int score = 0;
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        int row_sum = board[i][0] + board[i][1] + board[i][2];
        int col_sum = board[0][i] + board[1][i] + board[2][i];
        if (row_sum == SIZE) return MAX_SCORE;      // Win for player 1
        if (row_sum == -SIZE) return MIN_SCORE;     // Win for player 2
        if (abs(row_sum) == SIZE - 1) score += row_sum > 0 ? 5 : -5;
        if (col_sum == SIZE) return MAX_SCORE;
        if (col_sum == -SIZE) return MIN_SCORE;
        if (abs(col_sum) == SIZE - 1) score += col_sum > 0 ? 5 : -5;
    }

    int diag1_sum = board[0][0] + board[1][1] + board[2][2];
    int diag2_sum = board[0][2] + board[1][1] + board[2][0];
    if (diag1_sum == SIZE) return MAX_SCORE;
    if (diag1_sum == -SIZE) return MIN_SCORE;
    if (abs(diag1_sum) == SIZE - 1) score += diag1_sum > 0 ? 5 : -5;
    if (diag2_sum == SIZE) return MAX_SCORE;
    if (diag2_sum == -SIZE) return MIN_SCORE;
    if (abs(diag2_sum) == SIZE - 1) score += diag2_sum > 0 ? 5 : -5;
    if (board[1][1] != 0) score += board[1][1] * 3;

    return score;
}

// Check if game is over
bool is_terminal(const vector<vector<int>>& board) {
    return evaluate_board(board) == MAX_SCORE || evaluate_board(board) == MIN_SCORE ||
           !any_of(board.begin(), board.end(), [](const vector<int>& row) {
               return any_of(row.begin(), row.end(), [](int cell) { return cell == 0; });
           });
}

// Negamax with depth-limited recursion
int negamax(vector<vector<int>>& board, int depth, int color) {
    if (depth == 0 || is_terminal(board)) return color * evaluate_board(board);
    int best_score = MIN_SCORE;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                board[i][j] = color;
                int score = -negamax(board, depth - 1, -color);
                board[i][j] = 0;
                best_score = max(best_score, score);
            }
        }
    }
    return best_score;
}

// Get best move
pair<int, int> get_best_move(vector<vector<int>>& board, int depth, int color) {
    int best_score = MIN_SCORE;
    int best_row = -1, best_col = -1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                board[i][j] = color;
                int score = -negamax(board, depth - 1, -color);
                board[i][j] = 0;
                if (score > best_score) {
                    best_score = score;
                    best_row = i;
                    best_col = j;
                }
            }
        }
    }
    return make_pair(best_row, best_col);
}

// Display board
void display_board(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int cell : row) cout << (cell == 1 ? 'X' : cell == -1 ? 'O' : '.') << ' ';
        cout << endl;
    }
}

// Main game function
void play_game() {
    vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));
    int depth;
    int player = 1; // 1 for 'X', -1 for 'O'
    
    cout << "Enter AI search depth (1-9): ";
    cin >> depth;
    depth = max(1, min(depth, 9));

    // Determine who goes first
    char first_player;
    cout << "Who will play first? (X for you, O for AI): ";
    cin >> first_player;
    if (first_player == 'O' || first_player == 'o') player = -1;

    bool game_over = false;
    while (!is_terminal(board)) {
        display_board(board);
        if (player == 1) {
            // Player's turn
            int move;
            cout << "Enter your move (1-9): ";
            cin >> move;
            move--;  // Convert to zero-indexed
            int row = move / SIZE;
            int col = move % SIZE;
            if (move < 0 || move >= SIZE*SIZE || board[row][col] != 0) {
                cout << "Invalid move! Try again.\n";
                continue;
            }
            board[row][col] = player;
        } else {
            // AI's turn
            pair<int, int> best_move = get_best_move(board, depth, player);
            board[best_move.first][best_move.second] = player;
            cout << "AI plays: (" << best_move.first + 1 << ", " << best_move.second + 1 << ")\n";
        }

        // Check for game end
        if (evaluate_board(board) == MAX_SCORE) {
            display_board(board);
            cout << "Player 'X' wins!\n";
            game_over = true;
            break;
        } else if (evaluate_board(board) == MIN_SCORE) {
            display_board(board);
            cout << "Player 'O' (AI) wins!\n";
            game_over = true;
            break;
        } else if (all_of(board.begin(), board.end(), [](const vector<int>& row) {
                    return all_of(row.begin(), row.end(), [](int cell) { return cell != 0; });
                })) {
            display_board(board);
            cout << "It's a tie!\n";
            game_over = true;
            break;
        }

        player = -player;
    }
}

int main() {
    cout << "Welcome to Tic-Tac-Toe!\n";
    play_game();
    return 0;
}
