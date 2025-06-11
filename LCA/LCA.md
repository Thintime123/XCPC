下面我从零基础开始，带你一步步理解并实现常用的 **二进制 LCA（二分提升法）**。整个流程可以分为以下几个部分：

---

## 1. 什么是 LCA？

- **定义**：在一棵以某个节点（通常是 1）为根的树中，给定两个节点 u, v，它们的 **最近公共祖先（Lowest Common Ancestor, LCA）** 是同时是 u 和 v 的祖先中，距离它们最近的那个节点。

---

## 2. 为什么要用二分提升？

- **暴力做法**：每次查询 u, v 时，挨个往上跑，一个节点一个节点地向上找，会导致最坏 O(N) 时间，N≈树高。多次查询时太慢。
    
- **二分提升思想**：先预处理，让每个节点都记录“2^k 级祖先”（k=0,1,2…），这样查询时可以一次性“跳”大步向上，时间 O(log N)。
    

---

## 3. 算法流程

1. **建树并跑一遍 DFS（或 BFS）**
    
    - 记录每个节点的深度 `depth[x]`
        
    - 记录每个节点的直接父节点 `fa[0][x]`
        
2. **预处理 $fa[k][i]$**
    
    - 对所有 k 从 1 到 $⌊log₂N⌋$，对所有节点 i：
        
        ```
        fa[k][i] = fa[k-1][ fa[k-1][i] ]
        ```
        
    - 含义：$fa[k][i]$ 是 i 的 2^k 级祖先。
        
3. **查询 LCA(u,v)**
    
    - **第一步**：让 u, v 深度对齐。若 $depth[u]$ > $depth[v]$，就把 u 往上跳 `depth[u]-depth[v]` 层；反之同理。
        
    - **第二步**：如果 u == v，直接返回；否则从大 k 开始往下尝试，让 u 和 v 同时朝它们的 2^k 级祖先跳，如果跳完后两者依然不相同，就继续往下 k-1 跳……
        
    - 最后跳不到更高才结束，此时 `fa[0][u]` 就是答案。
        

---

## 4. 复杂度

- **预处理**：DFS O(N)，构造 fa 表 O(N log N)。
    
- **单次查询**：对齐深度 O(log N) + 搜索祖先 O(log N)，合计 O(log N)。
    

---

## 5. 代码示例（C++）

```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;           // 根据题目调整
const int LOGN = 17;               // 2^17 ≈ 131072 > MAXN

vector<int> tree[MAXN+1];
int fa[LOGN+1][MAXN+1];            // fa[k][i] = 2^k 级祖先 of i
int depth[MAXN+1];
int N;                              // 节点数

// 1) DFS 计算 depth 和 fa[0][]
void dfs(int u, int parent) {
    fa[0][u] = parent;
    depth[u] = (parent == 0 ? 0 : depth[parent] + 1);
    for (int v : tree[u]) {
        if (v == parent) continue;
        dfs(v, u);
    }
}

// 2) 预处理 fa 表
void init_lca() {
    // 假设根节点为 1
    dfs(1, 0);
    for (int k = 1; k <= LOGN; k++) {
        for (int i = 1; i <= N; i++) {
            int mid = fa[k-1][i];
            fa[k][i] = mid ? fa[k-1][mid] : 0;
        }
    }
}

// 3) LCA 查询
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    // 先让 u 提升到和 v 同一深度
    int diff = depth[u] - depth[v];
    for (int k = 0; k <= LOGN; k++) {
        if (diff & (1 << k)) {
            u = fa[k][u];
        }
    }
    if (u == v) return u;
    // 从最高位开始，同时提升
    for (int k = LOGN; k >= 0; k--) {
        if (fa[k][u] != 0 && fa[k][u] != fa[k][v]) {
            u = fa[k][u];
            v = fa[k][v];
        }
    }
    // 此时 u, v 已在 LCA 的两个不同子树，父节点即 LCA
    return fa[0][u];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    init_lca();

    int Q;
    cin >> Q;
    while (Q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
    return 0;
}
```

- **使用说明**
    
    1. 输入 N（节点数），接着 N−1 条边。
        
    2. 调用 `init_lca()` 做预处理。
        
    3. 对每次查询 (u,v) 调用 `lca(u,v)` 即可得到答案。
        

---

## 6. 小结与练习

1. **理解核心**：二分提升就是“预先记住 2^k 级祖先”，查询时就能按二进制位跳跃。
    
2. **练习建议**：
    
    - 手写一棵小树，模拟 `depth[]` 和 `fa[][]` 填表过程。
        
    - 实现并在 Codeforces、洛谷等平台上带 LCA 的树上题（如“树的直径”、“两点距离”）。
        
3. **拓展**：
    
    - 了解「$Euler Tour + RMQ」$方法，可实现 O(1) 查询，但预处理更复杂。
        

祝你早日掌握 LCA ，在 ACM 赛场上拿下更多分数！有任何疑问随时交流。