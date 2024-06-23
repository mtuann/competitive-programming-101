#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class SparseTable {
private:
    std::vector<std::vector<int>> st;
    std::vector<int> log;

public:
    SparseTable(const std::vector<int>& arr) {
        int n = arr.size();
        int K = log2(n) + 1;
        
        st.resize(n, std::vector<int>(K));
        log.resize(n + 1);

        // Precompute logs
        log[1] = 0;
        for (int i = 2; i <= n; i++)
            log[i] = log[i / 2] + 1;

        // Initialize Sparse Table for the intervals of length 1
        for (int i = 0; i < n; i++)
            st[i][0] = arr[i];

        // Compute values from smaller to bigger intervals
        for (int j = 1; j <= K; j++) {
            for (int i = 0; (i + (1 << j)) <= n; i++) {
                st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int query(int L, int R) {
        int j = log[R - L + 1];
        return std::min(st[L][j], st[R - (1 << j) + 1][j]);
    }
};

int main() {
    std::vector<int> arr = {1, 3, 2, 7, 9, 11};
    SparseTable st(arr);

    std::cout << "Minimum value in range (1, 4): " << st.query(1, 4) << std::endl; // Output: 2
    std::cout << "Minimum value in range (0, 5): " << st.query(0, 5) << std::endl; // Output: 1

    return 0;
}
