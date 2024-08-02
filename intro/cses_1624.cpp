#include <iostream>
#include <vector>

using namespace std;

const int N = 8;
int cnt = 0;

vector<vector<char>> board(N, vector<char>(N));

// Arrays to track columns and diagonals
vector<bool> cols(N, false);
vector<bool> diag1(2 * N, false);
vector<bool> diag2(2 * N, false);

void placeQueens(int row) {
    if (row == N) {
        cnt++;
        return;
    }

    for (int col = 0; col < N; ++col) {
        if (board[row][col] == '.' && !cols[col] && !diag1[row + col] && !diag2[row - col + N - 1]) {
            // Place the queen
            cols[col] = true;
            diag1[row + col] = true;
            diag2[row - col + N - 1] = true;

            // Recur to place the next queen
            placeQueens(row + 1);

            // Remove the queen
            cols[col] = false;
            diag1[row + col] = false;
            diag2[row - col + N - 1] = false;
        }
    }
}

int main() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
        }
    }

    placeQueens(0);

    cout << cnt << endl;

    return 0;
}
