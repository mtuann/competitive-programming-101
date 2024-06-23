#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr(i,j,k) for(int i=j;i<k;i++)
#define f(n) fr(i,0,n)
#define f1(n) fr(i,1,n+1)
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
const int mod = 1e9 + 7;
/*ll mi[1048576];
void build(int x, int l, int r) {
    if (l == r) {
        cin >> mi[x];
        return;
    }
    int mid = (l + r) >> 1;
    build(x<<1, l, mid);
    build(x<<1|1, mid + 1, r);
    mi[x] = max(mi[x<<1],mi[x<<1|1]);
}
void pushdown(int x) {
    if (!mi[x]) return;
    mi[x<<1] += mi[x];
    mi[x<<1|1] += mi[x];
    mi[x] = 0;
}
int query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) {
        return mi[x];
    }
    int mid = (l + r) >> 1;
    int mx = 0;
    if (ql <= mid) {
        mx = max(mx, query(x<<1,l,mid,ql,qr));
    }
    if (qr > mid){
        mx = max(mx, query(x<<1|1,mid+1,r,ql,qr));
    }
    return mx;
}
void update(int x, int l, int r, int pos, int v) {
    if (l == r) {
        mi[x] -= v;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        update(x<<1,l,mid,pos,v);
    }
    else {
        update(x<<1|1,mid+1,r,pos,v);
    }
    mi[x] = max(mi[x<<1],mi[x<<1|1]);
}*/
vector<ll>d;
int v[1058005];
int b[1058005];
int getID(int x) {
    return lower_bound(all(d),x) - d.begin() + 1;
}
void update(int x,int d) {
    //cout << x <<' '<<d<<endl;
    while (x < (1<<20)) {
        b[x] += d;
        x += (x) & (-x);
    }
}
int query(int x) {
    //cout << x << endl;
    int ret = 0;
    while (x) {
        ret += b[x];
        x -= x & (-x);
    }
    return ret;
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int,pair<int,int>>>op;
    f1(n) {
        cin >> v[i];
        d.pb(v[i]);
    }
    f1(m) {
        char c;
        int x, y;
        cin >> c;
        cin >> x >> y;
        if (c == '!') {
            op.pb({1,{x,y}});
            d.pb(y);
        }
        else {
            op.pb({2,{x,y}});
            d.pb(x);
            d.pb(y);
        }
    }
    sort(all(d));
    d.erase(unique(all(d)),d.end());
    f1(n) {
        update(getID(v[i]), 1);
    }
    for (auto &i : op) {
        if (i.F == 1) {
            update(getID(v[i.S.F]), -1);
            v[i.S.F] = i.S.S;
            update(getID(v[i.S.F]), 1);
        }
        else {
            cout << query(getID(i.S.S)) - query(getID(i.S.F) - 1) << '\n';
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    t = 1;
    while (t--) {
        solve();
    }
}