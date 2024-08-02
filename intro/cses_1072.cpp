#include <iostream>
#include <vector>

using namespace std;

// Function to count the number of attacking pairs of knights on a k x k board
long long countAttackingPairs(int k) {
    if (k < 3) return 0;
    
    long long count = 0;
    // Knights can attack in 8 possible ways
    int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    
    // Check each cell on the board
    for (int i = 1; i <= k; ++i) {
        for (int j = 1; j <= k; ++j) {
            for (int d = 0; d < 8; ++d) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni >= 1 && ni <= k && nj >= 1 && nj <= k) {
                    count++;
                }
            }
        }
    }
    
    // Each attacking pair is counted twice (once from each knight's perspective)
    return count / 2;
}

int main() {
    int n;
    cin >> n;
    
    vector<long long> results(n);
    
    for (int k = 1; k <= n; ++k) {
        long long totalPairs = (long long)k * k * (k * k - 1) / 2;
        long long attackingPairs = countAttackingPairs(k);
        results[k - 1] = totalPairs - attackingPairs;
    }
    
    for (const auto& result : results) {
        cout << result << endl;
    }
    
    return 0;
}
