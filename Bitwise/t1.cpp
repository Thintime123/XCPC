#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define ull unsigned long long
//#define int ll
#define pii pair<int, int>
#define all(x) x.begin(),x.end()
#define fer(i, m, n) for(int i = m; i < n; ++i)
#define ferd(i, m, n) for(int i = m; i >= n; --i)
#define dbg(x) cout << #x << ' ' << '=' << ' ' << x << '\n'

const int MOD = 1e9 + 7;
const int N = 2e5 + 2;
const int inf = 1e9;

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    auto lowbit = [](int x) {
    	return -x & x;
    };
    int x = 26;
    cout << "获取最右边的1: " << lowbit(x) << '\n';

    auto getNum = [](int x) {
    	int cnt = 0;
    	while(x) {
    		x -= x & -x;
    		cnt++;
    	}
    	return cnt;
    };
    cout << "1的个数: " << getNum(x) << '\n';

    auto ok = [](int x) -> bool {
    	if(x <= 0) return false;
    	return (x & x - 1) == 0;
    };
    cout << ok(x) << ' ' << ok(16) << '\n';
    auto sub = [](int x) -> int {
    	return x & x - 1;
    };

    cout << sub(26) << '\n';
    return 0;
}