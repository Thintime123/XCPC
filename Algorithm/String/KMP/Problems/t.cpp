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

signed main() {
    IOS;

    int n, m;
    cin >> n >> m;
    vector<int> arr(n);
    fer(i, 0, n) cin >> arr[i];

    int l = 0, r = 4e5 + 10;
    int ans = 0;
    while(l <= r) {
    	int mid = l + (r - l >> 1);

    	auto check = [&]() -> bool {
    		int ans = 0;
    		fer(i, 0, n) {
    			if(arr[i] > mid) ans += arr[i] - mid;
    			if(ans >= m) return true;
    		}
    		return false;
    	};

    	if(check()) {
    		l = mid + 1;
    		ans = max(ans, mid);
    	} else {
    		r = mid - 1;
    	}
    }
    // cout << ans << '\n';
    cout << l - 1 << '\n';

    return 0;
}