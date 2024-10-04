#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;

int dp[10][2][100][100];
vector<int> dig;
int k;

int f(int pos, bool tight, int sum, int rem) {
    // cout << pos << " " << tight << " " << sum << " " << rem << endl;
    if (pos == dig.size()) {
        return (rem == 0 && sum % k == 0);
        // if (rem == 0 && sum % k == 0) return dp[pos][tight][sum][rem] = 1;
        // else return dp[pos][tight][sum][rem] = 0;
    }
    int lim = tight ? dig[pos] : 9;
    if (dp[pos][tight][sum][rem] != -1) return dp[pos][tight][sum][rem];
    dp[pos][tight][sum][rem] = 0;
    for (int i = 0; i <= lim; i++) {
        dp[pos][tight][sum][rem] += f(pos + 1, tight && i == lim, sum + i, (rem * 10 + i) % k);
    }
    return dp[pos][tight][sum][rem];
}

void solve(int stt) {
    ll u, v;
    cin >> u >> v >> k;
    string a, b;
    
    a = to_string(u - 1);
    b = to_string(v);
    
    dig.clear();
    memset(dp, -1, sizeof(dp));
    for (auto c : a) dig.push_back(c - '0');
    int counta = f(0, 1, 0, 0);

    memset(dp, -1, sizeof(dp));
    dig.clear();
    for (auto c : b) dig.push_back(c - '0');
    int countb = f(0, 1, 0, 0);

    cout << "Case " << stt << ": " << countb - counta << endl;
}

int main() {
    int t;
    cin >> t;
    int stt = 0;
    while (t--) {
        solve(++stt);
    }

}

// g++ -std=c++11 -O2 -Wall LightOJ-1068.cpp -o a && ./a < a.in