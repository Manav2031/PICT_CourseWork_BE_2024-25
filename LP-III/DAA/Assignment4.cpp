#include <bits/stdc++.h>
using namespace std;

bool isSafe(int r , int c , vector<vector<int>>&board , int n )
{
    int i = r ; 
    int j = c;

    //upperleft
    while(i>=0 && j>=0)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        i--;
        j--;
    }
    i = r ;
    j =c ;

    //lowerleft
    while(i<n && j>=0 )
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        i++;
        j--;
    }

    //left
    i = r ; 
    j = c;
    while(j>=0)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        j--;
    }

    //upperright
    i = r ; 
    j = c ;
    while(i>=0 && j<n)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        i--;
        j++;
    }

    //lowerright
    i = r ;
    j= c ;
    while(i<n && j<n)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        i++;
        j++;
    }

    //right
    i = r ; 
    j = c ;
    while(j<n)
    {
        if(board[i][j] == 1)
        {
            return false;
        }
        j++;
    }

    return true;
}

// Function to print the board
void printBoard(vector<vector<int>>& board) {
    for (auto row : board) {
        for (auto cell : row) {
            cout << (cell ? "Q " : ". ") << " "; // Print 'Q' for queens and '.' for empty spaces
        }
        cout << endl;
    }
    cout << endl; // New line after the board
}

// Function to solve the N-Queens problem
void solve(int col, int col1, vector<vector<int>>& board, int n, int& cnt) {
    // If all queens are placed
    if (col == n) {
        cnt++;
        cout << "Solution " << cnt << " found:" << endl;
        printBoard(board);
        return;
    }

    // If the current column is the one with the pre-placed queen
    if (col == col1) {
        solve(col + 1, col1, board, n, cnt);
        return; // Skip placing another queen in this column
    }

    // Try placing queen in each row of the current column
    for (int i = 0; i < n; i++) {
        if (isSafe(i, col, board, n)) {
            board[i][col] = 1; // Place queen
            cout << "Placing queen at (" << i << ", " << col << "):" << endl;
            printBoard(board); // Print the board after placing a queen
            solve(col + 1, col1, board, n, cnt); // Recur to place rest of the queens
            board[i][col] = 0; // Backtrack
            cout << "Removing queen from (" << i << ", " << col << "):" << endl;
            printBoard(board); // Print the board after removing a queen
        }
    }
}

int main() {
    cout << "Enter the size of the matrix: ";
    int n;
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0)); // Initialize the board with 0s
    cout << "Enter the first queen's position (row and column): " << endl;
    
    int r, c;
    cout << "Row: ";
    cin >> r;
    cout << "Column: ";
    cin >> c;

    // Place the first queen
    board[r][c] = 1;

    // Show the initial placement
    cout << "Initial board with queen placed at (" << r << ", " << c << "):" << endl;
    printBoard(board);

    int cnt = 0; // Solution counter
    solve(0, c, board, n, cnt); // Start solving

    if (cnt == 0) {
        cout << "No possible solutions for the given input." << endl;
    } else {
        cout << "Total solutions found: " << cnt << endl;
    }

    return 0;
}
