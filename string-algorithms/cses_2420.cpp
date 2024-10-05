#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string s;

class SegmentTree {
private:
    vector<vector<int>> tree;
    int n;

    void build(int node, int start, int end, const string &s) {
        if (start == end) {
            // Leaf node will have a single character
            tree[node][s[start] - 'a']++;
        } else {
            int mid = (start + end) / 2;
            build(2 * node + 1, start, mid, s);
            build(2 * node + 2, mid + 1, end, s);
            // Merge counts from the left and right child
            for (int i = 0; i < 26; ++i) {
                tree[node][i] = tree[2 * node + 1][i] + tree[2 * node + 2][i];
            }
        }
    }

    void update(int node, int start, int end, int idx, char oldChar, char newChar) {
        if (start == end) {
            // Leaf node
            tree[node][oldChar - 'a']--;
            tree[node][newChar - 'a']++;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, oldChar, newChar);
            } else {
                update(2 * node + 2, mid + 1, end, idx, oldChar, newChar);
            }
            // Merge counts from the left and right child
            for (int i = 0; i < 26; ++i) {
                tree[node][i] = tree[2 * node + 1][i] + tree[2 * node + 2][i];
            }
        }
    }

    vector<int> query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return vector<int>(26, 0); // No overlap
        }
        if (l <= start && end <= r) {
            return tree[node]; // Total overlap
        }
        // Partial overlap
        int mid = (start + end) / 2;
        vector<int> leftCount = query(2 * node + 1, start, mid, l, r);
        vector<int> rightCount = query(2 * node + 2, mid + 1, end, l, r);
        vector<int> result(26);
        for (int i = 0; i < 26; ++i) {
            result[i] = leftCount[i] + rightCount[i];
        }
        return result;
    }

public:
    SegmentTree(const string &s) : n(s.size()) {
        tree.resize(4 * n, vector<int>(26, 0));
        build(0, 0, n - 1, s);
    }

    void update(int idx, char newChar) {
        char oldChar = ' '; // Placeholder for the old character
        for (int i = 0; i < n; ++i) {
            if (i == idx) {
                oldChar = s[i];
                break;
            }
        }
        update(0, 0, n - 1, idx, oldChar, newChar);
    }

    bool isPalindrome(int l, int r) {
        vector<int> count = query(0, 0, n - 1, l, r);
        int oddCount = 0;
        for (int c : count) {
            if (c % 2 != 0) {
                oddCount++;
            }
        }
        // For a substring to be a palindrome:
        // At most one character can have an odd count
        return oddCount <= 1;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    cin >> s;

    SegmentTree segmentTree(s);

    for (int i = 0; i < m; ++i) {
        int type;
        cin >> type;
        if (type == 1) { // Update operation
            int k;
            char x;
            cin >> k >> x; // Read position k and character x
            segmentTree.update(k - 1, x); // Update the character (convert 1-based to 0-based)
        } else if (type == 2) { // Palindrome check operation
            int a, b;
            cin >> a >> b; // Read positions a and b
            // Check if substring is a palindrome
            if (segmentTree.isPalindrome(a - 1, b - 1)) { // Convert to 0-based
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}
