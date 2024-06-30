
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define fi   first
#define se   second

template<class X, class Y>
    bool minimize(X &x, const Y &y) {
        if (x > y) {
            x = y;
            return true;
        } else return false;
    }
    
#define MAX   300300
int numNode, numEdge; // số đỉnh và số cạnh
pair<int, int> edges[MAX]; // danh sách các cạnh
vector<int> adj[MAX]; // danh sách kề
// used là mảng đánh dấu cạnh đã dùng, bridge là mảng đánh dấu cạnh là cầu.
bool used[MAX], bridge[MAX]; 
int low[MAX], num[MAX], cnt;
int numChild[MAX]; // numChild[u] = số con của đỉnh u trên cây DFS
bool isCut[MAX]; // isCut là mảng đánh dấu đỉnh là khớp

void dfs(int u) {
    low[u] = numNode + 1;
    num[u] = ++cnt;
    
    for (int id : adj[u]) if (!used[id]) { // xét các cạnh kề với u mà chưa được sử dụng
        used[id] = true; // đánh dấu cạnh (u, v) là đã sử dụng
        // lấy ra đỉnh còn lại trong hai đỉnh kề với u
        int v = edges[id].fi + edges[id].se - u;
        if (num[v] == 0) {
            numChild[u]++; // v là con của u, nên số con của u tăng 1
            dfs(v);
            minimize(low[u], low[v]);
            if (low[v] > num[u]) bridge[id] = true;
            if (low[v] >= num[u]) isCut[u] = true;
        } else minimize(low[u], num[v]);
    }
}

int main() {
    // đọc đồ thị
    scanf("%d%d", &numNode, &numEdge);
    for (int i = 1; i <= numEdge; i++) { // đọc vào các cạnh
        int u, v; scanf("%d%d", &u, &v);
        edges[i] = make_pair(u, v);
        // lưu ý, danh sách kề không lưu các đỉnh kề với nó mà lưu chỉ số của các cạnh kề
        // với nó.
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    for (int i = 1; i <= numNode; i++) {
        dfs(i); // khi một đỉnh có hàm dfs được gọi qua đây, nó là gốc của cây dfs
        if (numChild[i] == 1) isCut[i] = false; // gốc chỉ có 1 con thì không phải là khớp.
    }
    int cntBridge = 0, cntCut = 0;
    for (int i = 1; i <= numEdge; i++) if (bridge[i]) cntBridge++;
    for (int i = 1; i <= numNode; i++) if (isCut[i]) cntCut++;
    printf("%d %d\n", cntCut, cntBridge);
    return 0;
}

// g++ -std=c++17 -o a bridges_duplicate.cpp && ./a < a.in