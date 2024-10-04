#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int n, k, q;
int na, nb;
pair<int, int> a[100005];
pair<int, int> b[100005];
struct query {
    int l, r, id;
};
query c[100005];
int ans_c[100005];
// pair<int, int> c[100005];

int nexta[100005];
// int nextak[100005][20];
// int nextak[100005][30];
int rmq[100005][20];

int get_next_k(int u, int k) {
    int res = u;
    // k -= 1;
    // for (int i = 0; i < 20; i++) {
    //     if (k & (1 << i)) {
    //         res = nextak[res][i];
    //     }
    // }
    for (int i = 1; i < k; i++) {
        res = nexta[res];
    }
    // using rmq to get the next k
    
    return res;
}

// building segment tree with size [4 * 4 * 1e5]
int max_seg[4 * 4 * 100005];
int val_max[4 * 100005];
void build(int id, int l, int r) {
    if (l == r) {
        max_seg[id] = val_max[l];
        return;
    }
    int mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    max_seg[id] = max(max_seg[id * 2], max_seg[id * 2 + 1]);
}

void update(int id, int l, int r, int pos, int val) {
    if (l == r) {
        max_seg[id] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(id * 2, l, mid, pos, val);
    } else {
        update(id * 2 + 1, mid + 1, r, pos, val);
    }
    max_seg[id] = max(max_seg[id * 2], max_seg[id * 2 + 1]);
}

int get(int id, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return max_seg[id];
    int mid = (l + r) / 2;
    return max(get(id * 2, l, mid, u, v), get(id * 2 + 1, mid + 1, r, u, v));
}

map<int, int> mp;


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> na >> q >> k;
    for (int i = 1; i <= na; i++) {
        cin >> a[i].first >> a[i].second;
    }
    // remove all the intervals that are inside another interval using sorting
    sort(a + 1, a + na + 1);
    int last = -1;
    for (int i = 1; i <= na; i++) {
        if (a[i].second <= last) continue;
        b[++nb] = a[i];
        last = a[i].second;
    }
    na = nb;
    for (int i = 1; i <= na; i++) {
        a[i] = b[i];
        // cout << a[i].first << " " << a[i].second << endl;
    }
    // cout << "End" << endl;
    // find the next interval that can be reached from the current interval, i.e for [l, r] find the largest value of l that is less than r
    
    for (int i = 1; i <= na; i++) {
        int ll = i + 1, rr = na;
        while (ll < rr) {
            int mid = (ll + rr + 1) / 2;
            if (a[mid].first <= a[i].second) {
                ll = mid;
            } else {
                rr = mid - 1;
            }
        }

        nexta[i] = i;

        if (ll <= na && a[ll].first <= a[i].second) {
            nexta[i] = ll;
        } 
        // else {
        //     nexta[i] = i;
        // }
        // cout << i << " " << nexta[i] << endl;
        // nextak[i][1] = nexta[i];
    }
    // for (int j = 2; j < 20; j++) {
    //     for (int i = 1; i <= na; i++) {
    //         nextak[i][j] = nextak[nextak[i][j - 1]][j - 1];
    //     }
    // }
    // init rmq
    for (int i = 1; i <= na; i++) {
        rmq[i][0] = nexta[i];
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 1; i <= na; i++) {
            rmq[i][j] = rmq[rmq[i][j - 1]][j - 1];
        }
    }
    // for (int i = 1; i <= na; i++) {
    //     cout << a[i].first << " " << a[i].second << " " << nexta[i] << endl;
    // }   
    // cout << "END" << endl;
    // for (int kk = 0; kk < 30; kk++) {
    //     int s = 1;
    //     for (int i = 0; i < 20; i++) {
    //         if (kk & (1 << i)) {
    //             s = rmq[s][i];
    //         }
    //     }
    //     cout << kk << " " << s << endl;
    // }
    // cout << rmq[1][4] << endl;
    nb = 0;
    for(int i = 1; i <= na; i++) {
        int pos = i;
        // int pos = get_next_k(i, k);
        for (int j = 0; j < 20; j++) {
            if (k & (1 << j)) {
                pos = rmq[pos][j];
            }
        }
        // pos = min(pos, na);
        // int pos = get_next_k(i, k);
        b[++nb] = {a[i].first, a[pos].second};
        // cout << a[i].first << " " << a[i].second << " " << a[pos].first << " " << a[pos].second << endl;
        // for (int j = 1; j < k; j++) {
        //     pos = nextak[pos][j];
        // }
        // cout << a[i].first << " " << a[i].second << " " << a[pos].first << " " << a[pos].second << endl;
        
    }

    // for (int i = 1; i <= nb; i++) {
    //     cout << b[i].first << " " << b[i].second << endl;
    // }
    // remove all the intervals that are inside another interval using sorting
    sort(b + 1, b + nb + 1);
    last = -1;
    na = 0;
    for (int i = 1; i <= nb; i++) {
        if (b[i].second <= last) continue;
        a[++na] = b[i];
        last = b[i].second;
    }
    // cout << "----------" << endl;
    // for (int i = 1; i <= na; i++) {
    //     cout << a[i].first << " " << a[i].second << endl;
    // }
    for (int i = 1; i <= q; i++) {
        cin >> c[i].l >> c[i].r;
        c[i].id = i;
    }
    // sort c in increasing order of the second value
    sort(c + 1, c + q + 1, [](query x, query y) {
        return x.r < y.r;
    });

    // for (int i = 1; i <= q; i++) {
    //     cout << c[i].first << " " << c[i].second << endl;
    // }
    for (int i = 1; i <= na; i++) {
        if (mp.find(a[i].first) == mp.end()) {
            mp[a[i].first] = 1;
        }
        if (mp.find(a[i].second) == mp.end()) {
            mp[a[i].second] = 1;
        }
    }
    for (int i = 1; i <= q; i++) {
        if (mp.find(c[i].l) == mp.end()) {
            mp[c[i].l] = 1;
        }
        if (mp.find(c[i].r) == mp.end()) {
            mp[c[i].r] = 1;
        }
    }
    int cnt = 0;
    for (auto &x : mp) {
        x.second = ++cnt;
    }
    // cout << "cnt = " << cnt << endl;
    // cout << "A array" << endl;
    // for (int i = 1; i <= na; i++) {
    //     cout << mp[a[i].first] << " " << mp[a[i].second] << endl;
    // }
    // cout << "C array" << endl;
    // for (int i = 1; i <= q; i++) {
    //     cout << mp[c[i].first] << " " << mp[c[i].second] << endl;
    // }
    
    int pos_update = 1;
    for (int i = 1; i <= q; ++i) {
        int u = c[i].l, v = c[i].r;
        // cout << "Checking: " << u << " " << v << endl;
        while (pos_update <= na && a[pos_update].second <= v) {
            update(1, 1, cnt, mp[a[pos_update].first], a[pos_update].second - a[pos_update].first);
            // val_max[mp[a[pos_update].first]] = a[pos_update].second;
            // cout << "Update " <<  "i = " << i << " " << mp[a[pos_update].first] << " " << a[pos_update].second - a[pos_update].first << endl;
            pos_update++;
        }
        int max_ans = get(1, 1, cnt, mp[u], mp[v]);
        
        // cout << "Max ans = " << mp[u] << " " << mp[v] << " " <<  max_ans << endl;
        // continue;
        // finding the last position that a[i].first <= u
        int l = 1, r = na;
        int pos = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (a[mid].first <= u) {
                pos = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (pos != 0 && a[pos].second >= u) {
            max_ans = max(max_ans, min(v, a[pos].second) - u);
            // cout << "ans1 = " << min(v, a[pos].second) - u << endl;
        }
        // finding the first position that a[i].second >= v
        l = 1, r = na;
        pos = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (a[mid].second >= v) {
                pos = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (pos != 0 && a[pos].first <= v) {
            max_ans = max(max_ans, v - max(u, a[pos].first));
            // cout << "ans2 = " << v - max(u, a[pos].first) << endl;
        }
        // cout << max_ans << endl;
        ans_c[c[i].id] = max_ans;
        // cout << c[i].id << " " << max_ans << endl;
    }
    for (int i = 1; i <= q; i++) {
        cout << ans_c[i] << endl;
    }

    return 0;
}

//  g++ -std=c++11 -O2 -Wall hn21_p6.cpp -o a && ./a < a.in