#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int MAX = 200005;  // 2 * m
vector<int> adj[2 * MAX];  // Graph for implications
vector<int> adjRev[2 * MAX];  // Reverse graph for SCC
int index[MAX], lowlink[MAX], scc[MAX];
bool onStack[MAX];
stack<int> S;
int idx = 0, sccCounter = 0;

void tarjan(int u) {
    index[u] = lowlink[u] = idx++;
    S.push(u);
    onStack[u] = true;

    for (int v : adj[u]) {
        if (index[v] == -1) {
            // v has not been visited
            tarjan(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (onStack[v]) {
            // v is in the stack, so update the lowlink
            lowlink[u] = min(lowlink[u], index[v]);
        }
    }

    if (lowlink[u] == index[u]) {
        int v;
        do {
            v = S.top();
            S.pop();
            onStack[v] = false;
            scc[v] = sccCounter;
        } while (v != u);
        sccCounter++;
    }
}

// Function to add implication: A -> B
void addImplication(int a, int b) {
    adj[a].push_back(b);
}

bool twoSAT(int m) {
    // Step 1: Find SCCs using Tarjan's algorithm
    fill(index, index + 2 * m, -1);  // Initialize index array
    fill(lowlink, lowlink + 2 * m, -1);
    fill(onStack, onStack + 2 * m, false);

    for (int i = 0; i < 2 * m; i++) {
        if (index[i] == -1) {
            tarjan(i);
        }
    }

    // Step 2: Check if x and ¬x are in the same SCC
    for (int i = 0; i < m; i++) {
        if (scc[2 * i] == scc[2 * i + 1]) {
            return false;  // x and ¬x are in the same SCC, so no solution
        }
    }

    return true;
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        string wish1, wish2;
        int topping1, topping2;
        cin >> wish1 >> topping1 >> wish2 >> topping2;

        topping1--;  // Normalize topping to 0-indexed
        topping2--;

        int sign1 = (wish1 == "+") ? 0 : 1;  // +x -> sign=0, -x -> sign=1
        int sign2 = (wish2 == "+") ? 0 : 1;

        // Implications: ¬x -> y is the same as (¬x or y)
        addImplication(2 * topping1 + sign1, 2 * topping2 + (sign2 ^ 1));  // ¬x1 -> x2
        addImplication(2 * topping2 + sign2, 2 * topping1 + (sign1 ^ 1));  // ¬x2 -> x1
    }

    if (!twoSAT(m)) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        // Output the solution based on the SCC component assignment
        for (int i = 0; i < m; i++) {
            if (scc[2 * i] > scc[2 * i + 1]) {
                cout << "+";
            } else {
                cout << "-";
            }
        }
        cout << endl;
    }

    return 0;
}
