#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class SuffixArray {
public:
    SuffixArray(const string& s) : text(s), n(s.size()) {
        buildSuffixArray();
        buildLCP();
    }

    vector<int> getSuffixArray() const {
        return suffixArray;
    }

    vector<int> getLCP() const {
        return lcpArray;
    }

private:
    string text;
    int n;
    vector<int> suffixArray;
    vector<int> lcpArray;

    void buildSuffixArray() {
        suffixArray.resize(n);
        vector<int> rank(n), temp(n), count(max(256, n), 0);
        
        // Initial ranking based on the first character
        for (int i = 0; i < n; ++i) {
            rank[i] = text[i];
            suffixArray[i] = i;
        }

        // Sort based on the rank
        for (int length = 1; length < n; length *= 2) {
            fill(count.begin(), count.end(), 0);
            for (int i = 0; i < n; ++i) {
                count[rank[i]]++;
            }
            for (int i = 1; i < count.size(); ++i) {
                count[i] += count[i - 1];
            }
            for (int i = n - 1; i >= 0; --i) {
                int current = suffixArray[i];
                int next = (current + length < n) ? rank[current + length] : 0;
                suffixArray[--count[rank[current]]] = current;
                temp[count[rank[current]]] = next;
            }
            swap(rank, temp);
        }
    }

    void buildLCP() {
        lcpArray.resize(n);
        vector<int> rank(n);
        for (int i = 0; i < n; ++i) {
            rank[suffixArray[i]] = i;
        }
        
        int h = 0;
        for (int i = 0; i < n; ++i) {
            if (rank[i]) {
                int j = suffixArray[rank[i] - 1];
                while (i + h < n && j + h < n && text[i + h] == text[j + h]) {
                    h++;
                }
                lcpArray[rank[i]] = h;
                if (h) {
                    h--;
                }
            }
        }
    }
};

int main() {
    string s;
    cin >> s; // Read the string
    int k;
    cin >> k; // Read the value of k

    SuffixArray sa(s);
    vector<int> suffixArray = sa.getSuffixArray();
    vector<int> lcpArray = sa.getLCP();

    vector<string> distinctSubstrings;

    // Count distinct substrings
    for (int i = 0; i < suffixArray.size(); ++i) {
        int suffixIndex = suffixArray[i];
        int length = s.size() - suffixIndex; // Total length of the suffix
        int lcpLength = (i == 0) ? 0 : lcpArray[i]; // LCP with previous suffix

        // Number of new substrings contributed by this suffix
        int numNewSubstrings = length - lcpLength;

        for (int j = 1; j <= numNewSubstrings; ++j) {
            distinctSubstrings.push_back(s.substr(suffixIndex, j));
        }
    }

    // Sort and get the k-th substring
    sort(distinctSubstrings.begin(), distinctSubstrings.end());
    cout << distinctSubstrings[k - 1] << endl; // Output the k-th smallest substring

    return 0;
}
