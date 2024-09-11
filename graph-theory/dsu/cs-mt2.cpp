#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <cstring>

#define pii pair<int, int>
#define fi first
#define se second
using namespace std;
int n, m;

const int MAXN = 1e3 + 10;

int height[MAXN * MAXN];
int grid[MAXN * MAXN];
int parent[MAXN * MAXN];

const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int getRow(int index) { return index / n; }
int getCol(int index) { return index % n; }
int toIndex(int x, int y) { return x * n + y; }
bool isValid(int x, int y) { return x >= 0 && x < m && y >= 0 && y < n; }
bool cmp(int a, int b) {
    return height[a] > height[b];
}
vector<int> ans(MAXN * MAXN);


vector<list<int>> component(MAXN * MAXN);
void implementation() {
    for (int i = 0; i < n * m; i++) {
        parent[i] = -1;
        // component[i].push_back(i);
    }
}

int find_parent(int u) {
    return parent[u] == u ? u : parent[u] = find_parent(parent[u]);
}

void union_set(int a, int b, int current_height) {
    a = find_parent(a);
    b = find_parent(b);
    if (a == b) return;
    if (height[a] > height[b]) swap(a, b);
    // cout << a << " :: " << b << endl;
    parent[a] = b;
    if (height[a] == height[b]) {
        component[b].splice(component[b].end(), component[a]);
    }
    else {
        for (int i : component[a]) {
            ans[i] = height[a] - current_height;
        }
        component[a].clear();
    }
    return;
}
int main() {

    cin >> m >> n;
    implementation();
    // int dx[] = {1, n, -1, -n};
    // int dx[] = {-n, n, -1 , 1};
    // const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> height[toIndex(i, j)];
        }
    }
    for (int i = 0; i < n * m; i++) {
        grid[i] = i;
    }
    sort(grid, grid + n * m, cmp);
    // cout << grid[0] << endl;
    memset(parent, -1, sizeof(parent));

    for (int i = 0; i < n * m; i++) {
        // cout << "Grid:" << grid[i] << " ";
        parent[grid[i]] = grid[i];
        component[grid[i]].push_back(grid[i]);
        int nx = getRow(grid[i]);
        int ny = getCol(grid[i]);

        for (int j = 0; j < 4; j++) {
            int rows = nx + directions[j][0];
            int cols = ny + directions[j][1];
            int pos = toIndex(rows, cols);
            if (isValid(rows, cols) && parent[ pos ] != -1) {
                union_set(grid[i], pos, height[grid[i]]);
            }
        }
    }
    // Assign the final height to all cells in the largest component
    int root = find_parent(0);
    for (int idx : component[root]) {
        ans[idx] = height[root];
    }

    for (int i = 0; i < n * m; i++) {
        cout << ans[i] << " ";
        if (i % n == n - 1) cout << endl;
    }
    

    return 0;
}
// g++ -std=c++11 -O2 -Wall cs-mt2.cpp -o a && ./a < a.in