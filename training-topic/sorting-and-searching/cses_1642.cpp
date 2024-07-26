#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    unordered_map<int, vector<pair<int, int>>> pair_sum_map;
    
    // Store all pairs and their indices
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = arr[i] + arr[j];
            pair_sum_map[sum].emplace_back(i, j);
        }
    }
    
    // Check for valid quadruples
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = arr[i] + arr[j];
            int complement = x - sum;
            
            if (pair_sum_map.find(complement) != pair_sum_map.end()) {
                for (auto& [p1, p2] : pair_sum_map[complement]) {
                    if (p1 != i && p1 != j && p2 != i && p2 != j) {
                        cout << p1 + 1 << " " << p2 + 1 << " " << i + 1 << " " << j + 1 << endl;
                        return 0;
                    }
                }
            }
        }
    }
    
    cout << "IMPOSSIBLE" << endl;
    return 0;
}


// g++ -std=c++17 -o a cses_1642.cpp && ./a < a.in
