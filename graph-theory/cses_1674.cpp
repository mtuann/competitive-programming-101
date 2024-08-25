#include <iostream>
#include <vector>

using namespace std;

void dfs(int employee, const vector<vector<int>>& subordinates, vector<int>& subordinate_count) {
    for (int subordinate : subordinates[employee]) {
        dfs(subordinate, subordinates, subordinate_count);
        subordinate_count[employee] += 1 + subordinate_count[subordinate];
    }
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> subordinates(n + 1);  // subordinates[i] stores the list of direct subordinates of employee i
    vector<int> subordinate_count(n + 1, 0);  // subordinate_count[i] stores the count of all subordinates of employee i

    // Reading input: each employee's boss
    for (int i = 2; i <= n; i++) {
        int boss;
        cin >> boss;
        subordinates[boss].push_back(i);
    }

    // Perform DFS starting from the general director (employee 1)
    dfs(1, subordinates, subordinate_count);

    // Output the results for all employees from 1 to n
    for (int i = 1; i <= n; i++) {
        cout << subordinate_count[i] << " ";
    }
    cout << endl;

    return 0;
}
