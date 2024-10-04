#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

// Function to calculate the product of digits of a number
ll digit_product(ll n) {
    ll product = 1;
    while (n > 0) {
        ll digit = n % 10;
        if (digit == 0) return 0;  // If any digit is 0, the product will be 0
        product *= digit;
        n /= 10;
    }
    return product;
}

// Function to get the number with maximum digit product in range [a, b]
ll find_max_digit_product(ll a, ll b) {
    ll max_product = digit_product(a);
    ll result = a;

    // Check all candidate numbers near b by changing digits to 9
    string s_b = to_string(b);
    int n = s_b.size();

    // Check the number b itself
    ll b_product = digit_product(b);
    if (b_product > max_product) {
        max_product = b_product;
        result = b;
    }
    // Try to create numbers by setting some digits to 9 from b
    for (int i = 0; i < n; ++i) {
        if (s_b[i] == '0') continue;  // Skip if the digit is already 0

        // Create a number by decreasing the current digit and setting subsequent digits to 9
        string temp = s_b;
        temp[i]--;  // Decrease the current digit
        for (int j = i + 1; j < n; ++j) {
            temp[j] = '9';  // Set all digits after to 9
        } 

        ll candidate = stoll(temp);
        if (candidate >= a) {
            ll candidate_product = digit_product(candidate);
            if (candidate_product > max_product) {
                max_product = candidate_product;
                result = candidate;
            }
        }
    }

    return result;
}

int main() {
    ll a, b;
    cin >> a >> b;

    ll result = find_max_digit_product(a, b);
    cout << result << endl;

    return 0;
}

// g++ -std=c++11 hn21_product_digit2.cpp -o a && ./a