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

    int n, p;
    cin >> n >> p;
    vector<int> a(n + 1);
    fer(i, 1, n + 1) {
    	cin >> a[i];
    }
    vector<int> diff(n + 2);
    while(p--) {
    	int l, r, d;
    	cin >> l >> r >> d;
    	diff[l] += d, diff[r + 1] -= d;
    }
    int ans = inf;
    fer(i, 1, n + 1) {
    	diff[i] += diff[i - 1];
    	a[i] += diff[i];
    	ans = min(ans, a[i]);
    }
    cout << ans << '\n';
    
    return 0;
}