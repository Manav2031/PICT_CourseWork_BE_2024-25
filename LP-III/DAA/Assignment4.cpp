#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Check if the queen position is valid in the current board configuration
bool validate_board(const vector<int> &board, int row, int X_i) {
    for (int i = 0; i < row; i++) {
        if (board[i] == X_i || abs(board[i] - X_i) == abs(i - row)) {
            return false;
        }
    }
    return true;
}

// Print the current board configuration
void print_board(const vector<int> &board) {
    for (int i = 0; i < board.size(); i++) {
        cout << board[i] << " ";
    }
    cout << endl;
    cout << "===" << string(18, '=') << endl;  // Print a separator line
}

// Solve the N-Queens problem using backtracking
bool solve_n_queens(vector<int> &board, int N) {
    print_board(board);
    int i = 0;
    while (i < N && board[i] != -1) {
        i++;
    }
    if (i == N) {
        print_board(board);
        cout << "Solved!" << endl;
        return true;
    }

    // Iterate through possible values of X_i and check for valid boards
    for (int X_i = 0; X_i < N; X_i++) {
        if (validate_board(board, i, X_i)) {
            // If configuration board[i] = X_i is valid, set it and solve recursively
            vector<int> child_board = board; // Create a copy of the board
            child_board[i] = X_i;
            if (solve_n_queens(child_board, N)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;

    vector<int> board(N, -1); // Initialize the board with -1
    print_board(board);

    if (!solve_n_queens(board, N)) {
        cout << "No solution exists for " << N << " queens." << endl;
    }

    return 0;
}
