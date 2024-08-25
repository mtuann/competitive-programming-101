#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
#include <climits>
using namespace std;

struct State {
    int remainder;
    long long cost;
    bool operator>(const State &other) const {
        return cost > other.cost;
    }
};
const int MAXM = 1e5 + 10;
int n, m;
int a[60];
int w[60];
int ndigits[60];
int pow10[10];

long long dist[MAXM];

int num_digits(int n) {
    if (n == 0) return 1;
    int count = 0;
    while (n > 0) {
        n /= 10;
        count++;
    }
    return count;
}

int main() {
    cin >> n >> m;
    // Dijkstra setup
    
    priority_queue<State, vector<State>, greater<State>> pq;
    fill(dist, dist + m, LLONG_MAX);

    for (int i = 0; i < n ; i++) {
        cin >> a[i] >> w[i];
        int rev = a[i] % m;
        // if (rev < 0) rev += m;
        dist[rev] = min(dist[rev], (long long) w[i]);
        pq.push({rev, dist[rev]});
        ndigits[i] = num_digits(a[i]);
    }
    pow10[0] = 1;
    for (int i = 1; i < 10; i++) {
        pow10[i] = (pow10[i - 1] * 10) % m;
    }

    while (!pq.empty()) {
        State u = pq.top();
        pq.pop();
        if (u.cost != dist[u.remainder]) continue;

        for (int i = 0; i < n; i++) {
            // if (a[i] < 0) continue;
            int v = ((1ll * u.remainder * pow10[ndigits[i]]) % m + a[i]) % m;
            // if (v < 0) v += m;
            if (dist[v] > u.cost + w[i]) {
                dist[v] = u.cost + w[i];
                pq.push({v, dist[v]});
            }
        }
    }

    // The answer is the minimum cost to get to remainder 0
    if (dist[0] == LLONG_MAX) {
        cout << "-1" << endl;
    } else {
        cout << dist[0] << endl;
    }
    
    return 0;
}

// g++ -std=c++11 c3-merge.cpp -o a && ./a < a.in