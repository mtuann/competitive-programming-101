#include <iostream>
#include <vector>
#define MOD 1000000007
using namespace std;

// Define matrix type
typedef vector<vector<long long>> Matrix;

// Function to multiply two matrices
Matrix matMul(const Matrix &a, const Matrix &b, int n) {
    Matrix result(n, vector<long long>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return result;
}

// Function to perform matrix exponentiation
Matrix matPow(Matrix base, long long exp, int n) {
    Matrix result(n, vector<long long>(n, 0));
    // Initialize result as the identity matrix
    for (int i = 0; i < n; ++i) {
        result[i][i] = 1;
    }
    // Perform exponentiation
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = matMul(result, base, n);
        }
        base = matMul(base, base, n);
        exp /= 2;
    }
    return result;
}

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;

    // Initialize adjacency matrix
    Matrix adj(n, vector<long long>(n, 0));

    // Read edges
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;  // Convert to 0-based indexing
        adj[a][b] = (adj[a][b] + 1) % MOD;
    }

    // Exponentiate the adjacency matrix
    Matrix result = matPow(adj, k, n);

    // The result is the number of paths from node 1 to node n
    cout << result[0][n-1] << endl;

    return 0;
}
