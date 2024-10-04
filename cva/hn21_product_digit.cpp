// #include <iostream>
// #include <string>
// #include <algorithm>

// using namespace std;

// // Function to multiply a number represented as a string by a single digit
// string multiply_by_digit(const string& num, int digit) {
//     if (digit == 0) return "0"; // If the digit is 0, product is 0
//     string result;
//     int carry = 0;

//     for (int i = num.size() - 1; i >= 0; --i) {
//         int product = (num[i] - '0') * digit + carry;
//         result += (product % 10) + '0'; // Store the last digit
//         carry = product / 10; // Carry over the remaining
//     }
    
//     // If there's any carry left, add it to the result
//     while (carry) {
//         result += (carry % 10) + '0';
//         carry /= 10;
//     }

//     reverse(result.begin(), result.end()); // Reverse to get the correct order
//     return result;
// }

// // Function to calculate the product of digits of a large number represented as a string
// string digit_product(const string& num) {
//     string product = "1"; // Start with a multiplicative identity
//     for (char ch : num) {
//         int digit = ch - '0';  // Convert char to digit
//         if (digit == 0) return "0";  // If any digit is 0, the product will be 0
//         product = multiply_by_digit(product, digit); // Multiply the product by the digit
//     }
//     return product;
// }

// // Function to compare two large numbers represented as strings
// bool is_greater_equal(const string& a, const string& b) {
//     if (a.size() != b.size()) {
//         return a.size() > b.size();
//     }
//     return a >= b;
// }

// // Function to get the maximum digit product in range [a, b]
// string find_max_digit_product(const string& a, const string& b) {
//     string max_product = digit_product(a);
//     string result = a;

//     // Check the number b itself
//     string b_product = digit_product(b);
//     if (b_product > max_product) {
//         max_product = b_product;
//         result = b;
//     }

//     // Try to create numbers by setting some digits to 9 from b
//     int n = b.size();

//     // Check the number by modifying digits of b
//     for (int i = 0; i < n; ++i) {
//         if (b[i] == '0') continue;  // Skip if the digit is already 0

//         // Create a number by decreasing the current digit and setting subsequent digits to 9
//         string temp = b;
//         temp[i]--;  // Decrease the current digit
//         for (int j = i + 1; j < n; ++j) {
//             temp[j] = '9';  // Set all digits after to 9
//         }

//         // Only consider temp if it is >= a
//         if (is_greater_equal(temp, a)) {
//             string candidate_product = digit_product(temp);
//             if (candidate_product > max_product) {
//                 max_product = candidate_product;
//                 result = temp;
//             }
//         }
//     }

//     return max_product;
// }

// int main() {
//     string a, b;
//     cin >> a >> b;

//     string result = find_max_digit_product(a, b);
//     cout << result << endl;

//     return 0;
// }


// // g++ -std=c++11 hn21_product_digit.cpp -o a && ./a < a.in