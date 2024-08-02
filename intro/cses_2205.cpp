#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to generate Gray code sequence of length n
vector<string> generateGrayCode(int n) {
    if (n == 0) {
        return {""};
    }
    
    vector<string> previousGrayCode = generateGrayCode(n - 1);
    vector<string> grayCode;
    
    // Prefix with '0'
    for (const string& code : previousGrayCode) {
        grayCode.push_back("0" + code);
    }
    
    // Prefix with '1' and reverse the previousGrayCode
    for (auto it = previousGrayCode.rbegin(); it != previousGrayCode.rend(); ++it) {
        grayCode.push_back("1" + *it);
    }
    
    return grayCode;
}

int main() {
    int n;
    cin >> n;
    
    vector<string> grayCode = generateGrayCode(n);
    
    for (const string& code : grayCode) {
        cout << code << endl;
    }
    
    return 0;
}
