在图论中，**图的直径（diameter**定义为图中所有顶点对之间最短路径长度的最大值。也就是说，如果对任意两点 u,v 计算它们之间的最短路距离 d(u,v)，那么直径就是

$diameter=max⁡u,v∈Vd(u,v).$

---

## 1. 无向树（Tree）上的直径：两次 BFS/DFS

对树（无环连通图），可以用**BFS**或**DFS**在线性时间 O(N) 内求得：

1. **任意选一点** s，从 s 做一次 BFS，找到距离最远的点 u；
    
2. 从 u 再做一次 BFS，找到距离最远的点 v，则 d(u,v)d(u,v) 就是这棵树的直径。
    

```cpp
#include <bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;

int n;
vector<vector<int>> adj;

// 从 start 做 BFS，返回距离最远节点及其距离
pii bfs(int start) {
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int farNode = start, farDist = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > farDist) {
                    farDist = dist[v];
                    farNode = v;
                }
            }
        }
    }
    return {farNode, farDist};
}

int treeDiameter() {
    // 第一次 BFS：任意从 0 开始
    auto p1 = bfs(0);
    // 第二次 BFS：从上次最远节点出发
    auto p2 = bfs(p1.first);
    return p2.second;  // 直径长度
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    adj.assign(n, {});
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        // 假设输入 0~n-1 编号
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << treeDiameter() << "\n";
    return 0;
}
```

---

## 2. 一般无权图（Unweighted Graph）

若图不是树、可能有环或不连通：

1. 对每个连通分量各自用上述两次 BFS 算直径，取最大值；
    
2. 或者**对每个顶点** u 做一次 BFS，记录所有 d(u,v)，然后全局取最大——时间 O(V (V+E))。
    

---

## 3. 带权图（Weighted Graph）

- **稠密图**：可用 **Floyd–Warshall**，时间 $O(V^3)$。
    
- **稀疏图**：对每个节点运行 **Dijkstra**，时间 $O(V\,(E\log V))$。
    
- 如果只是树上带权，改用两次 **DFS + 记录最大距离**。
    

---

## 4. 大图/近似直径

对于超大规模图（例如社交网络），完全遍历开销太大，可用以下启发式

- **多起点 BFS/选点采样**：随机选几百个点做 BFS，记录当前最大值；
    
- **球跳法（landmark-based）**：预选若干“地标”点，对它们做全图最短路，估算所有点对间距。
    

---

### 小结

- **定义**：最大最短路径长度。
    
- **树**：两次 BFS/DFS，即 O(N)。
    
- **无权图**：每点 BFS，O(V (V+E))。
    
- **带权图**：Floyd 或多次 Dijkstra。
    

以上方法在 C++ 中都能高效实现，按照题目规模选取最合适的方案即可。