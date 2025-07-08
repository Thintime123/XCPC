## [题目连接](https://ac.nowcoder.com/acm/contest/111309)

## **好字符串**

### 题意

判断是否为好字符串，如果相同字母的大小写同时出现或者同时不出现就是好字符串

### 思路

用`set`或者`map`模拟即可

### 示例代码

```cpp
signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    set<char> st;
    for(char c : s) st.insert(c);

    for(char c : s) {
        if(c >= 'a' && !st.count(c - 'a' + 'A')) {
            cout << "NO" << '\n';
            return 0;
        } else if(c >= 'A' && c <= 'Z' && !st.count(c - 'A' + 'a')) {
            cout << "NO" << '\n';
            return 0;
        }
    }
    cout << "YES" << '\n';
    return 0;
}
```

## **平均数**

### 题意

一组数组中每个元素都是$[-1, 0, 1]$其中一个，表示与平均值的相对大小，判断数组是否合法

### 思路

记录$-1$和$1$的个数，如果有且只有一个为$0$就一定不合法，否则合法

### 示例代码

```cpp
signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    int cnt1 = 0, cnt2 = 0;
    fer(i, 0, n) {
        int x;
        cin >> x;
        if(x == -1) cnt1++;
        else if(x == 1) cnt2++;
    }
    if(cnt1 == 0 && cnt2 == 0) {
        cout << "YES" << '\n';
    } else if(cnt1 == 0 || cnt2 == 0) {
        cout << "NO" << '\n';
    } else {
        cout << "YES" << '\n';
    }
    return 0;
}
```

### **质数**

### 题意

有$q$次查询，每次给出$[l, r]$区间数组，要求分为两组$S1, S2$，并且要满足$gcd(S1) = 1, gcd(S2) != 1$，不可能满足就输出$-1$，否则满足就输出$|S1 - S2|$

### 思路

记$cnt = r - l + 1$表示数组长度，如果$cnt = 2$需要特殊讨论($l = 1$和$l != 1$)，否则的话，贪心，将所有奇数放在一个数组，全部偶数放在另一个数组

### 示例代码

```cpp
signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int q;
    cin >> q;
    while(q--) {
        ll l, r;
        cin >> l >> r;
        ll cnt = r - l + 1;
        if(cnt <= 2) {
            if(l == 1) cout << 0 << '\n';
            else cout << -1 << '\n';
            continue;
        }

        if(cnt & 1) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
    return 0;
}
```

## 众数

### 题意

给出一个数组，只能进行一次操作：选两个元素，将其中一个减一，另一个加一。求所有可能出现的众数。

### 思路

1. 考虑到$n$的范围是$2 <= n <= 1e3$，所以可以在考虑$O(N^2logN)$复杂度内计算，那么$O(N^2)$很明显就是让一个指针表示将对应的数$-1$，另一个指针表示将对应的数$+1$。这个$log$就是`set`的`earse`了。
2. 所以我们就用前后指针，分别操作两个数，然后就是操作后要更新结果（每个数对应的出现次数），然后`set`本身就是有序的，所以可以在$O(1)$内查找到每一步得到的众数

### 示例代码

```cpp
signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);

    set<pii> st;
    map<int, int> mp;
    fer(i, 0, n) {
        cin >> arr[i];
        mp[arr[i]]++;
    }
    for(auto& [x, cnt] : mp) {
        st.insert({cnt, x});
    }

    set<int> res;

    fer(i, 0, n) {
        auto sub = [&](int x) -> void {
            int cnt = mp[x];
            st.erase({cnt, x});
            st.insert({cnt - 1, x});
            mp[x]--;
        };
        auto add = [&](int x) -> void {
            int cnt = mp[x];
            st.erase({cnt, x});
            st.insert({cnt + 1, x});
            mp[x]++;
        };

        sub(arr[i]), add(arr[i] - 1);
        fer(j, 0, n) {
            if(i == j) continue;
            
            sub(arr[j]), add(arr[j] + 1);
            res.insert(st.rbegin()->second);
            add(arr[j]), sub(arr[j] + 1);
        }
        add(arr[i]), sub(arr[i] - 1);
    }

    for(auto x : res) cout << x << ' ';
    return 0;
}
```

### 种类数

### 题意

给定数组，可以进行任意次操作，将每个元素减去数组中元素的种类（就是有多少个不同的数），如果减去后小于零则变为零，求使得数组种类为$1$时的最少操作轮数。

### 思路

我们用`set`来存储数据（直接去重），然后遍历`set`，记录每次需要更新的轮数和`sum`标记，难点就是需要清晰的思路进行模拟

### 示例代码

```cpp
signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> arr(n);
    set<ll> st;

    bool has_zero = false;
    fer(i, 0, n) {
        cin >> arr[i];
        st.insert(arr[i]);
        if(arr[i] == 0) has_zero = true;
    }
    int x = st.size();

    if(x == 1) {
        cout << 0 << '\n';
        return 0;
    }

    ll t = *upper_bound(all(st), 0LL);
    ll cnt = (t + x - 1) / x;
    ll res = 0, sum = cnt * x;

    int ignore = 0;
    bool f = false;
    for(auto it =  st.begin(); it != st.end(); ++it) {
        if(*it <= sum) ignore++;
        else {
            if(!f) {
                x -= ignore - 1;
                f = true;
            } else {
                x -= ignore;
            }
            
            res += cnt;
            cnt = (*it - sum + x - 1) / x;
            sum += cnt * x;
            
            ignore = 1;
        }
    }
    cout << res + cnt << '\n';

    return 0;
}
```