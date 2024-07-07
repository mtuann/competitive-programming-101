#include <iostream>
#include <vector>

using namespace std;

bool is_subtask1(long long n) {
    return n <= 10;
}

bool is_subtask2(long long n) {
    return n <= 1000;
}

bool is_subtask3(long long n) {
    return n <= 1000000;
}

bool is_subtask4(long long n) {
    return n <= 1000000000;
}

namespace subtask1 {
    long long sum(long long n) {
        return n * (n + 1) / 2;
    }
};

namespace subtask2 {
    long long sum(long long n) {
        return n * (n + 1) / 2;
    }
};

namespace subtask3 {
    long long sum(long long n) {
        return n * (n + 1) / 2;
    }
};

namespace subtask4 {
    long long sum(long long n) {
        return n * (n + 1) / 2;
    }
};

int main() {
    long long n;
    cin >> n;

    if (is_subtask1(n)) return cout << subtask1::sum(n) << endl, 0;
    if (is_subtask2(n)) return cout << subtask2::sum(n) << endl, 0;
    if (is_subtask3(n)) return cout << subtask3::sum(n) << endl, 0;
    if (is_subtask4(n)) return cout << subtask4::sum(n) << endl, 0;

    return 0;
}

// g++ -std=c++14 -O2 -Wall -Wextra sumn.cpp -o sumn && ./sumn