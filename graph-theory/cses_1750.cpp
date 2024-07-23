#include <iostream>
#include <vector>
using namespace std;

const int MAX_L = 30; // 2^32 is larger than 10^9, suffices for k <= 10^9
const int MAXN = 2e5 + 5;
int lift[MAXN][MAX_L];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> teleports(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> teleports[i];
    }

    // vector<vector<int>> lift(n + 1, vector<int>(MAX_L));
    
    // Initialize the lift table
    for (int i = 1; i <= n; ++i) {
        lift[i][0] = teleports[i];
    }
    
    // Fill the table
    for (int j = 1; j < MAX_L; ++j) {
        for (int i = 1; i <= n; ++i) {
            lift[i][j] = lift[lift[i][j-1]][j-1];
        }
    }
    
    while (q--) {
        int x, k;
        cin >> x >> k;
        int current = x;
        
        for (int j = 0; j < MAX_L; ++j) {
            if (k & (1 << j)) {
                current = lift[current][j];
            }
        }
        
        cout << current << "\n";
    }
    
    return 0;
}
