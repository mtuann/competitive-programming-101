#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

// Matrix multiplication function
vector<vector<long long>> matMul(const vector<vector<long long>> &a, const vector<vector<long long>> &b) {
    int size = a.size();
    vector<vector<long long>> result(size, vector<long long>(size, 0));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return result;
}

// Matrix exponentiation function
vector<vector<long long>> matPow(vector<vector<long long>> base, long long exp) {
    int size = base.size();
    vector<vector<long long>> result(size, vector<long long>(size, 0));
    // Initialize result as the identity matrix
    for (int i = 0; i < size; ++i) {
        result[i][i] = 1;
    }
    // Perform matrix exponentiation
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = matMul(result, base);
        }
        base = matMul(base, base);
        exp /= 2;
    }
    return result;
}

int main() {
    long long n;
    cin >> n;

    // Base cases: precompute for n < 7
    if (n <= 6) {
        cout << (1LL << (n - 1)) % MOD << endl;
        return 0;
    }

    // Transition matrix for the recurrence relation
    vector<vector<long long>> transition(6, vector<long long>(6, 0));

    // Fill the first row with 1s because dp(i) = dp(i-1) + dp(i-2) + ... + dp(i-6)
    for (int i = 0; i < 6; ++i) {
        transition[0][i] = 1;
    }
    // Shift identity for the other rows
    for (int i = 1; i < 6; ++i) {
        transition[i][i-1] = 1;
    }

    // Initial vector for dp(0) to dp(5)
    vector<long long> dp = {1, 2, 4, 8, 16, 32};

    // Perform matrix exponentiation to get the transition matrix raised to power (n-6)
    vector<vector<long long>> powerMatrix = matPow(transition, n - 6);

    // Calculate the result by multiplying the powerMatrix with the initial vector
    long long result = 0;
    for (int i = 0; i < 6; ++i) {
        result = (result + powerMatrix[0][i] * dp[5 - i]) % MOD;
    }

    // Output the result
    cout << result << endl;
    return 0;
}

// g++ -std=c++11 -O2 -Wall cses_1096.cpp -o a && ./a < a.in
