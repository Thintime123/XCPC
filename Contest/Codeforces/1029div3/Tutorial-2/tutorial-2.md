## C

### Target

将一个数组分为尽可能多的子数组（有序），使得后一个子数组包含前一个所有元素

### Thinking

1. 记录所有数的个数，便于记录终止项
2. 记录当前子数组还需满足的条件（已经有的和还需满足的）
3. 可以用`unordered_set`提速




### Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define fer(i, m, n) for (ll i = m; i < n; i++)
using namespace std;

void solve() {
    int n; 
    cin >> n;
    vector<int> a(n);
    for (int &x : a) 
        cin >> x;

    vector<int> freq(n + 1, 0); 
    for (int x : a) 
        ++freq[x];

    unordered_set<int> req, cur, emts;
    int result = 0;

    fer(i, 0, n) {
        int v = a[i];
        
        --freq[v];             
        cur.insert(v);     

        if (freq[v] == 0) 
            emts.insert(v); 

        if (req.erase(v)) ;   

        
        if (i != n - 1 && req.empty() && emts.empty()) {
            ++result;             
            req.swap(cur); 
            cur.clear();        
            emts.clear(); 
        }
    }
    
    ++result; 
    cout << result << '\n';
}

int main() {
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

## D

### Target

判断一个数组(大小为`n`)是否可以由若干`1,2,...,n` 和 `n,...,2,1`相加而得

### Thinking

1. 显然它们必然是 **等差数列**

2. $$
   a_i = l \cdot i + k \cdot (n - i + 1) \quad \text{对所有 } i = 1..n
   $$

3. $$
   a_i = (l - k) \cdot i + k \cdot (n + 1)
   $$

4. $$
   a_1 = d + k(n + 1) \Rightarrow k = \frac{a_1 - d}{n + 1}
   $$

5. 相应条件满足即可

### Code

```c++
#include <bits/stdc++.h>
#define ll long long
#define fer(i, m, n) for (ll i = m; i < n; i++)
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    
    ll d = a[1] - a[0];
    for (int i = 2; i < n; i++) {
        if (a[i] - a[i-1] != d) {
            cout << "NO\n";
            return;
        }
    }

    
    ll c = a[0] - d;
    ll m = n + 1;
    if (c < 0 || c % m != 0) {
        cout << "NO\n";
        return;
    }
    ll l = c / m;        
    ll k = d + l;        

    
    if (k >= 0 && l >= 0) cout << "YES\n";
    else                 cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
```

## E

### Target

- 我们有两个长度为n的数组a和b
- 在开始操作前，我们可以选择最多一个位置i，删除a[i]和b[i]
- 之后可以进行任意次数的操作：选择位置i，将a[i]设为b[i+1]或将b[i]设为a[i+1]
- 目标是最大化最终两个数组相同位置的元素数量

### Thinking
- 如果我们不删除任何位置，那么最终两个数组必须完全相同
- 如果我们删除一个位置，那么最终两个数组除了这个位置外必须完全相同
- 操作的本质是让相邻位置的元素可以互相交换
- 这里使用贪心的思想，从后向前遍历数组
- 对于每个位置，检查是否可以通过操作使当前位置的元素相同
- 如果发现无法使当前位置相同，则记录这个位置作为可能的删除位置
- 最终答案是所有可能删除位置中能获得的最大匹配数
### Code

```c++
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fer(i,m,n) for (ll i = m;i < n;i++)
// #define fer
const ll ILL=2167167167167167167ll;
const int INF=2100000000;

void solve(){
    int N;
    cin >> N;
    vector<int> A(N), B(N);
    fer(i, 0, N) cin >> A[i];
    fer(i, 0, N) cin >> B[i];
    fer(i, 0, N) if (i & 1) swap(A[i], B[i]);
    vector<int> seenA(N + 1), seenB(N + 1);
    for (int i = N - 1; i >= 0; i--){
        fer(rp, 0, 2){
            swap(A, B);
            swap(seenA, seenB);
            seenA[A[i]]++;
            if (seenB[A[i]]){
                cout << i + 1 << "\n";
                return;
            }
            if (seenA[A[i]] > 2 || (seenA[A[i]] == 2 && A[i] != A[i + 1])){
                cout << i + 1 << "\n";
                return;
            }
        }
    }
    cout << "0\n";
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
 
    int t = 1;
    cin >> t;
    while(t--)
        solve();
}
```

