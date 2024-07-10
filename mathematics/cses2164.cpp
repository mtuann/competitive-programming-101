#include <iostream>
using namespace std;

int josephus_mth_removal(int n, int k, int m) {
    int index = 0;  // Bắt đầu từ người đầu tiên
    for (int i = 1; i <= m; ++i) {
        index = (index + k - 1) % n;
        cout << i << " " << index << endl;
        if (i == m) {
            return index + 1;  // Chuyển từ chỉ số bắt đầu từ 0 sang 1
        }
        --n;  // Số lượng người giảm đi 1
    }
    return -1;  // Trong trường hợp không tìm thấy
}


// const int MAX = 1e5 + 5;
// int dp[MAX];
// // Function to find the k-th removed child

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;

    while (q--) {
        int n, k;
        cin >> n >> k;
        cout << n << " " << k << endl;
        cout << josephus_mth_removal(n, 2, k) << "\n";
    }

    return 0;
}
// g++ -std=c++14 -o a cses2164.cpp && ./a < a.in