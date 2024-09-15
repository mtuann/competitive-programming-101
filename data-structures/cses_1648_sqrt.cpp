#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SqrtDecomposition {
private:
    vector<long long> arr, block_sum;
    int block_size;

public:
    SqrtDecomposition(const vector<long long>& input) {
        int n = input.size();
        block_size = sqrt(n);
        arr = input;
        block_sum.assign((n + block_size - 1) / block_size, 0);

        // Initialize block sums
        for (int i = 0; i < n; ++i) {
            block_sum[i / block_size] += arr[i];
        }
    }

    // Update value at index k to u
    void update(int k, int u) {
        int block_idx = k / block_size;
        block_sum[block_idx] += u - arr[k];
        arr[k] = u;
    }

    // Query sum in range [a, b]
    long long query(int a, int b) {
        long long sum = 0;
        int start_block = a / block_size;
        int end_block = b / block_size;

        if (start_block == end_block) {
            // If a and b are in the same block, just iterate through the range
            for (int i = a; i <= b; ++i) {
                sum += arr[i];
            }
        } else {
            // Sum elements from a to the end of the start block
            for (int i = a; i < (start_block + 1) * block_size; ++i) {
                sum += arr[i];
            }
            // Sum full blocks between start_block and end_block
            for (int i = start_block + 1; i < end_block; ++i) {
                sum += block_sum[i];
            }
            // Sum elements from the beginning of the end block to b
            for (int i = end_block * block_size; i <= b; ++i) {
                sum += arr[i];
            }
        }

        return sum;
    }
};

int main() {
    int n, q;
    cin >> n >> q;

    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    SqrtDecomposition sqrtDec(arr);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            // Update query: 1 k u
            int k, u;
            cin >> k >> u;
            sqrtDec.update(k - 1, u); // 1-based index to 0-based
        } else if (type == 2) {
            // Sum query: 2 a b
            int a, b;
            cin >> a >> b;
            cout << sqrtDec.query(a - 1, b - 1) << endl; // 1-based index to 0-based
        }
    }

    return 0;
}

// g++ -std=c++11 -O2 -Wall cses_1648_sqrt.cpp -o a && ./a < a.in
