#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>

using namespace std;

int n;
vector<pair<long long, long long>> v;
long long sumc[2222];
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        v.push_back({x, y});
    }
    // sort v by first element
    
    if (v.empty()) {
        cout << 0 << endl;
        return 0;
    }
    sort(v.begin(), v.end());
    sumc[0] = v[0].second;
    for (int i = 1; i < n; i++) {
        sumc[i] = sumc[i - 1] + v[i].second;
    }
    
    long long ans = 0;

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            long long max_c = v[i].first + v[j].first;
            int l = j + 1, r = n - 1;
            int pos1 = -1, pos2 = -1;
            // finding the last element that is less than max_c
            while (l <= r) {
                int mid = (l + r) / 2;
                if (v[mid].first < max_c) {
                    pos1 = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }

            if (pos1 == -1) {
                continue;
            }

            l = j + 1, r = pos1;
            long long min_c2 = v[i].first * v[i].first + v[j].first * v[j].first;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (v[mid].first * v[mid].first < min_c2) {
                    pos2 = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if (pos2 == -1) {
                continue;
            }
            ans += v[i].second * v[j].second * (sumc[pos2] - sumc[j]);
            // cout << i << " " << j << " " << pos2 << " " <<  v[i].first << " " << v[j].first << " " << v[pos2].first << " " << v[i].second << " " << v[j].second << " " << v[pos2].second << " " << v[i].second * v[j].second * (sumc[pos2] - sumc[j]) << endl;
        }
    }
    cout << ans << endl;
    
    
    return 0;
}

// g++ -std=c++11 -O2 -Wall hn21_p2.cpp -o a && ./a < a.in
