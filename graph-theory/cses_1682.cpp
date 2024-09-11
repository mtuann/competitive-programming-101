#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> index, lowlink, component;
vector<bool> inStack;
stack<int> nodeStack;
vector<vector<int>> scc;
vector<int> dfsNode;
int indexCounter = 0, sccCount = 0;

void tarjan(int u) {
    index[u] = lowlink[u] = indexCounter++;
    nodeStack.push(u);
    inStack[u] = true;

    for (int v : graph[u]) {
        if (index[v] == -1) {
            tarjan(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (inStack[v]) {
            lowlink[u] = min(lowlink[u], index[v]);
        }
    }

    if (lowlink[u] == index[u]) {
        int v;
        scc.push_back(vector<int>());
        do {
            v = nodeStack.top();
            nodeStack.pop();
            inStack[v] = false;
            component[v] = sccCount;
            scc[sccCount].push_back(v);
        } while (v != u);
        sccCount++;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    index.assign(n + 1, -1);
    lowlink.assign(n + 1, 0);
    component.assign(n + 1, -1);
    inStack.assign(n + 1, false);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    // Run Tarjan's algorithm on all nodes
    for (int i = 1; i <= n; i++) {
        if (index[i] == -1) {
            tarjan(i);
            dfsNode.push_back(i);
        }
    }

    // Check if all cities belong to the same SCC
    if (sccCount == 1) {
        cout << "YES\n";
    } else {
        // Find two cities that belong to different SCCs
        for (int i = 1; i <= n; i++) {
            for (int v : graph[i]) {
                if (component[i] != component[v]) {
                    cout << "NO\n" << v << " " << i << "\n";
                    return 0;
                }
            }
        }
        cout << "NO\n" << dfsNode[0] << " " << dfsNode[1] << "\n";

    }

    return 0;
}
