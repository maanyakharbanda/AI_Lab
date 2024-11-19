#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int MAX_SCORE = 10;
const int MIN_SCORE = -10;
const int SIZE = 3; // Tic-Tac-Toe board size

// Global variables to count Minimax and Alpha-Beta calls
int minimax_calls = 0;
int alpha_beta_calls = 0;

// Function to evaluate the board with specific scores for different configurations
int evaluate_board(const vector<vector<int>>& board) {
    int score = 0;

    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        int row_sum = board[i][0] + board[i][1] + board[i][2];
        int col_sum = board[0][i] + board[1][i] + board[2][i];

        // Evaluate rows
        if (row_sum == SIZE) return MAX_SCORE;      // Win for player 1
        if (row_sum == -SIZE) return MIN_SCORE;     // Win for player 2
        if (abs(row_sum) == SIZE - 1) score += row_sum > 0 ? 5 : -5; // Two-in-a-row

        // Evaluate columns
        if (col_sum == SIZE) return MAX_SCORE;      // Win for player 1
        if (col_sum == -SIZE) return MIN_SCORE;     // Win for player 2
        if (abs(col_sum) == SIZE - 1) score += col_sum > 0 ? 5 : -5; // Two-in-a-row
    }

    // Check diagonals
    int diag1_sum = board[0][0] + board[1][1] + board[2][2];
    int diag2_sum = board[0][2] + board[1][1] + board[2][0];

    if (diag1_sum == SIZE) return MAX_SCORE;        // Win for player 1
    if (diag1_sum == -SIZE) return MIN_SCORE;       // Win for player 2
    if (abs(diag1_sum) == SIZE - 1) score += diag1_sum > 0 ? 5 : -5; // Two-in-a-row

    if (diag2_sum == SIZE) return MAX_SCORE;        // Win for player 1
    if (diag2_sum == -SIZE) return MIN_SCORE;       // Win for player 2
    if (abs(diag2_sum) == SIZE - 1) score += diag2_sum > 0 ? 5 : -5; // Two-in-a-row

    // Center control bonus
    if (board[1][1] != 0) score += board[1][1] * 3;

    return score;
}


// Check if the game is over
bool is_terminal(const vector<vector<int>>& board) {
    return evaluate_board(board) == MAX_SCORE || evaluate_board(board) == MIN_SCORE ||
           !any_of(board.begin(), board.end(), [](const vector<int>& row) {
               return any_of(row.begin(), row.end(), [](int cell) { return cell == 0; });
           });
}

// Negamax with depth-limited recursion
int negamax(vector<vector<int>>& board, int depth, int color) {
    minimax_calls++; // Count Minimax calls
    if (depth == 0 || is_terminal(board)) return color * evaluate_board(board);

    int best_score = MIN_SCORE;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                board[i][j] = color; // Try move
                int score = -negamax(board, depth - 1, -color); // Recurse with negated color
                board[i][j] = 0; // Undo move
                best_score = max(best_score, score);
            }
        }
    }
    return best_score;
}

// Alpha-Beta Pruning implementation
int alpha_beta(vector<vector<int>>& board, int depth, int alpha, int beta, int color) {
    alpha_beta_calls++; // Count Alpha-Beta calls
    if (depth == 0 || is_terminal(board)) return color * evaluate_board(board);

    int best_score = MIN_SCORE;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                board[i][j] = color; // Try move
                int score = -alpha_beta(board, depth - 1, -beta, -alpha, -color); // Recurse
                board[i][j] = 0; // Undo move
                best_score = max(best_score, score);
                alpha = max(alpha, score); // Update alpha

                // Beta cutoff
                if (beta <= alpha) {
                    break; // Stop searching this branch
                }
            }
        }
    }
    return best_score;
}

// Get best move using Minimax
pair<int, int> get_best_move_minimax(vector<vector<int>>& board, int depth, int color) {
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

// Get best move using Alpha-Beta pruning
pair<int, int> get_best_move_alpha_beta(vector<vector<int>>& board, int depth, int color) {
    int best_score = MIN_SCORE;
    int best_row = -1, best_col = -1;
    int alpha = MIN_SCORE;
    int beta = MAX_SCORE;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == 0) {
                board[i][j] = color;
                int score = -alpha_beta(board, depth - 1, -beta, -alpha, -color);
                board[i][j] = 0; // Undo move
                if (score > best_score) {
                    best_score = score;
                    best_row = i;
                    best_col = j;
                }
                alpha = max(alpha, score); // Update alpha
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

    // Ask for depth from user
    int depth;
    do {
        cout << "Enter depth for Minimax and Alpha-Beta (1-9): ";
        cin >> depth;
    } while (depth < 1 || depth > 9); // Validate depth input

    int player = 1; // 1 for 'X', -1 for 'O'
    bool game_over = false;

    while (!game_over) {
        // User's turn
        display_board(board);
        int user_row, user_col;
        cout << "Your turn (enter row and column 0-2): ";
        cin >> user_row >> user_col;

        // Validate user input
        if (user_row < 0 || user_row >= SIZE || user_col < 0 || user_col >= SIZE || board[user_row][user_col] != 0) {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        board[user_row][user_col] = player;

        // Check for a win or draw
        if (evaluate_board(board) == MAX_SCORE) {
            display_board(board);
            cout << "You win!\n";
            break;
        } else if (is_terminal(board)) {
            display_board(board);
            cout << "It's a draw!\n";
            break;
        }

        // AI's turn using Negamax
        minimax_calls = 0; // Reset counter for Negamax
        cout << "AI is making a move using Negamax...\n";
        pair<int, int> best_move = get_best_move_minimax(board, depth, -player);
        board[best_move.first][best_move.second] = -player;

        // Display Negamax calls count
        cout << "Negamax calls: " << minimax_calls << endl;

        // Check for a win or draw
        // if (evaluate_board(board) == MIN_SCORE) {
        //     display_board(board);
        //     cout << "AI wins!\n";
        //     break;
        // } else if (is_terminal(board)) {
        //     display_board(board);
        //     cout << "It's a draw!\n";
        //     break;
        // }

        // AI's turn using Alpha-Beta pruning
        alpha_beta_calls = 0; // Reset counter for Alpha-Beta
        cout << "AI is making a move using Alpha-Beta...\n";
        pair<int, int> best_move_alpha_beta = get_best_move_alpha_beta(board, depth, -player);
        board[best_move_alpha_beta.first][best_move_alpha_beta.second] = -player;

        // Display the board after Alpha-Beta move
        display_board(board);
        cout << "AI's move using Alpha-Beta: (" << best_move_alpha_beta.first << ", " << best_move_alpha_beta.second << ")\n";
        
        // Display Alpha-Beta calls count
        cout << "Alpha-Beta calls: " << alpha_beta_calls << endl;

        // Check for a win or draw
        if (evaluate_board(board) == MIN_SCORE) {
            cout << "AI wins!\n";
            break;
        } else if (is_terminal(board)) {
            cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    play_game();
    return 0;
}