#include <iostream>
#include <vector>
using namespace std;

const int MOD = 998244353;

int main() {
    int N;
    cin >> N;
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }
    
    // dp[i] will store if we can paint square i black
    vector<bool> dp(N + 1, false);
    dp[1] = true;  // initially only square 1 is black
    
    for (int i = 1; i <= N; i++) {
        if (!dp[i]) continue;  // skip if we can't reach this square
        for (int j = i + A[i]; j <= N; j += A[i]) {
            dp[j] = true;
        }
    }
    
    // Now count how many distinct sets of squares can be painted black
    vector<int> painted;
    for (int i = 1; i <= N; i++) {
        if (dp[i]) painted.push_back(i);
    }
    
    // The number of distinct sets that can be painted is the number of 
    // different reachable squares. 
    // Each dp[i] tells us if square i can be painted.
    int result = 1;
    for (int i = 0; i < painted.size(); i++) {
        result = (result * 2) % MOD;
    }
    
    cout << result << endl;
    
    return 0;
}

// g++ -std=c++11 -O2 -Wall test.cpp -o a && ./a < a.in