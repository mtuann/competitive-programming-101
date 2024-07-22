#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs(int x, int y, const vector<vector<char>>& map, vector<vector<bool>>& visited) {
    int n = map.size();
    int m = map[0].size();
    stack<pair<int, int>> s;
    s.push({x, y});
    visited[x][y] = true;
    
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up

    while (!s.empty()) {
        int cx = s.top().first;
        int cy = s.top().second;
        s.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = cx + directions[i][0];
            int ny = cy + directions[i][1];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && map[nx][ny] == '.') {
                visited[nx][ny] = true;
                s.push({nx, ny});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> map(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> map[i][j];
        }
    }

    int room_count = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == '.' && !visited[i][j]) {
                ++room_count;
                dfs(i, j, map, visited);
            }
        }
    }

    cout << room_count << endl;

    return 0;
}
