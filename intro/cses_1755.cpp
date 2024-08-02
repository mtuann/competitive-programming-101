#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

string constructPalindrome(const string& s) {
    unordered_map<char, int> freq;
    
    // Count frequencies of each character
    for (char ch : s) {
        freq[ch]++;
    }
    
    string first_half;
    char odd_char = '\0';
    
    // Determine if we can create a palindrome
    for (const auto& pair : freq) {
        char ch = pair.first;
        int count = pair.second;
        
        if (count % 2 != 0) {
            if (odd_char != '\0') return "NO SOLUTION"; // More than one odd frequency
            odd_char = ch; // Store the character with odd frequency
        }
        
        first_half += string(count / 2, ch); // Append half of the characters
    }
    
    // Create the second half by mirroring the first half
    string second_half = first_half;
    reverse(second_half.begin(), second_half.end());
    
    // Construct the palindrome
    string palindrome = first_half;
    if (odd_char != '\0') {
        palindrome += odd_char; // Add the odd character in the center if exists
    }
    palindrome += second_half;
    
    return palindrome;
}

int main() {
    string s;
    cin >> s;
    
    cout << constructPalindrome(s) << endl;
    
    return 0;
}
