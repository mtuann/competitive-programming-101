#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Cell {
    int x, y;
    Cell(int x=0, int y=0) : x(x), y(y) {}
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> labyrinth(n, vector<char>(m));
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<Cell>> previous(n, vector<Cell>(m, {-1, -1}));
    vector<vector<char>> direction(n, vector<char>(m));
    Cell start, end;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> labyrinth[i][j];
            if (labyrinth[i][j] == 'A') {
                start = {i, j};
            } else if (labyrinth[i][j] == 'B') {
                end = {i, j};
            }
        }
    }

    queue<Cell> q;
    q.push(start);
    visited[start.x][start.y] = true;

    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    char dir_chars[4] = {'R', 'D', 'L', 'U'};

    bool found = false;

    while (!q.empty()) {
        Cell current = q.front();
        q.pop();

        if (current.x == end.x && current.y == end.y) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && labyrinth[nx][ny] != '#') {
                visited[nx][ny] = true;
                previous[nx][ny] = current;
                direction[nx][ny] = dir_chars[i];
                q.push({nx, ny});
            }
        }
    }

    if (found) {
        cout << "YES" << endl;

        // Reconstruct path
        string path;
        Cell current = end;
        while (current.x != start.x || current.y != start.y) {
            path.push_back(direction[current.x][current.y]);
            current = previous[current.x][current.y];
        }
        reverse(path.begin(), path.end());

        cout << path.length() << endl;
        cout << path << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
