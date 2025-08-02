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
#define lowbit(x)  ((x) & -(x))

#ifdef LOCAL
	#include<macro.hpp>
#else
	#define dbg(x) (void)0
	#define dbg_arr(a, i) (void)0
#endif

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
const int inf = 2e9;

struct basis {
	static const int LOG = 63;
	vector<ll> b;
	bool zero;

	basis() {
		b.resize(LOG + 1);
		zero = false;
	}

	void insert(ll x) {
		ferd(i, LOG, 0) {
			if(x >> i & 1) {
				if(!b[i]) {
					b[i] = x;
					break;
				}
				x ^= b[i];
			}
		}
		zero = true;
	}

	ll query_max(ll x = 0) {
		ferd(i, LOG, 0) {
			if((x ^ b[i]) > x) x ^= b[i];
		}
		return x;
	}

	ll query_min() {
		fer(i, 0, LOG + 1) {
			if(b[i]) return b[i];
		}
		return 0;
	}

	bool check(ll x) {
		ferd(i, LOG, 0) {
			if(x >> i & 1) {
				if(!b[i]) return false;
				x ^= b[i];
			}
		}
		return true;
	}

	int len;
	vector<ll> B;
	void gauss(vector<ll> &a) {
		len = 1;
		zero = false;
		B.assign(all(a));
		int n = a.size();

		ferd(i, LOG, 0) {
			fer(j, len, n + 1) {
				if(B[j] & (1LL << i)) {
					swap(j, len);
					break;
				}
			}
			if(B[len] & (1LL << i)) {
				fer(j, 1, n + 1) {
					if(j != len && B[j] & (1LL << i)) {
						B[j] ^= B[len];
					}
				}
				len++;
			}
		}
		len--;
		zero = len != n;
	}
};

signed main() {
    IOS;

    basis b;

    return 0;
}