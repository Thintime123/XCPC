## 问题类别

二维坐标点集合压缩问题

## 具体思路

1. 对上下左右最边界的点分别剔除来
2. 对剩下的点进行最大矩形寻找操作



## 细节注意

1. `return x * y if x * y > len(arr) else x * y + min(x, y)`



## AC 代码

```c++
// C++
#include <bits/stdc++.h>
#define ll long long
#define int long long
#define fer(i, m, n) for (ll i = m; i < n; i++)
using namespace std;

ll check(const vector<pair<int, int>>& arr) {
    int mxx = 0, mxy = 0;
    int mnx = 1e9, mny = 1e9;
    for (auto [a, b] : arr) {
        mxx = max(mxx, a);
        mxy = max(mxy, b);
        mnx = min(mnx, a);
        mny = min(mny, b);
    }
    int x = mxy - mny + 1;
    int y = mxx - mnx + 1;
    if (x * y > arr.size()) return x * y;
    else return x * y + min(x, y);
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> arr(n);
    fer(i, 0, n) {
        int a, b;
        cin >> a >> b;
        arr[i] = {a, b};
    }
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    ll ans = LLONG_MAX;
    sort(arr.begin(), arr.end());
    ans = min(ans, check(vector<pair<int, int>>(arr.begin() + 1, arr.end())));
    ans = min(ans, check(vector<pair<int, int>>(arr.begin(), arr.end() - 1)));
    sort(arr.begin(), arr.end(), [](const pair<int, int>& x, const pair<int, int>& y) {
        if (x.second == y.second) return x.first < y.first;
        return x.second < y.second;
    });
    ans = min(ans, check(vector<pair<int, int>>(arr.begin() + 1, arr.end())));
    ans = min(ans, check(vector<pair<int, int>>(arr.begin(), arr.end() - 1)));
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
```

```python
def check(arr):
    mxx=mxy=0
    mnx=mny=int(1e9)
    for a,b in arr:
        mxx=max(mxx,a)
        mxy=max(mxy,b)
        mnx=min(mnx,a)
        mny=min(mny,b)
    x=(mxy-mny+1)
    y=(mxx-mnx+1)
    return x*y if x*y>len(arr) else x*y+min(x,y)

for _ in range(int(input())):
    n=int(input())
    arr=[[*map(int,input().split())] for i in range(n)]
    if n==1:
        print(1)
        continue
    ans=float("inf")
    arr.sort()
    ans=min(ans,check(arr[1:]),check(arr[:-1]))
    arr.sort(key=lambda x:(x[1],x[0]))
    ans=min(ans,check(arr[1:]),check(arr[:-1]))
    print(ans)
```

