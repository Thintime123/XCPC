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
const int N = 2e5 + 2;
const int inf = 1e9;

ll arr[N];
ll tree[N << 2];
ll lazy[N << 2];

void build(int node_ind, int l, int r) {
    lazy[node_ind] = 0;

    if(l == r) {
        tree[node_ind] = arr[l];
    } else {
        int mid = l + (r - l >> 1);
        build(node_ind << 1, l, mid);
        build(node_ind << 1 | 1, mid + 1, r);
        tree[node_ind] = tree[node_ind << 1] + tree[node_ind << 1 | 1];
    }
}

void push_down(int node_ind, int l, int r) {
    if(lazy[node_ind] && l != r) {
        int mid = l + (r - l >> 1);
        tree[node_ind << 1] += lazy[node_ind] * (mid - l + 1);
        lazy[node_ind << 1] += lazy[node_ind];
        tree[node_ind << 1 | 1] += lazy[node_ind] * (r - mid);
        lazy[node_ind << 1 | 1] += lazy[node_ind];

        lazy[node_ind] = 0;
    }
}

void update_range(int node_ind, int l, int r, int upl, int upr, int val) {
    push_down(node_ind, l ,r);

    if(upr < l || upl > r) return;
    if(upl <= l && r <= upr) {
        tree[node_ind] += val * (r - l + 1);
        lazy[node_ind] += val;
    } else {
        int mid = l + (r - l >> 1);
        update_range(node_ind << 1, l, mid, upl, upr, val);
        update_range(node_ind << 1 | 1, mid + 1, r, upl, upr, val);
        tree[node_ind] = tree[node_ind << 1] + tree[node_ind << 1 | 1];
    }
}

ll query(int node_ind, int l, int r, int ql, int qr) {
    push_down(node_ind, l, r);

    if(qr < l || r < ql) return 0;
    if(ql <= l && r <= qr) return tree[node_ind];

    int mid = l + (r - l >> 1);
    ll p1 = query(node_ind << 1, l, mid, ql, qr);
    ll p2 = query(node_ind << 1 | 1, mid + 1, r, ql, qr);
    return p1 + p2;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    fer(i, 0, n) cin >> arr[i];

    build(1, 0, n - 1);
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            ll x, y, k;
            cin >> x >> y >> k;
            update_range(1, 0, n - 1, x - 1, y - 1, k);
        } else if(op == 2) {
            int x, y;
            cin >> x >> y;
            cout << query(1, 0, n - 1, x - 1, y - 1) << '\n';
        }
    }
    return 0;
}