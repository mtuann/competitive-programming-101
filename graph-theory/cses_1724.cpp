#include <iostream>
#include <vector>
#include <algorithm>
#define INF 2000000000000000000LL
#define MOD 1000000007
using namespace std;

// Define matrix type
typedef vector<vector<long long>> Matrix;

// Function to multiply two matrices (relaxation step)
Matrix matMul(const Matrix &a, const Matrix &b, int n) {
    Matrix result(n, vector<long long>(n, INF));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                if (a[i][k] != INF && b[k][j] != INF) {
                    result[i][j] = min(result[i][j], a[i][k] + b[k][j]);
                }
            }
        }
    }
    return result;
}

// Function to perform matrix exponentiation
Matrix matPow(Matrix base, long long exp, int n) {
    Matrix result(n, vector<long long>(n, INF));
    // Initialize result as the identity matrix
    for (int i = 0; i < n; ++i) {
        result[i][i] = 0;
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

    // Initialize adjacency matrix with INF
    Matrix adj(n, vector<long long>(n, INF));

    // Read edges
    for (int i = 0; i < m; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        --a; --b;  // Convert to 0-based indexing
        adj[a][b] = min(adj[a][b], c);  // Store the minimum weight of the edge
    }

    // Perform matrix exponentiation to calculate the shortest paths with exactly k edges
    Matrix result = matPow(adj, k, n);

    // Output the result
    if (result[0][n-1] == INF) {
        cout << -1 << endl;  // No valid path
    } else {
        cout << result[0][n-1] << endl;  // Minimum path length
    }

    return 0;
}
