/*
Problem Name: Sliding Median
Problem Link: https://cses.fi/problemset/task/1076
Author: Sachin Srivastava (mrsac7)
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
// using namespace __gnu_pbds;
using namespace std;
template<typename... T>
void see(T&... args) { ((cin >> args), ...);}
template<typename... T>
void put(T&&... args) { ((cout << args << " "), ...);}
template<typename... T>
void putl(T&&... args) { ((cout << args << " "), ...); cout<<'\n';}
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {cerr << *it << "=" << a << ", "; err(++it, args...);}
#define int long long
#define pb push_back
#define F first
#define S second
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define vi vector<int>
#define vii vector<pii>
#define vc vector
#define L cout<<'\n';
#define E cerr<<'\n';
#define all(x) x.begin(),x.end()
#define rep(i,a,b) for (int i=a; i<b; ++i)
#define rev(i,a,b) for (int i=a; i>b; --i)
#define IOS ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define setpr(x) cout<<setprecision(x)<<fixed
#define sz size()
#define seea(a,x,y) for(int i=x;i<y;i++){cin>>a[i];}
#define seev(v,n) for(int i=0;i<n;i++){int x; cin>>x; v.push_back(x);}
#define sees(s,n) for(int i=0;i<n;i++){int x; cin>>x; s.insert(x);}
#define ordered_set tree<int, null_type,less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>
const ll inf = INT_MAX;
const ld ep = 0.0000001;
const ld pi = acos(-1.0);
const ll md = 1000000007;

void solve(){
    int n,k; see(n,k);
    priority_queue<pii> l; //max heap == elements lesser than median in rev
    priority_queue<pii,vii,greater<pii>> r; //min heap == elements greater than median rev
    int a[n+1];
    seea(a,0,n);
    int m = (k+1)/2, b=0;
    rep(i,0,n){
        //dead elements
        while(!r.empty() && r.top().S<=i-k) r.pop();
        while(!l.empty() && l.top().S<=i-k) l.pop();
        cout << "i: " << i << '\n';
        if (b<m){ //store in left heap (least elements)
            r.push({a[i],i});
            l.push(r.top()); r.pop();
            b++;
        }
        else{ //store in right heap (greatest elements)
            l.push({a[i],i}); r.push(l.top());
            l.pop();
        }
        // print all elements in left heap
        cout<<"Left Heap: ";
        priority_queue<pii> temp = l;
        while(!temp.empty()) cout<<temp.top().F<<" ", temp.pop();
        cout<<'\n';

        // print all elements in right heap
        cout<<"Right Heap: ";
        priority_queue<pii,vii,greater<pii>> temp1 = r;
        while(!temp1.empty()) cout<<temp1.top().F<<" ", temp1.pop();
        

        // print median

        while(!r.empty() && r.top().S<=i-k) r.pop();
        while(!l.empty() && l.top().S<=i-k) l.pop();

        // if (i<k-1) continue;
        cout << '\n';
        put(l.top().F);
        cout<<'\n' << "\n";
        

        if (a[i-k+1]<=l.top().F) b--;//element to be removed lies in left heap then decrease balance 
        //to cause next addition in left heap
    }
}    
signed main(){
    IOS;
    #ifdef LOCAL
    freopen("input.txt", "r" , stdin);
    freopen("output.txt", "w", stdout);
    #endif
    int t=1;
    //cin>>t;
    while(t--){
        solve();
        //cout<<'\n';
    }
    #ifdef LOCAL
    clock_t tStart = clock();
    cerr<<fixed<<setprecision(10)<<"\nTime Taken: "<<(double)(clock()- tStart)/CLOCKS_PER_SEC<<endl;
    #endif
}

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <algorithm>
// #include <functional>

// using namespace std;

// // Helper function to add a number to the heaps and maintain balance
// void addNumber(priority_queue<int> &maxHeap, priority_queue<int, vector<int>, greater<int>> &minHeap, int num) {
//     if (maxHeap.empty() || num <= maxHeap.top()) {
//         maxHeap.push(num);
//     } else {
//         minHeap.push(num);
//     }
//     // Balance the heaps
//     if (maxHeap.size() > minHeap.size() + 1) {
//         minHeap.push(maxHeap.top());
//         maxHeap.pop();
//     } else if (minHeap.size() > maxHeap.size()) {
//         maxHeap.push(minHeap.top());
//         minHeap.pop();
//     }
// }

// // Helper function to remove a number from the heaps and maintain balance
// void removeNumber(priority_queue<int> &maxHeap, priority_queue<int, vector<int>, greater<int>> &minHeap, int num) {
//     if (num <= maxHeap.top()) {
//         // Use a temporary container to remove the element from the heap
//         priority_queue<int> temp;
//         while (!maxHeap.empty() && maxHeap.top() != num) {
//             temp.push(maxHeap.top());
//             maxHeap.pop();
//         }
//         if (!maxHeap.empty()) maxHeap.pop(); // Remove the element
//         while (!temp.empty()) {
//             maxHeap.push(temp.top());
//             temp.pop();
//         }
//     } else {
//         // Use a temporary container to remove the element from the heap
//         priority_queue<int, vector<int>, greater<int>> temp;
//         while (!minHeap.empty() && minHeap.top() != num) {
//             temp.push(minHeap.top());
//             minHeap.pop();
//         }
//         if (!minHeap.empty()) minHeap.pop(); // Remove the element
//         while (!temp.empty()) {
//             minHeap.push(temp.top());
//             temp.pop();
//         }
//     }
//     // Balance the heaps
//     if (maxHeap.size() > minHeap.size() + 1) {
//         minHeap.push(maxHeap.top());
//         maxHeap.pop();
//     } else if (minHeap.size() > maxHeap.size()) {
//         maxHeap.push(minHeap.top());
//         minHeap.pop();
//     }
// }

// // Function to calculate the medians of each window of k elements
// vector<int> slidingWindowMedians(const vector<int>& arr, int k) {
//     vector<int> result;
//     priority_queue<int> maxHeap; // Max-heap for the left side
//     priority_queue<int, vector<int>, greater<int>> minHeap; // Min-heap for the right side
    
//     for (int i = 0; i < int(arr.size()); ++i) {
//         addNumber(maxHeap, minHeap, arr[i]);
//         if (i >= k - 1) {
//             // Add the median of the current window to the result
//             result.push_back(maxHeap.top());
//             // Remove the element that is going out of the window
//             removeNumber(maxHeap, minHeap, arr[i - k + 1]);
//         }
//     }
//     return result;
// }

// int main() {
//     int n, k;
//     cin >> n >> k;
    
//     vector<int> arr(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> arr[i];
//     }
    
//     vector<int> medians = slidingWindowMedians(arr, k);
//     for (int median : medians) {
//         cout << median << " ";
//     }
//     cout << endl;

//     return 0;
// }


// #include <iostream>
// #include <vector>
// #include <set>

// using namespace std;

// void insertMultiset(multiset<int>& ms, int value) {
//     ms.insert(value);
// }

// void eraseMultiset(multiset<int>& ms, int value) {
//     auto it = ms.find(value);
//     if (it != ms.end()) {
//         ms.erase(it);
//     }
// }

// int getMedian(const multiset<int>& ms, int k) {
//     auto it = ms.begin();
//     advance(it, (k - 1) / 2);
//     return *it;
// }

// int main() {
//     int n, k;
//     cin >> n >> k;
    
//     vector<int> arr(n);
//     for (int i = 0; i < n; ++i) {
//         cin >> arr[i];
//     }
    
//     multiset<int> window;
//     vector<int> medians;

//     for (int i = 0; i < n; ++i) {
//         insertMultiset(window, arr[i]);
        
//         if (i >= k - 1) {
//             medians.push_back(getMedian(window, k));
//             eraseMultiset(window, arr[i - k + 1]);
//         }
//     }
    
//     for (int median : medians) {
//         cout << median << " ";
//     }
//     cout << endl;
    
//     return 0;
// }
