#include <iostream>
#include <vector>

using namespace std;

void de_bruijn(string& result, const string& alphabet, int n, int k) {
    vector<int> a(k * n);
    for (int i = 0; i < k * n; ++i) {
        a[i] = 0;
    }
    result = "";
    int j = 1;
    while (j <= n) {
        a[j] = 1;
        int i = 1;
        while (i <= j) {
            result += alphabet[a[i]];
            ++i;
        }
        while (a[j] == k - 1) {
            a[j] = 0;
            --j;
        }
        ++a[j];
        ++j;
    }
}

int main() {
    int n;
    cin >> n;

    if (n < 1 || n > 15) {
        cerr << "Invalid input" << endl;
        return 1;
    }

    string alphabet = "01";
    string result;

    de_bruijn(result, alphabet, n, 2);

    // To convert cyclic to linear, append first n-1 characters to the end
    result += result.substr(0, n - 1);

    cout << result << endl;

    return 0;
}
