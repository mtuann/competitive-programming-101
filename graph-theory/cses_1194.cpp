#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<string> labyrinth(n);
    Point start;
    vector<Point> monsters;

    for (int i = 0; i < n; ++i) {
        cin >> labyrinth[i];
        for (int j = 0; j < m; ++j) {
            if (labyrinth[i][j] == 'A') {
                start = {i, j};
            } else if (labyrinth[i][j] == 'M') {
                monsters.push_back({i, j});
            }
        }
    }

    // Directions for moving up, down, left, and right
    vector<int> dx = {0, 0, -1, 1};
    vector<int> dy = {-1, 1, 0, 0};
    string dir = "LRUD";

    // Check if the starting position is already on the boundary
    if (start.x == 0 || start.x == n - 1 || start.y == 0 || start.y == m - 1) {
        cout << "YES" << endl;
        cout << 0 << endl;
        return 0;
    }

    // BFS from all monster positions to calculate minimum time to reach each cell
    vector<vector<int>> monster_time(n, vector<int>(m, INT_MAX));
    queue<Point> mq;
    for (auto& monster : monsters) {
        mq.push(monster);
        monster_time[monster.x][monster.y] = 0;
    }

    while (!mq.empty()) {
        auto [x, y] = mq.front();
        mq.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && labyrinth[nx][ny] == '.' && monster_time[nx][ny] == INT_MAX) {
                monster_time[nx][ny] = monster_time[x][y] + 1;
                mq.push({nx, ny});
            }
        }
    }

    // BFS from the player's starting position to find the shortest safe path to the boundary
    vector<vector<int>> player_time(n, vector<int>(m, INT_MAX));
    vector<vector<Point>> parent(n, vector<Point>(m, {-1, -1}));
    queue<Point> pq;
    pq.push(start);
    player_time[start.x][start.y] = 0;

    bool found = false;
    Point exit_point = {-1, -1};

    while (!pq.empty() && !found) {
        auto [x, y] = pq.front();
        pq.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && labyrinth[nx][ny] == '.' && player_time[nx][ny] == INT_MAX) {
                if (player_time[x][y] + 1 < monster_time[nx][ny]) {
                    player_time[nx][ny] = player_time[x][y] + 1;
                    parent[nx][ny] = {x, y};
                    pq.push({nx, ny});
                    if (nx == 0 || nx == n - 1 || ny == 0 || ny == m - 1) {
                        found = true;
                        exit_point = {nx, ny};
                        break;
                    }
                }
            }
        }
    }

    if (!found) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        vector<char> path;
        Point current = exit_point;
        while (current.x != start.x || current.y != start.y) {
            Point prev = parent[current.x][current.y];
            for (int i = 0; i < 4; ++i) {
                if (prev.x + dx[i] == current.x && prev.y + dy[i] == current.y) {
                    path.push_back(dir[i]);
                    break;
                }
            }
            current = prev;
        }
        reverse(path.begin(), path.end());
        cout << path.size() << endl;
        for (char c : path) {
            cout << c;
        }
        cout << endl;
    }

    return 0;
}
