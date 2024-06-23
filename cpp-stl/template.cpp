#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Uncomment the lines below for fast input/output
#define fast_io ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
// #define endl '\n'

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;

#define INF 1000000000
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORR(i, a, b) for (int i = (a); i >= (b); --i)
#define REP(i, n) FOR(i, 0, n)
#define REPR(i, n) FORR(i, n, 0)
#define TR(c, it) for (auto it = (c).begin(); it != (c).end(); ++it)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define SWAP(a, b) { a ^= b; b ^= a; a ^= b; }

#define DEBUG(x) cerr << #x << " = " << x << endl;
#define DEBUG_ARRAY(arr, n) { REP(i, n) cerr << arr[i] << " "; cerr << endl; }

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int lcm(int a, int b) { return a / gcd(a, b) * b; }

int main() {
    // adding fast_io for fast input/output
    fast_io;

    // Your code here

    return 0;
}