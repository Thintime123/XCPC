#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000;           // 根据题目调整
const int LOGN = 20;               // 2^17 ≈ 131072 > MAXN

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
void init_lca(int s) {
    // 假设根节点为 1
    dfs(s, 0);
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

    int Q, s;
    cin >> N >> Q >> s;
    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    init_lca(s);

    while (Q--) {
        int u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
    return 0;
}