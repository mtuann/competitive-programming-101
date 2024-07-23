#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
vector<int> graph[MAXN];
vector<int> scc[MAXN];
bool inStack[MAXN];
int index[MAXN], lowlink[MAXN], component[MAXN];
stack<int> nodeStack;
int indexCounter = 0, sccCount = 0;
int n, m;

void tarjan(int u) {
    index[u] = lowlink[u] = indexCounter++;
    nodeStack.push(u);
    inStack[u] = true;

    for (int v : graph[u]) {
        if (index[v] == -1) {
            // v has not been visited
            tarjan(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (inStack[v]) {
            // v is in the stack (part of the current SCC)
            lowlink[u] = min(lowlink[u], index[v]);
        }
    }

    // If u is a root node, pop the stack and generate an SCC
    if (lowlink[u] == index[u]) {
        vector<int> currentSCC;
        int v;
        do {
            v = nodeStack.top();
            nodeStack.pop();
            inStack[v] = false;
            component[v] = sccCount;
            currentSCC.push_back(v);
        } while (v != u);
        scc[sccCount++] = currentSCC;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b; // Convert to 0-based indexing
        graph[a].push_back(b);
    }

    fill(index, index + n, -1); // Initialize all indices to -1
    fill(lowlink, lowlink + n, -1); // Initialize all lowlink values to -1

    for (int i = 0; i < n; ++i) {
        if (index[i] == -1) {
            tarjan(i);
        }
    }

    // Output results
    cout << sccCount << endl;
    for (int i = 0; i < n; ++i) {
        cout << component[i] + 1 << " "; // Convert back to 1-based indexing
    }
    cout << endl;

    return 0;
}
