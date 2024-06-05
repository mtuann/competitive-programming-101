// write disjoin set union find
// Time Complexity: O(logn) for find and O(1) for union
// Space Complexity: O(n)
#include <iostream>
#include <vector>
using namespace std;

class DSU {
    vector<int> parent; // parent of each node: if parent[i] = i, then i is the root
    vector<int> rank; // rank is used to keep the tree balanced
public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union_set(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[px] = py;
            rank[py]++;
        }
    }
};

int main() {
    DSU dsu(5);
    dsu.union_set(0, 1);
    dsu.union_set(1, 2);
    dsu.union_set(3, 4);
    cout << dsu.find(0) << endl;
    cout << dsu.find(2) << endl;
    cout << dsu.find(3) << endl;
    return 0;
}

// clang++ -std=c++17 -o dsu dsu.cpp
