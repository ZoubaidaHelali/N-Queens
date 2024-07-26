#include <iostream>
#include <vector>
#include <thread>
#include <future>
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

vector<vector<int>> solve(vector<int> board, int row, int n) {
    vector<vector<int>> solutions;
    if (row == n) {
        solutions.push_back(board);
        return solutions;
    }
    for (int col = 0; col < n; ++col) {
        if (is_safe(board, row, col)) {
            board[row] = col;
            auto sub_solutions = solve(board, row + 1, n);
            solutions.insert(solutions.end(), sub_solutions.begin(), sub_solutions.end());
        }
    }
    return solutions;
}

vector<vector<int>> solve_n_queens_parallel(int n, int num_threads) {
    vector<int> board(n, -1);
    vector<future<vector<vector<int>>>> futures;
    vector<vector<int>> solutions;

    for (int col = 0; col < n; ++col) {
        if (is_safe(board, 0, col)) {
            vector<int> board_copy = board;
            board_copy[0] = col;
            futures.push_back(async(launch::async, solve, board_copy, 1, n));
        }
    }

    for (auto& fut : futures) {
        auto result = fut.get();
        solutions.insert(solutions.end(), result.begin(), result.end());
    }

    return solutions;
}

int main() {
    int n =16; // Change this to 16 to test with N=16
    int num_threads = 4; // Specify the number of threads

    auto start = high_resolution_clock::now();
    auto solutions = solve_n_queens_parallel(n, num_threads);
    auto end = high_resolution_clock::now();
   
    auto duration = duration_cast<seconds>(end - start).count();
    cout << "Found " << solutions.size() << " solutions for N=" << n << " using " << num_threads << " threads in " << duration << " seconds" << endl;

    return 0;
}

