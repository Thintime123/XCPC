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
	vector<int> fa, rank;
	vector<int> sz;

	// 节点编号从 1 开始
	DSU(int n) : n(n) {
		fa.resize(n + 1);
		iota(all(fa), 0);
		rank.resize(n + 1);
		sz.resize(n + 1, 1);
	}

	int find(int x) {
		return x == fa[x] ? x : fa[x] = find(fa[x]);
	}

	void merge(int x, int y) {
		int rx = find(x), ry = find(y);
		if(rx != ry) {
			if(sz[rx] < sz[ry]) swap(rx, ry);
			fa[ry] = rx;
			sz[rx] += sz[ry];
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

    int n, m;
    cin >> n >> m;
    DSU uf(n);

    vector<vector<int>> g(n + 1);

    fer(i, 0, m) {
    	int a, b;
    	cin >> a >> b;
    	a++, b++;
    	g[a].push_back(b), g[b].push_back(a);
    }
    int k;
    cin >> k;
    vector<bool> st(n + 1, true);
    vector<int> arr(k);
    fer(i, 0, k) {
    	cin >> arr[i];
    	arr[i]++;
    	st[arr[i]] = false;
    }

    int cnt = n - arr.size();
    fer(u, 1, n + 1) {
    	if(!st[u]) continue;

    	for(auto v : g[u]) {
    		if(st[v]) {
    			if(!uf.same(u, v)) cnt--;
    			uf.merge(u, v);
    		}
    	}
    }

    

    vector<int> res;
    ferd(i, k - 1, 0) {
    	res.push_back(cnt);

    	int u = arr[i];
    	st[u] = true;
    	
    	bool ok = false;
    	fer(j, 0, g[u].size()) {
    		int v = g[u][j];
    		if(st[v]) {
    			if(j == 0) {
    				ok = true;
    				uf.merge(u, v);
    			} else {
    				if(!uf.same(u, v)) cnt--;
    				uf.merge(u, v);
    			}
    		}
    	}
    	if(!ok) cnt++;
    }
    reverse(all(res));
    cout << cnt << '\n';
    for(auto x : res) cout << x << '\n';

    return 0;
}