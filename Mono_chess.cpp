#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

bool is_safe(const vector<int>& board, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (board[i] == col ||
            board[i] - i == col - row ||
            board[i] + i == col + row) {
            return false;
        }
    }
    return true;
}

void solve(vector<int>& board, int row, vector<vector<int>>& solutions, int n) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    for (int col = 0; col < n; ++col) {
        if (is_safe(board, row, col)) {
            board[row] = col;
            solve(board, row + 1, solutions, n);
        }
    }
}

vector<vector<int>> solve_n_queens(int n) {
    vector<int> board(n, -1);
    vector<vector<int>> solutions;
    solve(board, 0, solutions, n);
    return solutions;
}

int main() {
    int n =16; // Change this to 16 to test with N=16,
    auto start = high_resolution_clock::now();
    auto solutions = solve_n_queens(n);
    auto end = high_resolution_clock::now();
   
    auto duration = duration_cast<seconds>(end - start).count();
    cout << "Found " << solutions.size() << " solutions for N=" << n << " in " << duration << " seconds" << endl;

    return 0;
}
