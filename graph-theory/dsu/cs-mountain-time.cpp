// https://csacademy.com/contest/archive/task/mountain-time
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

const int MAXN = 1e3 + 10, MAXM = 1e3 + 10;
const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int rows, cols;
int height[MAXN * MAXM], parent[MAXN * MAXM], order[MAXN * MAXM], answer[MAXN * MAXM];
// vector<int> component[MAXN * MAXM];
list<int> component[MAXN * MAXM];

// Utility functions to map between 1D and 2D coordinates
int getRow(int index) { return index / cols; }
int getCol(int index) { return index % cols; }
int toIndex(int x, int y) { return x * cols + y; }
bool isValid(int x, int y) { return x >= 0 && x < rows && y >= 0 && y < cols; }

// DSU functions
int findRoot(int u) {
    return (u == parent[u]) ? u : parent[u] = findRoot(parent[u]);
}

// Union two sets by height and update component answer
void unionSets(int u, int v, int currentHeight) {
    u = findRoot(u), v = findRoot(v);
    if (u == v) return;

    // Merge smaller height component into the larger one
    if (height[u] > height[v]) swap(u, v);

    parent[u] = v;

    // If heights are equal, merge the lists
    if (height[u] == height[v]) {
        component[v].splice(component[v].end(), component[u]);
        // merge(component[u].begin(), component[u].end(), back_inserter(component[v]));
        // component[v].insert(component[v].end(), component[u].begin(), component[u].end());
        // component[u].clear();
        
    } else {
        // Update answer for all elements in the smaller component
        // cout << "UPDATE: " << u << " " << v << " " << height[u] << " " << currentHeight << endl;
        for (int idx : component[u]) {
            answer[idx] = height[u] - currentHeight;
            // cout << "ANSWER: " << idx << " " << answer[idx] << endl;
            if (answer[idx] == 2) {
                cout << "ANSWER: " << idx << " " << answer[idx] << " " << height[u] << " " << currentHeight << endl;
            }
        }
        component[u].clear();
    }
}

// Custom comparator to sort cells by height (descending)
bool compareByHeight(int i, int j) {
    return height[i] > height[j];
}

int main() {
    // Input: read the dimensions of the grid
    cin >> rows >> cols;

    // Read the heights of the grid cells
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> height[toIndex(i, j)];
        }
    }

    // Initialize the order of the cells and sort them by height (descending)
    for (int i = 0; i < rows * cols; i++) {
        order[i] = i;
    }
    sort(order, order + rows * cols, compareByHeight);

    // Initialize DSU (Disjoint Set Union)
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < rows * cols; i++) {
        cout << "Grid:" << order[i] << " ";
        int cellIndex = order[i];
        int x = getRow(cellIndex), y = getCol(cellIndex);

        // Initialize a new component with only this cell
        parent[cellIndex] = cellIndex;
        component[cellIndex].push_back(cellIndex);

        // Try to merge with neighboring cells
        for (int d = 0; d < 4; d++) {
            int nx = x + directions[d][0], ny = y + directions[d][1];
            if (cellIndex == 8) {
                cout << "NEIGHBOR: " << nx << " " << ny << " " << toIndex(nx, ny) << " " << parent[toIndex(nx, ny)] << endl;
            }
            int neighborIndex = toIndex(nx, ny);
            if (isValid(nx, ny) && parent[neighborIndex] != -1) {
                unionSets(cellIndex, neighborIndex, height[cellIndex]);
                cout << "ALL: " << cellIndex << " " << neighborIndex << " " << height[cellIndex] << endl;
                if (neighborIndex == 7) {
                    cout << "Union: " << cellIndex << " " << neighborIndex << " " << height[cellIndex] << endl;
                }
                
            }
        }
    }

    // Assign the final height to all cells in the largest component
    int root = findRoot(0);
    for (int idx : component[root]) {
        answer[idx] = height[root];
    }

    // Output the results
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << answer[toIndex(i, j)] << " ";
        }
        cout << endl;
    }

    return 0;
}

// g++ -std=c++11 -O2 -Wall cs-mountain-time.cpp -o a && ./a < a.in