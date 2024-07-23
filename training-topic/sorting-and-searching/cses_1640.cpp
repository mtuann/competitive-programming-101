#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    unordered_map<int, int, custom_hash> value_to_index;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        int complement = x - a[i];
        if (value_to_index.find(complement) != value_to_index.end()) {
            cout << value_to_index[complement] + 1 << " " << i + 1 << "\n";
            return 0;
        }
        value_to_index[a[i]] = i;
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
