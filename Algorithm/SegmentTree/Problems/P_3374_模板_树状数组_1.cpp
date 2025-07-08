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
const int N = 5e5 + 10;
const int inf = 1e9;

int arr[N];
int tree[N << 2];

void build(int node_ind, int l, int r) {
    if(l == r) {
        tree[node_ind] = arr[l];
    } else {
        int mid = l + (r - l >> 1);
        build(node_ind << 1, l, mid);
        build(node_ind << 1 | 1, mid + 1, r);
        tree[node_ind] = tree[node_ind << 1] + tree[node_ind << 1 | 1];
    }
}

void update_point(int node_ind, int l, int r, int ind, int val) {
    if(l == r) {
        tree[node_ind] += val;
    } else {
        int mid = l + (r - l >> 1);
        if(ind <= mid) {
            update_point(node_ind << 1, l, mid, ind, val);
        } else {
            update_point(node_ind << 1 | 1, mid + 1, r, ind, val);
        }
        tree[node_ind] = tree[node_ind << 1] + tree[node_ind << 1 | 1];
    }
}

int query(int node_ind, int l, int r, int ql, int qr) {
    if(ql > r || qr < l) return 0;
    if(ql <= l && r <= qr) return tree[node_ind];
    
    int mid = l + (r - l >> 1);
    int p1 = query(node_ind << 1, l, mid, ql, qr);
    int p2 = query(node_ind << 1 | 1, mid + 1, r, ql, qr);
    return p1 + p2;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    fer(i, 0, n) cin >> arr[i];

    build(1, 0, n - 1);
    while(q--) {
        int op, x, y;
        cin >> op >> x >> y;
        if(op == 1) {
            update_point(1, 0, n - 1, x - 1, y);
        } else {
            cout << query(1, 0, n - 1, x - 1, y - 1) << '\n';
        }
    }
    return 0;
}