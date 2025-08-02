#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<string> g(n, string(m, '0'));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) cin >> g[i][j];

    vector<int> dist(n * m, INF);
    queue<pair<int,int>> q;
    auto id = [&](int r,int c){ return r * m + c; };
    const int dr[4] = {-1,1,0,0};
    const int dc[4] = {0,0,-1,1};

    for (int r=0;r<n;++r)
        for (int c=0;c<m;++c)
            if (g[r][c]=='1'){
                dist[id(r,c)] = 0;
                q.emplace(r,c);
            }
    // 多源 BFS
    while(!q.empty()){
        auto [r,c] = q.front(); q.pop();
        int d = dist[id(r,c)] + 1;
        for(int k=0;k<4;++k){
            int nr=r+dr[k], nc=c+dc[k];
            if(nr<0||nr>=n||nc<0||nc>=m) continue;
            int idx=id(nr,nc);
            if(dist[idx]>d){
                dist[idx]=d;
                q.emplace(nr,nc);
            }
        }
    }

    // 边界情况：若原本全黑
    int allBlack = 1;
    for(char ch: g[0]){} // just to keep clang happy
    for(char ch: g[0]){}
    for(int v: dist) if (v) { allBlack = 0; break; }
    if (allBlack){
        cout << 0 << '\n';
        return 0;
    }

    // 若原来没有黑格，直接算最小半径
    bool hasBlack = false;
    for(int v: dist) if (v==0){ hasBlack=true; break; }
    if(!hasBlack){
        int best = (n-1+1)/2 + (m-1+1)/2;              // ceil((n-1)/2)+ceil((m-1)/2)
        cout << best << '\n';
        return 0;
    }

    auto check = [&](int T)->bool{
        long long plow = -4e9, phigh = 4e9;
        long long qlow = -4e9, qhigh = 4e9;
        bool need = false;
        for(int r=0;r<n;++r){
            for(int c=0;c<m;++c){
                int d = dist[id(r,c)];
                if(d > T){
                    need = true;
                    long long p = r + c;
                    long long qv = r - c;
                    plow  = max(plow , p - T);
                    phigh = min(phigh, p + T);
                    qlow  = max(qlow , qv - T);
                    qhigh = min(qhigh, qv + T);
                }
            }
        }
        if(!need) return true;                 // 不用新增
        if(plow > phigh || qlow > qhigh) return false;  // 无交集

        // 再扫一遍找符合交集的白格
        for(int r=0;r<n;++r){
            for(int c=0;c<m;++c){
                if(g[r][c]=='0'){
                    long long p = r + c;
                    long long qv = r - c;
                    if(plow<=p && p<=phigh && qlow<=qv && qv<=qhigh)
                        return true;
                }
            }
        }
        return false;
    };

    int lo = 0, hi = n + m;         // hi 足够大
    while(lo < hi){
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << '\n';
    return 0;
}
