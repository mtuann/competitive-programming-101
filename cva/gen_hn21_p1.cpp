#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <numeric>
#include <ctime>

using namespace std;

long long randomNumber(long long min, long long max) {
    long long res = 0;
    for (int i = 0; i < 4; ++i)
        res = (res << 15) + (rand() & 0x7FFF);
    return min + res % (max - min + 1);
}

int main() {
    freopen("a.in", "w", stdout);
    srand(time(0));
    // int l, r = 1e6;
    // random number from 1e6 to 1e8
    long long l = randomNumber(1e6, 1e8);
    long long r = l + randomNumber(1e6, 1e8);
    cout << l << " " << r << endl;
    return 0;
}

// g++ -std=c++11 -O2 -Wall gen_hn21_p1.cpp -o a && ./a < a.in
