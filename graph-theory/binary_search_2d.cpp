
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <map>

using namespace std;

const int MAXN = 1e3 + 10;
int x1, y11, x2, y2;
struct hcn {
    int xduoi, xtren, yduoi, ytren;
};

bool RI(int& n){
    bool neg=0;
    char ch;
    for( ch=getchar();ch<'0' || ch>'9';ch=getchar()){
        if(ch==EOF) return 0;
        if(ch=='-') neg=1;
    }
    n=ch-'0';
    for(ch=getchar();ch>='0' && ch<='9';ch=getchar()) n=n*10+ch-'0';
    return 1;
}

bool isCorner(int x, int y, vector<int> treeY) {
    if ((int)treeY.size() == 0) return false;
    // for treeY find lower bound for x
    int lower = lower_bound(treeY.begin(), treeY.end(), x) - treeY.begin();
    // check y value at lower is equal to y
    if (treeY[lower] == x)  return true;
    
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n;
    vector<int> pos_x;
    vector<int> pos_y;
    // set<pair<int, int> > tree_pos;
    vector<pair<int, int>> cay;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        //tree_pos.insert({x, y});
        pos_x.push_back(x);
        pos_y.push_back(y);
        cay.push_back({x, y});
    }
    cin >> p;
    vector<int> kq(p, 0);
    vector<hcn> rec;
    for (int i = 0; i < p; ++i) {
        cin >> x1 >> y11 >> x2 >> y2;
        pos_x.push_back(x1);
        pos_x.push_back(x2);
        pos_y.push_back(y11);
        pos_y.push_back(y2);
        rec.push_back({x1, x2, y11, y2});
    }
    sort(pos_x.begin(), pos_x.end());
    sort(pos_y.begin(), pos_y.end());
    pos_x.erase(unique(pos_x.begin(), pos_x.end()), pos_x.end());
    pos_y.erase(unique(pos_y.begin(), pos_y.end()), pos_y.end());

    map<int, int> vtx, vty;
    for (int i = 0; i < pos_x.size(); ++i) vtx[pos_x[i]] = i + 1;
    for (int i = 0; i < pos_y.size(); ++i) vty[pos_y[i]] = i + 1;

    int nx = pos_x.size();
    int ny = pos_y.size();
    vector<vector<int>> cayx(nx), cayy(ny);
    for (int i = 0; i < n; ++i) {
        int xtemp = cay[i].first;
        int ytemp = cay[i].second;
        int vtxtemp = vtx[xtemp];
        int vtytemp = vty[ytemp];
        cayy[vtytemp].push_back(vtxtemp);
        cayx[vtxtemp].push_back(vtytemp);
    }
    for (int i = 0; i < nx; ++i) sort(cayx[i].begin(), cayx[i].end());
    for (int i = 0; i < ny; ++i) sort(cayy[i].begin(), cayy[i].end());
    //cout << " Check x[1] " << endl;
    for (int i = 0; i < cayx[1].size(); i++)  {
        //cout << cayx[1][i] << " ";
    }
    //cout << " Test xong" << endl;
    for (int i = 0; i < p; ++i) {
        int xtop = vtx[rec[i].xtren];
        int xbot = vtx[rec[i].xduoi];
        int ytop = vty[rec[i].ytren];
        int ybot = vty[rec[i].yduoi];
        // cout << "xbot " << xbot << " xtop " << xtop << " ybot " << ybot << " ytop " << ytop << endl;
        int upper1, lower1, upper2, lower2, upper3, lower3, upper4, lower4;
        
        // cout << "Y:" << ytop << endl;
        // for (int j = 0; j < cayy[ytop].size(); j++) {
        //     cout << cayy[ytop][j] << " ";
        // }
        // cout << endl;

        upper1 = upper_bound(cayy[ytop].begin(), cayy[ytop].end(), xtop) - cayy[ytop].begin();
        lower1 = lower_bound(cayy[ytop].begin(), cayy[ytop].end(), xbot) - cayy[ytop].begin();
        kq[i] += upper1 - lower1;
        // printf("upper1 %d lower1 %d\n", upper1, lower1);
        upper2 = upper_bound(cayy[ybot].begin(), cayy[ybot].end(), xtop) - cayy[ybot].begin();
        lower2 = lower_bound(cayy[ybot].begin(), cayy[ybot].end(), xbot) - cayy[ybot].begin();
        kq[i] += upper2 - lower2;
        // printf("upper2 %d lower2 %d\n", upper2, lower2);

        // cout << "X:" << xtop << endl;
        // for (int j = 0; j < cayx[xtop].size(); j++) {
        //     cout << cayx[xtop][j] << " ";
        // }
        // cout << endl;

        upper3 = upper_bound(cayx[xtop].begin(), cayx[xtop].end(), ytop) - cayx[xtop].begin();
        lower3 = lower_bound(cayx[xtop].begin(), cayx[xtop].end(), ybot) - cayx[xtop].begin();
        kq[i] += upper3 - lower3;
        // printf("upper3 %d lower3 %d\n", upper3, lower3);
        upper4 = upper_bound(cayx[xbot].begin(), cayx[xbot].end(), ytop) - cayx[xbot].begin();
        lower4 = lower_bound(cayx[xbot].begin(), cayx[xbot].end(), ybot) - cayx[xbot].begin();
        kq[i] += upper4 - lower4;
        // printf("upper4 %d lower4 %d\n", upper4, lower4);
        if (isCorner(xtop, ytop, cayy[ytop])) kq[i]--;
        if (isCorner(xtop, ybot, cayy[ybot])) kq[i]--;
        if (isCorner(xbot, ytop, cayy[ytop])) kq[i]--;
        if (isCorner(xbot, ybot, cayy[ybot])) kq[i]--;
        // cout << "After: " << kq[i] << endl;
        // cout << "=====================" << endl;
    }
    for (int i = 0; i < p; ++i) {
        cout << kq[i] << endl;
    }

    return 0;
}

// g++ -std=c++17 -o a test.cpp && ./a < a.in