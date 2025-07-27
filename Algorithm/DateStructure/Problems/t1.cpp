#include<bits/stdc++.h>

using namespace std;

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
#define ll long long
#define ull unsigned long long
//#define int ll
#define pii pair<int, int>
#define all(x) x.begin(),x.end()
#define fer(i, m, n) for(int i = m; i < n; ++i)
#define ferd(i, m, n) for(int i = m; i >= n; --i)
#define dbg(x) cerr << #x << char(61) << x << " ###\n"
#define dbg_arr(a, i) cerr << #a << '[' << i << "]=" << a[i] << " ###\n"
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

template<class T>
struct segmentTree {
	struct Node {
		int l, r;
		T sum;
		T lazy;
		T mn, mx;
	};

	int n;
	vector<Node> tr;
	int mod;

	segmentTree(int _n, int p = 1e9 + 7) {
		mod = p;
		init(vector<T> (_n));
	}
	segmentTree(vector<T> a, int p = 1e9 + 7) {
		mod = p;
		init(a);
	}

	void init(vector<T> a) {
		n = a.size();
		tr.resize(n << 2);

		function<void(int, int, int)> build = [&](int i, int l, int r) -> void {
			tr[i].l = l, tr[i].r = r;
			if(l == r) {
				tr[i].sum = tr[i].mn = tr[i].mx = a[l];
				return;
			}
			int mid = l + (r - l >> 1);
			build(i << 1, l, mid);
			build(i << 1 | 1, mid + 1, r);
			push_up(i);
		};
		build(1, 0, n - 1);
	}

	void push_up(int i) {
		tr[i].sum = tr[i << 1].sum + tr[i << 1 | 1].sum;
		tr[i].mx = max(tr[i << 1].mx, tr[i << 1 | 1].mx);
		tr[i].mn = min(tr[i << 1].mn, tr[i << 1 | 1].mn);
	}
	void push_down(int i) {
		if(tr[i].lazy != 0) {
			int l = tr[i].l, r = tr[i].r;
			int mid = l + (r - l >> 1);

			tr[i << 1].sum += tr[i].lazy * (mid - tr[i << 1].l + 1);
			tr[i << 1].lazy += tr[i].lazy;

			tr[i << 1 | 1].sum += tr[i].lazy * (tr[i << 1 | 1].r - mid);
			tr[i << 1 | 1].lazy += tr[i].lazy;

			tr[i].lazy = 0;
		}
	}

	void update1(int i, int ind, T val) {
		int l = tr[i].l, r = tr[i].r;
		if(l == r) {
			tr[i].sum += val;
			return;
		}
		int mid = l + (r - l >> 1);
		if(ind <= mid) update1(i << 1, ind, val);
		else update1(i << 1 | 1, ind, val);
		push_up(i);
	}
	void update2(int i, int ul, int ur, T val) {
		int l = tr[i].l, r = tr[i].r;

		if(r < ul || l > ur) return;
		if(ul <= l && r <= ur) {
			// 打懒标记，无需再往后更新
			tr[i].sum += val * (r - l + 1);
			tr[i].lazy += val;
			return;
		}

		push_down(i);
		int mid = l + (r - l >> 1);
		update2(i << 1, ul, ur, val);
		update2(i << 1 | 1, ul, ur, val);
		push_up(i);
	}

	T query1(int i, int ql, int qr) {
		int l = tr[i].l, r = tr[i].r;

		if(r < ql || l > qr) return inf;
		if(ql <= l && r <= qr) return tr[i].mn;

		push_down(i);
		return min(query1(i << 1, ql, qr), query1(i << 1 | 1, ql, qr));
	}

	T query2(int i, int ql, int qr) {
		int l = tr[i].l, r = tr[i].r;

		if(r < ql || l > qr) return -inf;
		if(ql <= l && r <= qr) return tr[i].mx;

		push_down(i);
		return max(query2(i << 1, ql, qr), query2(i << 1 | 1, ql, qr));
	}

	void update1(int ind, T val) {
		update1(1, ind, val);
	}
	void update2(int ul, int ur, T val) {
		update2(1, ul, ur, val);
	}
	T query1(int ql, int qr) {
		return query1(1, ql, qr);
	}
	T query2(int ql, int qr) {
		return query2(1, ql, qr);
	}
};

signed main() {
    IOS;

    int n, k;
    cin >> n >> k;
    vector<int> arr(n);
    fer(i, 0, n) cin >> arr[i];

    segmentTree seg(arr);
    vector<int> mn, mx;
    fer(i, 0, n - k + 1) {
    	int l = i, r = i + k - 1;
    	mx.push_back(seg.query2(l, r));
    	mn.push_back(seg.query1(l, r));
    }

    for(auto x : mn) cout << x << ' ';
    cout << '\n';
	for(auto x : mx) cout << x << ' ';

    return 0;
}