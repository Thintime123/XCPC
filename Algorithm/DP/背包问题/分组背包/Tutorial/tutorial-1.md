## 问题描述

分组背包问题是一种每组只能选一个物品的背包问题。它是01背包和完全背包的延伸。
- 给定 $N$ 种物品，每组有若干个物品
- 每组最多选 1 个物品（可以不选）
- 每个物品有对应的重量和价值
- 背包容量为 $V$ ，需要最大化总价值

比如有 $N$ 组物品，第i组有`k_i`个物品。每个物品有体积`group[i].first`和价值`group[i].second`。

目标：选若干物品，**每组至多选一个**，总体积 $≤V$ ，总价值最大。

## 状态定义

- $dp[j]$ 表示容量为 $j$ 的背包能装下的最大价值。

## 遍历方式

- 先遍历组数
- 再逆序遍历背包容量，这就满足了每组物品最多选一个，类似于01背包
- 最后遍历每组的每个物品

**注意**
- 一定是按照上面所说的遍历方式和遍历顺序，不可以将后面两个遍历调换，否则会导致在一组中选择了多个物品！

## 状态转移方程

- `if(j >= group[i].first) dp[j] = max(dp[j], dp[j - group[i].first] + group[i].second)`

## 模板

- v: 物品体积
- w: 物品价值

```cpp
struct Item { int v, w; };
int main() {
    int m, V;
    cin >> m >> V;
    vector<vector<Item>> group(m);
    for (int i = 0; i < m; i++) {
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int v, w; cin >> v >> w;
            group[i].push_back({v, w});
        }
    }
    vector<int> f(V + 1, 0);
    for (int i = 0; i < m; i++) {
        for (int j = V; j >= 0; j--) {
            for (auto &item : group[i]) {
                if (j >= item.v)
                    f[j] = max(f[j], f[j - item.v] + item.w);
            }
        }
    }
    cout << f[V] << endl;
}
```

## 变式

- 每组必须选一个：初始化`dp[j] = -inf`，`dp[0] = 0`，这样必须每组都参与转移。
- 限定了总件数：给 $dp$ 数组加维数，$dp[j][k]$ 表示容量为 $j$，选了 $k$ 件物品的最大价值。
- 每组限定选的件数（比如，一些组限定只能且必须选 $x_i$ 件，又或是一些组限定不能超过选 $x_i$ 件）：解决方法和上一种情况类似，给 $dp$ 数组加维数