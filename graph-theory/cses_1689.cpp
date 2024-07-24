#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 8;
const int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

vector<vector<int>> board(N, vector<int>(N, -1));
int move_count = 0;

bool is_valid(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1;
}

void print_board() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] + 1 << " ";
        }
        cout << endl;
    }
}

bool solve(int x, int y, int move_i) {
    if (move_i == N * N) {
        return true;
    }

    vector<pair<int, pair<int, int>>> moves;
    for (int i = 0; i < 8; ++i) {
        int new_x = x + dx[i];
        int new_y = y + dy[i];
        if (is_valid(new_x, new_y)) {
            int count = 0;
            for (int j = 0; j < 8; ++j) {
                int next_x = new_x + dx[j];
                int next_y = new_y + dy[j];
                if (is_valid(next_x, next_y)) {
                    ++count;
                }
            }
            moves.push_back({count, {new_x, new_y}});
        }
    }

    sort(moves.begin(), moves.end());

    for (const auto &move : moves) {
        int new_x = move.second.first;
        int new_y = move.second.second;

        board[new_x][new_y] = move_i;
        if (solve(new_x, new_y, move_i + 1)) {
            return true;
        }
        board[new_x][new_y] = -1;  // Backtrack
    }

    return false;
}

int main() {
    int start_x, start_y;
    cin >> start_x >> start_y;

    --start_x;
    --start_y;

    board[start_x][start_y] = 0;
    if (solve(start_x, start_y, 1)) {
        print_board();
    } else {
        cout << "No solution found" << endl;
    }

    return 0;
}
