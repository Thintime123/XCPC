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
#define dbg_arr(a, i) cerr << #a << '[' << #i << "]=" << a[i] << " ###\n";

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
const int N = 1e5 + 2;
const int inf = 1e9;

signed main() {
    IOS;

    int n, h;
    cin >> n >> h;
    vector<int> p(n + 1), c(n + 1);
    fer(i, 1, n + 1) cin >> p[i] >> c[i];

    vector<int> dp(N);
    int ans = inf;

    fer(i, 1, n + 1) {
    	fer(j, c[i], N) {
    		dp[j] = max(dp[j], dp[j - c[i]] + p[i]);
    		if(dp[j] >= h) {
    			ans = min(ans, j);
  				break;
    		}
    	}
    }
    cout << ans << '\n';
    return 0;
}