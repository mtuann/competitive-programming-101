#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, q;
    cin >> n >> q;

    vector<int> arr(n + 1, 0);
    vector<int> prefix_xor(n + 1, 0);

    // Reading the array values
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    // Compute the prefix XOR array
    for (int i = 1; i <= n; ++i) {
        prefix_xor[i] = prefix_xor[i - 1] ^ arr[i];
    }

    // Process each query
    while (q--) {
        int a, b;
        cin >> a >> b;
        // XOR sum from index a to b is prefix_xor[b] ^ prefix_xor[a - 1]
        cout << (prefix_xor[b] ^ prefix_xor[a - 1]) << endl;
    }

    return 0;
}
