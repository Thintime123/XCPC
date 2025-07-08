## [题目链接](https://www.acwing.com/activity/content/punch_the_clock/3988/)

## 5833. 热҈热҈热҈

### 题意

如果一天的温度大于等于 35 就可以获得免费的雪碧，但是星期四活动取消，求在连续 $n$ 天中有多少天你可以喝到免费的雪碧，又有多少天是因为星期四而导致你喝不到雪碧。

### 思路

模拟题，注意如何用取余处理对日期的循环。

### 示例代码

```cpp
signed main() {
    IOS;

    int n, s;
    cin >> n >> s;
    vector<int> arr(n);
    fer(i, 0, n) cin >> arr[i];

    int ans = 0, cnt = 0;

    int t = s - 1;
    fer(i, 0, n) {
    	if(arr[i] >= 35) {
    		if(t == 3) cnt++;
    		else ans++;
    	}
    	t = (t + 1) % 7;
    }
    cout << ans << ' ' << cnt;
    return 0;
}
```


## 5834. 谁进线下了？

### 题意

比赛共进行 N 场游戏，在每场游戏中，每支队伍在游戏中会获得一个排名和一个杀敌数,一支队伍在一场游戏的得分为杀敌数+排名分，计算每支队伍的总得分。

### 思路

模拟题。

### 示例代码

```cpp
signed main() {
    IOS;

    int n;
    cin >> n;
    map<int, int> mp;
    mp[1] = 12, mp[2] = 9, mp[3] = 7, mp[4] = 5, mp[5] = 4;
    mp[6] = mp[7] = 3, mp[8] = mp[9] = mp[10] = 2;
    fer(i, 11, 16) mp[i] = 1;
    fer(i, 16, 21) mp[i] = 0;

    vector<int> arr(20);

    while(n--) {
    	fer(i, 0, 20) {
    		int p, k;
    		cin >> p >> k;
    		arr[i] += mp[p] + k;
    	}
    }

    fer(i, 0, 20) {
    	cout << i + 1 << ' ' << arr[i] << '\n';
    }

    return 0;
}
```


## 5835. 暖炉与水豚

### 题意

题目较长，请自行阅读。

### 思路

读明白题意，就是一道模拟题，冰冷的水豚周围一定没有暖炉，根据这个进行判断状态不确定的水豚周围是否有可能有暖炉。

### 示例代码

```cpp
signed main() {
    IOS;

    int n, m;
    cin >> n >> m;
    string board[n];
    vector<pii> M;

	auto OnRange = [&](int x, int y) -> bool {
		return x >= 0 && x < n && y >= 0 && y < m;
	};
	auto check = [&](int i, int j) -> bool {
		fer(r, i - 1, i + 2) {
			fer(c, j - 1, j + 2) {
				if(OnRange(r, c) && board[r][c] == 'm') return true;
			}
		}
		return false;
	};

    vector<vector<bool>> vis(n, vector<bool>(m, true));

    fer(i, 0, n) {
    	cin >> board[i];
    	fer(j, 0, m) {
			if(board[i][j] == 'c') {
				fer(r, i - 1, i + 2) {
					fer(c, j - 1, j + 2) {
						if(OnRange(r, c)) vis[r][c] = false;
					}
				}
			}
		}
    }


    fer(i, 0, n) {
    	fer(j, 0, m) {
			if(board[i][j] == 'w') {
				if(check(i, j) == false) {
					fer(r, i - 1, i + 2) {
						fer(c, j - 1, j + 2) {
							if(OnRange(r, c) && vis[r][c] && board[r][c] == '.') M.emplace_back(r + 1, c + 1);
						}
					}
					if(M.empty()) {
						cout << "Too cold!";
					} else {
						for(auto [r, c] : M) cout << r << ' ' << c << '\n';
					}
					return 0;
				}
			}
    	}
    }
    cout << "Too cold!";
    return 0;
}
```


## 5836. 章鱼图的判断

### 题意

- 给出章鱼图的定义：在无向图的一个连通分量中，如果有且只有一个环，那么这个连通分量就是一个章鱼图。
- 给定一个无向图，判断是不是只有一个章鱼图存在。（不存在自环）
- 是，则输出章鱼图的环中的顶点数;否，则输出有多少个章鱼图。

### 思路

这是本场比赛最难的一题，解法多样，下面给出我喜欢的一种解法。我们来拆分一下问题：
- 在给出的图中，需要在每一个连通分量中寻找是否存在章鱼图
- 对应具体的连通分量时，我们需要判断的是是否有且只有一个环的存在：没有环 -> 跳过到下一个连通分量；有环 -> 有几个环？（多个环？-> 记录环的个数即可。 一个环？ -> 是一个章鱼图 -> 如何计算环内顶点数？)
- 如何判断是否有环呢？显然是拓扑排序了，当然，你也可以通过计算环的个数进行判断
- 如何计算有多少个环？ -> 环数 = 边数 + 1 - 顶点数
- 最终只有一个环 -> 满足所有条件，如何计算环内顶点数？这又是拓扑排序了，通过拓扑排序记录我们消除了多少个度为1的顶点，最终剩下的就是环内顶点数。
- 细节的你应该注意到，上面提到的在每个连通分量中计算环数的公式中，边数和顶点数我们也需要维护，如何维护呢？考虑到一个连通分量可以看作是一个集合，我们维护一个连通分量就是维护对应的集合，所以就是并查集了，在每次`merge`的时候维护集合的边数和顶点数。

### 示例代码

```cpp
class DSU {
private:
	int n;
	vector<int> parent, rank;
public:	
	vector<int> E, sz; // 每个集合的边数和点数

public:
	// 节点编号从 0 开始
	DSU(int n) : n(n), parent(n), rank(n, 0) {
		iota(all(parent), 0);
		E.resize(n);
		sz.resize(n, 1);
	}

	int find(int x) {
		if(x != parent[x]) {
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}

	void merge(int x, int y) {
		int rootx = find(x), rooty = find(y);
		if(rootx == rooty) {
			E[rootx]++;
			return;
		}

		if(rank[rootx] < rank[rooty]) {
			parent[rootx] = rooty;
			E[rooty] += E[rootx] + 1;
			sz[rooty] += sz[rootx];
		} else if(rank[rootx] > rank[rooty]) {
			parent[rooty] = rootx;
			E[rootx] += E[rooty] + 1;
			sz[rootx] += sz[rooty];
		} else {
			parent[rooty] = rootx;
			rank[rootx]++;
			E[rootx] += E[rooty] + 1;
			sz[rootx] += sz[rooty];
		}
	}

	bool same(int x, int y) {
		return find(x) == find(y);
	}
};

void solve() {
    int n, m;
    cin >> n >> m;

    DSU dsu(n);
    vector<vector<int>> g(n);
    vector<int> d(n);

    fer(i, 0, m) {
    	int u, v;
    	cin >> u >> v;
    	u--, v--;
    	dsu.merge(u, v);
    	g[u].push_back(v);
    	g[v].push_back(u);
    	d[u]++, d[v]++;
    }

    vector<int> st(n);
    int cnt = 0; // 章鱼图个数
    vector<int> V; // 每个章鱼图的根
    fer(i, 0, n) {
    	int x = dsu.find(i);
    	if(!st[x]) {
    		st[x] = true;
    		int c = dsu.E[x] + 1 - dsu.sz[x];
    		if(c == 1) {
				cnt++;
				V.push_back(x);
    		}
    	}
    }

    if(cnt != 1) {
    	cout << "No " << cnt << '\n';
    } else {
    	queue<int> q;
    	fer(i, 0, n) {
    		if(dsu.find(i) == V[0] && d[i] == 1) {
    			q.push(i);
    		}
    	}
    	int ans = 0;
    	while(!q.empty()) {
    		int u = q.front(); q.pop();
    		ans++;
    		for(auto v : g[u]) {
    			d[v]--;
    			if(d[v] == 1) q.push(v);
    		}
    	}
    	cout << "Yes " << dsu.sz[V[0]] - ans << '\n';
    }
}
```


### 5837. 工作安排

### 题意

给定一个 $n$ 个工作，每个工作都有完成所需要的时间、截止时间和完成后的报酬，同一时间最多只能执行一项工作，求最大报酬。

### 思路

很明显的背包问题，并且是01背包。
- 状态定义： $dp[j]$ 表示时间在j前已经选择了要做事情的总价值（不包括此时是否正在选择工作）
- 初始化： 初始化均为0
- 遍历方式：先枚举每项工作，然后从大到小枚举当前时间j，j的范围是怎样的呢？最小值当然是考虑到的当前的工作完成所需要的时间，最大值就是对应的截止时间了，如果你没能明白请再好好看看 $dp$ 数组的定义。
- 状态转移：考虑每项工作选/不选，实际上与01背包完全相同。`dp[j] = max(dp[j], dp[j - arr[i][0]] + arr[i][2])`

到这里其实还不能正确解决这个问题，我们似乎忽略了一个问题：不同工作选择的先后顺序对状态转移的正确性有影响吗？似乎在01背包中并没有这样的问题啊？
当然有影响了，因为状态转移的正确性依赖于“先处理截止时间较早的工作”，所以必须按截止时间从小到大排序。
1. **DP 状态保证可行性**  
    我们的 $dp[j]$ 表示在 j 时间内能获得的最大报酬。当用一个工作更新 dp 状态时，该工作必须在其截止时间之前开始。若按截止时间升序处理，保证了在更新 dp 时，之前计算的转移状态一定是满足其各自工作截止时间要求的。如果顺序乱了，就可能用到违反先后顺序的状态，得到一个不满足任务截止要求的调度，从而 WA。
    
2. **防止非法调度**  
    如果不按截止时间从小到大排序，可能先处理一个截止时间较晚的工作，更新了 dp 状态，而后又处理截止较早的工作时，看似更新时用到这些状态，但实际上这些状态可能来自不合法的工作安排，使得调度结果不满足各项工作的截止约束。

到这里还有一个重要的问题需要理解：为什么本题不能直接输出 `dp[W]`？01背包不就是这样吗？原因如下：
dp 数组中的每个状态 $dp[t]$ 表示恰好用 t 个单位时间完成任务所得到的最大报酬，并不是“不超过 t 时间”能获得的最大报酬。所以，如果在某个时刻 t₀ 收获了最大报酬，而 t₀ 后面没有任务被安排以扩展这个报酬，那么 $dp[t]$ （对于 t > t₀）不会自动继承 t₀ 的状态。例如：

假设 t₀ = 5 时，你的 $dp[5] = 100$，但如果没有任务满足“从时间 5 开始继续安排而又能合法完成”（比如任务要求必须在更早的截止时间开始），那么在 $dp[6]$、$dp[7]$ 等状态中，就不会使用 $dp[5]$ 的 100，因为转移是从 $dp[j - task_time]$ 处更新，而不在状态间自动传递最大值。

而在 01 背包问题中，我们通常要求“不超过容量”的最优解，所以最终答案可以直接取 $dp[capacity]$ 或者在遍历时传递上一个状态。而这里每个状态是独立的“完成时刻”，因此最终答案必须在整个 dp 数组中取最大值，以确保找到某个时刻完成任务的方案获得的最大报酬。

总之一句话，就是 $dp$ 数组状态定义不同，状态是否是独立“完成”。

### 示例代码

```cpp
void solve() {
    int n;
    cin >> n;
    vector<array<int, 3>> arr(n + 1);

    int W = -inf;
    fer(i, 1, n + 1) {
    	cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    	W = max(W, arr[i][1]);
    }

    sort(all(arr), [](array<int, 3> a, array<int, 3> b) {
    	return a[1] < b[1];
    });
    // 时间在j前已经选择了要做事情的总价值，左闭右开的区间
    // 选/不选
    // 选：最晚在截止时间arr[i][1]之前arr[i][0]开始做
    vector<int> dp(W + 10);
    fer(i, 1, n + 1) {
    	ferd(j, arr[i][1], arr[i][0]) {
    		dp[j] = max(dp[j], dp[j - arr[i][0]] + arr[i][2]);
    	}
    }
    cout << *max_element(all(dp)) << '\n';
    //cout << dp[W] << '\n';
}
```