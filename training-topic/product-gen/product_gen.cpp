#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to generate a random number in a given range [min, max]
long long randomNumber(long long min, long long max) {
    long long res = 0;
    for (int i = 0; i < 4; ++i)
        res = (res << 15) + (rand() & 0x7FFF);
    return min + res % (max - min + 1);
}

int main() {
    freopen("product.inp", "w", stdout);
    srand(time(nullptr)); // Seed for random number generation

    // random a, b in range [1, 10^9] with 4 subtask [1, 10], [1, 1e3], [1, 1e6], [1, 1e9]
    long long type = randomNumber(1, 4);
    long long a, b;
    if (type == 1) {
        a = randomNumber(1, 10);
        b = randomNumber(1, 10);
    } else if (type == 2) {
        a = randomNumber(1, 1000);
        b = randomNumber(1, 1000);
    } else if (type == 3) {
        a = randomNumber(1, 1000000);
        b = randomNumber(1, 1000000);
    } else {
        a = randomNumber(1, 1000000000);
        b = randomNumber(1, 1000000000);
    }
    cout << a << " " << b << endl;
    cerr << a << " " << b << endl;
    return 0;
}