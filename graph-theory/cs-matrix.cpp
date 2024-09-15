// find fibonaci number N using matrix exponentiation
#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;
int base[2][2];
int result[2][2];

void multiply(int a[2][2], int b[2][2]) {
    int res[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            res[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                res[i][j] = (res[i][j] + 1LL * a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            a[i][j] = res[i][j];
        }
    }
}

void power(long long n) {
    result[0][0] = 0; result[0][1] = 1;

    while (n > 0) {
        if (n & 1) {
            multiply(result, base);
        }
        multiply(base, base);
        n >>= 1;
    }

}

int main() {
    long long n;
    cin >> n;
    if (n <= 1) {
        cout << n << endl;
        return 0;
    }
    
    base[0][0] = 0;
    base[0][1] = base[1][0] = base[1][1] = 1;
    
    power(n);
    cout << result[0][0] << endl;

    return 0;
}

// g++ -std=c++11 -O2 -Wall cs-matrix.cpp -o a && ./a < a.in