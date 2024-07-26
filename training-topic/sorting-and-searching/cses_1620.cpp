#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
long long n, t;

bool canProduceProductsInTime(const vector<long long>& machines, long long n, long long t, long long time) {
    long long totalProducts = 0;
    for (long long machine : machines) {
        totalProducts += time / machine;
        if (totalProducts >= t) {
            return true;
        }
    }
    return false;
}

long long findMinimumTime(vector<long long>& machines, long long n, long long t) {
    long long left = 1;
    long long right = *max_element(machines.begin(), machines.end()) * t;
    long long result = right;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (canProduceProductsInTime(machines, n, t, mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int main() {
    
    cin >> n >> t;
    vector<long long> machines(n);
    for (long long i = 0; i < n; ++i) {
        cin >> machines[i];
    }

    cout << findMinimumTime(machines, n, t) << endl;

    return 0;
}
