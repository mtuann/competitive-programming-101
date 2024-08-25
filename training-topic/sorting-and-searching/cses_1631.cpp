#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    // Sort the times in descending order
    sort(t.rbegin(), t.rend());

    long long A = 0, B = 0;
    
    for (int i = 0; i < n; ++i) {
        if (A <= B) {
            A += t[i];
        } else {
            B += t[i];
        }
    }

    cout << max(A, B) << endl;
    
    return 0;
}
// g++ -std=c++14 -O2 -Wall cses_1631.cpp -o a && ./a < a.in