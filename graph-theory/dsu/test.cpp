#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;
//===========================================
const int MAX = 1e6+5;
int arr[MAX], res[MAX], MX, n, m;
bool in[MAX];
vector<int> p, mx;
vector<vector<int>> cmp;

void init(){
    p = vector<int>(n*m+5, -1);
    mx = vector<int>(n*m+5);
    for (int i = 1; i <= n*m; i++) mx[i] = arr[i];
    cmp = vector<vector<int>>(n*m+5);
    for (int i = 1; i <= n*m; i++) cmp[i].push_back(i);
    return;
}

int findP(int x){ return (p[x] < 0? x : p[x] = findP(p[x])); }

void unite(int a, int b){
    printf("update: a = %d, b = %d\n", a, b);
    int val = arr[a];
    a = findP(a), b = findP(b);
    if (a == b) return;
    if (mx[a] < mx[b]) swap(a, b);
    p[b] = a;
    printf("root: a = %d, b = %d\n", a, b);
    // print cmp[a], cmp[b]
    for (int i = 0; i < cmp[a].size(); i++) printf("%d ", cmp[a][i]);
    printf("\n");
    for (int i = 0; i < cmp[b].size(); i++) printf("%d ", cmp[b][i]);
    printf("\n");

    if (mx[a] > mx[b]){
        for (int i = 0; i < cmp[b].size(); i++) res[cmp[b][i]] = val;
        cmp[b].clear();
    }
    if (cmp[a].size() < cmp[b].size()) cmp[a].swap(cmp[b]);
    for (int i = 0; i < cmp[b].size(); i++) cmp[a].push_back(cmp[b][i]);
    // print after merge
    printf("after merge: a = %d, b = %d sz a: %d, sz b: %d\n", a, b, cmp[a].size(), cmp[b].size());
    for (int i = 0; i < cmp[a].size(); i++) printf("%d ", cmp[a][i]);
    cmp[b].clear();
    mx[a] = max(mx[a], mx[b]);
    return;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    //freopen("test.txt", "r", stdin);
    cin >> n >> m;
    vector<pair<int, int>> v;
    for (int i = 1; i <= n*m; i++){
        cin >> arr[i];
        v.push_back(make_pair(arr[i], i));
        MX = max(MX, arr[i]);
    }
    sort(v.rbegin(), v.rend());
    init();
    for (int i = 0; i < n*m; i++){
        int val = v[i].first, x = v[i].second;
        if (val == MX){ in[x] = true; continue; }
        if (x%m != 1 && in[x-1]) unite(x, x-1); //Merge with left
        if (x%m && in[x+1]) unite(x, x+1); //Merge with right
        if (x > m && in[x-m]) unite(x, x-m); //Merge with top
        if (x+m <= n*m && in[x+m]) unite(x, x+m); //Merge with bottom
        in[x] = true;
    }
    for (int i = 1; i <= n*m; i++) cout << arr[i]-res[i] << (i%m == 0? "\n" : " ");
}
// g++ -std=c++17 -o a test.cpp && ./a < a.in