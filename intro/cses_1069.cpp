#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;

    if (s.empty()) {
        cout << 0 << endl;
        return 0;
    }

    int maxLength = 1;
    int currentLength = 1;
    char currentChar = s[0];

    for (size_t i = 1; i < s.size(); ++i) {
        if (s[i] == currentChar) {
            ++currentLength;
        } else {
            maxLength = max(maxLength, currentLength);
            currentChar = s[i];
            currentLength = 1;
        }
    }

    // Final check for the last repetition
    maxLength = max(maxLength, currentLength);

    cout << maxLength << endl;

    return 0;
}
