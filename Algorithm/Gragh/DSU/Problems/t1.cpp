#include<bits/stdc++.h>

using namespace std;

#define IOS cin.tie(nullptr) -> ios::sync_with_stdio(false)
#define ll long long
#define ull unsigned long long
//#define int ll
#define pii pair<int, int>
#define all(x) x.begin(),x.end()
#define fer(i, m, n) for(int i = m; i < n; ++i)
#define ferd(i, m, n) for(int i = m; i >= n; --i)
#define dbg(x) cerr << #x << char(61) << x << " ###\n"
#define dbg_arr(a, i) cerr << #a << '[' << i << "]=" << a[i] << " ###\n";

#define lowbit(x)  ((x) & -(x))
#define popcount(x)  __builtin_popcount(x)
#define popcountll(x)  __builtin_popcountll(x)
#define clz(x)  __builtin_clz(x)
#define ctz(x)  __builtin_ctz(x)

using u32 = unsigned;
using i64 = ll;
using u64 = ull;
using i128 = __int128;
using u128 = unsigned __int128;

const int MOD = 1e9 + 7;
const int N = 2e5 + 2;
const int inf = 1e9;

struct DSU {
    int n;
    vector<int> fa, sz;
    vector<int> nxt;

    // 节点编号从 1 开始
    DSU(int n) : n(n) {
        fa.resize(n + 1);
        iota(all(fa), 0);
        sz.resize(n + 1, 1);
        nxt.resize(n + 2);
        iota(all(nxt), 1);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    // 找到编号 ≥ x 的第一个“未跳过”点
    int findNxt(int x) {
        return x == nxt[x] ? x : nxt[x] = findNxt(nxt[x]);
    }

    void merge(int x, int y) {
        int rx = find(x), ry = find(y);
        if(rx != ry) {
            if(sz[rx] < sz[ry]) swap(rx, ry);
            fa[ry] = rx;
            sz[rx] += sz[ry];
        }
    }

    void mergeRange(int l, int r) {
        int x = nxt[l];
        while(x <= r) {
            merge(l, x);
            nxt[x] = r + 1;
            x = findNxt(x);
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    int size(int x) {
        return sz[find(x)];
    }
};

signed main() {
    IOS;

    int n;
    cin >> n;
    DSU uf(n);
    vector<int> color(n + 2);

    int q;
    cin >> q;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r, c;
            cin >> l >> r >> c;
            uf.mergeRange(l, r);
            color[uf.find(l)] = c;
        } else if(op == 2) {
            int x;
            cin >> x;
            cout << color[uf.find(x)] << '\n';
        }
    }    

    return 0;
}